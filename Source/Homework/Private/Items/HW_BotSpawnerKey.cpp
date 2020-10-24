// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HW_BotSpawnerKey.h"
#include "HW_Character.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy/HW_Bot.h"
#include "Enemy/HW_BotSpawner.h"

AHW_BotSpawnerKey::AHW_BotSpawnerKey()
{
	BotSpawnerKeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealthBoxMeshComponent"));
	BotSpawnerKeyMeshComponent->SetupAttachment(RootComponent);
	BotSpawnerKeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AHW_BotSpawnerKey::Pickup(AHW_Character* PickupCharacter)
{
	Super::Pickup(PickupCharacter);
	AHW_Bot* BotOwner = Cast<AHW_Bot>(MyBot);
	AHW_BotSpawner* SpawnerOwner = Cast<AHW_BotSpawner>(BotOwner->MySpawner);
	if(IsValid(SpawnerOwner))
		SpawnerOwner->SetSpawnerStatus(false);
	Destroy();
}
