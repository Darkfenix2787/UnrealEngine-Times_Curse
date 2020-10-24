// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HW_LevelMusic.generated.h"

class UBillboardComponent;
class UAudioComponent;
class AHW_GameMode;

UCLASS()
class HOMEWORK_API AHW_LevelMusic : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
		UBillboardComponent* MusicBillboardComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
		UAudioComponent* MusicAudioComponent;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		FName AlertParamName;

	UPROPERTY(BlueprintReadOnly, Category = "References")
		AHW_GameMode* GameModeReference;

public:
	// Sets default values for this actor's properties
	AHW_LevelMusic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void StopLevelMusic();

	UFUNCTION()
		void ChangeLevelMusic(bool bIsAlert);
}; 
