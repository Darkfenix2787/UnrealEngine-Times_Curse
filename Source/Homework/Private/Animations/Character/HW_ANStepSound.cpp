// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Character/HW_ANStepSound.h"
#include "HW_Character.h"

void UHW_ANStepSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		AHW_Character* Character = Cast<AHW_Character>(CharacterActor);
		if (IsValid(Character))
		{
			Character->PlayStepSound();
		}
	}
}
