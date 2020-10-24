// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HW_HealthBox.h"
#include "HW_Character.h"
#include "Components/StaticMeshComponent.h"

AHW_HealthBox::AHW_HealthBox()
{
	HealthBoxMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealthBoxMeshComponent"));
	HealthBoxMeshComponent->SetupAttachment(RootComponent);
	HealthBoxMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthValue = 15.0f;
}

void AHW_HealthBox::Pickup(AHW_Character* PickupCharacter)
{
	Super::Pickup(PickupCharacter);
	bool bSuccesFullHeal = PickupCharacter->TryAddHealth(HealthValue);
	if(bSuccesFullHeal)
		Destroy();	
}
