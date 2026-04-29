// RaceGate.cpp — checkpoint, start, and finish trigger volumes that drive the RaceManager.

#include "RaceGate.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "GameFramework/Pawn.h"
#include "HoverAIRacer.h"
#include "RaceManager.h"

/** @brief Build the gate with a scene root, mesh visual, and an overlap-only trigger box. */
ARaceGate::ARaceGate()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMesh"));
    GateMesh->SetupAttachment(Root);
    GateMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(Root);
    TriggerBox->SetBoxExtent(FVector(250.0f, 350.0f, 250.0f));
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    TriggerBox->SetGenerateOverlapEvents(true);

    TriggeringActorClass = APawn::StaticClass();
}

/** @brief Re-assert collision settings, bind the overlap delegate, and locate the RaceManager. */
void ARaceGate::BeginPlay()
{
    Super::BeginPlay();

    if (GateMesh)
    {
        GateMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    if (TriggerBox)
    {
        TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
        TriggerBox->SetGenerateOverlapEvents(true);
        TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARaceGate::OnTriggerBeginOverlap);
    }

    if (!RaceManager)
    {
        RaceManager = FindRaceManagerInLevel();
    }
}

/**
 * @brief Filter overlaps to non-AI pawns and forward to RaceManager::HandleGateTriggered.
 *        AI racers follow the spline and bypass gates.
 */
void ARaceGate::OnTriggerBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this)
    {
        return;
    }

    if (TriggeringActorClass && !OtherActor->IsA(TriggeringActorClass))
    {
        return;
    }

    if (OtherActor->IsA<AHoverAIRacer>())
    {
        return;
    }

    if (!RaceManager)
    {
        RaceManager = FindRaceManagerInLevel();
    }

    if (RaceManager)
    {
        RaceManager->HandleGateTriggered(this, OtherActor);
    }
}

/** @brief Find the first ARaceManager in the level, or nullptr if none exists. */
ARaceManager* ARaceGate::FindRaceManagerInLevel() const
{
    const UWorld* World = GetWorld();
    if (!World)
    {
        return nullptr;
    }

    for (TActorIterator<ARaceManager> It(World); It; ++It)
    {
        return *It;
    }

    return nullptr;
}
