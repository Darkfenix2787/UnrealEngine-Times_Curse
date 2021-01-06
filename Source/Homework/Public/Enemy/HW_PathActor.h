// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HW_PathActor.generated.h"

class UBillboardComponent;

UCLASS()
class HOMEWORK_API AHW_PathActor : public AActor
{
	GENERATED_BODY()


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBillboardComponent* PathBillboardComponent;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget = true), Category = "Path")
		TArray<FVector> PathPoints;
	
public:	
	// Sets default values for this actor's properties
	AHW_PathActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
