// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "HW_MainMenuButton.generated.h"

UENUM(Blueprintable)
enum class EHW_ButtonStyleType : uint8
{
	ButtonStyleType_Mouse			UMETA(DisplayName = "Selected By Mouse"),
	ButtonStyleType_KeySelected		UMETA(DisplayName = "Selected By Keyboard"),
	ButtonStyleType_KeyNotSelected	UMETA(DisplayName = "Not Selected By Keyboard"),
};

UCLASS()
class HOMEWORK_API UHW_MainMenuButton : public UButton
{
	GENERATED_BODY()
	
public:

	UHW_MainMenuButton();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main Menu Button")
		float CheckFocusRate;

	FTimerHandle TimerHandle_CheckFocus;

protected:

	UFUNCTION(BlueprintCallable, Category = "Main Menu Button")
	void Start();

	void CheckFocus();

	void SetButtonStyle(EHW_ButtonStyleType NewStyleType);

	UFUNCTION(BlueprintImplementableEvent, Category = "Main Menu Button")
		void BP_SetButtonStyle(EHW_ButtonStyleType NewStyleType);
};
