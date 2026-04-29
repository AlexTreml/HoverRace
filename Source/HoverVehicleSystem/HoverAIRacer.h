#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HoverAIRacer.generated.h"

class UStaticMeshComponent;
class UFloatingPawnMovement;
class AHoverRaceSpline;
class ARaceManager;

/**
 * AI Racer that follows a HoverRaceSpline around the track.
 *
 * Setup:
 * 1. Place HoverAIRacer in your level near the start
 * 2. Assign a Static Mesh to give it a visual appearance
 * 3. Make sure HoverRaceSpline exists in the level
 * 4. Adjust speed and difficulty settings
 * 5. Press Play - the AI will race automatically!
 */
UCLASS()
class HOVERVEHICLESYSTEM_API AHoverAIRacer : public APawn
{
	GENERATED_BODY()

public:
	AHoverAIRacer();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// ========== COMPONENTS ==========

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Racer|Components")
	UStaticMeshComponent* VehicleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Racer|Components")
	UFloatingPawnMovement* MovementComponent;

	// ========== SPEED SETTINGS ==========

	// Base movement speed (units per second)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Speed", meta = (ClampMin = "100.0"))
	float BaseSpeed = 1200.0f;

	// Speed multiplier on straight sections
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Speed", meta = (ClampMin = "0.5", ClampMax = "2.0"))
	float StraightSpeedMultiplier = 1.2f;

	// Speed multiplier on tight corners (lower = more slowdown)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Speed", meta = (ClampMin = "0.2", ClampMax = "1.0"))
	float CornerSpeedMultiplier = 0.7f;

	// Curvature threshold to consider a section a "corner"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Speed", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float CornerCurvatureThreshold = 0.3f;

	// ========== STEERING SETTINGS ==========

	// Reverse the travel direction along the spline (for clockwise/anticlockwise control)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Steering")
	bool bReverseDirection = false;

	// Lateral offset from spline centre in cm (positive = right, negative = left).
	// Use this to stagger multiple AI racers so they don't overlap.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Steering")
	float LateralOffset = 0.0f;

	// How far ahead on spline the AI looks when steering (larger = smoother)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Steering", meta = (ClampMin = "10.0"))
	float LookAheadDistance = 600.0f;

	// How quickly the AI rotates to face target direction (degrees per second)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Steering", meta = (ClampMin = "10.0"))
	float RotationSpeed = 180.0f;

	// ========== HOVER SETTINGS ==========

	// Height above the spline to hover at
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Hover", meta = (ClampMin = "0.0"))
	float HoverHeight = 100.0f;

	// How quickly the AI adjusts its hover height
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Hover", meta = (ClampMin = "1.0"))
	float HoverAdjustSpeed = 5.0f;

	// Enable surface-tracing hover (like player vehicle). When true the AI
	// casts a ray downward, checks for the "Floor" actor tag, and aligns
	// its rotation to the surface normal so it banks on curves and can
	// handle loops / upside-down sections.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Hover")
	bool bUseSurfaceTracing = true;

	// How far below the AI to trace for the track surface
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Hover", meta = (ClampMin = "100.0", EditCondition = "bUseSurfaceTracing"))
	float SurfaceTraceDistance = 1000.0f;

	// How quickly the AI aligns to the surface normal (higher = snappier)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Hover", meta = (ClampMin = "1.0", EditCondition = "bUseSurfaceTracing"))
	float SurfaceAlignSpeed = 8.0f;

	// ========== WALL AVOIDANCE ==========

	// Enable wall detection and avoidance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Wall Avoidance")
	bool bEnableWallAvoidance = true;

	// How far left/right to check for walls
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Wall Avoidance", meta = (ClampMin = "50.0", EditCondition = "bEnableWallAvoidance"))
	float WallTraceDistance = 300.0f;

	// How strongly the AI steers away from walls (higher = stronger push)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Wall Avoidance", meta = (ClampMin = "0.1", EditCondition = "bEnableWallAvoidance"))
	float WallAvoidanceStrength = 500.0f;

	// ========== RUBBER BAND ==========

	// Enable rubber banding (AI slows when ahead, speeds up when behind)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Rubber Band")
	bool bEnableRubberBand = true;

	// Distance ahead of player the AI starts slowing down
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Rubber Band", meta = (EditCondition = "bEnableRubberBand"))
	float RubberBandAheadDistance = 3000.0f;

	// Distance behind player the AI starts speeding up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Rubber Band", meta = (EditCondition = "bEnableRubberBand"))
	float RubberBandBehindDistance = 5000.0f;

	// Max speed multiplier when catching up (rubber band boost)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Rubber Band", meta = (EditCondition = "bEnableRubberBand", ClampMin = "1.0", ClampMax = "3.0"))
	float RubberBandMaxBoost = 1.5f;

	// ========== RACE STATE ==========

	// Current distance along the spline
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI Racer|Runtime")
	float CurrentSplineDistance = 0.0f;

	// Number of laps completed
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI Racer|Runtime")
	int32 LapsCompleted = 0;

	// Is the AI currently racing?
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI Racer|Runtime")
	bool bIsRacing = false;

	// ========== RACE IDENTITY ==========

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer")
	FString RacerName = "AI Racer";

	// How many spline loops = finished
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer")
	int32 RequiredLaps = 1;

	// ========== FINISH STATE ==========

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI Racer|Runtime")
	bool bFinishedRace = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "AI Racer|Runtime")
	float FinishRaceTime = 0.0f;

	// Set by RaceManager on BeginPlay
	UPROPERTY(BlueprintReadOnly, Category = "AI Racer")
	ARaceManager* RaceManager = nullptr;

	UFUNCTION(BlueprintCallable, Category = "AI Racer")
	void SetRaceManager(ARaceManager* InRaceManager) { RaceManager = InRaceManager; }

	// ========== CONTROL ==========

	UFUNCTION(BlueprintCallable, Category = "AI Racer")
	void StartRacing();

	UFUNCTION(BlueprintCallable, Category = "AI Racer")
	void StopRacing();

	// Called by boost pads to temporarily increase AI speed
	UFUNCTION(BlueprintCallable, Category = "AI Racer")
	void ApplyBoostPad(float BoostStrength);

	// Get current speed for UI/comparison
	UFUNCTION(BlueprintPure, Category = "AI Racer")
	float GetCurrentSpeed() const { return CurrentSpeed; }

	// Get race progress (0.0 to 1.0 per lap)
	UFUNCTION(BlueprintPure, Category = "AI Racer")
	float GetRaceProgress() const;

	// ========== EVENTS ==========

	UFUNCTION(BlueprintImplementableEvent, Category = "AI Racer", meta = (DisplayName = "On Lap Completed"))
	void BP_OnLapCompleted(int32 NewLapCount);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI Racer", meta = (DisplayName = "On Boost Pad Hit"))
	void BP_OnBoostPadHit();

	// ========== DEBUG ==========

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Debug")
	bool bShowDebugInfo = false;

private:
	void FindSpline();
	void UpdateMovement(float DeltaTime);
	void UpdateSurfaceHover(float DeltaTime);
	float CalculateTargetSpeed() const;
	float CalculateRubberBandMultiplier() const;
	float GetCurvatureAtDistance(float Distance) const;

	// Cached surface normal from last successful trace
	FVector CachedSurfaceNormal = FVector::UpVector;

	UPROPERTY(Transient)
	AHoverRaceSpline* RaceSpline;

	float CurrentSpeed = 0.0f;
	float SplineLength = 0.0f;
	bool bHasCompletedFirstLoop = false;

	// Boost pad state
	bool bIsBoosted = false;
	float BoostTimeRemaining = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Boost", meta = (ClampMin = "1.0", AllowPrivateAccess = "true"))
	float BoostSpeedMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Racer|Boost", meta = (ClampMin = "0.0", AllowPrivateAccess = "true"))
	float BoostDuration = 3.0f;
};
