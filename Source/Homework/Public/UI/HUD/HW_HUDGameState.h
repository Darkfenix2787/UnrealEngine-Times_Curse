// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HW_HUDGameState.generated.h"

class AHW_GameMode;

UCLASS()
class HOMEWORK_API UHW_HUDGameState : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		AHW_GameMode* GameModeReference;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		FName GameStateName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		FName VictoryName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		FName GameOverName;

public:

	UFUNCTION(BlueprintCallable)
		void InitializeWidget();

	UFUNCTION()
		void OnVictory();

	UFUNCTION()
		void OnGameOver();

	
};
