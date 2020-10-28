// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HW_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/HW_Enemy.h"
#include "SaveSystem/HW_SaveGame.h"


UHW_GameInstance::UHW_GameInstance()
{
	SaveSlotName = "HW_SaveData";
}

void UHW_GameInstance::AddEnemyDefeatedToCounter()
{
	EnemiesDefeatedCounter++;
	OnEnemyKilledDelegate.Broadcast(EnemiesDefeatedCounter);
	BP_AddEnemyDefeatedToCounter();
}

void UHW_GameInstance::SaveData()
{
	USaveGame* SaveGameObject = nullptr;	

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHW_Enemy::StaticClass(), CurrentsEnemies);

	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);

	if (bExistingData)
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	else
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(UHW_SaveGame::StaticClass());

	if (IsValid(SaveGameObject))
	{
		UHW_SaveGame* SaveFile = Cast<UHW_SaveGame>(SaveGameObject);
		if (IsValid(SaveFile))
		{
			SaveFile->SetEnemiesDefeatedCounterInfo(EnemiesDefeatedCounter);
			SaveFile->SetEnemiesInfo(CurrentsEnemies);
			UGameplayStatics::SaveGameToSlot(SaveFile, SaveSlotName, 0);
		}
	}
}

void UHW_GameInstance::LoadData()
{
	USaveGame* SaveGameObject = nullptr;
	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);

	if (bExistingData)
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);

	if (IsValid(SaveGameObject))
	{
		UHW_SaveGame* SaveFile = Cast<UHW_SaveGame>(SaveGameObject);
		if (IsValid(SaveFile))
		{
			EnemiesDefeatedCounter = SaveFile->GetEnemiesDefeatedCounterInfo();
			CurrentsEnemies = SaveFile->GetEnemiesInfo();
		}
	}
}

void UHW_GameInstance::ResetData()
{
	EnemiesDefeatedCounter = 0;
	BP_ResetData();
}
