// Fill out your copyright notice in the Description page of Project Settings.


#include "HW_SpectatorCamera.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHW_SpectatorCamera::AHW_SpectatorCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpectatingCameraComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpectatingCameraComponent"));
	RootComponent = SpectatingCameraComponent;
}