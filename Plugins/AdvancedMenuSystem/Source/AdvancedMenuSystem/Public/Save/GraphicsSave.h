//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Save/Variables.h"
#include "GraphicsSave.generated.h"

/// <summary>
/// Graphics settings save.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UGraphicsSave : public USaveGame
{
	GENERATED_BODY()
	
public:

	UGraphicsSave();

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
	/// General settings array
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (BindWidget))
	TArray<FSavedSetting> GeneralSettings;

	/// <summary>
	/// Advanced settings array
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (BindWidget))
	TArray<FSavedSetting> AdvancedSettings;

};
