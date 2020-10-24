// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HW_HUDUltimate.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK_API UHW_HUDUltimate : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "SetUp")
		float UltimatePercent;

	UPROPERTY(BlueprintReadOnly, Category = "SetUp")
		FLinearColor UltimateColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SetUp")
		FLinearColor UltimateEnableColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SetUp")
		FLinearColor UltimateDisableColor;


public:

	UFUNCTION(BlueprintCallable)
		void InitializeWidget();

	UFUNCTION()
		void UpdateUltimateValue(float CurrentUltimateXP, float MaxUltimateXP);

	UFUNCTION()
		void UpdateUltimateStatus(bool bIsAvailable);

	
};
