// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HW_SpectatorCamera.generated.h"

class UStaticMeshComponent;


UENUM(Blueprintable)
enum class EHW_SpectatingCameraType : uint8
{
	CameraType_None			UMETA(DisplayName = "None"),
	CameraType_Victory		UMETA(DisplayName = "Victory"),
	CameraType_GameOver		UMETA(DisplayName = "Game Over")
};


UCLASS()
class HOMEWORK_API AHW_SpectatorCamera : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* SpectatingCameraComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spectating Camera")
		EHW_SpectatingCameraType CameraType;
	
public:	
	// Sets default values for this actor's properties
	AHW_SpectatorCamera();

	EHW_SpectatingCameraType GetCameraType() { return CameraType; };



};
