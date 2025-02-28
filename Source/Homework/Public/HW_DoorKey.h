// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/HW_Item.h"
#include "HW_DoorKey.generated.h"

class UStaticMeshComponent;


/**
 * 
 */
UCLASS()
class HOMEWORK_API AHW_DoorKey : public AHW_Item
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* KeyMeshComponent;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
		float XPValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
		FName KeyTag;

public:
	// Sets default values for this actor's properties
	AHW_DoorKey();

public:

	UFUNCTION(BlueprintCallable, Category = "Getter")
	FName GetKeyTag() const {
		return KeyTag;
	};

protected:

	virtual void Pickup(AHW_Character* PickupCharacter) override;

};
