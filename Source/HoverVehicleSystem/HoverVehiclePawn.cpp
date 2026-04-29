// HoverVehiclePawn.cpp - Hover Vehicle System
// Converted from Blueprint to C++

#include "HoverVehiclePawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

// Constructor
AHoverVehiclePawn::AHoverVehiclePawn()
{
	// Set this pawn to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Create root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create plane mesh component
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
	PlaneMesh->SetupAttachment(RootComponent);

	// Create front line trace point
	FrontLineTracePoint = CreateDefaultSubobject<USceneComponent>(TEXT("FrontLineTracePoint"));
	FrontLineTracePoint->SetupAttachment(PlaneMesh);

	// Create jumping timeline component
	JumpingTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("JumpingTimeline"));

	// Initialize movement variables with default values
	CurrentForwardSpeed = 0.0;
	MinSpeed = -100.0;
	MaxSpeed = 2000.0;
	Acceleration = 500.0;
	TurningRate = 100.0;

	CurrentYawSpeed = 0.0;
	CurrentPitchSpeed = 0.0;
	CurrentRollSpeed = 0.0;

	// Initialize hover system variables
	MaxHoverHeight = 300.0;
	MinHoverHeight = 100.0;
	CurrentHoverHeight = 0.0;
	HoverForce = 10000.0;
	BobRate = 1.0;
	SpringStrength = 1000.0;
	SpringDamping = 100.0;

	// Initialize state variables
	bIsInAir = false;
	bIsRotating = false;
	bMovementLockedByRace = false;
	LastTickPosition = FVector::ZeroVector;
	CurrentVelocity = 0.0;
	JumpHeight = 500.0;
	GravityForce = 980.0;
	RollingStartLocation = FVector::ZeroVector;
	RotateToVar = FRotator::ZeroRotator;

	// Initialize input values
	ThrustInput = 0.0f;
	MoveUpInput = 0.0f;
	MoveRightInput = 0.0f;
}

// Called when the game starts or when spawned
void AHoverVehiclePawn::BeginPlay()
{
	Super::BeginPlay();

	// Initialize last tick position
	LastTickPosition = GetActorLocation();
}

// Called every frame
void AHoverVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Skip movement updates if locked by race
	if (bMovementLockedByRace)
	{
		return;
	}

	// Update hover physics
	UpdateHoverPhysics(DeltaTime);

	// Update forward movement based on input
	UpdateForwardMovement(DeltaTime);

	// Update rotation based on input
	UpdateRotation(DeltaTime);

	// Apply movement
	ApplyMovement(DeltaTime);

	// Calculate current velocity
	CurrentVelocity = GetCurrentVelocity(LastTickPosition);
	LastTickPosition = GetActorLocation();
}

// Called to bind functionality to input
void AHoverVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind axis inputs
	PlayerInputComponent->BindAxis("Thrust", this, &AHoverVehiclePawn::OnThrustInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &AHoverVehiclePawn::OnMoveUpInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHoverVehiclePawn::OnMoveRightInput);
}

// ========== INPUT FUNCTIONS ==========

void AHoverVehiclePawn::OnThrustInput(float AxisValue)
{
	ThrustInput = AxisValue;
}

void AHoverVehiclePawn::OnMoveUpInput(float AxisValue)
{
	MoveUpInput = AxisValue;
}

void AHoverVehiclePawn::OnMoveRightInput(float AxisValue)
{
	MoveRightInput = AxisValue;
}

// ========== UPDATE FUNCTIONS ==========

void AHoverVehiclePawn::UpdateForwardMovement(float DeltaTime)
{
	// Check if there's thrust input
	if (ThrustInput != 0.0f)
	{
		// Calculate acceleration value
		double AccelerationValue = ThrustInput * Acceleration * DeltaTime;

		// Add to current forward speed
		CurrentForwardSpeed += AccelerationValue;
	}
	else
	{
		// If no input, apply braking (interpolate to 0)
		double BrakingValue = -Acceleration * DeltaTime;
		CurrentForwardSpeed += BrakingValue;
	}

	// Clamp speed between min and max
	CurrentForwardSpeed = FMath::Clamp(CurrentForwardSpeed, MinSpeed, MaxSpeed);
}

void AHoverVehiclePawn::UpdateRotation(float DeltaTime)
{
	// Update yaw (left/right turning)
	if (MoveRightInput != 0.0f)
	{
		double YawChange = MoveRightInput * TurningRate * DeltaTime;
		CurrentYawSpeed += YawChange;

		// Apply roll when turning (for visual effect)
		double TargetRoll = MoveRightInput * 30.0; // 30 degrees max roll
		CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRoll, DeltaTime, 2.0);
	}
	else
	{
		// Return to level when not turning
		CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, 0.0, DeltaTime, 2.0);
	}

	// Update pitch (up/down)
	if (MoveUpInput != 0.0f)
	{
		double PitchChange = MoveUpInput * TurningRate * DeltaTime;
		CurrentPitchSpeed += PitchChange;
	}

	// Apply rotation to the mesh only (not the whole actor)
	if (PlaneMesh)
	{
		FRotator CurrentMeshRotation = PlaneMesh->GetRelativeRotation();
		FRotator NewMeshRotation = FRotator(CurrentPitchSpeed, 0.0, CurrentRollSpeed);
		PlaneMesh->SetRelativeRotation(NewMeshRotation);
	}

	// Apply yaw to the entire actor
	FRotator CurrentActorRotation = GetActorRotation();
	FRotator NewActorRotation = FRotator(CurrentActorRotation.Pitch, CurrentActorRotation.Yaw + (CurrentYawSpeed * DeltaTime), CurrentActorRotation.Roll);
	SetActorRotation(NewActorRotation);
}

void AHoverVehiclePawn::UpdateHoverPhysics(float DeltaTime)
{
	// Perform hover line trace
	HoverLineTrace();

	// Get current hover height
	CurrentHoverHeight = FindCurrentHoverHeight(FrontLineTracePoint);

	// Calculate hover force based on height
	if (CurrentHoverHeight > 0.0 && CurrentHoverHeight < MaxHoverHeight)
	{
		// Spring physics for smooth hovering
		double HeightError = MaxHoverHeight - CurrentHoverHeight;
		double HoverForceCurrent = (HeightError * SpringStrength) - (GetVelocity().Z * SpringDamping);

		// Apply upward force
		FVector UpwardForce = GetActorUpVector() * HoverForceCurrent * DeltaTime;
		AddActorWorldOffset(UpwardForce, true);

		bIsInAir = false;
	}
	else
	{
		// Apply gravity if too high or no ground detected
		FVector GravityVector = FVector(0.0, 0.0, -GravityForce) * DeltaTime;
		AddActorWorldOffset(GravityVector, true);

		bIsInAir = true;
	}
}

void AHoverVehiclePawn::ApplyMovement(float DeltaTime)
{
	// Calculate forward movement
	FVector ForwardMovement = GetActorForwardVector() * CurrentForwardSpeed * DeltaTime;

	// Apply movement with collision detection
	FHitResult HitResult;
	AddActorWorldOffset(ForwardMovement, true, &HitResult);

	// Handle collision
	if (HitResult.bBlockingHit)
	{
		// Reduce speed on collision
		CurrentForwardSpeed *= 0.5;
	}
}

// ========== CUSTOM FUNCTIONS ==========

void AHoverVehiclePawn::HoverLineTrace()
{
	if (!FrontLineTracePoint)
	{
		return;
	}

	// Get start location (front trace point)
	FVector StartLocation = FrontLineTracePoint->GetComponentLocation();

	// Calculate end location (downward trace)
	FVector DownVector = -GetActorUpVector() * (MaxHoverHeight + 100.0);
	FVector EndLocation = StartLocation + DownVector;

	// Setup trace parameters
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	TArray<FHitResult> OutHits;

	// Perform multi line trace
	bool bHit = UKismetSystemLibrary::LineTraceMultiForObjects(
		GetWorld(),
		StartLocation,
		EndLocation,
		ObjectTypes,
		false, // bTraceComplex
		ActorsToIgnore,
		EDrawDebugTrace::None, // Change to ForDuration for debugging
		OutHits,
		true // bIgnoreSelf
	);

	// Process hits for ground alignment if needed
	if (bHit && OutHits.Num() > 0)
	{
		// Get the first hit (closest ground)
		FHitResult FirstHit = OutHits[0];

		// You can add ground alignment logic here
		// For example, rotating the vehicle to match ground normal
		FVector GroundNormal = FirstHit.Normal;

		// Optional: Smooth rotation towards ground normal
		// FRotator TargetRotation = GroundNormal.Rotation();
		// SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 2.0f));
	}
}

double AHoverVehiclePawn::FindCurrentHoverHeight(USceneComponent* SceneComponent)
{
	if (!SceneComponent)
	{
		return 0.0;
	}

	// Get start location
	FVector StartLocation = SceneComponent->GetComponentLocation();

	// Calculate end location (downward trace)
	FVector DownVector = -GetActorUpVector() * (MaxHoverHeight + MinHoverHeight);
	FVector EndLocation = StartLocation + DownVector;

	// Setup trace
	FHitResult OutHit;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	// Perform line trace
	bool bHit = UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		StartLocation,
		EndLocation,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false, // bTraceComplex
		ActorsToIgnore,
		EDrawDebugTrace::None, // Change to ForDuration for debugging
		OutHit,
		true // bIgnoreSelf
	);

	if (bHit)
	{
		// Calculate distance from hit point
		double Distance = FVector::Dist(StartLocation, OutHit.Location);
		return Distance;
	}

	// Return 0 if no hit (too high or no ground)
	return 0.0;
}

double AHoverVehiclePawn::GetCurrentVelocity(FVector PrevLocation)
{
	// Get current location
	FVector CurrentLocation = GetActorLocation();

	// Calculate displacement
	FVector Displacement = CurrentLocation - PrevLocation;

	// Calculate velocity magnitude
	double Velocity = Displacement.Size() / GetWorld()->GetDeltaSeconds();

	return Velocity;
}

FName AHoverVehiclePawn::GetActorTag()
{
	if (Tags.Num() > 0)
	{
		return Tags[0];
	}

	return NAME_None;
}

void AHoverVehiclePawn::SetMovementLockedByRace(bool bLocked)
{
	bMovementLockedByRace = bLocked;

	// Optionally reset input values when locked
	if (bLocked)
	{
		ThrustInput = 0.0f;
		MoveUpInput = 0.0f;
		MoveRightInput = 0.0f;
	}
}
