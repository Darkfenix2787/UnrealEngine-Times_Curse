// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HW_HUDObjetive.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK_API UHW_HUDObjetive : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		bool bIsCompleted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		FName ObjetiveName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		FLinearColor CurrentColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		FLinearColor CompletedColor;

public:

	void ObjetiveCompleted();
	
};
