// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/HW_MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Core/HW_GameInstance.h"


void UHW_MainMenuWidget::NewGame()
{
	BP_NewGame();

	UHW_GameInstance* GameInstanceReference = Cast<UHW_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->ResetData();
	}

	UGameplayStatics::OpenLevel(GetWorld(),GamePlayLevelName);
}

void UHW_MainMenuWidget::ContinueGame()
{
	BP_ContinueGame();

	UHW_GameInstance* GameInstanceReference = Cast<UHW_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->LoadData();
	}

	UGameplayStatics::OpenLevel(GetWorld(), GamePlayLevelName);
}

void UHW_MainMenuWidget::QuitGame()
{
	BP_QuitGame();
	APlayerController* PlayerControler = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerControler, EQuitPreference::Quit, false);
}