// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HW_Enemy.h"
#include "Weapon/HW_Rifle.h"
#include "HW_Character.h"
#include "Components/HW_HealthComponent.h"
#include "Items/HW_Item.h"
#include "AIModule/Classes/Perception/AISense_Damage.h"
#include "Enemy/Controller/HW_AIController.h"
#include "Enemy/HW_BotSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Core/HW_GameInstance.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/Enemy/HW_EnemyHealthBar.h"
#include "Core/HW_GameMode.h"
#include "Items/HW_HealthBox.h"


AHW_Enemy::AHW_Enemy() 
{
	bLoopPath = false;
	DirectionIndex = 1;
	WaitingTimeOnPathPoint = 1.0f;
	XPValue = 20.0f;
	LootProbability = 100.0f;	

	WidgetHealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetHealtBarComponent"));	
	WidgetHealthBarComponent->SetupAttachment(RootComponent);
}

void AHW_Enemy::BeginPlay()
{
	Super::BeginPlay();
	MyAIController = Cast<AHW_AIController>(GetController());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHW_BotSpawner::StaticClass(), BotSpawners);

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AHW_Enemy::HealthChanged);
	HealthComponent->OnDeadDelegate.AddDynamic(this, &AHW_Enemy::GiveXP);

	UUserWidget* WidgetObjet = WidgetHealthBarComponent->GetUserWidgetObject();
	if (IsValid(WidgetObjet))
	{
		EnemyHealthBar = Cast<UHW_EnemyHealthBar>(WidgetObjet);
		if (IsValid(EnemyHealthBar))
		{
			HealthComponent->OnHealthUpdateDelegate.AddDynamic(EnemyHealthBar, &UHW_EnemyHealthBar::UpdateHealth);
			HideHealthBar();
		}
		
	}
}

void AHW_Enemy::GiveXP(AActor* DamageCauser)
{
	AHW_Rifle* PossibleRifle = Cast<AHW_Rifle>(DamageCauser);
	if (IsValid(PossibleRifle))
	{
		AHW_Character* RifleOwner = Cast<AHW_Character>(PossibleRifle->GetOwner());
		if (IsValid(RifleOwner) && (RifleOwner->GetCharacterType() == EHW_CharacteraType::CharacteraType_Player))
		{
			RifleOwner->GainUltimateXP(XPValue);
			TrySpawnLoot();
		}
		
	}

	BP_GiveXP(DamageCauser);	

	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->AddEnemyDefeatedToCounter();
	}
}

bool AHW_Enemy::TrySpawnLoot()
{
	if (!IsValid(LootItemClass))
	{
		return false;
	}

	float SelectedProbability = FMath::RandRange(0.0f, 100.0f);
	if (SelectedProbability <= LootProbability)
	{		
		FActorSpawnParameters SpawnParameters;		
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AHW_Item>(LootItemClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);		
	}

	return true;
}


void AHW_Enemy::HealthChanged(UHW_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!IsValid(MyAIController))
	{
		return;
	}

	if (bIsShowingHealthBar)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HideHealthBar);
	}
	else
	{
		ShowHealthBar();
	}
		
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_HideHealthBar, this, &AHW_Enemy::HideHealthBar, 1.0f, false);


	if (CurrentHealthComponent->IsDead())
	{
		MyAIController->DeactivateAIPerception();
		MyAIController->UnPossess();	
		SetAlert(false);
		HideHealthBar();
	}
	else
	{
		AHW_Rifle* Rifle = Cast<AHW_Rifle>(DamageCauser);
		if (IsValid(Rifle))
		{
			AActor* RifleOwner = Rifle->GetOwner();
			MyAIController->SetReceiveDamage(true);
			UAISense_Damage::ReportDamageEvent(GetWorld(), this, RifleOwner, Damage, RifleOwner->GetActorLocation(), FVector::ZeroVector);

			for (AActor* Spawner : BotSpawners)
			{
				AHW_BotSpawner* BotSpwaner = Cast<AHW_BotSpawner>(Spawner);
				BotSpwaner->SetSpawnerStatus(true);
			}
		}
	}
}

void AHW_Enemy::HideHealthBar()
{
	EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
	bIsShowingHealthBar = false;
}

void AHW_Enemy::ShowHealthBar()
{
	EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
	bIsShowingHealthBar = true;
}

void AHW_Enemy::SetAlert(bool bValue)
{
	bIsAlert = bValue;

	if (IsValid(GameModeReference))
	{
		GameModeReference->CheckAlertMode();
	}
}
