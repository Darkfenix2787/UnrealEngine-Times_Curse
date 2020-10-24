// Fill out your copyright notice in the Description page of Project Settings.


#include "HW_VictoryZone.h"
#include "Components/BoxComponent.h"
#include "HW_Character.h"
#include "Core/HW_GameMode.h"

// Sets default values
AHW_VictoryZone::AHW_VictoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VictoryZoneComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("VictoryZoneComponent"));
	RootComponent = VictoryZoneComponent;
	VictoryZoneComponent->SetBoxExtent(FVector(100.0f));
}



// Called when the game starts or when spawned
void AHW_VictoryZone::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<AHW_GameMode>(GetWorld()->GetAuthGameMode());
	
}

// Called every frame
void AHW_VictoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHW_VictoryZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (IsValid(OtherActor) && IsValid(GameModeReference))
	{
		AHW_Character* HW_Character = Cast<AHW_Character>(OtherActor);
		if (IsValid(HW_Character) && (HW_Character->GetCharacterType() == EHW_CharacteraType::CharacteraType_Player) )
		{
			GameModeReference->Victory(HW_Character);
		}
	}
}

