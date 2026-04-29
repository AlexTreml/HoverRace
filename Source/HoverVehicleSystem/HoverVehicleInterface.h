// HoverVehicleInterface.h
// Interface for Blueprint hover vehicles to work with C++ race system

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HoverVehicleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UHoverVehicleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface that Blueprint hover vehicles should implement
 * to work with C++ race mechanics
 *
 * NOTE: You don't need to implement this interface!
 * Just add the functions GetCurrentForwardSpeed() and SetMovementLockedByRace()
 * to your FlyingPawn Blueprint and C++ will call them automatically.
 */
class IHoverVehicleInterface
{
	GENERATED_BODY()

public:
	// These are optional - not required for the Blueprint integration to work
	// The C++ code uses FindFunction() instead of this interface
};
