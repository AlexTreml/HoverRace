// RespawnVolume.cpp — overlap volume that calls RaceManager::ResetVehiclePosition on the player pawn.

#include "RespawnVolume.h"

#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "GameFramework/Pawn.h"
#include "RaceManager.h"

/** @brief Build the volume with an overlap-only trigger box and bind the begin-overlap delegate. */
ARespawnVolume::ARespawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create trigger box
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	// Set up box extent (can be adjusted in editor)
	TriggerBox->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));

	// Set collision to overlap with vehicles/pawns
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	// Alternative: If the above causes too many overlaps, use this instead:
	// TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	// TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Overlap);
	// TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);

	// Generate overlap events
	TriggerBox->SetGenerateOverlapEvents(true);

	// Bind overlap event
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARespawnVolume::OnTriggerBeginOverlap);
}

/** @brief Cache the RaceManager reference on play start. */
void ARespawnVolume::BeginPlay()
{
	Super::BeginPlay();

	if (!RaceManager)
	{
		FindRaceManager();
	}
}

/** @brief On pawn overlap, call RaceManager::ResetVehiclePosition. */
void ARespawnVolume::OnTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Only respawn if it's a pawn (player vehicle)
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn)
	{
		return;
	}

	// Make sure we have a race manager
	if (!RaceManager)
	{
		FindRaceManager();
	}

	if (!RaceManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("RespawnVolume: No RaceManager found in level!"));
		return;
	}

	// Trigger respawn
	RaceManager->ResetVehiclePosition();

	if (bShowDebugMessage && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			(uint64)-1,
			2.0f,
			FColor::Yellow,
			TEXT("Respawn Volume Triggered!")
		);
	}
}

/** @brief Locate the first ARaceManager in the level. */
void ARespawnVolume::FindRaceManager()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	for (TActorIterator<ARaceManager> It(World); It; ++It)
	{
		RaceManager = *It;
		break;
	}
}
