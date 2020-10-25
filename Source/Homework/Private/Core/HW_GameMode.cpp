// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HW_GameMode.h"
#include "HW_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HW_SpectatorCamera.h"
#include "Sound/SoundCue.h"
#include "Enemy/HW_Enemy.h"

AHW_GameMode::AHW_GameMode()
{
	MainMenuMapName = "MainMenu";
}

void AHW_GameMode::BeginPlay()
{
	Super::BeginPlay();
	SetupSpectatingCameras();		

	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHW_Enemy::StaticClass(), EnemyActors);

	for (AActor* EnemyActor : EnemyActors)
	{
		if (IsValid(EnemyActor))
		{
			AHW_Enemy* NewEnemy = Cast<AHW_Enemy>(EnemyActor);
			if (IsValid(NewEnemy))
			{
				LevelEnemies.AddUnique(NewEnemy);
			}
		}
		else
		{
			continue;
		}
	}	
}

void AHW_GameMode::SetupSpectatingCameras()
{
	TArray<AActor*> SpectatingCameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHW_SpectatorCamera::StaticClass(), SpectatingCameraActors);

	if (SpectatingCameraActors.Num() > 0)
	{
		for (AActor* SpectatingActor : SpectatingCameraActors)
		{
			AHW_SpectatorCamera* SpectatingCamera = Cast<AHW_SpectatorCamera>(SpectatingActor);

			if (IsValid(SpectatingCamera))
			{
				switch (SpectatingCamera->GetCameraType())
				{
				case EHW_SpectatingCameraType::CameraType_Victory:
						VictoryCamera = SpectatingCamera;
					break;
				case EHW_SpectatingCameraType::CameraType_GameOver:
						GameOverCamera = SpectatingCamera;
					break;
				default:
					break;
				}
			}
		}
	}
}

void AHW_GameMode::AddKeyToCharacter(AHW_Character* KeyOwner, FName KeyTag)
{
	if (IsValid(KeyOwner))
	{
		OnKeyAddedDelegate.Broadcast(KeyTag);
		KeyOwner->AddKey(KeyTag);
	}
}

void AHW_GameMode::Victory(AHW_Character* Character)
{	
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Item", Keys);
	if (!Keys.IsValidIndex(0))
	{
		Character->DisableInput(nullptr);
		MoveCameraToSpectatingPoint(Character, VictoryCamera);
		OnVictoryDelegate.Broadcast();
		PlayMusic(VictoryMusic);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_BackToMainMenu, this, &AHW_GameMode::BackToMainMenu, 5.0f, false);
		BP_Victory(Character);
	}	
}


void AHW_GameMode::GameOver(AHW_Character* Character)
{
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	if (Character->HasToDestroy())
	{
		Character->DetachFromControllerPendingDestroy();
		Character->SetLifeSpan(3.0);
	}
	else
	{
		Character->DisableInput(nullptr);
		MoveCameraToSpectatingPoint(Character, GameOverCamera);
	}
	
	OnGameOverDelegate.Broadcast();
	PlayMusic(GameOverMusic);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_BackToMainMenu, this, &AHW_GameMode::BackToMainMenu, 8.0f, false);
	BP_GameOver(Character);
}

void AHW_GameMode::BackToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), MainMenuMapName);
}

void AHW_GameMode::CheckAlertMode()
{
	bool bEnemyInAlertMode = false;

	for (AHW_Enemy* EnemyOnLevel : LevelEnemies)
	{
		if (IsValid(EnemyOnLevel))
		{
			if (EnemyOnLevel->IsAlert())
			{
				bEnemyInAlertMode = true;
				break;
			}
		}
		else
		{
			continue;
		}
	}

	if (bIsAlertMode != bEnemyInAlertMode)
	{
		bIsAlertMode = bEnemyInAlertMode;
		OnAlertModeChangeDelegate.Broadcast(bIsAlertMode);
	}


}


void AHW_GameMode::MoveCameraToSpectatingPoint(AHW_Character* Character, AHW_SpectatorCamera* SpectatingCamera)
{
	if (!IsValid(Character) || !IsValid(SpectatingCamera))
	{
		return;
	}

	AController* CharacterController = Character->GetController();
	if (IsValid(CharacterController))
	{
		APlayerController* PlayerController = Cast<APlayerController>(CharacterController);
		if (IsValid(PlayerController))
		{
			PlayerController->SetViewTargetWithBlend(SpectatingCamera, SpectatingBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
}

void AHW_GameMode::PlayMusic(USoundCue* MusicCue)
{
	if (!IsValid(MusicCue))
	{
		return;
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), MusicCue);
	}
}
