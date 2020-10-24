// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HW_HUDEnemyCounter.h"
#include "Core/HW_GameInstance.h"

void UHW_HUDEnemyCounter::InitializeWidget()
{
	GameInstanceReference = Cast<UHW_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->OnEnemyKilledDelegate.AddDynamic(this, &UHW_HUDEnemyCounter::UpdateCounter);
		UpdateCounter(GameInstanceReference->GetEnemiesDefeatedCounter());
	}
}

void UHW_HUDEnemyCounter::UpdateCounter(int EnemyDefeatedCounter)
{
	EnemiesDefeated = EnemyDefeatedCounter;
}
