// HoverVehiclePawn.h - Hover Vehicle System
// Converted from Blueprint to C++

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/TimelineComponent.h"
#include "HoverVehiclePawn.generated.h"

UCLASS()
class HOVERVEHICLESYSTEM_API AHoverVehiclePawn : public APawn
{
	GENERATED_BODY()

public:
	// Constructor
	AHoverVehiclePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ========== COMPONENTS ==========

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlaneMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* FrontLineTracePoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTimelineComponent* JumpingTimeline;

	// ========== MOVEMENT VARIABLES ==========

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
	double CurrentForwardSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
	double MinSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
	double MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
	double Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Rotation")
	double CurrentYawSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Rotation")
	double CurrentPitchSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Rotation")
	double CurrentRollSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Rotation")
	double TurningRate;

	// ========== HOVER SYSTEM VARIABLES ==========

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover")
	double MaxHoverHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover")
	double MinHoverHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover")
	double CurrentHoverHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover")
	double HoverForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover")
	double BobRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover")
	double SpringStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover")
	double SpringDamping;

	// ========== STATE VARIABLES ==========

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsInAir;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsRotating;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	FVector LastTickPosition;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	double CurrentVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	double JumpHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	double GravityForce;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	FVector RollingStartLocation;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	FRotator RotateToVar;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bMovementLockedByRace;

	// ========== PUBLIC API FUNCTIONS ==========

public:
	/**
	 * Gets the current forward speed of the vehicle
	 * @return Current forward speed value
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	double GetCurrentForwardSpeed() const { return CurrentForwardSpeed; }

	/**
	 * Locks or unlocks movement during race events
	 * @param bLocked - True to lock movement, false to unlock
	 */
	UFUNCTION(BlueprintCallable, Category = "Race")
	void SetMovementLockedByRace(bool bLocked);

private:
	// Input values
	float ThrustInput;
	float MoveUpInput;
	float MoveRightInput;

	// ========== INPUT FUNCTIONS ==========

	void OnThrustInput(float AxisValue);
	void OnMoveUpInput(float AxisValue);
	void OnMoveRightInput(float AxisValue);

	// ========== CUSTOM FUNCTIONS ==========

	/**
	 * Function responsible for aligning the vehicle to the ground.
	 */
	UFUNCTION(BlueprintCallable, Category = "Hover")
	void HoverLineTrace();

	/**
	 * Finds the current hover height from the ground.
	 * @param SceneComponent - The component to trace from
	 * @return The current height above ground
	 */
	UFUNCTION(BlueprintCallable, Category = "Hover")
	double FindCurrentHoverHeight(USceneComponent* SceneComponent);

	/**
	 * Finds the current velocity in Unreal units per second
	 * @param PrevLocation - The previous location to calculate velocity from
	 * @return The current velocity
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	double GetCurrentVelocity(FVector PrevLocation);

	/**
	 * Gets an actor tag (if needed for collision detection)
	 * @return Actor tag
	 */
	UFUNCTION(BlueprintCallable, Category = "Utility")
	FName GetActorTag();

	// ========== HELPER FUNCTIONS ==========

	void UpdateForwardMovement(float DeltaTime);
	void UpdateRotation(float DeltaTime);
	void UpdateHoverPhysics(float DeltaTime);
	void ApplyMovement(float DeltaTime);
};
