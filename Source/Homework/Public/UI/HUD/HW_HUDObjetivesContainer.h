// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HW_HUDObjetivesContainer.generated.h"

class AHW_GameMode;
class UHW_HUDObjetive;

UCLASS()
class HOMEWORK_API UHW_HUDObjetivesContainer : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "SetUp")
		AHW_GameMode* GameModeReference;

	UPROPERTY(BlueprintReadOnly, Category = "SetUp")
		TArray<UHW_HUDObjetive*> Objetives;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION(BlueprintCallable)
	void InitializeObjetives(TArray<UHW_HUDObjetive*> NewObjetives);

	UFUNCTION()
	void UpdateObjetives(FName KeyTag);	
};
