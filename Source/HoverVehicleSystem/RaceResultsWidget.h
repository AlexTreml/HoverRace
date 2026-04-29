#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "RaceResultsWidget.generated.h"

struct FRacerResult;

UCLASS()
class HOVERVEHICLESYSTEM_API URaceResultsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Container for result rows — add a VerticalBox called "ResultsBox" in the designer
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ResultsBox;

	// Keep old ResultsText as optional fallback
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* ResultsText;

	// Text block named "PlayerPositionText" in the widget Blueprint — shows "1st", "2nd", etc.
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* PlayerPositionText;

	// Colour for the player's row
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Results")
	FLinearColor PlayerRowColor = FLinearColor(0.0f, 0.8f, 1.0f, 1.0f);

	// Colour for AI rows
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Results")
	FLinearColor AIRowColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Font size for result rows
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Results")
	int32 ResultFontSize = 15;

	// Called by RaceManager to fill in the results table
	UFUNCTION(BlueprintCallable, Category = "Race")
	void PopulateResults(const TArray<FRacerResult>& Results);

private:
	static FString GetOrdinalString(int32 Position);
	static FString FormatRaceTime(float Seconds);
	void AddResultRow(const FRacerResult& Result);
};
