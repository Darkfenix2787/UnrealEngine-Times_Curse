// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/HW_Weapon.h"
#include "HW_GrenadeLauncher.generated.h"

class AHW_Projectile;

UCLASS()
class HOMEWORK_API AHW_GrenadeLauncher : public AHW_Weapon
{
	GENERATED_BODY()

public:

	AHW_GrenadeLauncher();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grenade Launcher")
		TSubclassOf<AHW_Projectile> ProjectileClass;


protected:

	virtual void StartAction() override;

	virtual void StopAction() override;
};