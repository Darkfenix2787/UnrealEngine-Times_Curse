// Fill out your copyright notice in the Description page of Project Settings.


#include "HW_Barrel.h"
#include "Homework/Homework.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HW_Character.h"
#include "TimerManager.h"


// Sets default values
AHW_Barrel::AHW_Barrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsExploded = false;
	bIsInArea = false;
	FreezeSeconds = 5.0f;
	BaseSeconds = 0.0f;	

	BarrelComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BarrelComponent"));
	RootComponent = BarrelComponent;	
	BarrelComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BarrelComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BarrelComponent->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	BarrelComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);

	ExplosionAreaComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionAreaComponent"));
	ExplosionAreaComponent->SetSphereRadius(500.0f);	
	ExplosionAreaComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ExplosionAreaComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ExplosionAreaComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);
	ExplosionAreaComponent->SetupAttachment(BarrelComponent);
	
	BarrelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMeshComponent"));
	BarrelMeshComponent->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void AHW_Barrel::BeginPlay()
{
	Super::BeginPlay();
	
	ExplosionAreaComponent->OnComponentBeginOverlap.AddDynamic(this, &AHW_Barrel::ExplosionAreaBeginOverlap);
	ExplosionAreaComponent->OnComponentEndOverlap.AddDynamic(this, &AHW_Barrel::ExplosionAreaEndOverlap);	
}

void AHW_Barrel::ExplosionAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		HW_Character = Cast<AHW_Character>(OtherActor);

		if (IsValid(HW_Character))
		{
			bIsInArea = true;
		}
	}
	
}

void AHW_Barrel::ExplosionAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor))
	{
		HW_Character = Cast<AHW_Character>(OtherActor);

		if (IsValid(HW_Character))
		{
			bIsInArea = false;
		}
	}
}



void AHW_Barrel::ExplosionAction()
{
	if (Cast<AHW_Character>(HW_Character))
	{
		BaseSeconds = GetWorld()->GetTimeSeconds();
		bIsExploded = true;
	}
	else
	{
		Destroy();
	}

}



// Called every frame
void AHW_Barrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	if (bIsExploded)
	{		
		if (Cast<AHW_Character>(HW_Character))
		{			
			if (bIsInArea) 
			{
				if ((FreezeSeconds >= SecondCounter))
				{
					HW_Character->StopMoveCharacter(0, false);
					SetActorHiddenInGame(true);					
					SecondCounter = FMath::RoundFromZero(GetWorld()->GetTimeSeconds() - BaseSeconds);					
				}
				else
				{
					HW_Character->StopMoveCharacter(1, true);
					bIsInArea = false;
				}
			}
			else
			{	
				bIsExploded = false;
				Destroy();								
			}
		}			
	}		
}

