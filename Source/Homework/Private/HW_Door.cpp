// Fill out your copyright notice in the Description page of Project Settings.


#include "HW_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "HW_Character.h"

// Sets default values
AHW_Door::AHW_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustromRoot"));
	RootComponent = CustomRootComponent;

	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameComponent->SetupAttachment(CustomRootComponent);

	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorComponent->SetupAttachment(CustomRootComponent);

	KeyZoneColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyZoneCollider"));
	KeyZoneColliderComponent->SetupAttachment(CustomRootComponent);	
	KeyZoneColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KeyZoneColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	KeyZoneColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);


	OpenAngle = -90.0f;
	DoorTag = "KeyA";
}

// Called when the game starts or when spawned
void AHW_Door::BeginPlay()
{
	Super::BeginPlay();	
	KeyZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AHW_Door::CheckKeyFromPlayer);
}

void AHW_Door::OpenDoor()
{
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
	DoorComponent->SetRelativeRotation(NewRotation);
}

void AHW_Door::CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor)) 
	{
		AHW_Character* OverlappedCharacter = Cast<AHW_Character>(OtherActor);		
		if (IsValid(OverlappedCharacter))
		{
			bool bIsPlayer = OverlappedCharacter->GetCharacterType() == EHW_CharacteraType::CharacteraType_Player;
			if (OverlappedCharacter->HasKey(DoorTag) && bIsPlayer) {
				OpenDoor();
			}
		}
	}
}

