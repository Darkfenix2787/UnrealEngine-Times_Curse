// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Enemy/HW_Enemy.h"
#include "HW_SaveGame.generated.h"


/**
 * 
 */
UCLASS()
class HOMEWORK_API UHW_SaveGame : public USaveGame
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "Data")
		int EnemiesDefeatedCounter;

	UPROPERTY(VisibleDefaultsOnly, Category = "Data")
		TArray<AActor*> Enemies;

public:

	UFUNCTION(BlueprintCallable)
		void SetEnemiesDefeatedCounterInfo (int NewValue) { EnemiesDefeatedCounter = NewValue; };

	UFUNCTION(BlueprintCallable)
		int GetEnemiesDefeatedCounterInfo() { return EnemiesDefeatedCounter; };


	UFUNCTION(BlueprintCallable)
		void SetEnemiesInfo(TArray<AActor*> NewValue) { Enemies = NewValue; };

	UFUNCTION(BlueprintCallable)
		TArray<AActor*> GetEnemiesInfo() { return Enemies; };
	
};
