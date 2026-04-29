#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HoverVehiclePlayerController.generated.h"

class ARaceManager;
class UHoverRaceUI;

UCLASS(Blueprintable)
class HOVERVEHICLESYSTEM_API AHoverVehiclePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void OnPossess(APawn* InPawn) override;
    virtual void SetupInputComponent() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UHoverRaceUI> RaceUIClass;

    UPROPERTY(Transient, BlueprintReadOnly, Category = "UI")
    TObjectPtr<UHoverRaceUI> RaceUI;

    // Generic pawn pointer - works with Blueprint FlyingPawn
    UPROPERTY(Transient, BlueprintReadOnly, Category = "Runtime")
    TObjectPtr<APawn> ControlledVehicle;

    UPROPERTY(Transient, BlueprintReadOnly, Category = "Runtime")
    TObjectPtr<ARaceManager> RaceManager;

private:
    void CacheRuntimeReferences();
    void UpdateUI();
    void ResetVehicle();
};
