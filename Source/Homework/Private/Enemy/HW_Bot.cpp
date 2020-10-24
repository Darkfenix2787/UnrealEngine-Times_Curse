// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HW_Bot.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HW_Character.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "DrawDebugHelpers.h"
#include "Components/HW_HealthComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Enemy/HW_Enemy.h"
#include "Enemy/HW_BotSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Items/HW_BotSpawnerKey.h"
#include "Core/HW_GameInstance.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Items/HW_Item.h"


// Sets default values
AHW_Bot::AHW_Bot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BotMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BotMeshComponent"));	
	BotMeshComponent->SetCanEverAffectNavigation(false);
	BotMeshComponent->SetSimulatePhysics(true);
	RootComponent = BotMeshComponent;

	healthComponent = CreateDefaultSubobject<UHW_HealthComponent>(TEXT("HealthComponent"));

	SelfDestructionDetectorComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SelfDestructionDetector"));
	SelfDestructionDetectorComponent->SetupAttachment(RootComponent);
	SelfDestructionDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SelfDestructionDetectorComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SelfDestructionDetectorComponent->SetSphereRadius(150.0f);

	TimerSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("TimerSoundComponent"));
	TimerSoundComponent->SetupAttachment(RootComponent);

	MinDistanceToTarget = 100.0f;
	ForceMagnitude = 500.0f;
	ExplosionDamage = 100.0f;
	ExplosionRadius = 100.0f;
	LootProbability = 25.0f;
}

// Called when the game starts or when spawned
void AHW_Bot::BeginPlay()
{
	Super::BeginPlay();	

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHW_Enemy::StaticClass(), Enemies);	

	if(IsValid(PlayerPawn))
		PlayerCharacter = Cast<AHW_Character>(PlayerPawn);

	GameInstanceReference = Cast<UHW_GameInstance>(GetWorld()->GetGameInstance());
	healthComponent->OnHealthChangeDelegate.AddDynamic(this, &AHW_Bot::TakingDamage);
	SelfDestructionDetectorComponent->OnComponentBeginOverlap.AddDynamic(this, &AHW_Bot::StartCountDown);
	BotMaterial = BotMeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, BotMeshComponent->GetMaterial(0)); 
	NextPathPoint = GetNextPathPoint();
	
}

FVector AHW_Bot::GetNextPathPoint()
{
	AActor* ActorToFollow = PlayerCharacter;
	
	for (AActor* Enemy : Enemies)
	{
		if (!GetWorld()->ContainsActor(Enemy))
			continue;		

			EnemyToHealth = Cast<AHW_Enemy>(Enemy);
		if (IsValid(EnemyToHealth) && EnemyToHealth->GetHealth() < EnemyToHealth->GetMaxHealth())
		{
			ActorToFollow = EnemyToHealth;			
			break;
		}				
	}	

	if (ActorToFollow == nullptr)
	{
		ActorToFollow = this;
	}
	
	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(), GetActorLocation(), ActorToFollow);
	if (NavigationPath->PathPoints.Num() > 1)
	{
		return NavigationPath->PathPoints[1];
	}

	// If navigation points are less or equal than 1
	return GetActorLocation();
}

void AHW_Bot::TakingDamage(UHW_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsValid(BotMaterial))	
		BotMaterial->SetScalarParameterValue("Pulse", GetWorld()->TimeSeconds);

	if (CurrentHealthComponent->IsDead())
	{
		SelfDestruction();
	}
		
}

void AHW_Bot::SelfDestruction()
{
	if (bIsExploded)
		return;

	bIsExploded = true;

	if(IsValid(ExplosionEffect))
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplosionDamage, GetActorLocation(), ExplosionRadius, nullptr, IgnoredActors, this, GetInstigatorController(), true);

	if (bDebug)
		DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 20.0f, FColor::Red, true, 5.0f, 0, 2);


	if (IsValid(MySpawner))
		MySpawner->NotifyBotDead();

	SpawnKey();

	PlayExplosionSound();

	Destroy();
}

void AHW_Bot::StartCountDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == EnemyToHealth && EnemyToHealth->GetHealth() != EnemyToHealth->GetMaxHealth())
	{		
		EnemyToHealth->Healing();
		if (IsValid(HealingEffect))
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HealingEffect, GetActorLocation());
	}

	if (bIsStartingCountDown)
		return;

	if (OtherActor == PlayerCharacter)
	{		
		bIsStartingCountDown = true;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_SelfDamage, this, &AHW_Bot::SelfDamage, 0.5f, true);
	}
}

void AHW_Bot::SelfDamage()
{
	PlayTimerSound();
	UGameplayStatics::ApplyDamage(this, 20.0f, GetInstigatorController(), nullptr, nullptr);
}

void AHW_Bot::SpawnKey()
{
	if (IsValid(LootItemKeyClass))
	{
		float SelectedProbability = FMath::RandRange(0.0f, 100.0f);
		if (SelectedProbability <= LootProbability)
		{	
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AHW_BotSpawnerKey* NewBotSpawnerKey = Cast<AHW_BotSpawnerKey>(GetWorld()->SpawnActor<AHW_Item>(LootItemKeyClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParameters));
			if(IsValid(NewBotSpawnerKey))
				NewBotSpawnerKey->SetMyBot(this);
		}
	}
}

void AHW_Bot::PlayTimerSound()
{
	TimerSoundComponent->Play();
}

void AHW_Bot::PlayExplosionSound()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
}

// Called every frame
void AHW_Bot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceToTarget = (GetActorLocation() - NextPathPoint).Size();

	if (DistanceToTarget <= MinDistanceToTarget)
	{
		NextPathPoint = GetNextPathPoint();
	}
	else
	{
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= ForceMagnitude;
		BotMeshComponent->AddForce(ForceDirection, NAME_None, true);
	}

	if(bDebug)
		DrawDebugSphere(GetWorld(), NextPathPoint, 30.0f, 15.0f, FColor::Purple, false, 0.0f, 0, 1);

}

