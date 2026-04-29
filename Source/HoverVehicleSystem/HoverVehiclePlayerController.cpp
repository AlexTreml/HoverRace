// HoverVehiclePlayerController.cpp — bridges the player pawn, RaceManager, and HUD widget.

#include "HoverVehiclePlayerController.h"

#include "EngineUtils.h"
#include "HoverRaceUI.h"
#include "RaceManager.h"
#include "Kismet/GameplayStatics.h"

/** @brief Set GameOnly input mode, create the HUD widget, cache references, and push initial UI state. */
void AHoverVehiclePlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeGameOnly());
    bShowMouseCursor = false;

    if (RaceUIClass)
    {
        RaceUI = CreateWidget<UHoverRaceUI>(this, RaceUIClass);
        if (RaceUI)
        {
            RaceUI->AddToViewport();
        }
    }

    CacheRuntimeReferences();
    UpdateUI();
}

/** @brief Per-frame: refresh references and push current race data into the HUD. */
void AHoverVehiclePlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    CacheRuntimeReferences();
    UpdateUI();
}

/** @brief Cache the controlled pawn whenever the controller possesses one. */
void AHoverVehiclePlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    ControlledVehicle = InPawn;
}

/** @brief Bind the ResetVehicle action input. */
void AHoverVehiclePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent)
    {
        InputComponent->BindAction("ResetVehicle", IE_Pressed, this, &AHoverVehiclePlayerController::ResetVehicle);
    }
}

/** @brief Lazy-cache ControlledVehicle and RaceManager references. */
void AHoverVehiclePlayerController::CacheRuntimeReferences()
{
    if (!ControlledVehicle)
    {
        ControlledVehicle = GetPawn();
    }

    if (!RaceManager)
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
}

/**
 * @brief Pull speed from the pawn (via Blueprint GetCurrentForwardSpeed) and race data
 *        from the RaceManager, then forward both to the HUD widget.
 */
void AHoverVehiclePlayerController::UpdateUI()
{
    if (!RaceUI)
    {
        return;
    }

    if (ControlledVehicle)
    {
        UFunction* Function = ControlledVehicle->FindFunction(FName("GetCurrentForwardSpeed"));
        if (Function)
        {
            struct { double ReturnValue; } Params;
            ControlledVehicle->ProcessEvent(Function, &Params);
            RaceUI->UpdateSpeed(Params.ReturnValue);
        }
    }

    if (RaceManager)
    {
        RaceUI->UpdateRaceState(
            RaceManager->GetRaceState(),
            RaceManager->GetCountdownRemaining(),
            RaceManager->GetCurrentRaceTime(),
            RaceManager->GetFinalRaceTime(),
            RaceManager->GetBestRaceTime(),
            RaceManager->GetPassedCheckpointCount(),
            RaceManager->GetTotalCheckpointCount(),
            RaceManager->GetCurrentLap(),
            RaceManager->GetRequiredLaps(),
            RaceManager->GetPlayerRacePosition(),
            RaceManager->GetTotalRacers(),
            RaceManager->GetCurrentLapTime(),
            RaceManager->GetBestLapTime());
    }
}

/** @brief Forward the ResetVehicle input to RaceManager::ResetVehiclePosition. */
void AHoverVehiclePlayerController::ResetVehicle()
{
    if (RaceManager)
    {
        RaceManager->ResetVehiclePosition();
    }
}
