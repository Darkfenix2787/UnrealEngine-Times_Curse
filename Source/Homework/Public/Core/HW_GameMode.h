// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HW_GameMode.generated.h"

class AHW_Character;
class AHW_SpectatorCamera;
class USoundCue;
class AHW_Enemy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKeyAddedSignature, FName, KeyTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStateChangeSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAlertModeChangeSignature, bool, bIsAlert);

UCLASS()
class HOMEWORK_API AHW_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spectating Camera")
		float SpectatingBlendTime;	

	UPROPERTY(BlueprintReadOnly, Category = "Level")
		bool bIsAlertMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Flow")
		FName MainMenuMapName;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
		AHW_SpectatorCamera* VictoryCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
		AHW_SpectatorCamera* GameOverCamera;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music")
		USoundCue* VictoryMusic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music")
		USoundCue* GameOverMusic;

	UPROPERTY(BlueprintReadOnly, Category = "Level")
		TArray<AHW_Enemy*> LevelEnemies;

	UPROPERTY(BlueprintReadOnly, Category = "Victory")
		TArray<AActor*> Keys;

	FTimerHandle TimerHandle_BackToMainMenu;

public:

	AHW_GameMode();

	UPROPERTY(BlueprintAssignable)
		FOnKeyAddedSignature OnKeyAddedDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnGameStateChangeSignature OnVictoryDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnGameStateChangeSignature OnGameOverDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnAlertModeChangeSignature OnAlertModeChangeDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupSpectatingCameras();

	void MoveCameraToSpectatingPoint(AHW_Character* Character, AHW_SpectatorCamera* SpectatingCamera);

	void PlayMusic(USoundCue* MusicCue);
	
public:

	UFUNCTION()
		void AddKeyToCharacter(AHW_Character* KeyOwner, FName KeyTag);

	UFUNCTION()
		void Victory(AHW_Character* Character);	

	UFUNCTION()
		void GameOver(AHW_Character* Character);

	void BackToMainMenu();

	void CheckAlertMode();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BP_Victory(AHW_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BP_GameOver(AHW_Character* Character);
};