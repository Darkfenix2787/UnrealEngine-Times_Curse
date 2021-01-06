// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HW_BotSpawner.generated.h"

class UBillboardComponent;
class AHW_Bot;

UCLASS()
class HOMEWORK_API AHW_BotSpawner : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBillboardComponent* SpawnerBillboardComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
		bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta= (UMin = 1.0, ClampMin = 1.0), Category = "Spawner" )
		int MaxBotsCounter;

	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
		int CurrentBotsCounter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UMin = 0.1, ClampMin = 0.1), Category = "Spawner")
		float TimeToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget = true), Category = "Spawner")
		TArray<FVector> SpawnPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawner")
		TSubclassOf<AHW_Bot> BotClass;

	FTimerHandle TimerHandleSpawnBot;

	
public:	
	// Sets default values for this actor's properties
	AHW_BotSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnBot();

	FVector GetSpawnPoint();

public:

	void NotifyBotDead();

	void SetSpawnerStatus(bool NewStatus) { bIsActive = NewStatus; };
};
