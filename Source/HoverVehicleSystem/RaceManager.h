#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "HoverRaceSpline.h"
#include "RaceManager.generated.h"

class ARaceGate;
class AHoverAIRacer;

USTRUCT(BlueprintType)
struct FRacerResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Race Result")
    FString RacerName;

    // Finish time in seconds. -1 = did not finish.
    UPROPERTY(BlueprintReadOnly, Category = "Race Result")
    float FinishTime = -1.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Race Result")
    int32 Position = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Race Result")
    bool bIsPlayer = false;

    UPROPERTY(BlueprintReadOnly, Category = "Race Result")
    bool bFinished = false;

    // Used to order DNF racers by how far they got
    UPROPERTY(BlueprintReadOnly, Category = "Race Result")
    float SplineProgress = 0.0f;
};

UENUM(BlueprintType)
enum class ERaceState : uint8
{
    WaitingToStart,
    Countdown,
    Racing,
    Finished
};

UCLASS(Blueprintable)
class HOVERVEHICLESYSTEM_API ARaceManager : public AActor
{
    GENERATED_BODY()

public:
    ARaceManager();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Race")
    void StartCountdown();

    UFUNCTION(BlueprintCallable, Category = "Race")
    void ResetRace();

    UFUNCTION(BlueprintCallable, Category = "Race")
    void HandleGateTriggered(ARaceGate* Gate, AActor* TriggeringActor);

    UFUNCTION(BlueprintPure, Category = "Race")
    ERaceState GetRaceState() const
    {
        return RaceState;
    }

    UFUNCTION(BlueprintPure, Category = "Race")
    float GetCountdownRemaining() const
    {
        return CountdownRemaining;
    }

    UFUNCTION(BlueprintPure, Category = "Race")
    float GetCurrentRaceTime() const
    {
        return CurrentRaceTime;
    }

    UFUNCTION(BlueprintPure, Category = "Race")
    float GetFinalRaceTime() const
    {
        return FinalRaceTime;
    }

    UFUNCTION(BlueprintPure, Category = "Race")
    float GetBestRaceTime() const
    {
        return BestRaceTime;
    }

    UFUNCTION(BlueprintPure, Category = "Race")
    float GetCurrentLapTime() const
    {
        return CurrentLapTime;
    }

    UFUNCTION(BlueprintPure, Category = "Race")
    float GetLastLapTime() const
    {
        return LastLapTime;
    }

    UFUNCTION(BlueprintPure, Category = "Race")
    float GetBestLapTime() const
    {
        return BestLapTime;
    }

    UFUNCTION(BlueprintPure, Category = "Race")
    int32 GetPassedCheckpointCount() const
    {
        return FMath::Clamp(NextCheckpointArrayIndex, 0, CheckpointGates.Num());
    }

    UFUNCTION(BlueprintPure, Category = "Race")
    int32 GetTotalCheckpointCount() const
    {
        return CheckpointGates.Num();
    }

    UFUNCTION(BlueprintPure, Category = "Race")
    bool AreAllCheckpointsPassed() const;

    UFUNCTION(BlueprintPure, Category = "Race")
    int32 GetCurrentLap() const { return CurrentLap; }

    UFUNCTION(BlueprintPure, Category = "Race")
    int32 GetRequiredLaps() const { return RequiredLaps; }

    // ========== RESPAWN SYSTEM ==========

    UFUNCTION(BlueprintCallable, Category = "Race|Respawn")
    void ResetVehiclePosition();

    UFUNCTION(BlueprintPure, Category = "Race|Respawn")
    FVector GetLastCheckpointLocation() const { return LastCheckpointLocation; }

    UFUNCTION(BlueprintPure, Category = "Race|Respawn")
    FRotator GetLastCheckpointRotation() const { return LastCheckpointRotation; }

    // ========== LIVE POSITION ==========

    UFUNCTION(BlueprintPure, Category = "Race|Position")
    int32 GetPlayerRacePosition() const { return CurrentPlayerPosition; }

    UFUNCTION(BlueprintPure, Category = "Race|Position")
    int32 GetTotalRacers() const { return AIRacers.Num() + 1; }

    // ========== RESULTS ==========

    void RegisterAIFinish(AHoverAIRacer* Racer);

    UFUNCTION(BlueprintPure, Category = "Race|Results")
    TArray<FRacerResult> GetFinalResults() const { return FinalResults; }

    UFUNCTION(BlueprintCallable, Category = "Race|UI")
    void ShowResultsScreen();

    UFUNCTION(BlueprintCallable, Category = "Race|UI")
    void HideResultsScreen();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Race")
    float CountdownDuration = 3.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Race")
    bool bAutoStartCountdownOnBeginPlay = true;

    // Delay before countdown begins (for intro camera etc.)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Race", meta = (ClampMin = "0.0"))
    float PreRaceDelay = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Race")
    bool bLockPlayerInputDuringCountdown = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Race")
    bool bAllowRestartFromStartGate = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Race|Debug")
    bool bEnableDebugMessages = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
    FString PlayerName = "Player";

    // Number of laps to complete the race. Applied to both player and AI.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Race", meta = (ClampMin = "1"))
    int32 RequiredLaps = 1;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Results")
    TArray<FRacerResult> FinalResults;

    // ========== UI ==========

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race|UI")
    TSubclassOf<UUserWidget> ResultsScreenClass;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|UI")
    UUserWidget* ResultsScreenWidget = nullptr;

    // ========== RESPAWN SETTINGS ==========

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race|Respawn")
    float ResetHeightOffset = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race|Respawn")
    bool bResetPhysicsOnRespawn = true;

    // Auto-respawn if vehicle falls below this height (Z position)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race|Respawn")
    bool bAutoRespawnOnFall = true;

    // Height threshold - vehicle auto-respawns if it falls below this Z value
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race|Respawn", meta = (EditCondition = "bAutoRespawnOnFall"))
    float KillZHeight = -5000.0f;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Runtime")
    ERaceState RaceState = ERaceState::WaitingToStart;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Runtime")
    float CountdownRemaining = 0.0f;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Runtime")
    float CurrentRaceTime = 0.0f;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Runtime")
    float FinalRaceTime = 0.0f;

    // Best completed race time for this play session.
    // Set to -1.0f when no completed run exists yet.
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Runtime")
    float BestRaceTime = -1.0f;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Runtime")
    int32 CurrentLap = 0;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Runtime")
    float CurrentLapTime = 0.0f;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Runtime")
    float LastLapTime = 0.0f;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Runtime")
    float BestLapTime = -1.0f;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Runtime")
    int32 NextCheckpointArrayIndex = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Race")
    TArray<ARaceGate*> CheckpointGates;

    UFUNCTION(BlueprintImplementableEvent, Category = "Race", meta = (DisplayName = "On Countdown Started"))
    void BP_OnCountdownStarted(float Seconds);

    UFUNCTION(BlueprintImplementableEvent, Category = "Race", meta = (DisplayName = "On Race Started"))
    void BP_OnRaceStarted();

    UFUNCTION(BlueprintImplementableEvent, Category = "Race", meta = (DisplayName = "On Checkpoint Passed"))
    void BP_OnCheckpointPassed(int32 PassedCount, int32 TotalCount);

    UFUNCTION(BlueprintImplementableEvent, Category = "Race", meta = (DisplayName = "On Race Finished"))
    void BP_OnRaceFinished(float TimeSeconds);

    UFUNCTION(BlueprintImplementableEvent, Category = "Race", meta = (DisplayName = "On Lap Completed"))
    void BP_OnLapCompleted(int32 NewLapNumber, int32 TotalLaps);

    UFUNCTION(BlueprintImplementableEvent, Category = "Race|Position", meta = (DisplayName = "On Position Changed"))
    void BP_OnPositionChanged(int32 NewPosition, int32 TotalRacers);

    // How long the vehicle coasts after crossing the finish line before results appear
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race|UI")
    float RaceEndDelay = 2.0f;

    // Set to true when the race ends — FlyingPawn Blueprint reads this to switch to autopilot mode
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Race|Autopilot")
    bool bAutopilot = false;

private:
    void CollectGates();
    void CollectRacers();
    void StartRaceNow();
    void OnRaceEndDelayComplete();
    void UpdatePlayerPosition();
    float GetPlayerSplineProgress() const;

    FTimerHandle RaceEndTimerHandle;
    bool bFreezeVehicle = false;
    int32 CurrentPlayerPosition = 1;
    void FinishRace();
    void BuildFinalResults();
    void SetPlayerInputLocked(bool bLocked);

    TArray<AHoverAIRacer*> AIRacers;

    UPROPERTY(Transient)
    AHoverRaceSpline* RaceSpline = nullptr;

    // ========== RESPAWN DATA ==========

    FVector LastCheckpointLocation;
    FRotator LastCheckpointRotation;
    FVector StartGateLocation;
    FRotator StartGateRotation;
};
