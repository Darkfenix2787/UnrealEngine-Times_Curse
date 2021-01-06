// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HW_Bot.generated.h"

class UStaticMeshComponent;
class AHW_Character;
class UHW_HealthComponent;
class UParticleSystem;
class USphereComponent;
class AHW_Enemy;
class AHW_BotSpawner;
class AHW_BotSpawnerKey;
class UHW_GameInstance;
class UAudioComponent;
class USoundCue;
class AHW_Item;

UCLASS()
class HOMEWORK_API AHW_Bot : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* BotMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* SelfDestructionDetectorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UHW_HealthComponent* healthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAudioComponent* TimerSoundComponent;


protected:

	UPROPERTY(BlueprintReadOnly, Category = "Bot Movement")
		bool bIsExploded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
		bool bDebug;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
		bool bIsStartingCountDown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Movement")
		float MinDistanceToTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Movement")
		float ForceMagnitude;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Effect")
		float ExplosionDamage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Effect")
		float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot Key System")
		float LootProbability;

	UPROPERTY(BlueprintReadOnly, Category = "Bot")
		FVector NextPathPoint;

	UPROPERTY(BlueprintReadOnly, Category = "References")
		AHW_Character* PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "References")
		AHW_Enemy* EnemyToHealth;

	UPROPERTY(BlueprintReadOnly, Category = "References")
		TArray<AActor*> Enemies;

	UMaterialInstanceDynamic* BotMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Effect")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Effect")
		UParticleSystem* HealingEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot Key System")
		TSubclassOf<AHW_Item> LootItemKeyClass;

	FTimerHandle TimerHandle_SelfDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundCue* ExplosionSound;

public:

	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
		AHW_BotSpawner* MySpawner;

	UHW_GameInstance* GameInstanceReference;

public:
	// Sets default values for this pawn's properties
	AHW_Bot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Navigation")
		FVector GetNextPathPoint();

	UFUNCTION()
		void TakingDamage(UHW_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	void SelfDestruction();

	UFUNCTION()
		void StartCountDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SelfDamage();

	void SpawnKey();

	void PlayTimerSound();

	void PlayExplosionSound();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpawner(AHW_BotSpawner* NewSpawner) { MySpawner = NewSpawner; };
};
