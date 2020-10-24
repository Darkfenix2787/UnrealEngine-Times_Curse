// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HW_HUDObjetivesContainer.h"
#include "Core/HW_GameMode.h"
#include "UI/HUD/HW_HUDObjetive.h"

void UHW_HUDObjetivesContainer::InitializeWidget()
{
	GameModeReference = Cast<AHW_GameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameModeReference))
	{
		GameModeReference->OnKeyAddedDelegate.AddDynamic(this, &UHW_HUDObjetivesContainer::UpdateObjetives);
	}
}

void UHW_HUDObjetivesContainer::InitializeObjetives(TArray<UHW_HUDObjetive*> NewObjetives)
{
	for (UHW_HUDObjetive* NewObjetive : NewObjetives)
	{
		Objetives.AddUnique(NewObjetive);
	}
}

void UHW_HUDObjetivesContainer::UpdateObjetives(FName KeyTag)
{
	int ObjetiveIndex = -1;	
	
	if (KeyTag == "MemoryKey01")
	{
		ObjetiveIndex = 0;
	}

	if (KeyTag == "MemoryKey02")
	{
		ObjetiveIndex = 1;
	}

	if (KeyTag == "MemoryKey03")
	{
		ObjetiveIndex = 2;
	}

	if (KeyTag == "MemoryKey04")
	{
		ObjetiveIndex = 3;
	}

	if (KeyTag == "MemoryKey05")
	{
		ObjetiveIndex = 4;
	}

	if (Objetives.IsValidIndex(ObjetiveIndex))
	{
		UHW_HUDObjetive* CurrentObjetive = Objetives[ObjetiveIndex];
		if (IsValid(CurrentObjetive))
		{
			CurrentObjetive->ObjetiveCompleted();
		}
	}
}
