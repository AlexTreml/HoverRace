#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RespawnVolume.generated.h"

class ARaceManager;
class UBoxComponent;

/**
 * Trigger volume that respawns the vehicle when entered.
 * Place these around track edges where players can fall off.
 */
UCLASS()
class HOVERVEHICLESYSTEM_API ARespawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ARespawnVolume();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Respawn Volume")
	UBoxComponent* TriggerBox;

	// Optional: Set this in the editor, or leave empty to auto-find RaceManager
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Respawn Volume")
	ARaceManager* RaceManager;

	// Show debug message when triggered?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn Volume")
	bool bShowDebugMessage = false;

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

	void FindRaceManager();
};
