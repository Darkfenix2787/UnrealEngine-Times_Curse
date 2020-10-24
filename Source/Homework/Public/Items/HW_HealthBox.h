// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/HW_Item.h"
#include "HW_HealthBox.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK_API AHW_HealthBox : public AHW_Item
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* HealthBoxMeshComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health Box")
		float HealthValue;	

public:
	// Sets default values for this actor's properties
	AHW_HealthBox();

public:

	UFUNCTION(BlueprintCallable, Category = "Getter")
		float GetHealthValue() const {
		return HealthValue;
	};

protected:

	virtual void Pickup(AHW_Character* PickupCharacter) override;

};
