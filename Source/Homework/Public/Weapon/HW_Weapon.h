// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HW_Weapon.generated.h"

class UDamageType;
class ACharacter;
class USoundCue;

UCLASS()
class HOMEWORK_API AHW_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHW_Weapon();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		TSubclassOf<UDamageType> DamageType;

	ACharacter* CurrentOwnerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
		USoundCue* ShootSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
		void BP_StartAction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
		void BP_StopAction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		virtual void StartAction();

	UFUNCTION(BlueprintCallable)
		virtual void StopAction();

	UFUNCTION(BlueprintCallable)
		void SetCharacterOwner(ACharacter* NewOwner);

	UFUNCTION(BlueprintCallable)
		void PlaySound(USoundCue* SoundCue, bool bIs3D = false, FVector SoundLocation = FVector::ZeroVector);

};
