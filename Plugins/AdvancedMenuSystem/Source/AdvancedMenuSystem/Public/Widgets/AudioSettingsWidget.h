//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/SliderWidget.h"
#include "Components/Button.h"
#include "Save/AudioSave.h"
#include "Kismet/GameplayStatics.h"
#include "CommonActivatableWidget.h"
#include "Sound/SoundClass.h"
#include "AudioSettingsWidget.generated.h"

/// <summary>
/// Audio setting param widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UAudioSettingsWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Master Slider
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USliderWidget* MasterSlider;

	/// <summary>
	/// SFX Slider
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USliderWidget* SFXSlider;

	/// <summary>
	/// Music Slider
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USliderWidget* MusicSlider;

	/// <summary>
	/// Voice Slider
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USliderWidget* VoiceSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* ApplyButton;

	UAudioSettingsWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	/// <summary>
	/// Master Sound Class variable.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	USoundClass* MasterSoundClass;

	/// <summary>
	/// SFX Sound Class variable.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	USoundClass* SFXSoundClass;

	/// <summary>
	/// Music Sound Class variable.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	USoundClass* MusicSoundClass;

	/// <summary>
	/// Voice Sound Class variable.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	USoundClass* VoiceSoundClass;

	/// <summary>
	/// Current slider master volume volume.
	/// </summary>
	float MasterVolume;

	/// <summary>
	/// SFX slider master volume volume.
	/// </summary>
	float SFXVolume;

	/// <summary>
	/// Music slider master volume volume.
	/// </summary>
	float MusicVolume;

	/// <summary>
	/// Voice slider master volume volume.
	/// </summary>
	float VoiceVolume;

	/// <summary>
	/// Instant settings applly.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bInstantApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* ResetButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TSubclassOf<UAudioSave> AudioSaveClass;

	/// <summary>
	/// Save settings to the save class.
	/// </summary>
	virtual void SaveSettings();

	virtual bool IsSettingsSaved();

	/// <summary>
	/// Load settings from save.
	/// </summary>
	virtual void LoadSettings();

	UFUNCTION()
	virtual void ResetSettings();

protected:

	/// <summary>
	/// This function only executes when master volume slider is changed.
	/// </summary>
	/// <param name="Value">New value</param>
	UFUNCTION()
	void OnMasterUpdate(float Value);

	/// <summary>
	/// This function only executes when SFX volume slider is changed.
	/// </summary>
	/// <param name="Value">New value</param>
	UFUNCTION()
	void OnSFXUpdate(float Value);

	/// <summary>
	/// This function only executes when music volume slider is changed.
	/// </summary>
	/// <param name="Value">New value</param>
	UFUNCTION()
	void OnMusicUpdate(float Value);

	/// <summary>
	/// This function only executes when voice volume slider is changed.
	/// </summary>
	/// <param name="Value">New value</param>
	UFUNCTION()
	void OnVoiceUpdate(float Value);

	/// <summary>
	/// This function only executes when the apply button is pressed.
	/// </summary>
	UFUNCTION()
	void OnApplyPress();

	virtual void SynchronizeProperties() override;

};
