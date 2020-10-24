// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HW_Character.generated.h"



class USpringArmComponent;
class UCameraComponent;
class AHW_Weapon;
class UAnimMontage;
class UAnimInstance;
class UHW_HealthComponent;
class AHW_GameMode;
class UHW_GameInstance;
class UHW_PauseMenuWidget;
class UUserWidget;
class UAudioComponent;
class USoundCue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUltimateUpdateSignature, float, CurrentUltimateXP, float, MaxUltimateXP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateStatusSignature, bool, bIsAvailable);


UENUM(Blueprintable)
enum class EHW_CharacteraType : uint8
{
	CharacteraType_Player			UMETA(DisplayName = "Player"),
	CharacteraType_Enemy		UMETA(DisplayName = "Enemy"),
	
};



UCLASS()
class HOMEWORK_API AHW_Character : public ACharacter
{
	GENERATED_BODY()

protected:
	

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
		FName FPSCameraSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Melee")
		FName MeleeSocketName;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Levels")
		FName MainMenuMapName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
		bool bIsLookInversion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
		bool bUseFirstPersonView;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
		bool bIsDoingMelee;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
		bool bCanMakeCombos;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
		bool bIsComboEnable;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
		bool bCanUseUltimate;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
		bool bIsUsingUltimate;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
		bool bCanUseWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Over")
		bool bHasToDestroy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate")
		bool bUltimateWithTick;		

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
		float MeleeDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = bCanMakeCombos, ClampMin = 1.0, UIMin = 1.0), Category = "Melee")
		float MaxComboMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = bCanMakeCombos, ClampMin = 1.0, UIMin = 1.0), Category = "Melee")
		float CurrentComboMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0.1, UIMin = 0.1, ClampMax = 1.0, UIMax = 1.0), Category = "Mine")
		float Dilation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0, UIMin = 0, ClampMax = 1.0, UIMax = 1.0), Category = "Barrel")
		float Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0, UIMin = 0), Category = "Ultimate")
		float MaxUltimateExp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate")
		float CurrentUltimateXP;
	
	UPROPERTY(BlueprintReadOnly, meta = (ClampMin = 0.0f, UIMin = 0.0f), Category = "Ultimate|Time")
		float MaxUltimateDuration;

	UPROPERTY(BlueprintReadOnly, meta = (ClampMin = 0.0f, UIMin = 0.0f), Category = "Ultimate|Time")
		float CurrentUltimateDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate|Time")
		float UltimateFrequency;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f, UIMin = 0.0f), Category = "Ultimate|Abilities")
		float UltimateWalkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f, UIMin = 0.0f), Category = "Ultimate|Abilities")
		float UltimateShootFrequency;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate|Abilities")
		float NormalWalkSpeed;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Ultimate|Abilities")
		float UltimatePlayRate;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate|Abilities")
		float PlayRate;
	

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* TPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCapsuleComponent* MeleeDetectorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UHW_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAudioComponent* StepSoundComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAudioComponent* VoicesSoundComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
		TArray<FName> DoorKeys;	

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
		EHW_CharacteraType CharacterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	 	TArray<TSubclassOf<AHW_Weapon>> WeaponClass;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		AHW_Weapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
		UAnimMontage* MeeleMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
		UAnimMontage* UltimateMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pause")
		TSubclassOf<UHW_PauseMenuWidget> PauseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pause")
		UHW_PauseMenuWidget* PauseWidget;


	
	UAnimInstance* MyAnimInstance;
	AHW_GameMode* GameModeReference;
	UHW_GameInstance* GameInstanceReference;

	FTimerHandle TimerHandle_Ultimate;
	FTimerHandle TimerHandle_AutomaticShoot;
	FTimerHandle TimerHandle_BeginUltimateBehaviour;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
		USoundCue* HurtSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
		USoundCue* DeadSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
		USoundCue* UltimateSound;
	
	
public:

	UPROPERTY(BlueprintAssignable)
		FOnUltimateUpdateSignature OnUltimateUpdateDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnUltimateStatusSignature OnUltimateStatusDelegate;


public:
	// Sets default values for this character's properties
	AHW_Character();

	virtual FVector GetPawnViewLocation() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;		
	virtual void Jump () override;
	virtual void StopJumping() override;
	void InitializaReferences();
	void MoveForward(float value);
	void MoveRight(float value);
	UFUNCTION(BlueprintCallable)
		void StartWeaponAction();
	UFUNCTION(BlueprintCallable)
		void StopWeaponAction();	
	void CreateInitialWeapon();
	void ChangeWeapon();
	UFUNCTION(BlueprintCallable)
		void StartMeele();
	void StopMeele();
	void StartUltimate();	
	void StopUltimate();
	void GoToMainMenu();
	void Pause();

	UFUNCTION()
		void MakeMeleeDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnHealthChange(UHW_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AddControllerPitchInput(float value) override;

	void AddKey(FName NewKey);

	bool HasKey(FName KayTag);

	bool TryAddHealth(float HealthToAdd);

	float GetCurrentComboMultiplier();

	void SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState);

	void SetMeleeState(bool NewState);		

	void ModifyDilation(float ModifyValue);

	void StopMoveCharacter(float NewSpeed, bool UseWeapon);

	UFUNCTION(BlueprintCallable)
		void SetComboEnable(bool bNewState);
	
	UFUNCTION(BlueprintCallable)
		void ResetCombo();

	bool HasToDestroy() { return bHasToDestroy; };

	float GetHealth();

	float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
		void GainUltimateXP(float XPGained);

		void UpdateUltimateDuration(float Value);

		void UpdateUltimateDurationWithTimer();

		void BeginUltimateBehaviour();

		void DilationIteration(float CustomIterator);

		void Healing();

		UFUNCTION(BlueprintCallable)
			EHW_CharacteraType GetCharacterType() { return CharacterType; };	

		UHW_HealthComponent* GetHealthComponent() { return HealthComponent; };

		void PlayStepSound();

		void PlayVoiceSound(USoundCue* VoiceSound);

protected:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BP_GainUltimateXP(float XPGained);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BP_StartUltimate();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BP_StopUltimate();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BP_UpdateUltimateDuration(float Value);


};
