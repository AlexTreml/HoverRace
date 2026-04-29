// RaceResultsWidget.cpp — end-of-race results screen built from FRacerResult rows.

#include "RaceResultsWidget.h"
#include "RaceManager.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"

/** @brief Return the ordinal suffix string for a 1-based position (e.g. 2 → "2nd"). */
FString URaceResultsWidget::GetOrdinalString(int32 Position)
{
	switch (Position)
	{
	case 1: return TEXT("1st");
	case 2: return TEXT("2nd");
	case 3: return TEXT("3rd");
	default: return FString::Printf(TEXT("%dth"), Position);
	}
}

/** @brief Format seconds as `MM:SS.ms`. */
FString URaceResultsWidget::FormatRaceTime(float Seconds)
{
	const int32 TotalMilliseconds = FMath::RoundToInt(FMath::Max(0.0f, Seconds) * 1000.0f);
	const int32 Minutes = TotalMilliseconds / 60000;
	const int32 WholeSeconds = (TotalMilliseconds / 1000) % 60;
	const int32 Milliseconds = TotalMilliseconds % 1000;
	return FString::Printf(TEXT("%02d:%02d.%03d"), Minutes, WholeSeconds, Milliseconds);
}

/**
 * @brief Build one HorizontalBox row (position / name / time) and add it to ResultsBox.
 *        Player rows use PlayerRowColor; AI rows use AIRowColor.
 */
void URaceResultsWidget::AddResultRow(const FRacerResult& Result)
{
	if (!ResultsBox) return;

	const FLinearColor RowColor = Result.bIsPlayer ? PlayerRowColor : AIRowColor;
	const FString Time = Result.bFinished ? FormatRaceTime(Result.FinishTime) : TEXT("DNF");

	UHorizontalBox* Row = NewObject<UHorizontalBox>(this);

	// Font setup
	FSlateFontInfo ResultFont = FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), ResultFontSize);
	UObject* FontObj = LoadObject<UObject>(nullptr, TEXT("/Game/Fonts/F_Arial.F_Arial"));
	if (FontObj)
	{
		ResultFont = FSlateFontInfo(FontObj, ResultFontSize);
	}

	// Position text (e.g. "1st")
	UTextBlock* PosText = NewObject<UTextBlock>(this);
	PosText->SetText(FText::FromString(GetOrdinalString(Result.Position)));
	PosText->SetColorAndOpacity(FSlateColor(RowColor));
	PosText->SetFont(ResultFont);
	UHorizontalBoxSlot* PosSlot = Row->AddChildToHorizontalBox(PosText);
	PosSlot->SetPadding(FMargin(0.0f, 0.0f, 30.0f, 0.0f));
	PosSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));

	// Name text
	UTextBlock* NameText = NewObject<UTextBlock>(this);
	NameText->SetText(FText::FromString(Result.RacerName));
	NameText->SetColorAndOpacity(FSlateColor(RowColor));
	NameText->SetFont(ResultFont);
	UHorizontalBoxSlot* NameSlot = Row->AddChildToHorizontalBox(NameText);
	NameSlot->SetPadding(FMargin(0.0f, 0.0f, 30.0f, 0.0f));
	NameSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));

	// Time text
	UTextBlock* TimeText = NewObject<UTextBlock>(this);
	TimeText->SetText(FText::FromString(Time));
	TimeText->SetColorAndOpacity(FSlateColor(RowColor));
	TimeText->SetFont(ResultFont);
	UHorizontalBoxSlot* TimeSlot = Row->AddChildToHorizontalBox(TimeText);
	TimeSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));

	// Add row to vertical box
	UVerticalBoxSlot* RowSlot = ResultsBox->AddChildToVerticalBox(Row);
	RowSlot->SetPadding(FMargin(0.0f, 5.0f, 0.0f, 5.0f));
}

/**
 * @brief Replace the contents of ResultsBox with one row per FRacerResult and
 *        update the player-position text. Falls back to a single TextBlock if no ResultsBox is bound.
 */
void URaceResultsWidget::PopulateResults(const TArray<FRacerResult>& Results)
{
	if (ResultsBox)
	{
		ResultsBox->ClearChildren();
	}

	// Add each result as a row
	for (const FRacerResult& Result : Results)
	{
		AddResultRow(Result);
	}

	// Fallback to old text block if it exists
	if (ResultsText)
	{
		if (ResultsBox)
		{
			ResultsText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			FString Text;
			for (const FRacerResult& Result : Results)
			{
				FString Time = Result.bFinished ? FormatRaceTime(Result.FinishTime) : TEXT("DNF");
				Text += FString::Printf(TEXT("%s  %s  -  %s\n"), *GetOrdinalString(Result.Position), *Result.RacerName, *Time);
			}
			ResultsText->SetText(FText::FromString(Text));
		}
	}

	// Set player position text
	if (PlayerPositionText)
	{
		for (const FRacerResult& Result : Results)
		{
			if (Result.bIsPlayer)
			{
				PlayerPositionText->SetText(FText::FromString(GetOrdinalString(Result.Position)));
				break;
			}
		}
	}
}
