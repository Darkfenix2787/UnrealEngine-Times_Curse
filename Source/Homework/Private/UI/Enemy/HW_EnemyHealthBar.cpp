// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enemy/HW_EnemyHealthBar.h"

void UHW_EnemyHealthBar::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	HealthPercent = CurrentHealth / MaxHealth;
}
