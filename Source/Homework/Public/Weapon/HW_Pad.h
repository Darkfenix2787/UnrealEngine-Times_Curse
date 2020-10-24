// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HW_Pad.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class AHW_PadLauncher;

UCLASS()
class HOMEWORK_API AHW_Pad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHW_Pad();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* ProjectileCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		AHW_PadLauncher* PadOwner;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Launch(AHW_Character* LaunchCharacter);	
	

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Objects")
		void BP_Launch(AHW_Character* LaunchCharacter);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;	
	virtual void SetOwner(AActor* NewOwner) override;

};
