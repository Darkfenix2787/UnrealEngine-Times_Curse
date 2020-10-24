// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HW_EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK_API UHW_EnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "SetUp")
		float HealthPercent;	

public:

	UFUNCTION()
		void UpdateHealth(float CurrentHealth, float MaxHealth);

};
