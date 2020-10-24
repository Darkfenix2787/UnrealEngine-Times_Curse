// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HW_Character.h"
#include "HW_Enemy.generated.h"

class AHW_PathActor;
class AHW_Item;
class AHW_AIController;
class AHW_BotSpawner;
class UWidgetComponent;
class UHW_EnemyHealthBar;
class AHW_HealthBox;


/**
 * 
 */
UCLASS()
class HOMEWORK_API AHW_Enemy : public AHW_Character
{
	GENERATED_BODY()


public:

	AHW_Enemy();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UWidgetComponent* WidgetHealthBarComponent;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Navigation Path")
		bool bLoopPath;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
		bool bIsShowingHealthBar;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
		bool bIsAlert;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Navigation Path")
		int DirectionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Navigation Path")
		float WaitingTimeOnPathPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Ultimate XP")
		float XPValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot System")
		float LootProbability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Navigation Path")
		AHW_PathActor* MyPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot System")
		TSubclassOf<AHW_Item> LootItemClass;

	UPROPERTY(BlueprintReadOnly, Category = "AI | Controller")
		AHW_AIController* MyAIController;	

	UPROPERTY(BlueprintReadOnly, Category = "References")
		TArray<AActor*> BotSpawners;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
		UHW_EnemyHealthBar* EnemyHealthBar;

	FTimerHandle TimerHandle_HideHealthBar;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
		void GiveXP(AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
		void BP_GiveXP(AActor* DamageCauser);

	bool TrySpawnLoot();

	UFUNCTION()
		void HealthChanged(UHW_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:

	bool GetLoopPath() { return bLoopPath; };
	bool IsAlert() { return bIsAlert; };
	int GetDirectionIndex() { return DirectionIndex; };
	float GetWaitingTime() { return WaitingTimeOnPathPoint; };

	void HideHealthBar();
	void ShowHealthBar();
	void SetAlert(bool bValue);

};
