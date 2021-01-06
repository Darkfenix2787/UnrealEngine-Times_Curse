// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HW_LaunchPad.generated.h"

class UBoxComponent;
class AHW_Character;

UCLASS()
class HOMEWORK_API AHW_LaunchPad : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* LaunchColliderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* LaunchMeshComponent;
	
public:	
	// Sets default values for this actor's properties
	AHW_LaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void LaunchPad(AHW_Character* LaunchCharacter);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Objects")
		void BP_LaunchPad(AHW_Character* LaunchCharacter);

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
