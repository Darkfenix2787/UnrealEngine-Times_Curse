// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HW_Item.h"
#include "Components/SphereComponent.h"
#include "HW_Character.h"
#include "Core/HW_GameMode.h"

// Sets default values
AHW_Item::AHW_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	
	MainColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	RootComponent = MainColliderComponent;
}

// Called when the game starts or when spawned
void AHW_Item::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<AHW_GameMode>(GetWorld()->GetAuthGameMode());
	
}


// Called every frame
void AHW_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHW_Item::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor)) {
		AHW_Character* OverlappedCharacter = Cast<AHW_Character>(OtherActor);
		if(IsValid(OverlappedCharacter) && (OverlappedCharacter->GetCharacterType() == EHW_CharacteraType::CharacteraType_Player) )
			Pickup(OverlappedCharacter);
	}	
}

void AHW_Item::Pickup(AHW_Character* PickupCharacter)
{
	BP_PickUp(PickupCharacter);
}

