// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "HW_CheatManager.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK_API UHW_CheatManager : public UCheatManager
{
	GENERATED_BODY()

public:

	UFUNCTION(exec)
		void HW_UltimateReady();	
};
