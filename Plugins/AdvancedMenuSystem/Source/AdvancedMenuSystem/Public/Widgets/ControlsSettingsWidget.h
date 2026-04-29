//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/KeyBindingWidget.h"
#include "Components/ScrollBox.h"
#include "Components/CanvasPanel.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Button.h"
#include "CommonActivatableWidget.h"
#include "Materials/Material.h"
#include "InputMappingContext.h"
#include "Save/ControlsSave.h"
#include "EnhancedActionKeyMapping.h"
#include "Engine/Texture2D.h"
#include "ControlsSettingsWidget.generated.h"

/// <summary>
/// Input setting param widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UControlsSettingsWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:

	/*Components*/
	
	/// <summary>
	/// Scroll box. Controlls will be added here.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	/// <summary>
	/// Apply settings button.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* ApplyButton;

	/// <summary>
	/// Key Bindings Setting widgets array.
	/// </summary>
	TArray<UKeyBindingWidget*> KeyBindingParamLineArr;

	/*Functions*/
	UControlsSettingsWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	/*Getters& Setters*/

	/// <summary>
	/// Sets text color for each setting.
	/// </summary>
	/// <param name="Color"></param>
	UFUNCTION(BlueprintSetter)
	void SetTitleTextColor(FColor Color);

	/// <summary>
	/// Setting text font for each setting.
	/// </summary>
	/// <param name="Font"></param>
	UFUNCTION(BlueprintSetter)
	void SetTitleTextFont(FSlateFontInfo Font);

	UFUNCTION(BlueprintSetter)
	void SetDefaultKeyArray(TArray<FEnhancedActionKeyMapping> Array);

	/*Parameters*/
	TArray<FEnhancedActionKeyMapping> KeyArray;

	/// <summary>
	/// Save which stores all controlls info.
	/// </summary>
	//UControlsSave* ControlsSave;

	/// <summary>
	/// Key binding widget class which will be used for each key setting.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Key Binding Parametr Widget Class"))
	TSubclassOf<UKeyBindingWidget> KeyBindingWidgetClass;

	/// <summary>
	/// Instant setting apply
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bInstantApply;

	/// <summary>
	/// Key binding type. Text or icons.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	EKeyBindingTypes KeyBindingType;

	/// <summary>
	/// Key binding icons. Only if KeyBindingType == EKeyBindingTypes::Icons.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Settings", meta = (AllowPrivateAccess = "true", EditCondition = "KeyBindingType == EKeyBindingTypes::Icons", EditConditionHides))
	TArray<FButtonIcon> ButtonIcons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	UInputMappingContext* PlayerInputMapping;

	/*Title text settings*/

	TArray<FEnhancedActionKeyMapping> DefaultKeyArray;

	/// <summary>
	/// True if update the title text.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Custom Title Text Style"))
	bool bCustomTitleTextStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* ResetButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TSubclassOf<UControlsSave> ControlsSaveClass;

	/// <summary>
	/// This function saves input mappings into the save.
	/// </summary>
	virtual void SaveInputMappings();

	/// <summary>
	/// This function checks whether or not settings are saved.
	/// </summary>
	/// <returns></returns>
	virtual bool IsSettingsSaved();

	/// <summary>
	/// This function loads data from game save into this class.
	/// </summary>
	virtual void LoadInputMappings();

	UFUNCTION()
	virtual void ResetSettings();

protected:

	/// <summary>
	/// This function adds a setting line to the scroll box.
	/// </summary>
	/// <param name="KeyIndex"></param>
	void AddKeyBindingParamLine(int KeyIndex);

	/// <summary>
	/// This function updates style for all settings.
	/// </summary>
	void UpdateTextBlock();

	/// <summary>
	/// This function runs on apply button press. Apply and save changes into save class.
	/// </summary>
	UFUNCTION()
	void OnApplyPress();

	/// <summary>
	/// Title text color of the key binding setting.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleTextColor, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Color", EditCondition = "bCustomTitleTextStyle == true", EditConditionHides))
	FColor TitleTextColor;

	/// <summary>
	/// Title text font of the key binding setting.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleTextFont, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Font", EditCondition = "bCustomTitleTextStyle == true", EditConditionHides))
	FSlateFontInfo TitleTextFont;

};
