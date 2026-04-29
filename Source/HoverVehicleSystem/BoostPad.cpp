// BoostPad.cpp — overlap-triggered speed boost with per-vehicle cooldown.

#include "BoostPad.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Pawn.h"
#include "HoverAIRacer.h"

/** @brief Construct mesh + trigger components and bind the overlap delegate. */
ABoostPad::ABoostPad()
{
	PrimaryActorTick.bCanEverTick = true;

	PadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PadMesh"));
	RootComponent = PadMesh;
	PadMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(200.0f, 200.0f, 50.0f));

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	TriggerBox->SetGenerateOverlapEvents(true);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABoostPad::OnTriggerBeginOverlap);
}

/** @brief No additional setup at runtime. */
void ABoostPad::BeginPlay()
{
	Super::BeginPlay();
}

/**
 * @brief Filter overlap to pawns, enforce per-vehicle cooldown, then dispatch to ApplyBoost.
 */
void ABoostPad::OnTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Only boost pawns (vehicles)
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn)
	{
		return;
	}

	// Check cooldown
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if (VehicleCooldowns.Contains(OtherActor))
	{
		const float LastBoostTime = VehicleCooldowns[OtherActor];
		const float TimeSinceBoost = CurrentTime - LastBoostTime;

		if (TimeSinceBoost < BoostCooldown)
		{
			const float RemainingCooldown = BoostCooldown - TimeSinceBoost;
			BP_OnBoostCooldown(OtherActor, RemainingCooldown);

			if (bShowDebugMessage && GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					(uint64)-1,
					1.0f,
					FColor::Orange,
					FString::Printf(TEXT("Boost cooldown: %.1fs"), RemainingCooldown)
				);
			}
			return;
		}
	}

	// Apply boost
	ApplyBoost(OtherActor);

	// Update cooldown
	VehicleCooldowns.Add(OtherActor, CurrentTime);

	// Trigger Blueprint event
	BP_OnBoostActivated(OtherActor);

	if (bShowDebugMessage && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			(uint64)-1,
			2.0f,
			FColor::Cyan,
			TEXT("BOOST!")
		);
	}
}

/**
 * @brief Route the boost: AI racers receive a timed speed multiplier;
 *        player vehicles route through Impulse / Velocity / Blueprint mode.
 */
void ABoostPad::ApplyBoost(AActor* Vehicle)
{
	if (!Vehicle)
	{
		return;
	}

	AHoverAIRacer* AIRacer = Cast<AHoverAIRacer>(Vehicle);
	if (AIRacer)
	{
		AIRacer->ApplyBoostPad(BoostImpulseStrength);
		return;
	}

	UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Vehicle->GetRootComponent());
	if (!RootComp)
	{
		return;
	}

	switch (BoostMode)
	{
		case EBoostMode::Impulse:
			ApplyImpulseBoost(Vehicle, RootComp);
			break;

		case EBoostMode::VelocityMultiplier:
			ApplyVelocityBoost(Vehicle, RootComp);
			break;

		case EBoostMode::BlueprintFunction:
			ApplyBlueprintBoost(Vehicle);
			break;
	}
}

/** @brief Add an impulse along the vehicle's forward vector. */
void ABoostPad::ApplyImpulseBoost(AActor* Vehicle, UPrimitiveComponent* RootComp)
{
	if (!RootComp || !RootComp->IsSimulatingPhysics())
	{
		return;
	}

	// Apply impulse in vehicle's forward direction
	const FVector ForwardDirection = Vehicle->GetActorForwardVector();
	const FVector Impulse = ForwardDirection * BoostImpulseStrength;
	RootComp->AddImpulse(Impulse, NAME_None, true);
}

/** @brief Multiply the vehicle's current physics velocity by VelocityMultiplier. */
void ABoostPad::ApplyVelocityBoost(AActor* Vehicle, UPrimitiveComponent* RootComp)
{
	if (!RootComp || !RootComp->IsSimulatingPhysics())
	{
		return;
	}

	// Multiply current velocity
	const FVector CurrentVelocity = RootComp->GetPhysicsLinearVelocity();
	const FVector BoostedVelocity = CurrentVelocity * VelocityMultiplier;
	RootComp->SetPhysicsLinearVelocity(BoostedVelocity);
}

/** @brief Call the Blueprint function `OnBoostPadActivated` on the vehicle, passing the boost strength. */
void ABoostPad::ApplyBlueprintBoost(AActor* Vehicle)
{
	UFunction* Function = Vehicle->FindFunction(FName("OnBoostPadActivated"));
	if (Function)
	{
		struct
		{
			float BoostStrength;
		} Params;

		Params.BoostStrength = (BoostMode == EBoostMode::Impulse)
			? BoostImpulseStrength
			: VelocityMultiplier;

		Vehicle->ProcessEvent(Function, &Params);
	}
}
