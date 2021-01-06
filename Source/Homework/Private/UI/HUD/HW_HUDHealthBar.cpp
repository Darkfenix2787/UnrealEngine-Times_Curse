// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HW_HUDHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "HW_Character.h"
#include "Components/HW_HealthComponent.h"

void UHW_HUDHealthBar::InitializeWidget()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		AHW_Character* PlayerCharacter = Cast<AHW_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter))
		{
			UHW_HealthComponent* PlayerHealthComponent = Cast<UHW_HealthComponent>(PlayerCharacter->GetHealthComponent());
			if (IsValid(PlayerHealthComponent))
			{
				PlayerHealthComponent->OnHealthUpdateDelegate.AddDynamic(this, &UHW_HUDHealthBar::UpdateHealth);
			}
		}
	}
}

void UHW_HUDHealthBar::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	HealthPercent = CurrentHealth / MaxHealth;
	HealthColor = FMath::Lerp(EmptyHealthColor, FullHealthColor, HealthPercent);
}