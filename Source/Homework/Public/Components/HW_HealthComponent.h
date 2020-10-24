// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HW_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealtChangeSignature, UHW_HealthComponent*, HealthComponent, AActor*, DamagedActor, float, Damage, const UDamageType*, DamageType, AController*, InstigatedBy, AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeadSignature, AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthUpdateSignature, float, CurrentHealth, float, MaxHealth);

UCLASS( ClassGroup=(Home), meta=(BlueprintSpawnableComponent) )
class HOMEWORK_API UHW_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category="Health Component")
		bool bIsDead;

	UPROPERTY(EditanyWhere, BlueprintReadWrite, Category = "Health Component")
		float Health;

	UPROPERTY(EditanyWhere, BlueprintReadWrite, meta=(ClampMIn = 0.0,UIMin = 0.0) , Category = "Health Component")
		float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Health Component")
		AActor* MyOwner;

	FTimerHandle TimerHandle_UpdateInitialHealth;

public:

	UPROPERTY(BlueprintAssignable)
		FOnHealtChangeSignature OnHealthChangeDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnDeadSignature OnDeadDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnHealthUpdateSignature OnHealthUpdateDelegate;

public:	
	// Sets default values for this component's properties
	UHW_HealthComponent();

	UFUNCTION(BlueprintCallable)
		bool IsDead() const { return bIsDead; };
	
	UFUNCTION(BlueprintCallable)
		float GetHealth() const { return Health; };

	UFUNCTION(BlueprintCallable)
		float GetMaxHealth() const { return MaxHealth; };

	void Healing();

	bool TryAddHealth(float HealthToAdd);

	void UpdateInitialHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void TakingDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

		
};
