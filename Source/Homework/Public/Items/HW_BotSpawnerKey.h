// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/HW_Item.h"
#include "HW_BotSpawnerKey.generated.h"

class AHW_Bot;

/**
 * 
 */
UCLASS()
class HOMEWORK_API AHW_BotSpawnerKey : public AHW_Item
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* BotSpawnerKeyMeshComponent;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
		AHW_Bot* MyBot;

public:
	// Sets default values for this actor's properties
	AHW_BotSpawnerKey();

	void SetMyBot(AHW_Bot* NewBot) { MyBot = NewBot; };

protected:

	virtual void Pickup(AHW_Character* PickupCharacter) override;

	
};
