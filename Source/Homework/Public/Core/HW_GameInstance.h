// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HW_GameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyKilledSignature, int, EnemiesDefeated);

UCLASS()
class HOMEWORK_API UHW_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UHW_GameInstance();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Save System")
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "Enemy Data")
		int EnemiesDefeatedCounter;

	UPROPERTY(VisibleAnywhere, Category = "Enemy Data")
		TArray<AActor*> CurrentsEnemies;

public:

	UPROPERTY(BlueprintAssignable)
		FOnEnemyKilledSignature OnEnemyKilledDelegate;

public:
	UFUNCTION(BlueprintCallable)
		int GetEnemiesDefeatedCounter() { return EnemiesDefeatedCounter; };

	UFUNCTION(BlueprintCallable)
		void SetEnemiesDefeatedCounter(int NewValue) { EnemiesDefeatedCounter = NewValue; };

	UFUNCTION(BlueprintCallable)
		void AddEnemyDefeatedToCounter();

	UFUNCTION(BlueprintCallable)
		void SaveData();

	UFUNCTION(BlueprintCallable)
		void LoadData();

	UFUNCTION(BlueprintCallable)
		void ResetData();

protected:

	UFUNCTION(BlueprintImplementableEvent)
		void BP_AddEnemyDefeatedToCounter();

	UFUNCTION(BlueprintImplementableEvent)
		void BP_SaveData();

	UFUNCTION(BlueprintImplementableEvent)
		void BP_LoadData();

	UFUNCTION(BlueprintImplementableEvent)
		void BP_ResetData();

	
};
