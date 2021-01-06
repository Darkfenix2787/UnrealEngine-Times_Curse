// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HW_GrenadeLauncher.h"
#include "Weapon/HW_Projectile.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

AHW_GrenadeLauncher::AHW_GrenadeLauncher()
{
	MuzzleSocketName = "Muzzle_04";
}

void AHW_GrenadeLauncher::StartAction()
{
	Super::StartAction();

	if (IsValid(CurrentOwnerCharacter))
	{
		USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();
		if (IsValid(CharacterMeshComponent))
		{
			FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
			FRotator MuzzleSocketRotator = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);
			AHW_Projectile* CurrentProjectile = GetWorld()->SpawnActor<AHW_Projectile>(ProjectileClass, MuzzleSocketLocation, MuzzleSocketRotator);
		}
	}
}

void AHW_GrenadeLauncher::StopAction()
{
	Super::StopAction();
}