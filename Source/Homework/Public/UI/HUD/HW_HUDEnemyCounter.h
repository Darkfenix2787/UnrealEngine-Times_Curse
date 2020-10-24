// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HW_HUDEnemyCounter.generated.h"

class UHW_GameInstance;

UCLASS()
class HOMEWORK_API UHW_HUDEnemyCounter : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		int EnemiesDefeated;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		UHW_GameInstance* GameInstanceReference;

public:

	UFUNCTION(BlueprintCallable)
		void InitializeWidget();

	UFUNCTION()
		void UpdateCounter(int EnemyDefeatedComponent);
	
};
