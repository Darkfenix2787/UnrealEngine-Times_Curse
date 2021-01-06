// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HW_MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK_API UHW_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main Menu")
		FName GamePlayLevelName;

protected:

	UFUNCTION(BlueprintCallable, Category = "Main Menu")
		void NewGame();

	UFUNCTION(BlueprintCallable, Category = "Main Menu")
		void ContinueGame();

	UFUNCTION(BlueprintCallable, Category = "Main Menu")
		void QuitGame();

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Main Menu")
		void BP_NewGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "Main Menu")
		void BP_ContinueGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "Main Menu")
		void BP_QuitGame();	
};