// Fill out your copyright notice in the Description page of Project Settings.


#include "HW_DoorKey.h"
#include "Components/StaticMeshComponent.h"
#include "HW_Character.h"
#include "Core/HW_GameMode.h"

AHW_DoorKey::AHW_DoorKey()
{
	KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	KeyMeshComponent->SetupAttachment(RootComponent);
	KeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	XPValue = 40.0f;
	KeyTag = "KeyA";
}

void AHW_DoorKey::Pickup(AHW_Character* PickupCharacter)
{
	Super::Pickup(PickupCharacter);


	if (IsValid(PickupCharacter) && PickupCharacter->GetCharacterType() == EHW_CharacteraType::CharacteraType_Player)
	{
		if (IsValid(GameModeReference))
		{
			GameModeReference->AddKeyToCharacter(PickupCharacter, KeyTag);
		}
	}
		
	PickupCharacter->GainUltimateXP(XPValue);	
	Destroy();
	GameModeReference->Victory(PickupCharacter);
}
