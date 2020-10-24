// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HW_BotSpawner.h"
#include "Components/BillboardComponent.h"
#include "Enemy/HW_Bot.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AHW_BotSpawner::AHW_BotSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnerBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("SpawnBillboard"));
	RootComponent = SpawnerBillboardComponent;

	bIsActive = false;
	MaxBotsCounter = 1;
	TimeToSpawn = 1.0;
}

// Called when the game starts or when spawned
void AHW_BotSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandleSpawnBot, this, &AHW_BotSpawner::SpawnBot, TimeToSpawn, true);
	
}

// Called every frame
void AHW_BotSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHW_BotSpawner::SpawnBot()
{
	if (!bIsActive)
		return;

	if (CurrentBotsCounter >= MaxBotsCounter)
		return;

	if (IsValid(BotClass))
	{
		FVector LocalSpawnPoint = GetSpawnPoint();
		FVector SpawnPoint = UKismetMathLibrary::TransformLocation(GetActorTransform(), LocalSpawnPoint);
		FTransform BotTransform = FTransform(FRotator::ZeroRotator, SpawnPoint);

		AHW_Bot* NewBot = GetWorld()->SpawnActorDeferred<AHW_Bot>(BotClass, BotTransform);
		if (IsValid(NewBot))
			NewBot->SetSpawner(this);

		NewBot->FinishSpawning(BotTransform);

		CurrentBotsCounter++;
	}
		

}

FVector AHW_BotSpawner::GetSpawnPoint()
{
	if (SpawnPoints.Num() > 0)
	{
		int IndexSelected = FMath::RandRange(0, SpawnPoints.Num() - 1);
		return SpawnPoints[IndexSelected];
	}
	else
	{
		return GetActorLocation();
	}
}

void AHW_BotSpawner::NotifyBotDead()
{
	CurrentBotsCounter--;
}

