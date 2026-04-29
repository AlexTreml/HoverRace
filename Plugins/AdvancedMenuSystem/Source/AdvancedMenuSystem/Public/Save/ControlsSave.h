//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "EnhancedActionKeyMapping.h"
#include "ControlsSave.generated.h"

/// <summary>
/// Controls settings save.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UControlsSave : public USaveGame
{
	GENERATED_BODY()
	
public:

	UControlsSave();

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
	/// Key mappings array
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (BindWidget))
	TArray<FEnhancedActionKeyMapping> KeyArray;
};
