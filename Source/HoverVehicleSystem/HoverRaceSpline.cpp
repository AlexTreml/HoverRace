// HoverRaceSpline.cpp — race-track spline path used by AI racers and player progress tracking.

#include "HoverRaceSpline.h"

#include "Components/SplineComponent.h"
#include "DrawDebugHelpers.h"

/** @brief Construct the actor with a SceneComponent root and an attached USplineComponent. */
AHoverRaceSpline::AHoverRaceSpline()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(RootComponent);

	// SetClosedLoop is set in the Blueprint defaults — calling it here breaks the editor spline handles.
}

/** @brief Optionally draw the spline path as persistent debug lines for in-editor inspection. */
void AHoverRaceSpline::BeginPlay()
{
	Super::BeginPlay();

	if (bDrawDebugSpline)
	{
		const float SplineLength = Spline->GetSplineLength();
		const float Step = 200.0f;

		for (float Distance = 0.0f; Distance < SplineLength; Distance += Step)
		{
			FVector Location = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
			FVector NextLocation = Spline->GetLocationAtDistanceAlongSpline(
				FMath::Fmod(Distance + Step, SplineLength),
				ESplineCoordinateSpace::World
			);

			DrawDebugLine(GetWorld(), Location, NextLocation, DebugColor, true, -1.0f, 0, 5.0f);
		}
	}
}

/** @brief World-space location at a given distance along the spline. */
FVector AHoverRaceSpline::GetLocationAtDistance(float Distance) const
{
	return Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
}

/** @brief World-space rotation at a given distance along the spline. */
FRotator AHoverRaceSpline::GetRotationAtDistance(float Distance) const
{
	return Spline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
}

/** @brief Tangent direction at a given distance along the spline. */
FVector AHoverRaceSpline::GetDirectionAtDistance(float Distance) const
{
	return Spline->GetDirectionAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
}

/** @brief Total length of the spline in unreal units. */
float AHoverRaceSpline::GetSplineLength() const
{
	return Spline->GetSplineLength();
}

/** @brief Distance along the spline closest to a world-space point. */
float AHoverRaceSpline::GetClosestDistanceToWorldLocation(FVector WorldLocation) const
{
	return Spline->GetDistanceAlongSplineAtLocation(WorldLocation, ESplineCoordinateSpace::World);
}

/**
 * @brief Advance a distance along the spline, wrapping for closed loops or clamping for open splines.
 */
float AHoverRaceSpline::AdvanceDistance(float CurrentDistance, float AdvanceAmount) const
{
	const float SplineLength = Spline->GetSplineLength();
	if (SplineLength <= 0.0f)
	{
		return 0.0f;
	}

	float NewDistance = CurrentDistance + AdvanceAmount;

	// Wrap around for closed loop
	if (Spline->IsClosedLoop())
	{
		while (NewDistance >= SplineLength)
		{
			NewDistance -= SplineLength;
		}
		while (NewDistance < 0.0f)
		{
			NewDistance += SplineLength;
		}
	}
	else
	{
		NewDistance = FMath::Clamp(NewDistance, 0.0f, SplineLength);
	}

	return NewDistance;
}

/**
 * @brief Reverse the spline in place: re-add points in reverse order with negated tangents.
 */
void AHoverRaceSpline::ReverseSpline()
{
	if (!Spline)
	{
		return;
	}

	const int32 NumPoints = Spline->GetNumberOfSplinePoints();
	if (NumPoints < 2)
	{
		return;
	}

	TArray<FVector> Locations;
	TArray<FVector> ArriveTangents;
	TArray<FVector> LeaveTangents;
	TArray<ESplinePointType::Type> PointTypes;

	Locations.Reserve(NumPoints);
	ArriveTangents.Reserve(NumPoints);
	LeaveTangents.Reserve(NumPoints);
	PointTypes.Reserve(NumPoints);

	for (int32 i = 0; i < NumPoints; ++i)
	{
		Locations.Add(Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local));
		ArriveTangents.Add(Spline->GetArriveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local));
		LeaveTangents.Add(Spline->GetLeaveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local));
		PointTypes.Add(Spline->GetSplinePointType(i));
	}

	Spline->ClearSplinePoints(false);

	for (int32 i = NumPoints - 1; i >= 0; --i)
	{
		const int32 NewIndex = NumPoints - 1 - i;
		Spline->AddSplinePoint(Locations[i], ESplineCoordinateSpace::Local, false);
		Spline->SetTangentsAtSplinePoint(NewIndex, -LeaveTangents[i], -ArriveTangents[i], ESplineCoordinateSpace::Local, false);
		Spline->SetSplinePointType(NewIndex, PointTypes[i], false);
	}

	Spline->UpdateSpline();

#if WITH_EDITOR
	Modify();
#endif
}

#if WITH_EDITOR
void AHoverRaceSpline::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
