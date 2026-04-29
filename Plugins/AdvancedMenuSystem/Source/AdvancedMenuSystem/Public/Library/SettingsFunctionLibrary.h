//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/SoundClass.h"
#include "InputMappingContext.h"
#include "SettingsFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDMENUSYSTEM_API USettingsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Settings")
	static void UpdateGraphics();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	static void UpdateVideo();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	static void UpdateAudio(TArray<USoundClass*> SoundClassArray);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	static void UpdateControls(UInputMappingContext* PlayerInputMapping);

};
