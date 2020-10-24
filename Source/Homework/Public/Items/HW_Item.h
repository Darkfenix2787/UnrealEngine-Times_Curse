// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HW_Item.generated.h"

class USphereComponent;
class AHW_Character;
class AHW_GameMode;

UCLASS()
class HOMEWORK_API AHW_Item : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* MainColliderComponent;

protected:

	UPROPERTY(BlueprintReadOnly)
		AHW_GameMode* GameModeReference;
	
public:	
	// Sets default values for this actor's properties
	AHW_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Pickup(AHW_Character* PickupCharacter);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
		void BP_PickUp(AHW_Character* PickupCharacter);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
