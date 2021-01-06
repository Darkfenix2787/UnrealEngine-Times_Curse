// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HW_Pad.h"
#include "HW_Character.h"
#include "Components/BoxComponent.h"
#include "components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Weapon/HW_PadLauncher.h"

// Sets default values
AHW_Pad::AHW_Pad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollision"));
	RootComponent = ProjectileCollision;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(ProjectileCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComponent->InitialSpeed = 300.0f;
	ProjectileMovementComponent->MaxSpeed = 300.0f;
}

// Called when the game starts or when spawned
void AHW_Pad::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AHW_Pad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHW_Pad::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor)) {
		AHW_Character* OverlappedCharacter = Cast<AHW_Character>(OtherActor);
		if (IsValid(OverlappedCharacter))
		{
			Launch(OverlappedCharacter);
		}
	}
}

void AHW_Pad::SetOwner(AActor* NewOwner)
{
	PadOwner = Cast<AHW_PadLauncher>(NewOwner);
}

void AHW_Pad::Launch(AHW_Character* LaunchCharacter)
{
	BP_Launch(LaunchCharacter);	

	if (IsValid(PadOwner))
	{
		PadOwner->DecreaseNumPads();
	}
}

