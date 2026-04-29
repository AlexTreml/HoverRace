//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Save/Variables.h"
#include "VideoSave.generated.h"

/// <summary>
/// Video settings save.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UVideoSave : public USaveGame
{
	GENERATED_BODY()
	
public:

	UVideoSave();

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
	/// FPS Settings
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (BindWidget))
	TArray<FSavedSetting> FPSSettings;

	/// <summary>
	/// HDR Settings
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (BindWidget))
	TArray<FSavedSetting> HDRSettings;

	/// <summary>
	/// Saved resolution
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (BindWidget))
	FIntPoint Resolution;

	/// <summary>
	/// Saved aspect ratio
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (BindWidget))
	FIntPoint AspectRatio;

	/// <summary>
	/// Saved Window Mode
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (BindWidget))
	int WindowMode;

	/// <summary>
	/// Saved brightness
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (BindWidget))
	float Brightness;

};
