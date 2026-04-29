#include "RaceManager.h"

#include "Algo/Sort.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "RaceResultsWidget.h"
#include "EngineUtils.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "HoverAIRacer.h"
#include "HoverRaceSpline.h"
#include "RaceGate.h"

// RaceManager.cpp — central race lifecycle, state machine, timing, and results.

DEFINE_LOG_CATEGORY_STATIC(LogRaceManager, Log, All);

/** @brief Enable Tick on the actor. */
ARaceManager::ARaceManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

/** @brief Collect gates and racers, then optionally schedule the countdown. */
void ARaceManager::BeginPlay()
{
    Super::BeginPlay();

    CollectGates();
    CollectRacers();
    ResetRace();

    if (bEnableDebugMessages)
    {
        const FString DebugText = FString::Printf(TEXT("RaceManager ready. Checkpoints: %d"), CheckpointGates.Num());
        UE_LOG(LogRaceManager, Log, TEXT("%s"), *DebugText);
        // if (GEngine)
        // {
        //     GEngine->AddOnScreenDebugMessage((uint64)-1, 4.0f, FColor::Green, DebugText);
        // }
    }

    if (bAutoStartCountdownOnBeginPlay)
    {
        if (PreRaceDelay > 0.0f)
        {
            FTimerHandle PreRaceTimerHandle;
            GetWorldTimerManager().SetTimer(
                PreRaceTimerHandle,
                this,
                &ARaceManager::StartCountdown,
                PreRaceDelay,
                false
            );
        }
        else
        {
            StartCountdown();
        }
    }
}

/**
 * @brief Per-frame state-machine update: input lock, countdown, race timer, freeze, kill-z respawn.
 */
void ARaceManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Re-apply movement lock each tick so late pawn possession picks up the correct state.
    const bool bShouldLockMovement =
        (RaceState == ERaceState::Countdown && bLockPlayerInputDuringCountdown) ||
        (RaceState == ERaceState::WaitingToStart && PreRaceDelay > 0.0f) ||
        bFreezeVehicle;
    SetPlayerInputLocked(bShouldLockMovement);

    if (RaceState == ERaceState::Countdown)
    {
        CountdownRemaining -= DeltaTime;
        if (CountdownRemaining <= 0.0f)
        {
            StartRaceNow();
        }
        return;
    }

    if (RaceState == ERaceState::Racing || RaceState == ERaceState::Finished)
    {
        CurrentRaceTime += DeltaTime;
        if (RaceState == ERaceState::Racing)
        {
            CurrentLapTime += DeltaTime;
            UpdatePlayerPosition();
        }
    }

    // Keep vehicle stationary after freeze — hover system re-applies forces every tick
    if (bFreezeVehicle)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            APlayerController* PC = World->GetFirstPlayerController();
            if (PC)
            {
                if (APawn* Vehicle = PC->GetPawn())
                {
                    if (UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(Vehicle->GetRootComponent()))
                    {
                        FVector Vel = Root->GetPhysicsLinearVelocity();
                        Vel.X = 0.f;
                        Vel.Y = 0.f;
                        Root->SetPhysicsLinearVelocity(Vel);
                    }
                }
            }
        }
    }

    // Auto-respawn if vehicle falls below kill height
    if (bAutoRespawnOnFall)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            APlayerController* PC = World->GetFirstPlayerController();
            if (PC)
            {
                APawn* Vehicle = PC->GetPawn();
                if (Vehicle)
                {
                    const float VehicleZ = Vehicle->GetActorLocation().Z;
                    if (VehicleZ < KillZHeight)
                    {
                        ResetVehiclePosition();

                        if (bEnableDebugMessages && GEngine)
                        {
                            GEngine->AddOnScreenDebugMessage(
                                (uint64)-1,
                                2.0f,
                                FColor::Orange,
                                FString::Printf(TEXT("Auto-respawn: fell below %.0f"), KillZHeight)
                            );
                        }
                    }
                }
            }
        }
    }
}

/** @brief Enter the Countdown state and start the per-tick countdown timer. */
void ARaceManager::StartCountdown()
{
    if (RaceState == ERaceState::Countdown || RaceState == ERaceState::Racing)
    {
        return;
    }

    CollectGates();

    NextCheckpointArrayIndex = 0;
    CurrentRaceTime = 0.0f;
    FinalRaceTime = 0.0f;

    RaceState = ERaceState::Countdown;
    CountdownRemaining = FMath::Max(0.0f, CountdownDuration);

    SetPlayerInputLocked(bLockPlayerInputDuringCountdown);
    BP_OnCountdownStarted(CountdownRemaining);

    if (bEnableDebugMessages)
    {
        const FString DebugText = FString::Printf(TEXT("Race countdown started: %.1fs"), CountdownRemaining);
        UE_LOG(LogRaceManager, Log, TEXT("%s"), *DebugText);
        // if (GEngine)
        // {
        //     GEngine->AddOnScreenDebugMessage((uint64)-1, 2.0f, FColor::Yellow, DebugText);
        // }
    }

    if (CountdownRemaining <= KINDA_SMALL_NUMBER)
    {
        StartRaceNow();
    }
}

/** @brief Reset all race state back to WaitingToStart and lock player movement. */
void ARaceManager::ResetRace()
{
    RaceState = ERaceState::WaitingToStart;
    CountdownRemaining = 0.0f;
    CurrentRaceTime = 0.0f;
    CurrentLapTime = 0.0f;
    LastLapTime = 0.0f;
    FinalRaceTime = 0.0f;
    CurrentLap = 0;
    NextCheckpointArrayIndex = 0;

    // Keep pod stationary until the next countdown/start.
    SetPlayerInputLocked(true);
}

/**
 * @brief Dispatch a gate overlap to the appropriate handler:
 *        Start → optional restart, Checkpoint → advance index, Finish → next lap or finish.
 */
void ARaceManager::HandleGateTriggered(ARaceGate* Gate, AActor* TriggeringActor)
{
    if (!Gate || !TriggeringActor)
    {
        return;
    }

    if (bEnableDebugMessages)
    {
        const FString GateTypeString = StaticEnum<ERaceGateType>()
            ? StaticEnum<ERaceGateType>()->GetValueAsString(Gate->GetGateType())
            : TEXT("UnknownGate");
        const FString DebugText = FString::Printf(
            TEXT("Gate hit: %s by %s"),
            *GateTypeString,
            *GetNameSafe(TriggeringActor)
        );
        UE_LOG(LogRaceManager, Log, TEXT("%s"), *DebugText);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage((uint64)-1, 1.5f, FColor::Cyan, DebugText);
        }
    }

    switch (Gate->GetGateType())
    {
        case ERaceGateType::Start:
        {
            // Start gates are optional visual markers.
            // Race start is handled by BeginPlay countdown flow, not gate overlap.
            if (RaceState == ERaceState::Finished && bAllowRestartFromStartGate)
            {
                ResetRace();
                StartCountdown();
            }
            else if (bEnableDebugMessages && GEngine)
            {
                GEngine->AddOnScreenDebugMessage((uint64)-1, 1.5f, FColor::Silver, TEXT("Start gate is visual-only before race start"));
            }
            break;
        }

        case ERaceGateType::Checkpoint:
        {
            if (RaceState != ERaceState::Racing)
            {
                if (bEnableDebugMessages && GEngine)
                {
                    GEngine->AddOnScreenDebugMessage((uint64)-1, 1.5f, FColor::Orange, TEXT("Checkpoint ignored: race not in Racing state"));
                }
                return;
            }

            if (CheckpointGates.IsEmpty())
            {
                return;
            }

            if (!CheckpointGates.IsValidIndex(NextCheckpointArrayIndex))
            {
                return;
            }

            const ARaceGate* ExpectedGate = CheckpointGates[NextCheckpointArrayIndex];
            const int32 ExpectedIndex = ExpectedGate ? ExpectedGate->GetCheckpointIndex() : NextCheckpointArrayIndex;
            const int32 TriggeredIndex = Gate->GetCheckpointIndex();

            // Ignore stale retriggers from an already-passed checkpoint.
            if (TriggeredIndex < ExpectedIndex)
            {
                return;
            }

            if (TriggeredIndex > ExpectedIndex)
            {
                if (bEnableDebugMessages && GEngine)
                {
                    const FString DebugText = FString::Printf(
                        TEXT("Wrong checkpoint order. Expected index %d, got %d"),
                        ExpectedIndex,
                        TriggeredIndex
                    );
                    GEngine->AddOnScreenDebugMessage((uint64)-1, 2.0f, FColor::Red, DebugText);
                }
                return;
            }

            // Advance at least one step; if duplicate indices exist, consume all of them.
            ++NextCheckpointArrayIndex;
            while (CheckpointGates.IsValidIndex(NextCheckpointArrayIndex))
            {
                const ARaceGate* NextGate = CheckpointGates[NextCheckpointArrayIndex];
                if (!NextGate || NextGate->GetCheckpointIndex() != TriggeredIndex)
                {
                    break;
                }
                ++NextCheckpointArrayIndex;
            }

            BP_OnCheckpointPassed(GetPassedCheckpointCount(), GetTotalCheckpointCount());

            // Store checkpoint position for respawn
            LastCheckpointLocation = Gate->GetActorLocation();
            LastCheckpointRotation = Gate->GetActorRotation();

            if (bEnableDebugMessages && GEngine)
            {
                const FString DebugText = FString::Printf(
                    TEXT("Checkpoint OK: %d / %d"),
                    GetPassedCheckpointCount(),
                    GetTotalCheckpointCount()
                );
                GEngine->AddOnScreenDebugMessage((uint64)-1, 1.5f, FColor::Green, DebugText);
            }
            break;
        }

        case ERaceGateType::Finish:
        {
            if (RaceState != ERaceState::Racing)
            {
                if (bEnableDebugMessages && GEngine)
                {
                    GEngine->AddOnScreenDebugMessage((uint64)-1, 1.5f, FColor::Orange, TEXT("Finish ignored: race not in Racing state"));
                }
                return;
            }

            if (!AreAllCheckpointsPassed())
            {
                UE_LOG(LogRaceManager, Verbose, TEXT("Finish gate touched before all checkpoints were passed."));
                if (bEnableDebugMessages && GEngine)
                {
                    const FString DebugText = FString::Printf(
                        TEXT("Finish blocked: checkpoints %d/%d"),
                        GetPassedCheckpointCount(),
                        GetTotalCheckpointCount()
                    );
                    GEngine->AddOnScreenDebugMessage((uint64)-1, 2.0f, FColor::Red, DebugText);
                }
                return;
            }

            if (CurrentLap + 1 >= RequiredLaps)
            {
                FinishRace();
            }
            else
            {
                // Save lap time
                LastLapTime = CurrentLapTime;
                if (BestLapTime < 0.0f || CurrentLapTime < BestLapTime)
                {
                    BestLapTime = CurrentLapTime;
                }
                CurrentLapTime = 0.0f;

                CurrentLap++;
                NextCheckpointArrayIndex = 0;
                BP_OnLapCompleted(CurrentLap, RequiredLaps);
                if (bEnableDebugMessages && GEngine)
                {
                    const FString DebugText = FString::Printf(TEXT("Lap %d / %d"), CurrentLap, RequiredLaps);
                    GEngine->AddOnScreenDebugMessage((uint64)-1, 2.0f, FColor::Green, DebugText);
                }
            }
            break;
        }

        default:
            break;
    }
}

/** @brief True when every checkpoint gate has been passed in order. */
bool ARaceManager::AreAllCheckpointsPassed() const
{
    return NextCheckpointArrayIndex >= CheckpointGates.Num();
}

/** @brief Find every ARaceGate, store checkpoint gates sorted by index, cache start gate transform. */
void ARaceManager::CollectGates()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    CheckpointGates.Reset();

    // Reset start gate location in case gates have changed
    StartGateLocation = FVector::ZeroVector;
    StartGateRotation = FRotator::ZeroRotator;

    for (TActorIterator<ARaceGate> It(World); It; ++It)
    {
        ARaceGate* Gate = *It;
        if (!IsValid(Gate))
        {
            continue;
        }

        if (!Gate->GetRaceManager())
        {
            Gate->SetRaceManager(this);
        }

        if (Gate->GetGateType() == ERaceGateType::Checkpoint)
        {
            CheckpointGates.Add(Gate);
        }
        else if (Gate->GetGateType() == ERaceGateType::Start)
        {
            // Store start gate position for respawn fallback
            StartGateLocation = Gate->GetActorLocation();
            StartGateRotation = Gate->GetActorRotation();
        }
    }

    Algo::SortBy(CheckpointGates, [](const ARaceGate* Gate)
    {
        return Gate ? Gate->GetCheckpointIndex() : MAX_int32;
    });

    for (int32 Index = 1; Index < CheckpointGates.Num(); ++Index)
    {
        if (CheckpointGates[Index - 1] && CheckpointGates[Index] &&
            CheckpointGates[Index - 1]->GetCheckpointIndex() == CheckpointGates[Index]->GetCheckpointIndex())
        {
            UE_LOG(
                LogRaceManager,
                Warning,
                TEXT("Duplicate checkpoint index %d detected."),
                CheckpointGates[Index]->GetCheckpointIndex()
            );
        }
    }
}

/** @brief Transition to Racing, start each AI racer, and unlock player movement. */
void ARaceManager::StartRaceNow()
{
    RaceState = ERaceState::Racing;
    CountdownRemaining = 0.0f;
    CurrentRaceTime = 0.0f;
    NextCheckpointArrayIndex = 0;

    // Start all AI racers now that countdown is done
    for (AHoverAIRacer* AI : AIRacers)
    {
        if (AI)
        {
            AI->bFinishedRace = false;
            AI->FinishRaceTime = 0.0f;
            AI->StartRacing();
        }
    }

    SetPlayerInputLocked(false);
    BP_OnRaceStarted();
}

/** @brief Record an AI's finish; build final results once every racer is done. */
void ARaceManager::RegisterAIFinish(AHoverAIRacer* Racer)
{
    if (!Racer) return;

    if (bEnableDebugMessages && GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            (uint64)-1, 3.0f, FColor::Cyan,
            FString::Printf(TEXT("AI Finished: %s - %.2fs"), *Racer->RacerName, Racer->FinishRaceTime)
        );
    }

    // Check if all racers have finished
    bool bAllFinished = true;
    for (AHoverAIRacer* AI : AIRacers)
    {
        if (AI && !AI->bFinishedRace)
        {
            bAllFinished = false;
            break;
        }
    }

    // Only build results once player has also finished (RaceState transitions
    // to Finished in FinishRace). Otherwise the player's hard-coded "finished"
    // result records 1st place with 0 time. The race-end-delay timer in
    // OnRaceEndDelayComplete acts as the fallback once player crosses the line.
    if (bAllFinished && RaceState == ERaceState::Finished)
    {
        BuildFinalResults();
    }
}

/**
 * @brief Build FinalResults — player + AI rows, sorted by finish time, then assign positions.
 */
void ARaceManager::BuildFinalResults()
{
    FinalResults.Reset();

    // Player result
    FRacerResult PlayerResult;
    PlayerResult.RacerName = PlayerName;
    PlayerResult.FinishTime = FinalRaceTime;
    PlayerResult.bIsPlayer = true;
    PlayerResult.bFinished = true;
    PlayerResult.SplineProgress = 1.0f;
    FinalResults.Add(PlayerResult);

    // AI results
    for (AHoverAIRacer* AI : AIRacers)
    {
        if (!AI) continue;
        FRacerResult AIResult;
        AIResult.RacerName = AI->RacerName;
        AIResult.bIsPlayer = false;
        AIResult.bFinished = AI->bFinishedRace;
        AIResult.FinishTime = AI->bFinishedRace ? AI->FinishRaceTime : -1.0f;
        AIResult.SplineProgress = static_cast<float>(AI->LapsCompleted) + AI->GetRaceProgress();
        FinalResults.Add(AIResult);
    }

    // Sort: finished first by time, then DNF by spline progress
    FinalResults.Sort([](const FRacerResult& A, const FRacerResult& B)
    {
        if (A.bFinished && B.bFinished) return A.FinishTime < B.FinishTime;
        if (A.bFinished) return true;
        if (B.bFinished) return false;
        return A.SplineProgress > B.SplineProgress;
    });

    for (int32 i = 0; i < FinalResults.Num(); ++i)
    {
        FinalResults[i].Position = i + 1;
    }
}

/** @brief Transition to Finished, record final/best times, and schedule the results timer. */
void ARaceManager::FinishRace()
{
    RaceState = ERaceState::Finished;
    FinalRaceTime = CurrentRaceTime;
    bFreezeVehicle = true;

    // Save final lap time
    LastLapTime = CurrentLapTime;
    if (BestLapTime < 0.0f || CurrentLapTime < BestLapTime)
    {
        BestLapTime = CurrentLapTime;
    }

    if (BestRaceTime < 0.0f || FinalRaceTime < BestRaceTime)
    {
        BestRaceTime = FinalRaceTime;
    }

    BP_OnRaceFinished(FinalRaceTime);

    // Coast for RaceEndDelay seconds then freeze + show results
    GetWorldTimerManager().SetTimer(
        RaceEndTimerHandle,
        this,
        &ARaceManager::OnRaceEndDelayComplete,
        RaceEndDelay,
        false
    );

    if (bEnableDebugMessages)
    {
        const FString DebugText = FString::Printf(TEXT("Race finished: %.2fs"), FinalRaceTime);
        UE_LOG(LogRaceManager, Log, TEXT("%s"), *DebugText);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage((uint64)-1, 4.0f, FColor::Green, DebugText);
        }
    }
}

/** @brief Call SetMovementLockedByRace on the controlled pawn (Blueprint function). */
void ARaceManager::SetPlayerInputLocked(bool bLocked)
{
    // Movement freeze only — other controller actions (pause etc.) continue to work.
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!PlayerController)
    {
        return;
    }

    APawn* ControlledPawn = PlayerController->GetPawn();
    if (!ControlledPawn)
    {
        return;
    }

    // Call Blueprint function SetMovementLockedByRace
    UFunction* Function = ControlledPawn->FindFunction(FName("SetMovementLockedByRace"));
    if (Function)
    {
        struct { bool bLocked; } Params;
        Params.bLocked = bLocked;
        ControlledPawn->ProcessEvent(Function, &Params);
    }
}

/** @brief Find every AHoverAIRacer and the level race spline; bind both to this manager. */
void ARaceManager::CollectRacers()
{
    AIRacers.Reset();
    for (TActorIterator<AHoverAIRacer> It(GetWorld()); It; ++It)
    {
        AHoverAIRacer* AI = *It;
        if (IsValid(AI))
        {
            AI->SetRaceManager(this);
            AI->RequiredLaps = RequiredLaps;
            AIRacers.Add(AI);
        }
    }

    // Find the race spline for player position tracking
    for (TActorIterator<AHoverRaceSpline> It(GetWorld()); It; ++It)
    {
        RaceSpline = *It;
        break;
    }
}

/** @brief Return total spline progress = lap count + fractional position along the spline. */
float ARaceManager::GetPlayerSplineProgress() const
{
    if (!RaceSpline) return 0.0f;

    UWorld* World = GetWorld();
    if (!World) return 0.0f;

    APlayerController* PC = World->GetFirstPlayerController();
    if (!PC) return 0.0f;

    APawn* Vehicle = PC->GetPawn();
    if (!Vehicle) return 0.0f;

    float SplineLength = RaceSpline->GetSplineLength();
    if (SplineLength <= 0.0f) return 0.0f;

    float PlayerDist = RaceSpline->GetClosestDistanceToWorldLocation(Vehicle->GetActorLocation());
    float Progress = PlayerDist / SplineLength;

    // Total progress includes completed laps
    return static_cast<float>(CurrentLap) + Progress;
}

/** @brief Compare player progress against each AI to compute and broadcast race position. */
void ARaceManager::UpdatePlayerPosition()
{
    float PlayerProgress = GetPlayerSplineProgress();

    int32 Position = 1;
    for (const AHoverAIRacer* AI : AIRacers)
    {
        if (!AI) continue;

        // AI that finished the race are always ahead
        if (AI->bFinishedRace)
        {
            Position++;
            continue;
        }

        float AIProgress = static_cast<float>(AI->LapsCompleted) + AI->GetRaceProgress();
        if (AIProgress > PlayerProgress)
        {
            Position++;
        }
    }

    if (Position != CurrentPlayerPosition)
    {
        CurrentPlayerPosition = Position;
        BP_OnPositionChanged(CurrentPlayerPosition, GetTotalRacers());
    }
}

// ========== UI ==========

/** @brief End-of-race timer callback: enable autopilot, build/show results, call StartAutopilot on the pawn. */
void ARaceManager::OnRaceEndDelayComplete()
{
    bAutopilot = true;

    // Build results if not already built (fallback in case AI didn't all finish)
    if (FinalResults.Num() == 0)
    {
        BuildFinalResults();
    }

    ShowResultsScreen();

    // Call StartAutopilot on the FlyingPawn Blueprint
    UWorld* World = GetWorld();
    if (World)
    {
        APlayerController* PC = World->GetFirstPlayerController();
        if (PC)
        {
            APawn* Vehicle = PC->GetPawn();
            if (Vehicle)
            {
                UFunction* Func = Vehicle->FindFunction(FName("StartAutopilot"));
                if (Func)
                {
                    Vehicle->ProcessEvent(Func, nullptr);
                }
            }
        }
    }
}

/** @brief Create the results widget, populate it, add to viewport, and switch to GameAndUI input. */
void ARaceManager::ShowResultsScreen()
{
    if (!ResultsScreenClass)
    {
        UE_LOG(LogRaceManager, Warning, TEXT("ShowResultsScreen: ResultsScreenClass not set in BP_RaceManager Details panel."));
        return;
    }

    UWorld* World = GetWorld();
    if (!World) return;

    APlayerController* PC = World->GetFirstPlayerController();
    if (!PC) return;

    URaceResultsWidget* ResultsWidget = CreateWidget<URaceResultsWidget>(PC, ResultsScreenClass);
    if (!ResultsWidget) return;

    ResultsScreenWidget = ResultsWidget;
    ResultsWidget->PopulateResults(FinalResults);
    ResultsWidget->AddToViewport();

    // Game and UI so camera keeps rendering and mouse works for results
    FInputModeGameAndUI InputMode;
    InputMode.SetWidgetToFocus(ResultsWidget->TakeWidget());
    PC->SetInputMode(InputMode);
    PC->SetShowMouseCursor(true);
}

/** @brief Remove the results widget, unfreeze the vehicle, and restore GameOnly input. */
void ARaceManager::HideResultsScreen()
{
    if (ResultsScreenWidget)
    {
        ResultsScreenWidget->RemoveFromParent();
        ResultsScreenWidget = nullptr;
    }

    bFreezeVehicle = false;

    UWorld* World = GetWorld();
    if (!World) return;

    APlayerController* PC = World->GetFirstPlayerController();
    if (!PC) return;

    bAutopilot = false;

    FInputModeGameOnly InputMode;
    PC->SetInputMode(InputMode);
    PC->SetShowMouseCursor(false);
}

// ========== RESPAWN SYSTEM ==========

/**
 * @brief Teleport the player vehicle to the last checkpoint, falling back to start gate or current location.
 *        Optionally clears physics velocity.
 */
void ARaceManager::ResetVehiclePosition()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!PlayerController)
    {
        return;
    }

    APawn* Vehicle = PlayerController->GetPawn();
    if (!Vehicle)
    {
        return;
    }

    // Determine respawn location
    FVector ResetLocation;
    FRotator ResetRotation;

    // If we have a checkpoint, use it; otherwise use start gate
    if (!LastCheckpointLocation.IsZero())
    {
        ResetLocation = LastCheckpointLocation;
        ResetRotation = LastCheckpointRotation;
    }
    else if (!StartGateLocation.IsZero())
    {
        ResetLocation = StartGateLocation;
        ResetRotation = StartGateRotation;
    }
    else
    {
        // Fallback: use vehicle's current location slightly higher
        ResetLocation = Vehicle->GetActorLocation();
        ResetLocation.Z += ResetHeightOffset;
        ResetRotation = Vehicle->GetActorRotation();
        ResetRotation.Pitch = 0.0f;
        ResetRotation.Roll = 0.0f;
    }

    // Add height offset to avoid spawning in ground
    ResetLocation.Z += ResetHeightOffset;

    // Reset vehicle transform
    Vehicle->SetActorLocation(ResetLocation);
    Vehicle->SetActorRotation(ResetRotation);

    // Reset physics if enabled
    if (bResetPhysicsOnRespawn)
    {
        if (UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Vehicle->GetRootComponent()))
        {
            RootComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
            RootComp->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
        }
    }

    if (bEnableDebugMessages && GEngine)
    {
        GEngine->AddOnScreenDebugMessage((uint64)-1, 2.0f, FColor::Yellow, TEXT("Vehicle Reset!"));
    }
}
