// HoverAIRacer.cpp — spline-following AI opponent.
// Speed = BaseSpeed * curvature factor * rubber-band factor (* boost).
// Hover trace aligns rotation to "Floor" impact normal so the AI handles loops.

#include "HoverAIRacer.h"

#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "HoverRaceSpline.h"
#include "RaceManager.h"

/** @brief Construct the pawn with mesh and floating-movement defaults. */
AHoverAIRacer::AHoverAIRacer()
{
	PrimaryActorTick.bCanEverTick = true;

	VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
	RootComponent = VehicleMesh;
	VehicleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	VehicleMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->MaxSpeed = 3000.0f;
	MovementComponent->Acceleration = 4000.0f;
	MovementComponent->Deceleration = 4000.0f;
}

/** @brief Find the level spline and snap to its nearest point. */
void AHoverAIRacer::BeginPlay()
{
	Super::BeginPlay();

	FindSpline();

	if (RaceSpline)
	{
		SplineLength = RaceSpline->GetSplineLength();
		// Snap to the nearest point on the spline.
		CurrentSplineDistance = RaceSpline->GetClosestDistanceToWorldLocation(GetActorLocation());
	}
}

/** @brief Per-frame entry point. Skips work if not racing. */
void AHoverAIRacer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsRacing || !RaceSpline)
	{
		return;
	}

	UpdateMovement(DeltaTime);

	if (bShowDebugInfo && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			(uint64)(uintptr_t)this,
			0.0f,
			FColor::Green,
			FString::Printf(TEXT("AI Speed: %.0f | Spline: %.0f / %.0f | Laps: %d"),
				CurrentSpeed,
				CurrentSplineDistance,
				SplineLength,
				LapsCompleted)
		);
	}
}

/** @brief Begin processing movement on the next tick. */
void AHoverAIRacer::StartRacing()
{
	bIsRacing = true;
}

/** @brief Halt movement and zero the current speed. */
void AHoverAIRacer::StopRacing()
{
	bIsRacing = false;
	CurrentSpeed = 0.0f;
}

/** @brief Return current spline distance as a 0–1 fraction of total length. */
float AHoverAIRacer::GetRaceProgress() const
{
	if (SplineLength <= 0.0f)
	{
		return 0.0f;
	}
	return CurrentSplineDistance / SplineLength;
}

/** @brief Locate the first AHoverRaceSpline in the level. */
void AHoverAIRacer::FindSpline()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	for (TActorIterator<AHoverRaceSpline> It(World); It; ++It)
	{
		RaceSpline = *It;
		break;
	}

	if (!RaceSpline)
	{
		UE_LOG(LogTemp, Warning, TEXT("HoverAIRacer: No HoverRaceSpline found in level! Place one and draw it along the track."));
	}
}

/**
 * @brief Run the per-tick movement pipeline:
 *        speed → spline advance → lap detection → hover trace → wall avoidance.
 */
void AHoverAIRacer::UpdateMovement(float DeltaTime)
{
	if (!RaceSpline || SplineLength <= 0.0f)
	{
		return;
	}

	// Tick down the boost-pad timer.
	if (bIsBoosted)
	{
		BoostTimeRemaining -= DeltaTime;
		if (BoostTimeRemaining <= 0.0f)
		{
			bIsBoosted = false;
			BoostTimeRemaining = 0.0f;
		}
	}

	// Compute target speed and ease toward it.
	float TargetSpeed = CalculateTargetSpeed();
	if (bIsBoosted)
	{
		TargetSpeed *= BoostSpeedMultiplier;
	}
	CurrentSpeed = FMath::FInterpTo(CurrentSpeed, TargetSpeed, DeltaTime, 3.0f);

	// Distance to advance this frame, signed by travel direction.
	const float DistanceThisFrame = CurrentSpeed * DeltaTime * (bReverseDirection ? -1.0f : 1.0f);
	const float PrevDistance = CurrentSplineDistance;

	// Stall progress if knocked > 1500 cm from the spline.
	const FVector CurrentSplinePos = RaceSpline->GetLocationAtDistance(CurrentSplineDistance);
	const float DistFromSpline = FVector::Dist(GetActorLocation(), CurrentSplinePos);
	if (DistFromSpline < 1500.0f)
	{
		CurrentSplineDistance = RaceSpline->AdvanceDistance(CurrentSplineDistance, DistanceThisFrame);
	}

	// Detect lap-wrap discontinuity in spline distance.
	const bool bWrapped = bReverseDirection
		? (CurrentSplineDistance > PrevDistance + SplineLength * 0.5f)
		: (CurrentSplineDistance < PrevDistance - SplineLength * 0.5f);

	if (bHasCompletedFirstLoop && bWrapped)
	{
		LapsCompleted++;
		BP_OnLapCompleted(LapsCompleted);

		if (bShowDebugInfo && GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				(uint64)-1,
				3.0f,
				FColor::Yellow,
				FString::Printf(TEXT("AI Lap %d completed!"), LapsCompleted)
			);
		}

		// Check if race is finished
		if (!bFinishedRace && LapsCompleted >= RequiredLaps)
		{
			bFinishedRace = true;
			if (RaceManager)
			{
				FinishRaceTime = RaceManager->GetCurrentRaceTime();
				RaceManager->RegisterAIFinish(this);
			}
			StopRacing();
		}
	}

	// bHasCompletedFirstLoop prevents false wrap detection at race start.
	// Forward: wait until past the first 10% of the spline.
	// Reverse: wait until the first wrap has happened (distance jumps to >90%).
	if (!bHasCompletedFirstLoop)
	{
		if (bReverseDirection)
			bHasCompletedFirstLoop = (CurrentSplineDistance > SplineLength * 0.9f);
		else
			bHasCompletedFirstLoop = (CurrentSplineDistance > SplineLength * 0.1f);
	}

	// Look-ahead steering target offset by LateralOffset on the spline-perpendicular axis.
	const float LookAheadDist = RaceSpline->AdvanceDistance(CurrentSplineDistance, LookAheadDistance);
	const FVector LookAheadRight = FVector::CrossProduct(
		RaceSpline->GetDirectionAtDistance(LookAheadDist), FVector::UpVector).GetSafeNormal();
	FVector TargetLocation = RaceSpline->GetLocationAtDistance(LookAheadDist) + LookAheadRight * LateralOffset;

	// Hover trace: cast downward along local up to find a "Floor"-tagged surface.
	const FVector TraceStart = GetActorLocation();
	const FVector TraceDir = -GetActorUpVector();
	const FVector TraceEnd = TraceStart + TraceDir * SurfaceTraceDistance;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bOnTrack = false;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		if (HitResult.GetActor() && HitResult.GetActor()->Tags.Num() > 0
			&& HitResult.GetActor()->Tags[0] == FName(TEXT("Floor")))
		{
			bOnTrack = true;

			// Position: HoverHeight above the surface along the impact normal.
			const FVector TargetPos = HitResult.ImpactPoint + HitResult.ImpactNormal * HoverHeight;
			const FVector NewPos = FMath::VInterpTo(GetActorLocation(), TargetPos, DeltaTime, HoverAdjustSpeed);
			SetActorLocation(NewPos);

			// Rotation: align Z to surface normal, X to spline direction.
			const FVector SplineDir = RaceSpline->GetDirectionAtDistance(CurrentSplineDistance);
			const FMatrix RotMatrix = FRotationMatrix::MakeFromZX(HitResult.ImpactNormal, SplineDir);
			const FRotator TargetRotation = RotMatrix.Rotator();
			const FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, RotationSpeed / 90.0f);
			SetActorRotation(NewRotation);
		}
	}

	if (!bOnTrack)
	{
		// Fallback: hover above the spline at HoverHeight when no floor is found.
		const FVector SplineLocation = RaceSpline->GetLocationAtDistance(CurrentSplineDistance);
		const FVector FallbackPos = SplineLocation + FVector(0.0f, 0.0f, HoverHeight);
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), FallbackPos, DeltaTime, HoverAdjustSpeed));
	}

	// Forward velocity follows the spline direction.
	const FVector ForwardDir = RaceSpline->GetDirectionAtDistance(CurrentSplineDistance);
	FVector FinalVelocity = ForwardDir * CurrentSpeed;

	// Wall avoidance: side traces add a counter-push scaled by inverse distance.
	if (bEnableWallAvoidance)
	{
		const FVector RightDir = GetActorRightVector();
		const FVector AILocation = GetActorLocation();

		FHitResult WallHitRight;
		FHitResult WallHitLeft;
		FCollisionQueryParams WallParams;
		WallParams.AddIgnoredActor(this);

		const bool bHitRight = GetWorld()->LineTraceSingleByChannel(
			WallHitRight, AILocation, AILocation + RightDir * WallTraceDistance,
			ECC_Visibility, WallParams);

		const bool bHitLeft = GetWorld()->LineTraceSingleByChannel(
			WallHitLeft, AILocation, AILocation - RightDir * WallTraceDistance,
			ECC_Visibility, WallParams);

		if (bHitRight)
		{
			// Push strength scales inversely with distance to the wall.
			const float DistToWall = WallHitRight.Distance;
			const float PushStrength = (1.0f - (DistToWall / WallTraceDistance)) * WallAvoidanceStrength;
			FinalVelocity -= RightDir * PushStrength;
		}

		if (bHitLeft)
		{
			const float DistToWall = WallHitLeft.Distance;
			const float PushStrength = (1.0f - (DistToWall / WallTraceDistance)) * WallAvoidanceStrength;
			FinalVelocity += RightDir * PushStrength;
		}

		if (bShowDebugInfo)
		{
			DrawDebugLine(GetWorld(), AILocation, AILocation + RightDir * WallTraceDistance,
				bHitRight ? FColor::Red : FColor::Green, false, -1.0f, 0, 1.0f);
			DrawDebugLine(GetWorld(), AILocation, AILocation - RightDir * WallTraceDistance,
				bHitLeft ? FColor::Red : FColor::Green, false, -1.0f, 0, 1.0f);
		}
	}

	MovementComponent->Velocity = FinalVelocity;

	if (bShowDebugInfo)
	{
		DrawDebugSphere(GetWorld(), TargetLocation, 50.0f, 8, FColor::Green, false, -1.0f);
		DrawDebugLine(GetWorld(), GetActorLocation(), TargetLocation, FColor::Yellow, false, -1.0f, 0, 3.0f);
	}
}

/** @brief World-axis hover trace; updates cached normal and lifts above the floor. Currently unused — UpdateMovement handles hover inline. */
void AHoverAIRacer::UpdateSurfaceHover(float DeltaTime)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	// Trace bracketed around the AI on the world Z axis.
	const FVector TraceStart = GetActorLocation() + FVector(0.0f, 0.0f, SurfaceTraceDistance * 0.5f);
	const FVector TraceEnd = GetActorLocation() - FVector(0.0f, 0.0f, SurfaceTraceDistance * 0.5f);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	const bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		QueryParams
	);

	if (bHit && HitResult.GetActor())
	{
		// Only react to "Floor"-tagged geometry.
		const TArray<FName>& HitActorTags = HitResult.GetActor()->Tags;
		if (HitActorTags.Num() > 0 && HitActorTags[0] == FName(TEXT("Floor")))
		{
			CachedSurfaceNormal = FMath::VInterpNormalRotationTo(
				CachedSurfaceNormal,
				HitResult.ImpactNormal,
				DeltaTime,
				SurfaceAlignSpeed
			);

			// Lift above the floor if the AI has dropped below HoverHeight.
			const float SurfaceZ = HitResult.ImpactPoint.Z + HoverHeight;
			if (GetActorLocation().Z < SurfaceZ)
			{
				FVector CorrectedLocation = GetActorLocation();
				CorrectedLocation.Z = SurfaceZ;
				SetActorLocation(CorrectedLocation);
			}
		}
	}

	if (bShowDebugInfo)
	{
		DrawDebugLine(World, TraceStart, TraceEnd, bHit ? FColor::Cyan : FColor::Red, false, -1.0f, 0, 2.0f);
		if (bHit)
		{
			DrawDebugSphere(World, HitResult.ImpactPoint, 30.0f, 6, FColor::Cyan, false, -1.0f);
		}
	}
}

/** @brief Activate a timed boost. Called by ABoostPad on overlap. */
void AHoverAIRacer::ApplyBoostPad(float BoostStrength)
{
	bIsBoosted = true;
	BoostTimeRemaining = BoostDuration;
	BP_OnBoostPadHit();
}

/** @brief Compute target speed = BaseSpeed * curvature factor * rubber-band factor. */
float AHoverAIRacer::CalculateTargetSpeed() const
{
	const float Curvature = GetCurvatureAtDistance(CurrentSplineDistance);
	float SpeedMultiplier = 1.0f;

	// Above the corner threshold, lerp from straight → corner multiplier.
	if (Curvature > CornerCurvatureThreshold)
	{
		const float CurvatureFactor = FMath::GetMappedRangeValueClamped(
			FVector2D(CornerCurvatureThreshold, 1.0f),
			FVector2D(1.0f, 0.0f),
			Curvature
		);
		SpeedMultiplier = FMath::Lerp(CornerSpeedMultiplier, StraightSpeedMultiplier, CurvatureFactor);
	}
	else
	{
		SpeedMultiplier = StraightSpeedMultiplier;
	}

	const float RubberBandMultiplier = CalculateRubberBandMultiplier();
	SpeedMultiplier *= RubberBandMultiplier;

	return BaseSpeed * SpeedMultiplier;
}

/**
 * @brief Speed multiplier based on signed spline-distance gap between AI and player.
 *        Returns 0.85 when ahead, 1.0 in neutral zone, up to RubberBandMaxBoost when behind.
 */
float AHoverAIRacer::CalculateRubberBandMultiplier() const
{
	if (!bEnableRubberBand)
	{
		return 1.0f;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return 1.0f;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC || !PC->GetPawn())
	{
		return 1.0f;
	}

	const FVector PlayerLocation = PC->GetPawn()->GetActorLocation();

	if (!RaceSpline)
	{
		return 1.0f;
	}

	const float PlayerSplineDist = RaceSpline->GetClosestDistanceToWorldLocation(PlayerLocation);
	const float AISplineDist = CurrentSplineDistance;

	// Signed gap: positive = AI ahead, negative = AI behind.
	float SplineDifference = AISplineDist - PlayerSplineDist;

	// Wrap correction when the two are on opposite sides of the start line.
	if (SplineDifference > SplineLength * 0.5f)
	{
		SplineDifference -= SplineLength;
	}
	else if (SplineDifference < -SplineLength * 0.5f)
	{
		SplineDifference += SplineLength;
	}

	if (SplineDifference > RubberBandAheadDistance)
	{
		// Ahead zone: fixed slowdown.
		return 0.85f;
	}
	else if (SplineDifference < -RubberBandBehindDistance)
	{
		// Behind zone: scale boost from 1.0 up to RubberBandMaxBoost over a 2× window.
		const float BehindAmount = FMath::Abs(SplineDifference) - RubberBandBehindDistance;
		const float BoostFactor = FMath::GetMappedRangeValueClamped(
			FVector2D(0.0f, RubberBandBehindDistance * 2.0f),
			FVector2D(1.0f, RubberBandMaxBoost),
			BehindAmount
		);
		return BoostFactor;
	}

	// Neutral zone.
	return 1.0f;
}

/**
 * @brief Curvature at a spline distance, sampled by ±200 cm direction dot product.
 *        Returns 0 for straight, 1 for a hairpin.
 */
float AHoverAIRacer::GetCurvatureAtDistance(float Distance) const
{
	if (!RaceSpline)
	{
		return 0.0f;
	}

	const float SampleOffset = 200.0f;
	const float DistA = RaceSpline->AdvanceDistance(Distance, -SampleOffset);
	const float DistB = RaceSpline->AdvanceDistance(Distance, SampleOffset);

	const FVector DirA = RaceSpline->GetDirectionAtDistance(DistA);
	const FVector DirB = RaceSpline->GetDirectionAtDistance(DistB);

	// Dot product: 1 = straight, 0 = 90°, -1 = U-turn.
	const float DotProduct = FVector::DotProduct(DirA, DirB);

	// Map to 0 (straight) – 1 (curved).
	return FMath::Clamp(1.0f - DotProduct, 0.0f, 1.0f);
}
