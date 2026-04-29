// HoverRaceUI.cpp — race HUD widget. Updates speed and race-state text blocks each tick.

#include "HoverRaceUI.h"

#include "Components/TextBlock.h"
#include "Math/UnrealMathUtility.h"

/** @brief Convert raw forward speed to MPH or KPH and write it to SpeedText. */
void UHoverRaceUI::UpdateSpeed(float ForwardSpeedUS)
{
    const float DisplaySpeed = FMath::Abs(ForwardSpeedUS) * (bUseMPH ? 0.022f : 0.036f);

    if (bAutoUpdateTextBlocks && SpeedText)
    {
        SpeedText->SetText(FText::AsNumber(FMath::RoundToInt(DisplaySpeed)));
    }

    BP_OnSpeedUpdated(DisplaySpeed);
}

/**
 * @brief Update every race-related text block from the data passed by the controller.
 *        Toggles countdown / finish overlay visibility based on race state.
 */
void UHoverRaceUI::UpdateRaceState(
    ERaceState InRaceState,
    float InCountdownRemaining,
    float InCurrentRaceTime,
    float InFinalRaceTime,
    float InBestRaceTime,
    int32 InPassedCheckpoints,
    int32 InTotalCheckpoints,
    int32 InCurrentLap,
    int32 InTotalLaps,
    int32 InPlayerPosition,
    int32 InTotalRacers,
    float InCurrentLapTime,
    float InBestLapTime)
{
    if (bAutoUpdateTextBlocks)
    {
        if (CountdownText)
        {
            if (InRaceState == ERaceState::Countdown)
            {
                CountdownText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
                CountdownText->SetText(FText::AsNumber(FMath::Max(0, FMath::CeilToInt(InCountdownRemaining))));
            }
            else
            {
                CountdownText->SetVisibility(ESlateVisibility::Collapsed);
            }
        }

        if (LapTimeText)
        {
            LapTimeText->SetText(FormatTime(InCurrentLapTime));
        }

        if (BestTimeText)
        {
            if (InBestLapTime >= 0.0f)
            {
                BestTimeText->SetText(FormatTime(InBestLapTime));
            }
            else
            {
                BestTimeText->SetText(FText::FromString(TEXT("--:--.---")));
            }
        }

        if (LapCountText && InTotalLaps > 1)
        {
            LapCountText->SetText(FText::FromString(
                FString::Printf(TEXT("Lap %d / %d"), InCurrentLap + 1, InTotalLaps)));
        }

        if (FinishPositionText)
        {
            if (InRaceState == ERaceState::Finished)
            {
                FString Suffix;
                if (InPlayerPosition == 1) Suffix = TEXT("st");
                else if (InPlayerPosition == 2) Suffix = TEXT("nd");
                else if (InPlayerPosition == 3) Suffix = TEXT("rd");
                else Suffix = TEXT("th");

                FinishPositionText->SetText(FText::FromString(
                    FString::Printf(TEXT("%d%s"), InPlayerPosition, *Suffix)));
                FinishPositionText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
            }
            else
            {
                FinishPositionText->SetVisibility(ESlateVisibility::Collapsed);
            }
        }

        if (PositionText && InTotalRacers > 1)
        {
            // Format as "1st", "2nd", "3rd", "4th" etc.
            FString Suffix;
            if (InPlayerPosition == 1) Suffix = TEXT("st");
            else if (InPlayerPosition == 2) Suffix = TEXT("nd");
            else if (InPlayerPosition == 3) Suffix = TEXT("rd");
            else Suffix = TEXT("th");

            PositionText->SetText(FText::FromString(
                FString::Printf(TEXT("%d%s / %d"), InPlayerPosition, *Suffix, InTotalRacers)));
        }
    }

    BP_OnRaceStateUpdated(
        InRaceState,
        InCountdownRemaining,
        InCurrentRaceTime,
        InFinalRaceTime,
        InPassedCheckpoints,
        InTotalCheckpoints,
        InCurrentLap,
        InTotalLaps);

    BP_OnBestTimeUpdated(InBestRaceTime);
}

/** @brief Format seconds as `MM:SS.ms` text. */
FText UHoverRaceUI::FormatTime(float Seconds)
{
    const int32 TotalMilliseconds = FMath::RoundToInt(FMath::Max(0.0f, Seconds) * 1000.0f);
    const int32 Minutes = TotalMilliseconds / 60000;
    const int32 WholeSeconds = (TotalMilliseconds / 1000) % 60;
    const int32 Milliseconds = TotalMilliseconds % 1000;

    return FText::FromString(FString::Printf(TEXT("%02d:%02d.%03d"), Minutes, WholeSeconds, Milliseconds));
}
