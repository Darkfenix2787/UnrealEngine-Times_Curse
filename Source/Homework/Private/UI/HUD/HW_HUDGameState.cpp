// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HW_HUDGameState.h"
#include "Core/HW_GameMode.h"

void UHW_HUDGameState::InitializeWidget()
{
	GameModeReference = Cast<AHW_GameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameModeReference))
	{
		GameModeReference->OnVictoryDelegate.AddDynamic(this, &UHW_HUDGameState::OnVictory);
		GameModeReference->OnGameOverDelegate.AddDynamic(this, &UHW_HUDGameState::OnGameOver);
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UHW_HUDGameState::OnVictory()
{
	GameStateName = VictoryName;
	SetVisibility(ESlateVisibility::Visible);
}

void UHW_HUDGameState::OnGameOver()
{
	GameStateName = GameOverName;
	SetVisibility(ESlateVisibility::Visible);
}
