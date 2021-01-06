// Fill out your copyright notice in the Description page of Project Settings.


#include "HW_LaunchPad.h"
#include "HW_Character.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHW_LaunchPad::AHW_LaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaunchColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchColliderComponent"));
	RootComponent = LaunchColliderComponent;
	LaunchColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LaunchColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	LaunchColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	LaunchColliderComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	LaunchColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);	

	LaunchMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchPadMeshComponent"));
	LaunchMeshComponent->SetupAttachment(RootComponent);
	LaunchMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AHW_LaunchPad::BeginPlay()
{
	Super::BeginPlay();	
}

void AHW_LaunchPad::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor)) {
		AHW_Character* OverlappedCharacter = Cast<AHW_Character>(OtherActor);
		if (IsValid(OverlappedCharacter))
		{
			LaunchPad(OverlappedCharacter);
		}			
	}
}

void AHW_LaunchPad::LaunchPad(AHW_Character* LaunchCharacter)
{
	BP_LaunchPad(LaunchCharacter);
}