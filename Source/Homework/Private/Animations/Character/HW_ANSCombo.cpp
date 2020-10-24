// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Character/HW_ANSCombo.h"
#include "HW_Character.h"

void UHW_ANSCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		AHW_Character* Character = Cast<AHW_Character>(CharacterActor);
		if (IsValid(Character))
		{
			Character->SetComboEnable(true);
			UE_LOG(LogTemp, Warning, TEXT("InicioCombo"));
		}
	}
}

void UHW_ANSCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		AHW_Character* Character = Cast<AHW_Character>(CharacterActor);
		if (IsValid(Character))
		{
			Character->ResetCombo();			
		}
	}
}
