//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/SwitchWidget.h"
#include "Save/GraphicsSave.h"
#include "Components/Button.h"
#include "CommonActivatableWidget.h"
#include "GraphicsSettingsWidget.generated.h"

/// <summary>
/// Game graphics settings widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UGraphicsSettingsWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:

	UGraphicsSettingsWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USwitchWidget* ShadowQualityWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USwitchWidget* TextureQualityWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USwitchWidget* EffectsQualityWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* FoliageQualityWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* ViewDistanceQualityWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USwitchWidget* AntiAliasingQualityWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* GlobalIlluminationQualityWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* ReflectionQualityWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USwitchWidget* PostProcessQualityWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* ShadingQualityWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USwitchWidget*> GeneralSwitches;

	//Advanced 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* GIMWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* ReflectionMethodWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* MotionBlurWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* LensFlaresWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* BloomWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* AmbientOcclusionWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* AntiAliasingMethodWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class USwitchWidget* MSAACountWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* ApplyButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* ResetButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USwitchWidget*> AdvancedSwitches;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TSubclassOf<UGraphicsSave> GraphicsSaveClass;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void SaveSettings();

	UFUNCTION()
	virtual bool IsSettingsSaved();

	UFUNCTION()
	virtual void LoadSettings();

	UFUNCTION()
	virtual void ResetSettings();

protected:

	//virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<FSetting> Settings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<FSetting> AdvancedSettings;

	TArray<FSetting> SettingsSave;
	TArray<FSetting> AdvancedSettingsSave;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bInstantApply;

	//UGraphicsSave* SaveGraphics;

	UFUNCTION()
	void OnShadowQualityChanged(int Value);

	UFUNCTION()
	void OnTextureQualityChanged(int Value);

	UFUNCTION()
	void OnEffectsQualityChanged(int Value);

	UFUNCTION()
	void OnFoliageQualityChanged(int Value);

	UFUNCTION()
	void OnViewDistanceQualityChanged(int Value);

	UFUNCTION()
	void OnAntiAliasingQualityChanged(int Value);

	UFUNCTION()
	void OnGlobalIlluminationQualityChanged(int Value);

	UFUNCTION()
	void OnReflectionQualityChanged(int Value);

	UFUNCTION()
	void OnPostProcessQualityChanged(int Value);

	UFUNCTION()
	void OnShadingQualityChanged(int Value);

	//Advanced

	UFUNCTION()
	void OnGIMChanged(int Value);

	UFUNCTION()
	void OnReflectionMethodChanged(int Value);

	UFUNCTION()
	void OnMotionBlurChanged(int Value);

	UFUNCTION()
	void OnLensFlaresChanged(int Value);

	UFUNCTION()
	void OnBloomChanged(int Value);

	UFUNCTION()
	void OnAmbientOcclusionChanged(int Value);

	UFUNCTION()
	void OnAntiAliasingMethodChanged(int Value);

	UFUNCTION()
	void OnMSAACountChanged(int Value);

	UFUNCTION()
	void OnApplyPress();

private:

	void CheckValuesNum();

};
