// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HW_HealthComponent.h"

// Sets default values for this component's properties
UHW_HealthComponent::UHW_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;

}


void UHW_HealthComponent::Healing()
{
	Health = MaxHealth;
}

// Called when the game starts
void UHW_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	MyOwner = GetOwner();
	
	if (IsValid(MyOwner))
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHW_HealthComponent::TakingDamage);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateInitialHealth, this, &UHW_HealthComponent::UpdateInitialHealth, 0.2f, false);
	
}

void UHW_HealthComponent::TakingDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{	
	if (Damage < 0.0f || bIsDead)
	{
		return;
	}
		
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health: , %f"), Health);

	if (Health == 0.0f)
	{
		bIsDead = true;
		OnDeadDelegate.Broadcast(DamageCauser);
	}

	OnHealthChangeDelegate.Broadcast(this, DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
	OnHealthUpdateDelegate.Broadcast(Health, MaxHealth);
	
}

bool UHW_HealthComponent::TryAddHealth(float HealthToAdd)
{
	if (bIsDead)
	{
		return false;
	}

	if (Health == MaxHealth)
	{
		return false;
	}

	Health = FMath::Clamp(Health + HealthToAdd, 0.0f, MaxHealth);
	OnHealthUpdateDelegate.Broadcast(Health, MaxHealth);

	UE_LOG(LogTemp, Warning, TEXT("Health: , %f"), Health);

	return true;
}

void UHW_HealthComponent::UpdateInitialHealth()
{
	OnHealthUpdateDelegate.Broadcast(Health, MaxHealth);
}
