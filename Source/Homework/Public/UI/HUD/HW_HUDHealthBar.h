// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HW_HUDHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK_API UHW_HUDHealthBar : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "SetUp")
		float HealthPercent;

	UPROPERTY(BlueprintReadOnly, Category = "SetUp")
		FLinearColor HealthColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SetUp")
		FLinearColor FullHealthColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SetUp")
		FLinearColor EmptyHealthColor;

public:

	UFUNCTION(BlueprintCallable)
		void InitializeWidget();

	UFUNCTION()
		void UpdateHealth(float CurrentHealth, float MaxHealth);
	
};
