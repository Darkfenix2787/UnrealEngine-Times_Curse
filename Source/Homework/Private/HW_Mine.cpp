// Fill out your copyright notice in the Description page of Project Settings.


#include "HW_Mine.h"
#include "Homework/Homework.h"
#include "Components/SphereComponent.h"
#include "HW_Character.h"
#include "Weapon/HW_Rifle.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AHW_Mine::AHW_Mine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MineLocation = FVector(100, 250, 0);
	DilationModifier = 0.30f;
	MineDamage = 50.0f;	

	MineComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MineComponent"));
	RootComponent = MineComponent;
	MineComponent->SetSphereRadius(25.5f);	
	MineComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MineComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MineComponent->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	MineComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);

	MineAlertAreaComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MineAlertAreaComponent"));	
	MineAlertAreaComponent->SetSphereRadius(500.0f);
	MineAlertAreaComponent->SetRelativeLocation(MineLocation);
	MineAlertAreaComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MineAlertAreaComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MineAlertAreaComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);
	MineAlertAreaComponent->SetupAttachment(MineComponent);

	MineMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMeshComponent"));
	MineMeshComponent->SetupAttachment(RootComponent);	

	AlertMineMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AlertMineMeshComponent"));
	AlertMineMeshComponent->SetupAttachment(MineAlertAreaComponent);

}

// Called when the game starts or when spawned
void AHW_Mine::BeginPlay()
{
	Super::BeginPlay();	

	MineAlertAreaComponent->OnComponentBeginOverlap.AddDynamic(this, &AHW_Mine::MineAlertBegin);
	MineAlertAreaComponent->OnComponentEndOverlap.AddDynamic(this, &AHW_Mine::MineAlertEnd);
	MineComponent->OnComponentBeginOverlap.AddDynamic(this, &AHW_Mine::MineExplosion);	
}

void AHW_Mine::MineAlertBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		AHW_Character* HW_Character = Cast<AHW_Character>(OtherActor);

		if (IsValid(HW_Character) && HW_Character->GetCharacterType() == EHW_CharacteraType::CharacteraType_Player)
		{
			HW_Character->ModifyDilation(-DilationModifier);
		}

	}
}

void AHW_Mine::MineAlertEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor))
	{
		AHW_Character* HW_Character = Cast<AHW_Character>(OtherActor);

		if (IsValid(HW_Character))
		{
			bool bIsPlayer = HW_Character->GetCharacterType() == EHW_CharacteraType::CharacteraType_Player;
			USphereComponent *OComponent = Cast<USphereComponent>(OverlappedComponent);

			if (IsValid(OComponent) && bIsPlayer)
			{
				HW_Character->ModifyDilation(DilationModifier);
			}			
		}
	}
}

void AHW_Mine::MineExplosion(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		AHW_Character* HW_Character = Cast<AHW_Character>(OtherActor);		

		if (IsValid(HW_Character))
		{
			bool bIsPlayer = HW_Character->GetCharacterType() == EHW_CharacteraType::CharacteraType_Player;
			if (IsValid(ExplosionEffect) && bIsPlayer)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, this->GetTransform(), true);
				UGameplayStatics::ApplyDamage(OtherActor, MineDamage, GetInstigatorController(), this, nullptr);
				Destroy();
			}			
		}

	}
}


