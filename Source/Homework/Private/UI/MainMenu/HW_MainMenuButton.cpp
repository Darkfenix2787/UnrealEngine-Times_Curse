// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/HW_MainMenuButton.h"


UHW_MainMenuButton::UHW_MainMenuButton()
{
	CheckFocusRate = 0.1f;
}

void UHW_MainMenuButton::Start()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_CheckFocus, this, &UHW_MainMenuButton::CheckFocus, CheckFocusRate, true);
}

void UHW_MainMenuButton::CheckFocus()
{
	if (IsHovered())
	{
		//this button is affected by mouse
		SetKeyboardFocus();
		SetButtonStyle(EHW_ButtonStyleType::ButtonStyleType_Mouse);
	}
	else
	{
		//check if the keyboard/gamepad is on me!
		EHW_ButtonStyleType StyleTypeSelected = HasKeyboardFocus() ? EHW_ButtonStyleType::ButtonStyleType_KeySelected : EHW_ButtonStyleType::ButtonStyleType_KeyNotSelected;
		SetButtonStyle(StyleTypeSelected);
	}
}

void UHW_MainMenuButton::SetButtonStyle(EHW_ButtonStyleType NewStyleType)
{
	BP_SetButtonStyle(NewStyleType);
}