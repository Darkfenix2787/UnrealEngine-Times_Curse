// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HW_PadLauncher.h"
#include "Weapon/HW_Pad.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AHW_PadLauncher::AHW_PadLauncher()
{
	MuzzleSocketName = "Muzzle_04";
	MaxPads = 3;
	CurrentPads = 0;
}

void AHW_PadLauncher::StartAction()
{
	Super::StartAction();

	if (CurrentPads < MaxPads)
	{
		if (IsValid(CurrentOwnerCharacter))
		{		
			MovementComponent = CurrentOwnerCharacter->GetCharacterMovement();

			if (!MovementComponent->IsFalling())
			{
				USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();
				if (IsValid(CharacterMeshComponent))
				{
					FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
					FRotator MuzzleSocketRotator = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);
					AHW_Pad* CurrentProjectile = GetWorld()->SpawnActor<AHW_Pad>(ProjectileClass, MuzzleSocketLocation, MuzzleSocketRotator);
					if (IsValid(CurrentProjectile))
						CurrentProjectile->SetOwner(this);
					CurrentPads++;
				}
			}			
		}
	}
}

void AHW_PadLauncher::StopAction()
{
	Super::StopAction();
}

void AHW_PadLauncher::DecreaseNumPads()
{
	CurrentPads--;
}

