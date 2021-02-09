// Fill out your copyright notice in the Description page of Project Settings.


#include "HW_Character.h"
#include "Homework/Homework.h"
#include "Camera/CameraComponent.h"
#include "Weapon/HW_Weapon.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components//SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation//AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/HW_HealthComponent.h"
#include "Core/HW_GameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EngineUtils.h"
#include "Core/HW_GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "UI/PauseMenu/HW_PauseMenuWidget.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

//====================================================================================================================================//
// Sets default values
AHW_Character::AHW_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseFirstPersonView = true;
	bCanUseWeapon = true;
	FPSCameraSocketName = "SCK_Camera_Eye";
	MeleeSocketName = "SCK_Melee";
	MeleeDamage = 10.0f;
	Dilation = 1.0f;
	MaxComboMultiplier = 4.0f;
	CurrentComboMultiplier = 1.0f;
	Speed = 1;
	MainMenuMapName = "MainMenu";
	JumpMaxCount = 1;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CameraComponent"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(GetMesh(), FPSCameraSocketName);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CameraComponent"));
	TPSCameraComponent->SetupAttachment(SpringArmComponent);

	MeleeDetectorComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeDetectorComponent"));
	MeleeDetectorComponent->SetupAttachment(GetMesh(), MeleeSocketName);
	MeleeDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeDetectorComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);
	MeleeDetectorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthComponent = CreateDefaultSubobject<UHW_HealthComponent>(TEXT("HealthComponent"));

	StepSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("StepSoundComponent"));
	StepSoundComponent->SetupAttachment(RootComponent);

	VoicesSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("VoicesSoundComponent"));
	VoicesSoundComponent->SetupAttachment(RootComponent);

	MaxUltimateExp = 100;
	MaxUltimateDuration = 10.0f;
	bUltimateWithTick = true;
	UltimateFrequency = 0.5f;
	UltimateWalkSpeed = 2000.0f;
	UltimatePlayRate = 2.0f;
	PlayRate = 1.0f;
	UltimateShootFrequency = 0.1f;
}

//====================================================================================================================================//
FVector AHW_Character::GetPawnViewLocation() const
{
	if (IsValid(FPSCameraComponent) && bUseFirstPersonView)
	{
		return FPSCameraComponent->GetComponentLocation();
	}

	if (IsValid(TPSCameraComponent) && !bUseFirstPersonView)
	{
		return TPSCameraComponent->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();

}

//====================================================================================================================================//
// Called when the game starts or when spawned
void AHW_Character::BeginPlay()
{
	Super::BeginPlay();
	InitializaReferences();
	CreateInitialWeapon();
	MeleeDetectorComponent->OnComponentBeginOverlap.AddDynamic(this, &AHW_Character::MakeMeleeDamage);
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AHW_Character::OnHealthChange);
	NormalWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	Pause();
}

//====================================================================================================================================//
void AHW_Character::InitializaReferences()
{
	if (IsValid(GetMesh()))
	{
		MyAnimInstance = GetMesh()->GetAnimInstance();
	}

	if (IsValid(PauseWidgetClass))
	{
		PauseWidget = CreateWidget<UHW_PauseMenuWidget>(GetWorld(), PauseWidgetClass);
		PauseWidget->AddToViewport();
	}

	GameModeReference = Cast<AHW_GameMode>(GetWorld()->GetAuthGameMode());
	GameInstanceReference = Cast<UHW_GameInstance>(GetWorld()->GetGameInstance());
}

//====================================================================================================================================//
void AHW_Character::CreateInitialWeapon()
{
	if (WeaponClass.IsValidIndex(0))
	{
		CurrentWeapon = GetWorld()->SpawnActor<AHW_Weapon>(WeaponClass[0], GetActorLocation(), GetActorRotation());

		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetCharacterOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

//====================================================================================================================================//
void AHW_Character::ChangeWeapon()
{
	if (IsValid(CurrentWeapon) && WeaponClass.IsValidIndex(0))
	{
		TArray<FName> Name = CurrentWeapon->Tags;
		FString SName = Name[0].ToString();

		if (SName == "Rifle")
		{
			CurrentWeapon = GetWorld()->SpawnActor<AHW_Weapon>(WeaponClass[1], GetActorLocation(), GetActorRotation());
		}
		else
		{
			CurrentWeapon = GetWorld()->SpawnActor<AHW_Weapon>(WeaponClass[0], GetActorLocation(), GetActorRotation());
		}

		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetCharacterOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

//====================================================================================================================================//
void AHW_Character::StartMeele()
{
	if (bIsDoingMelee && !bCanMakeCombos)
	{
		return;
	}


	if (bCanMakeCombos)
	{
		if (bIsDoingMelee)
		{
			if (bIsComboEnable)
			{
				if (CurrentComboMultiplier < MaxComboMultiplier)
				{
					CurrentComboMultiplier++;
					SetComboEnable(false);
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
		}
	}

	if (IsValid(MyAnimInstance) && IsValid(MeeleMontage))
	{
		MyAnimInstance->Montage_Play(MeeleMontage, PlayRate);
	}

	SetMeleeState(true);
}

//====================================================================================================================================//
void AHW_Character::StartUltimate()
{
	if (bCanUseUltimate && !bIsUsingUltimate)
	{
		CurrentUltimateDuration = MaxUltimateDuration;

		bCanUseUltimate = false;

		PlayVoiceSound(UltimateSound);

		if (IsValid(MyAnimInstance) && IsValid(UltimateMontage))
		{
			GetCharacterMovement()->MaxWalkSpeed = 0.0f;
			bCanUseWeapon = false;
			const float StarUltimateMontageDuration = MyAnimInstance->Montage_Play(UltimateMontage);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_BeginUltimateBehaviour, this, &AHW_Character::BeginUltimateBehaviour, StarUltimateMontageDuration, false);
		}
		else
		{
			BeginUltimateBehaviour();
		}

		BP_StartUltimate();
	}
}

//====================================================================================================================================//
void AHW_Character::BeginUltimateBehaviour()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	bIsUsingUltimate = true;
	bCanUseWeapon = true;
	GetCharacterMovement()->MaxWalkSpeed = UltimateWalkSpeed;

	DilationIteration(0.1f);

	if (!bUltimateWithTick)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Ultimate, this, &AHW_Character::UpdateUltimateDurationWithTimer, UltimateFrequency, true);
	}
}

//====================================================================================================================================//
void AHW_Character::DilationIteration(float CustomIterator)
{
	for (TActorIterator<AActor> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
	{
		AActor* Actor = *ActorIterator;
		if (Actor && Actor != this)
		{
			Actor->CustomTimeDilation = CustomIterator;
		}
	}
}

//====================================================================================================================================//
void AHW_Character::Healing()
{
	HealthComponent->Healing();
}

//====================================================================================================================================//
void AHW_Character::PlayStepSound()
{
	StepSoundComponent->Play();
}

//====================================================================================================================================//
void AHW_Character::PlayVoiceSound(USoundCue* VoiceSound)
{
	if (!IsValid(VoiceSound))
	{
		return;
	}

	VoicesSoundComponent->SetSound(VoiceSound);
	VoicesSoundComponent->Play();
}

//====================================================================================================================================//
void AHW_Character::GoToMainMenu()
{
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->SaveData();
	}

	UGameplayStatics::OpenLevel(GetWorld(), MainMenuMapName);
}

//====================================================================================================================================//
void AHW_Character::Pause()
{
	bool bIsPaused = UGameplayStatics::IsGamePaused(GetWorld());

	UGameplayStatics::SetGamePaused(GetWorld(), !bIsPaused);

	if (IsValid(PauseWidget))
	{
		if (!bIsPaused)
			PauseWidget->SetVisibility(ESlateVisibility::Visible);
		else
			PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

//====================================================================================================================================//
void AHW_Character::MakeMeleeDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{

		if (OtherActor == this)
		{
			return;
		}

		AHW_Character* MeleeTarget = Cast<AHW_Character>(OtherActor);
		if (IsValid(MeleeTarget))
		{
			bool bPlayerAttackingEnemy = GetCharacterType() == EHW_CharacteraType::CharacteraType_Player && MeleeTarget->GetCharacterType() == EHW_CharacteraType::CharacteraType_Enemy;
			bool bEnemyAttackingPlayer = GetCharacterType() == EHW_CharacteraType::CharacteraType_Enemy && MeleeTarget->GetCharacterType() == EHW_CharacteraType::CharacteraType_Player;

			if (bPlayerAttackingEnemy || bEnemyAttackingPlayer)
				UGameplayStatics::ApplyPointDamage(OtherActor, MeleeDamage * CurrentComboMultiplier, SweepResult.Location, SweepResult, GetInstigatorController(), this, nullptr);

		}
		else
			UGameplayStatics::ApplyPointDamage(OtherActor, MeleeDamage * CurrentComboMultiplier, SweepResult.Location, SweepResult, GetInstigatorController(), this, nullptr);
	}
}

//====================================================================================================================================//
void AHW_Character::OnHealthChange(UHW_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

	if (HealthComponent->IsDead())
	{
		PlayVoiceSound(DeadSound);

		if (GetCharacterType() == EHW_CharacteraType::CharacteraType_Player)
		{
			if (IsValid(GameModeReference))
			{
				GameModeReference->GameOver(this);
			}
		}
	}
	else
	{
		PlayVoiceSound(HurtSound);
	}
}

//====================================================================================================================================//
// Called every frame
void AHW_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bUltimateWithTick && bIsUsingUltimate)
	{
		UpdateUltimateDuration(DeltaTime);
	}

}

//====================================================================================================================================//
// Called to bind functionality to input
void AHW_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Camera
	PlayerInputComponent->BindAxis("LookUp", this, &AHW_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &ACharacter::AddControllerYawInput);
	//Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AHW_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHW_Character::MoveRight);
	//Actions
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHW_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHW_Character::StopJumping);
	PlayerInputComponent->BindAction("WeaponAction", IE_Pressed, this, &AHW_Character::StartWeaponAction);
	PlayerInputComponent->BindAction("WeaponAction", IE_Released, this, &AHW_Character::StopWeaponAction);
	PlayerInputComponent->BindAction("WeaponChange", IE_Pressed, this, &AHW_Character::ChangeWeapon);
	PlayerInputComponent->BindAction("Meele", IE_Pressed, this, &AHW_Character::StartMeele);	
	PlayerInputComponent->BindAction("Ultimate", IE_Pressed, this, &AHW_Character::StartUltimate);	
	PlayerInputComponent->BindAction("Exit", IE_Pressed, this, &AHW_Character::GoToMainMenu);
	FInputActionBinding& toggle = PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AHW_Character::Pause);
	toggle.bExecuteWhenPaused = true;
}

//====================================================================================================================================//
void AHW_Character::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value * Speed);
}

//====================================================================================================================================//
void AHW_Character::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value * Speed);
}

//====================================================================================================================================//
void AHW_Character::Jump()
{
	Super::Jump();
}

//====================================================================================================================================//
void AHW_Character::StopJumping()
{
	Super::StopJumping();
}

//====================================================================================================================================//
void AHW_Character::StartWeaponAction()
{
	if (!bCanUseWeapon)
	{
		return;
	}

	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartAction();

		if (bIsUsingUltimate)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AutomaticShoot, CurrentWeapon, &AHW_Weapon::StartAction, UltimateShootFrequency, true);
		}

	}
}

//====================================================================================================================================//
void AHW_Character::StopWeaponAction()
{
	if (!bCanUseWeapon)
	{
		return;
	}

	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopAction();

		if (bIsUsingUltimate)
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AutomaticShoot);
		}

	}
}

//====================================================================================================================================//
void AHW_Character::AddControllerPitchInput(float value)
{
	Super::AddControllerPitchInput(bIsLookInversion ? -value : value);
}

//====================================================================================================================================//
void AHW_Character::AddKey(FName NewKey)
{
	DoorKeys.Add(NewKey);
}

//====================================================================================================================================//
bool AHW_Character::HasKey(FName KeyTag)
{
	return DoorKeys.Contains(KeyTag);
}

//====================================================================================================================================//
bool AHW_Character::TryAddHealth(float HealthToAdd)
{
	return HealthComponent->TryAddHealth(HealthToAdd);
}

//====================================================================================================================================//
void AHW_Character::SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState)
{
	MeleeDetectorComponent->SetCollisionEnabled(NewCollisionState);
}

//====================================================================================================================================//
void AHW_Character::SetMeleeState(bool NewState)
{
	bIsDoingMelee = NewState;
	bCanUseWeapon = !NewState;
}

//====================================================================================================================================//
void AHW_Character::ModifyDilation(float ModifyValue)
{
	Dilation = Dilation + ModifyValue;

	if (Dilation <= 0)
	{
		Dilation = 0.0f;
	}

	this->CustomTimeDilation = Dilation;
}

//====================================================================================================================================//
void AHW_Character::StopMoveCharacter(float NewSpeed, bool UseWeapon)
{
	bCanUseWeapon = UseWeapon;
	Speed = NewSpeed;
}

//====================================================================================================================================//
float AHW_Character::GetCurrentComboMultiplier()
{
	return CurrentComboMultiplier;
}

//====================================================================================================================================//
void AHW_Character::SetComboEnable(bool bNewState)
{
	bIsComboEnable = bNewState;
}

//====================================================================================================================================//
void AHW_Character::ResetCombo()
{
	SetComboEnable(false);
	CurrentComboMultiplier = 1.0f;
}

//====================================================================================================================================//
float AHW_Character::GetHealth()
{
	return HealthComponent->GetHealth();
}

//====================================================================================================================================//
float AHW_Character::GetMaxHealth()
{
	return HealthComponent->GetMaxHealth();
}

//====================================================================================================================================//
void AHW_Character::GainUltimateXP(float XPGained)
{
	if (bCanUseUltimate || bIsUsingUltimate)
	{
		return;
	}

	CurrentUltimateXP = FMath::Clamp(CurrentUltimateXP + XPGained, 0.0f, MaxUltimateExp);
	OnUltimateUpdateDelegate.Broadcast(CurrentUltimateXP, MaxUltimateExp);

	if (CurrentUltimateXP == MaxUltimateExp)
	{
		bCanUseUltimate = true;
		OnUltimateStatusDelegate.Broadcast(true);
	}

	BP_GainUltimateXP(XPGained);
}

//====================================================================================================================================//
void AHW_Character::UpdateUltimateDuration(float Value)
{
	CurrentUltimateDuration = FMath::Clamp(CurrentUltimateDuration - Value, 0.0f, MaxUltimateDuration);
	OnUltimateUpdateDelegate.Broadcast(CurrentUltimateDuration, MaxUltimateDuration);
	BP_UpdateUltimateDuration(Value);

	if (CurrentUltimateDuration == 0.0f)
	{
		bIsUsingUltimate = false;
		CurrentUltimateXP = 0.0f;
		OnUltimateStatusDelegate.Broadcast(false);

		GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;
		PlayRate = 1.0f;
		DilationIteration(1.0f);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AutomaticShoot);

		if (!bUltimateWithTick)
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Ultimate);
		}

		BP_StopUltimate();
	}
}

//====================================================================================================================================//
void AHW_Character::UpdateUltimateDurationWithTimer()
{
	UpdateUltimateDuration(UltimateFrequency);
}
