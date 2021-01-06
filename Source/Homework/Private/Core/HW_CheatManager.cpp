// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/HW_CheatManager.h"
#include "Kismet/GameplayStatics.h"
#include "HW_Character.h"

void UHW_CheatManager::HW_UltimateReady()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		AHW_Character* PlayerCharacter = Cast<AHW_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter) && PlayerCharacter->GetCharacterType() == EHW_CharacteraType::CharacteraType_Player)
		{
			PlayerCharacter->GainUltimateXP(10000);
		}
	}
}