// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HW_HUDUltimate.h"
#include "HW_Character.h" 
#include "Kismet/GameplayStatics.h"

void UHW_HUDUltimate::InitializeWidget()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		AHW_Character* PlayerCharacter = Cast<AHW_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->OnUltimateUpdateDelegate.AddDynamic(this, &UHW_HUDUltimate::UpdateUltimateValue);
			PlayerCharacter->OnUltimateStatusDelegate.AddDynamic(this, &UHW_HUDUltimate::UpdateUltimateStatus);
		}
	}
}

void UHW_HUDUltimate::UpdateUltimateValue(float CurrentUltimateXP, float MaxUltimateXP)
{
	UltimatePercent = CurrentUltimateXP / MaxUltimateXP;
}

void UHW_HUDUltimate::UpdateUltimateStatus(bool bIsAvailable)
{
	UltimateColor = bIsAvailable ? UltimateEnableColor : UltimateDisableColor;
}