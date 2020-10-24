// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HW_Character.h"
#include "GameFramework/Actor.h"
#include "HW_Barrel.generated.h"


class AHW_Character;
class USphereComponent;
class UBoxComponent;
UCLASS()
class HOMEWORK_API AHW_Barrel : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* BarrelComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* ExplosionAreaComponent;	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BarrelMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		AHW_Character* HW_Character;


protected:

	UPROPERTY(BlueprintReadOnly, Category = "Barrel")
		bool bIsExploded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel")
		bool bIsInArea;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel")
		float FreezeSeconds;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel")
		float BaseSeconds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel")
		float SecondCounter;	

protected:
	UFUNCTION()
		void ExplosionAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	

	UFUNCTION()
		void ExplosionAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:	
	// Sets default values for this actor's properties
	AHW_Barrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ExplosionAction();

};
