#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RaceGate.generated.h"

class ARaceManager;
class UBoxComponent;
class UPrimitiveComponent;
class USceneComponent;
class UStaticMeshComponent;
struct FHitResult;

UENUM(BlueprintType)
enum class ERaceGateType : uint8
{
    Start,
    Checkpoint,
    Finish
};

UCLASS(Blueprintable)
class HOVERVEHICLESYSTEM_API ARaceGate : public AActor
{
    GENERATED_BODY()

public:
    ARaceGate();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintPure, Category = "Race Gate")
    ERaceGateType GetGateType() const
    {
        return GateType;
    }

    UFUNCTION(BlueprintPure, Category = "Race Gate")
    int32 GetCheckpointIndex() const
    {
        return CheckpointIndex;
    }

    UFUNCTION(BlueprintCallable, Category = "Race Gate")
    void SetRaceManager(ARaceManager* InRaceManager)
    {
        RaceManager = InRaceManager;
    }

    UFUNCTION(BlueprintPure, Category = "Race Gate")
    ARaceManager* GetRaceManager() const
    {
        return RaceManager;
    }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race Gate|Components")
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race Gate|Components")
    UStaticMeshComponent* GateMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race Gate|Components")
    UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race Gate")
    ERaceGateType GateType = ERaceGateType::Checkpoint;

    // Per-instance order for checkpoint progression (0,1,2...).
    // Start/Finish gates ignore this value.
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Race Gate", meta = (ClampMin = "0"))
    int32 CheckpointIndex = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Race Gate")
    TSubclassOf<AActor> TriggeringActorClass;

private:
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Race Gate", meta = (AllowPrivateAccess = "true"))
    ARaceManager* RaceManager = nullptr;

    UFUNCTION()
    void OnTriggerBeginOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    ARaceManager* FindRaceManagerInLevel() const;
};
