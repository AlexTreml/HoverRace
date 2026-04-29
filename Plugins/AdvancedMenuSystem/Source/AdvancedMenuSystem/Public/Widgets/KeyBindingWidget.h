//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SettingsParamBase.h"
#include "Components/InputKeySelector.h"
#include "Save/Variables.h"
#include "UObject/ConstructorHelpers.h"
#include "KeyBindingWidget.generated.h"

/// <summary>
/// Input setting line widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UKeyBindingWidget : public USettingsParamBase
{
	GENERATED_BODY()
	
public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKeySelected, FInputChord, SelectedKey);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIsSelectingKeyChanged);

	/*General*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UInputKeySelector* InputKeySelector;

	UKeyBindingWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	void CheckInputType();

	/*Parametrs*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	EKeyBindingTypes Type;

	/*Input Key Selector: Default Parametrs*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetButtonStyle", Setter = "SetButtonStyle", Category = Appearance, meta = (DisplayName = "Style"))
	FButtonStyle WidgetButtonStyle;

		/** The button style used at runtime */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Appearance, meta = (DisplayName = "Text Style"))
	FTextBlockStyle TextStyle;

		/** The currently selected key chord. */
	UPROPERTY(BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetSelectedKey", FieldNotify, Category = "Key Selection")
	FInputChord SelectedKey;

		/** The amount of blank space around the text used to display the currently selected key. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = Appearance)
	FMargin Margin;

		/** Sets the text which is displayed while selecting keys. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetKeySelectionText", Category = Appearance)
	FText KeySelectionText;

		/** Sets the text to display when no key text is available or not selecting a key. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetNoKeySpecifiedText", Category = Appearance)
	FText NoKeySpecifiedText;

		/**
		 * When true modifier keys such as control and alt are allowed in the
		 * input chord representing the selected key, if false modifier keys are ignored.
		 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "AllowModifierKeys", Setter = "SetAllowModifierKeys", BlueprintSetter = "SetAllowModifierKeys", Category = "Key Selection")
	bool bAllowModifierKeys;

		/** When true gamepad keys are allowed in the input chord representing the selected key, otherwise they are ignored. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "AllowGamepadKeys", Setter = "SetAllowGamepadKeys", BlueprintSetter = "SetAllowGamepadKeys", Category = "Key Selection")
	bool bAllowGamepadKeys;

	/** When true gamepad keys are allowed in the input chord representing the selected key, otherwise they are ignored. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key Selection")
	TArray<FKey> EscapeKeys;

	/** Called whenever a new key is selected by the user. */
	UPROPERTY(BlueprintAssignable, Category = "Widget Event")
	FOnKeySelected OnKeySelected;

	/** Called whenever the key selection mode starts or stops. */
	UPROPERTY(BlueprintAssignable, Category = "Widget Event")
	FOnIsSelectingKeyChanged OnIsSelectingKeyChanged;

	/*Setters & Getters*/

	/** Sets the currently selected key. */
	UFUNCTION(BlueprintCallable, Category = "Widget")
	 void SetSelectedKey(const FInputChord& InSelectedKey);

	/** Returns the currently selected key. */
	 FInputChord GetSelectedKey() const;

	/** Sets the text which is displayed while selecting keys. */
	UFUNCTION(BlueprintCallable, Category = "Widget")
	 void SetKeySelectionText(FText InKeySelectionText);

	/** Returns the text which is displayed while selecting keys. */
	 const FText& GetKeySelectionText() const;

	/** Sets the text to display when no key text is available or not selecting a key. */
	UFUNCTION(BlueprintCallable, Category = "Widget")
	 void SetNoKeySpecifiedText(FText InNoKeySpecifiedText);

	/** Returns the text to display when no key text is available or not selecting a key. */
	 const FText& GetNoKeySpecifiedText() const;

	/** Sets whether or not modifier keys are allowed in the selected key. */
	UFUNCTION(BlueprintCallable, Category = "Widget")
	 void SetAllowModifierKeys(bool bInAllowModifierKeys);

	/** Returns true if modifier keys keys are allowed, otherwise returns false. */
	 bool AllowModifierKeys() const;

	/** Sets whether or not gamepad keys are allowed in the selected key. */
	UFUNCTION(BlueprintCallable, Category = "Widget")
	 void SetAllowGamepadKeys(bool bInAllowGamepadKeys);

	/** Returns true if gamepad keys are allowed, otherwise returns false. */
	 bool AllowGamepadKeys() const;

	/** Returns true if the widget is currently selecting a key, otherwise returns false. */
	UFUNCTION(BlueprintCallable, Category = "Widget")
	 bool GetIsSelectingKey() const;

	/** Sets the visibility of the text block. */
	UFUNCTION(BlueprintCallable, Category = "Widget")
	 void SetSelectionBlockVisibility(const ESlateVisibility InVisibility);

	/** Sets the style of the button used to start key selection mode. */
	 void SetButtonStyle(const FButtonStyle& ButtonStyle);

	/** Sets the style of the button used to start key selection mode. */
	void SetButtonStyle(const FButtonStyle* ButtonStyle);

	/** Returns the style of the button used to start key selection mode. */
	 const FButtonStyle& GetButtonStyle() const;

	/** Sets the style of the text used inside the button. */
	 void SetTextStyle(const FTextBlockStyle& InTextStyle);

	/** Returns the style of the text used inside the button. */
	 const FTextBlockStyle& GetTextStyle() const;

	/** Sets the amount of blank space around the text used to display the currently selected key. */
	 void SetMargin(const FMargin& InMargin);

	/** Returns the amount of blank space around the text used to display the currently selected key. */
	 const FMargin& GetMargin() const;

	/** Sets escape keys. */
	UFUNCTION(BlueprintCallable, Category = "Widget")
	 void SetEscapeKeys(const TArray<FKey>& InKeys);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	 EKeyBindingTypes KeyBindingType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true", EditCondition = "KeyBindingType == EKeyBindingTypes::Icons", EditConditionHides))
	 TArray<FButtonIcon> ButtonIcons;

	 void UpdateIcon(FInputChord Key);

private:

	UFUNCTION()
	void KeySelected(FInputChord Key);

	UFUNCTION()
	void IsSelectingKeyChanged();

};
