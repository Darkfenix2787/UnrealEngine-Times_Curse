// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HW_Weapon.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AHW_Weapon::AHW_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Damage = 20.f;
}

// Called when the game starts or when spawned
void AHW_Weapon::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AHW_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHW_Weapon::StartAction()
{
	BP_StartAction();
	PlaySound(ShootSound);
}

void AHW_Weapon::StopAction()
{
	BP_StopAction();
}

void AHW_Weapon::SetCharacterOwner(ACharacter* NewOwner)
{
	if (IsValid(NewOwner))
	{
		SetOwner(NewOwner);
		CurrentOwnerCharacter = NewOwner;
	}
}

void AHW_Weapon::PlaySound(USoundCue* SoundCue, bool bIs3D, FVector SoundLocation)
{
	if (!IsValid(SoundCue))
		return;

	if (bIs3D)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCue, SoundLocation);
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SoundCue);
	}
}



