//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AudioSave.generated.h"

/// <summary>
/// Audio settings save.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UAudioSave : public USaveGame
{
	GENERATED_BODY()
	
public:

	UAudioSave();

	/// <summary>
	/// Save slot name
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	/// <summary>
	/// Default User index
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 DefaultUserIndex;

	/// <summary>
	/// Volume Settings values
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (BindWidget))
	TArray<float> VolumeSettings;

};
