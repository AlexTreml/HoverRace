//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SettingsParamBase.h"
#include "Components/Slider.h"
#include "SliderWidget.generated.h"

/// <summary>
/// Slider param setting widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API USliderWidget : public USettingsParamBase
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseCaptureBegin);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseCaptureEnd);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerCaptureBegin);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerCaptureEnd);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChanged, float, Value);

public:

	USliderWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UTextBlock* SliderValueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class USlider* Slider;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	UFUNCTION()
	void SliderMouseCaptureBegin();

	UFUNCTION()
	void SliderMouseCaptureEnd();

	UFUNCTION()
	void SliderControllerCaptureBegin();

	UFUNCTION()
	void SliderControllerCaptureEnd();

	UFUNCTION()
	void SliderOnValueChanged(float Value);

	void UpdateSliderValues();

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderValue(float Value);

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE float GetSliderValue() const { return Slider->GetValue(); }

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderMinValue(float Value);

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE float GetSliderMinValue() const { return MinSliderValue; }

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderMaxValue(float Value);

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE float GetSliderMaxValue() const { return MaxSliderValue; }

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderWidgetStyle(FSliderStyle Style);

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE FSliderStyle GetSliderWidgetStyle() const { return SliderWidgetStyle; }

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderOrientation(TEnumAsByte<EOrientation> Orientation);

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE TEnumAsByte<EOrientation> GetSliderOrientation() const { return SliderOrientation; }

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderBarColor(FLinearColor Color);

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE FLinearColor GetSliderBarColor() const { return SliderBarColor; }

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderHandleColor(FLinearColor Color);

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE FLinearColor GetSliderHandleColor() const { return SliderHandleColor; }

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetIndentHandle(bool Value);

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE bool HasIndentHandle() const { return SliderIndentHandle; }

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderLocked(bool Value);

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE bool IsSliderLocked() const { return SliderLocked; }

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderMouseUsesStep(bool Value);

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderRequiresControllerLock(bool Value);

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderStepSize(float Value);

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSliderFocusable(bool Value);

	/** Invoked when the mouse is pressed and a capture begins. */
	UPROPERTY(BlueprintAssignable, Category = "Widget Event")
	FOnMouseCaptureBegin OnMouseCaptureBegin;

	/** Invoked when the mouse is released and a capture ends. */
	UPROPERTY(BlueprintAssignable, Category = "Widget Event")
	FOnMouseCaptureEnd OnMouseCaptureEnd;

	/** Invoked when the controller capture begins. */
	UPROPERTY(BlueprintAssignable, Category = "Widget Event")
	FOnControllerCaptureBegin OnControllerCaptureBegin;

	/** Invoked when the controller capture ends. */
	UPROPERTY(BlueprintAssignable, Category = "Widget Event")
	FOnControllerCaptureEnd OnControllerCaptureEnd;

	/** Called when the value is changed by slider or typing. */
	UPROPERTY(BlueprintAssignable, Category = "Widget Event")
	FOnValueChanged OnValueChanged;

	/** The value to display. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetSliderValue, FieldNotify, BlueprintSetter = SetSliderValue, Category = "Settings|Slider", meta = (UIMin = "0", UIMax = "1", DisplayName = "Value"))
	float SliderValue;

	/** The minimum value the slider can be set to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetSliderMinValue, BlueprintSetter = SetSliderMinValue, Category = "Settings|Slider", meta = (DisplayName = "Min Value"))
	float MinSliderValue;

	/** The maximum value the slider can be set to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetSliderMaxValue, BlueprintSetter = SetSliderMaxValue, Category = "Settings|Slider", meta = (DisplayName = "Max Value"))
	float MaxSliderValue;

	/** The progress bar style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetSliderWidgetStyle, BlueprintGetter = GetSliderWidgetStyle, Category = "Settings|Slider", BlueprintSetter = SetSliderWidgetStyle, meta = (DisplayName = "Style"))
	FSliderStyle SliderWidgetStyle;

	/** The slider's orientation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetSliderOrientation, BlueprintSetter = SetSliderOrientation, Category = "Settings|Slider", meta = (DisplayName = "Orientation"))
	TEnumAsByte<EOrientation> SliderOrientation;

	/** The color to draw the slider bar in. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetSliderBarColor, BlueprintGetter = GetSliderBarColor, BlueprintSetter = SetSliderBarColor, Category = "Settings|Slider")
	FLinearColor SliderBarColor;

	/** The color to draw the slider handle in. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetSliderHandleColor, BlueprintSetter = SetSliderHandleColor, Category = "Settings|Slider")
	FLinearColor SliderHandleColor;

	/** Whether the slidable area should be indented to fit the handle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetIndentHandle, BlueprintSetter = SetIndentHandle, Category = "Settings|Slider", AdvancedDisplay)
	bool SliderIndentHandle;

	/** Whether the handle is interactive or fixed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetSliderLocked, BlueprintSetter = SetSliderLocked, Category = "Settings|Slider", AdvancedDisplay)
	bool SliderLocked;

	/** Sets new value if mouse position is greater/less than half the step size. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetSliderMouseUsesStep, BlueprintSetter = SetSliderMouseUsesStep, Category = "Settings|Slider", AdvancedDisplay)
	bool MouseUsesStep;

	/** Sets whether we have to lock input to change the slider value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Setter = SetSliderRequiresControllerLock, BlueprintSetter = SetSliderRequiresControllerLock, Category = "Settings|Slider", AdvancedDisplay)
	bool RequiresControllerLock;

	/** The amount to adjust the value by, when using a controller or keyboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetSliderStepSize, BlueprintSetter = SetSliderStepSize, Category = "Settings|Slider", meta = (UIMin = "0", UIMax = "1"))
	float SliderStepSize;

	/** Should the slider be focusable? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetSliderFocusable, BlueprintSetter = SetSliderFocusable, Category = "Settings|Slider")
	bool IsSliderFocusable;

};
