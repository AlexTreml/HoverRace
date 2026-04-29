//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MultiplayerSave.generated.h"

/// <summary>
/// Multiplayer settings save.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UMultiplayerSave : public USaveGame
{
	GENERATED_BODY()
	
public:

	UMultiplayerSave();

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
	/// Nickname string.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (BindWidget))
	FString Nickname;
};
