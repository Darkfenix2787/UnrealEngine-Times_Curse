// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations\Character\HW_ANDisableHitOne.h"
#include "HW_Character.h"

void UHW_ANDisableHitOne::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	float fCurrentCombo;
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		AHW_Character* Character = Cast<AHW_Character>(CharacterActor);
		if (IsValid(Character))
		{
			fCurrentCombo = Character->GetCurrentComboMultiplier();

			if (fCurrentCombo == 1.0f)
			{
				Character->ResetCombo();
			}			
		}
	}
}
