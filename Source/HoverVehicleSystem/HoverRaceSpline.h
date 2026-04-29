#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoverRaceSpline.generated.h"

class USplineComponent;

/**
 * Place this actor in your level and draw its spline along the race track.
 * AI racers will automatically find and follow this spline.
 *
 * Setup:
 * 1. Place HoverRaceSpline in level
 * 2. Select it and use the spline editing tools to draw it along your track
 * 3. Make sure it forms a complete loop
 * 4. AI racers will find it automatically at BeginPlay
 */
UCLASS()
class HOVERVEHICLESYSTEM_API AHoverRaceSpline : public AActor
{
	GENERATED_BODY()

public:
	AHoverRaceSpline();

	// The spline that defines the race track path
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race Spline")
	USplineComponent* Spline;

	// Get the world position at a given distance along the spline
	UFUNCTION(BlueprintPure, Category = "Race Spline")
	FVector GetLocationAtDistance(float Distance) const;

	// Get the world rotation at a given distance along the spline
	UFUNCTION(BlueprintPure, Category = "Race Spline")
	FRotator GetRotationAtDistance(float Distance) const;

	// Get the forward direction at a given distance along the spline
	UFUNCTION(BlueprintPure, Category = "Race Spline")
	FVector GetDirectionAtDistance(float Distance) const;

	// Get the total length of the spline
	UFUNCTION(BlueprintPure, Category = "Race Spline")
	float GetSplineLength() const;

	// Find the closest distance along the spline to a world position
	UFUNCTION(BlueprintPure, Category = "Race Spline")
	float GetClosestDistanceToWorldLocation(FVector WorldLocation) const;

	// Given a distance, advance it forward and wrap around if looping
	UFUNCTION(BlueprintPure, Category = "Race Spline")
	float AdvanceDistance(float CurrentDistance, float AdvanceAmount) const;

	// Reverse the order of all spline points (use if AI travel direction is wrong)
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Race Spline")
	void ReverseSpline();

	// Draw debug visualization of the spline in editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race Spline|Debug")
	bool bDrawDebugSpline = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race Spline|Debug")
	FColor DebugColor = FColor::Cyan;

protected:
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
