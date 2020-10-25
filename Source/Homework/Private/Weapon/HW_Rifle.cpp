// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/HW_Rifle.h"
#include "Homework/Homework.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "HW_Mine.h"
#include "HW_Barrel.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"


AHW_Rifle::AHW_Rifle() 
{
	TraceLenght = 10000.0f;
	MuzzleSocketName = "Muzzle_04";
}

void AHW_Rifle::StartAction()
{
	Super::StartAction();	

	AActor* CurrentOwner = GetOwner();

	if (IsValid(CurrentOwner))
	{
		FVector EyeLocation;
		FRotator EyeRotation;


		CurrentOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * TraceLenght);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(CurrentOwner);
		QueryParams.bTraceComplex = true;

		FVector TraceEndPoint = TraceEnd;
		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,EyeLocation,TraceEnd,COLLISION_WEAPON,QueryParams);

		if (bHit)
		{
			AActor* HitActor = HitResult.GetActor();
			if (IsValid(HitActor))
			{
				TraceEndPoint = HitResult.ImpactPoint;
				if (IsValid(Cast<AHW_Mine>(HitActor)))
				{
					if (IsValid(ExplosionEffect))
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, TraceEndPoint, HitResult.ImpactNormal.Rotation(), true);
						HitActor->Destroy();
					}
				}
				else
					if (IsValid(Cast<AHW_Barrel>(HitActor)))
					{						
						AHW_Barrel* HW_Barrel = Cast<AHW_Barrel>(HitActor);
						HW_Barrel->ExplosionAction();
					}
					else

					{
						UGameplayStatics::ApplyPointDamage(HitActor, Damage, ShotDirection, HitResult, CurrentOwner->GetInstigatorController(), this, DamageType);

						if (IsValid(ImpactEffect))
						{
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, TraceEndPoint, HitResult.ImpactNormal.Rotation());
						}
					}
			}
		}

		if (bdrawLineTrace) 
		{
			DrawDebugLine(GetWorld(),EyeLocation,TraceEnd,FColor::White,false,1.0f,0.0f,1.0f);
		}

		if (IsValid(MuzzleEffect))
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, CurrentOwnerCharacter->GetMesh(), MuzzleSocketName);
		}

		if (IsValid(TraceEffect))
		{
			USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();
			if (IsValid(CharacterMeshComponent))
			{
				FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
				UParticleSystemComponent* TraceComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, MuzzleSocketLocation);
				if (IsValid(TraceComponent))
				{
					TraceComponent->SetVectorParameter(TraceParamName, TraceEndPoint);
				}
			}
		}


	}
	
}

void AHW_Rifle::StopAction()
{
	Super::StopAction();	
	
}
