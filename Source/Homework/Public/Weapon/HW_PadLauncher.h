// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/HW_Weapon.h"
#include "HW_PadLauncher.generated.h"

class AHW_Pad;
class UCharacterMovementComponent;

UCLASS()
class HOMEWORK_API AHW_PadLauncher : public AHW_Weapon
{
	GENERATED_BODY()

public:

	AHW_PadLauncher();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pad Launcher")
		TSubclassOf<AHW_Pad> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		UCharacterMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pad Launcher")
		int MaxPads;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pad Launcher")
		int CurrentPads;

protected:

	virtual void StartAction() override;

	virtual void StopAction() override;

public:

	void DecreaseNumPads();
	
};
