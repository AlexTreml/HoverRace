#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceManager.h"
#include "HoverRaceUI.generated.h"

class UTextBlock;

/**
 * Lightweight C++ HUD bridge.
 * Blueprint subclasses can stay layout-only if using the optional TextBlock bindings.
 */
UCLASS(Abstract, Blueprintable)
class HOVERVEHICLESYSTEM_API UHoverRaceUI : public UUserWidget
{
    GENERATED_BODY()

public:
    // Update speed display from unreal units/second.
    void UpdateSpeed(float ForwardSpeedUS);

    // Update race state display from the active race manager.
    void UpdateRaceState(
        ERaceState InRaceState,
        float InCountdownRemaining,
        float InCurrentRaceTime,
        float InFinalRaceTime,
        float InBestRaceTime,
        int32 InPassedCheckpoints,
        int32 InTotalCheckpoints,
        int32 InCurrentLap,
        int32 InTotalLaps,
        int32 InPlayerPosition = 1,
        int32 InTotalRacers = 1,
        float InCurrentLapTime = 0.0f,
        float InBestLapTime = -1.0f);

protected:
    // Toggle speed conversion (KPH by default, MPH when true).
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    bool bUseMPH = false;

    // If true, this class writes directly to bound TextBlocks each update.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    bool bAutoUpdateTextBlocks = true;

    // Optional direct widget bindings (layout-only Blueprint workflow).
    UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly, Category = "UI")
    UTextBlock* SpeedText = nullptr;

    UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly, Category = "UI")
    UTextBlock* CountdownText = nullptr;

    UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly, Category = "UI")
    UTextBlock* LapTimeText = nullptr;

    UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly, Category = "UI")
    UTextBlock* BestTimeText = nullptr;

    UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly, Category = "UI")
    UTextBlock* LapCountText = nullptr;

    UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly, Category = "UI")
    UTextBlock* PositionText = nullptr;

    UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly, Category = "UI")
    UTextBlock* FinishPositionText = nullptr;

    UFUNCTION(BlueprintImplementableEvent, Category = "UI", meta = (DisplayName = "On Speed Updated"))
    void BP_OnSpeedUpdated(float DisplaySpeed);

    UFUNCTION(BlueprintImplementableEvent, Category = "UI", meta = (DisplayName = "On Race State Updated"))
    void BP_OnRaceStateUpdated(
        ERaceState RaceState,
        float CountdownRemaining,
        float CurrentRaceTime,
        float FinalRaceTime,
        int32 PassedCheckpoints,
        int32 TotalCheckpoints,
        int32 CurrentLap,
        int32 TotalLaps);

    UFUNCTION(BlueprintImplementableEvent, Category = "UI", meta = (DisplayName = "On Best Time Updated"))
    void BP_OnBestTimeUpdated(float BestRaceTime);

private:
    static FText FormatTime(float Seconds);
};
