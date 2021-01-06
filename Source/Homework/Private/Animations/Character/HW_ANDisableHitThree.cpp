// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations\Character\HW_ANDisableHitThree.h"
#include "HW_Character.h"

void UHW_ANDisableHitThree::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	float CurrentCombo;
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		AHW_Character* Character = Cast<AHW_Character>(CharacterActor);
		if (IsValid(Character))
		{
			CurrentCombo = Character->GetCurrentComboMultiplier();

			if (CurrentCombo == 3.0f)
			{
				Character->ResetCombo();
			}
		}
	}
}
