// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HW_HUDObjetive.h"

void UHW_HUDObjetive::ObjetiveCompleted()
{
	bIsCompleted = true;
	CurrentColor = CompletedColor;
}