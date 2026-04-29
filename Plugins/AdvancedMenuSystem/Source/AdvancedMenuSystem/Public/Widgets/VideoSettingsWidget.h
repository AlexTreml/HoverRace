//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/ComboBoxWidget.h"
#include "Widgets/SliderWidget.h"
#include "Save/VideoSave.h"
#include "CommonActivatableWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/SwitchWidget.h"
#include "VideoSettingsWidget.generated.h"

/// <summary>
/// Game video settings widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UVideoSettingsWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	//Components

	/// <summary>
	/// Window Mode ComboBox
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USwitchWidget* WindowModeWidget;

	/// <summary>
	/// Aspect Ratio ComboBox
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UComboBoxWidget* AspectRatioBox;

	/// <summary>
	/// Resolutions ComboBox
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UComboBoxWidget* WindowResolutionBox;

	/// <summary>
	/// Brightness Slider
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USliderWidget* BrightnessSlider;

	/// <summary>
	/// Apply button
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* ApplyButton;

	//FPS

	/// <summary>
	/// FPS Lock switch widget
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USwitchWidget* LockFPSWidget;

	/// <summary>
	/// VSync widget
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USwitchWidget* VSyncWidget;

	//Colors

	/// <summary>
	/// HDR switch widget 
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USwitchWidget* HDRStatusWidget;

	/// <summary>
	/// HDR display profile switch widget
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USwitchWidget* HDRDisplayProfileWidget;

	/// <summary>
	/// HDR Color Space Switch widget
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USwitchWidget* HDRColorSpaceWidget;

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="ObjectInitializer"></param>
	UVideoSettingsWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	/// <summary>
	/// Properties synchronize
	/// </summary>
	virtual void SynchronizeProperties() override;

	/// <summary>
	/// This Function executes on brightness slider update.
	/// </summary>
	/// <param name="Value"></param>
	UFUNCTION()
	void OnBrightnessUpdate(float Value);

	/// <summary>
	/// Check if platform is desktop. We need that to avoid crashes on mobile, VR and other devices.
	/// </summary>
	void CheckIfCanChangeResolution();

	/// <summary>
	/// Executes on Lock FPS change.
	/// </summary>
	/// <param name="Value">New Value</param>
	UFUNCTION()
	void OnLockFPSChanged(int Value);

	/// <summary>
	/// Executes on VSync change. 
	/// </summary>
	/// <param name="Value">New Value</param>
	UFUNCTION()
	void OnVSyncChanged(int Value);

	/// <summary>
	/// Executes on window mode change. 
	/// </summary>
	/// <param name="Value">New Value</param>
	UFUNCTION()
	void OnWindowModeChanged(int Value);

	/// <summary>
	/// Executes on aspect ratio combo box change. 
	/// </summary>
	/// <param name="SelectedItem"></param>
	/// <param name="SelectionType"></param>
	UFUNCTION()
	void OnAspectRatioChange(FString SelectedItem, ESelectInfo::Type SelectionType);

	/// <summary>
	/// Executes on window resolution combo box change. 
	/// </summary>
	/// <param name="SelectedItem"></param>
	/// <param name="SelectionType"></param>
	UFUNCTION()
	void OnWindowResolutionBoxChange(FString SelectedItem, ESelectInfo::Type SelectionType);

	/// <summary>
	/// Executes on HDR change. 
	/// </summary>
	/// <param name="Value">New Value</param>
	UFUNCTION()
	void OnHDRChanged(int Value);

	/// <summary>
	/// True if platform is Desktop
	/// </summary>
	/// <returns>True if platform is Desktop</returns>
	bool IsDesktopPlatform()
	{
		bool IsInDesktop = false;

#ifdef PLATFORM_WINDOWS
		IsInDesktop = true;
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX
		IsInDesktop = true;
#endif // PLATFORM_LINUX

#ifdef PLATFORM_MAC
		IsInDesktop = true;
#endif // PLATFORM_MAC

		return IsInDesktop;
	};

	/// <summary>
	/// FPS Settings
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<FSetting> FPSSettings;

	/// <summary>
	/// HDR Settings
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<FSetting> HDRSettings;

	/// <summary>
	/// FPS switch widgets
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USwitchWidget*> FPSSwitches;

	/// <summary>
	///  HDR switch widgets
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USwitchWidget*> HDRSwitches;

	int GCD(int a, int b) {
		int R;
		while ((a % b) > 0) {
			R = a % b;
			a = b;
			b = R;
		}
		return b;
	}

	/// <summary>
	/// Returns all resolutions of the ratio.
	/// </summary>
	/// <param name="Ratio"></param>
	/// <returns>Returns all resolutions of the ratio.</returns>
	TArray<FIntPoint> GetResolutionsByRatio(FIntPoint Ratio);

	/// <summary>
	/// Returns the ratio of the resolution.
	/// </summary>
	/// <param name="Resolution"></param>
	/// <returns>Returns the ratio of the resolution.</returns>
	FIntPoint GetRatioByRess(FIntPoint Resolution);

	/// <summary>
	/// True if we need instatnt apply settings.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bInstantApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* ResetButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TSubclassOf<UVideoSave> VideoSaveClass;

	/// <summary>
	/// Save Settings
	/// </summary>
	virtual void SaveSettings();

	virtual bool IsSettingsSaved();

	UFUNCTION()
	virtual void ResetSettings();

protected:
	
	/// <summary>
	/// Current supported resolutions.
	/// </summary>
	TArray<FIntPoint> SupportedResolutions;

	/// <summary>
	/// Current supported aspect ratios.
	/// </summary>
	TArray<FIntPoint> SupportedAspectRatios;

	/// <summary>
	/// Current Resolution
	/// </summary>
	FIntPoint CurrentResolution;

	/// <summary>
	/// Current Aspect Ratio
	/// </summary>
	FIntPoint CurrentAspectRatio;

	///// <summary>
	///// Video saved information saved here.
	///// </summary>
	//UVideoSave* VideoSave;

	/// <summary>
	/// Loaded FPS Settings
	/// </summary>
	TArray<FSetting> FPSSettingsSave;

	/// <summary>
	/// Loaded HDR Settings
	/// </summary>
	TArray<FSetting> HDRSettingsSave;

	/// <summary>
	/// Load Settings
	/// </summary>
	virtual void LoadSettings();

	/// <summary>
	/// Set up window modes
	/// </summary>
	void SetUpWindowModes();

	/// <summary>
	/// FPS Lock values depending on the monitor refresh rate.
	/// </summary>
	void SetUpFPS();

	/// <summary>
	/// Get and set all resolutions into combo box.
	/// </summary>
	void SetUpResolutions();

	/// <summary>
	/// Set current brightness value.
	/// </summary>
	/// <param name="Value"></param>
	void SetUpBrightnessValue(float Value);

	/// <summary>
	/// Set HDR Settings
	/// </summary>
	void SetUpHDRSettings();

	/// <summary>
	/// Function that executes on Aplly press.
	/// </summary>
	UFUNCTION()
	void OnApplyPress();
};
