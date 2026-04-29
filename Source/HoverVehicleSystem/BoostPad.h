#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoostPad.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class UNiagaraComponent;

UENUM(BlueprintType)
enum class EBoostMode : uint8
{
	// Add a force impulse in the vehicle's forward direction
	Impulse,
	// Multiply the vehicle's current velocity
	VelocityMultiplier,
	// Call Blueprint function "OnBoostPadActivated" on the vehicle
	BlueprintFunction
};

/**
 * Boost pad that increases vehicle speed when driven over.
 * Place these on your race track for speed boosts.
 */
UCLASS()
class HOVERVEHICLESYSTEM_API ABoostPad : public AActor
{
	GENERATED_BODY()

public:
	ABoostPad();

protected:
	virtual void BeginPlay() override;

	// ========== COMPONENTS ==========

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boost Pad|Components")
	UStaticMeshComponent* PadMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boost Pad|Components")
	UBoxComponent* TriggerBox;

	// ========== BOOST SETTINGS ==========

	// How the boost is applied
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost Pad")
	EBoostMode BoostMode = EBoostMode::Impulse;

	// Impulse mode: Force strength to apply
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost Pad", meta = (EditCondition = "BoostMode == EBoostMode::Impulse", ClampMin = "0.0"))
	float BoostImpulseStrength = 50000.0f;

	// VelocityMultiplier mode: Multiply current velocity by this amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost Pad", meta = (EditCondition = "BoostMode == EBoostMode::VelocityMultiplier", ClampMin = "1.0"))
	float VelocityMultiplier = 1.5f;

	// Cooldown time before the same vehicle can use this pad again
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost Pad", meta = (ClampMin = "0.0"))
	float BoostCooldown = 2.0f;

	// Show debug messages when activated?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost Pad|Debug")
	bool bShowDebugMessage = false;

	// ========== VISUAL FEEDBACK ==========

	// Called when a vehicle activates the boost pad
	UFUNCTION(BlueprintImplementableEvent, Category = "Boost Pad", meta = (DisplayName = "On Boost Activated"))
	void BP_OnBoostActivated(AActor* Vehicle);

	// Called when boost is on cooldown and vehicle tries to use it
	UFUNCTION(BlueprintImplementableEvent, Category = "Boost Pad", meta = (DisplayName = "On Boost Cooldown"))
	void BP_OnBoostCooldown(AActor* Vehicle, float RemainingCooldown);

private:
	UFUNCTION()
	void OnTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void ApplyBoost(AActor* Vehicle);
	void ApplyImpulseBoost(AActor* Vehicle, UPrimitiveComponent* RootComp);
	void ApplyVelocityBoost(AActor* Vehicle, UPrimitiveComponent* RootComp);
	void ApplyBlueprintBoost(AActor* Vehicle);

	// Track cooldown per vehicle
	UPROPERTY(Transient)
	TMap<AActor*, float> VehicleCooldowns;
};
