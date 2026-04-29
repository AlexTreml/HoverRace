//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#include "Widgets/SliderWidget.h"

USliderWidget::USliderWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MinSliderValue = 0.0f;
	MaxSliderValue = 1.0f;
	SliderOrientation = EOrientation::Orient_Horizontal;
	SliderBarColor = FLinearColor::White;
	SliderHandleColor = FLinearColor::White;
	SliderStepSize = 0.01f;
	IsSliderFocusable = true;
	MouseUsesStep = false;
	RequiresControllerLock = true;
}

void USliderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateSliderValues();

	Slider->OnMouseCaptureBegin.Clear();
	Slider->OnMouseCaptureEnd.Clear();
	Slider->OnControllerCaptureBegin.Clear();
	Slider->OnControllerCaptureBegin.Clear();
	Slider->OnValueChanged.Clear();

	Slider->OnMouseCaptureBegin.AddDynamic(this, &USliderWidget::SliderMouseCaptureBegin);
	Slider->OnMouseCaptureEnd.AddDynamic(this, &USliderWidget::SliderMouseCaptureEnd);
	Slider->OnControllerCaptureBegin.AddDynamic(this, &USliderWidget::SliderControllerCaptureBegin);
	Slider->OnControllerCaptureBegin.AddDynamic(this, &USliderWidget::SliderControllerCaptureEnd);
	Slider->OnValueChanged.AddDynamic(this, &USliderWidget::SliderOnValueChanged);
}

void USliderWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	UpdateSliderValues();
}

void USliderWidget::SliderMouseCaptureBegin()
{
	OnMouseCaptureBegin.Broadcast();
}

void USliderWidget::SliderMouseCaptureEnd()
{
	OnMouseCaptureEnd.Broadcast();
}

void USliderWidget::SliderControllerCaptureBegin()
{
	OnControllerCaptureBegin.Broadcast();
}

void USliderWidget::SliderControllerCaptureEnd()
{
	OnControllerCaptureEnd.Broadcast();
}

void USliderWidget::SliderOnValueChanged(float Value)
{
	SliderValueText->SetText(FText::AsCultureInvariant(FString::FromInt((int)Value)));

	OnValueChanged.Broadcast(Value);
}

void USliderWidget::UpdateSliderValues()
{
	if (Slider && SliderValueText)
	{
		Slider->SetValue(SliderValue);
		Slider->SetMinValue(MinSliderValue);
		Slider->SetMaxValue(MaxSliderValue);
		Slider->SetWidgetStyle(SliderWidgetStyle);
		Slider->SetOrientation(SliderOrientation);
		Slider->SetSliderBarColor(SliderBarColor);
		Slider->SetSliderHandleColor(SliderHandleColor);
		Slider->SetIndentHandle(SliderIndentHandle);
		Slider->SetLocked(SliderLocked);
		Slider->MouseUsesStep = MouseUsesStep;
		Slider->RequiresControllerLock = RequiresControllerLock;
		Slider->SetStepSize(SliderStepSize);
		Slider->IsFocusable = IsSliderFocusable;

		SliderValueText->SetText(FText::AsCultureInvariant(FString::FromInt((int)SliderValue)));
	}
}

void USliderWidget::SetSliderValue(float Value)
{
	SliderValue = Value;

	UpdateSliderValues();
}

void USliderWidget::SetSliderMinValue(float Value)
{
	MinSliderValue = Value;

	UpdateSliderValues();
}

void USliderWidget::SetSliderMaxValue(float Value)
{
	MaxSliderValue = Value;

	UpdateSliderValues();
}

void USliderWidget::SetSliderWidgetStyle(FSliderStyle Style)
{
	SliderWidgetStyle = Style;

	UpdateSliderValues();
}

void USliderWidget::SetSliderOrientation(TEnumAsByte<EOrientation> Orientation)
{
	SliderOrientation = Orientation;

	UpdateSliderValues();
}

void USliderWidget::SetSliderBarColor(FLinearColor Color)
{
	SliderBarColor = Color;

	UpdateSliderValues();
}

void USliderWidget::SetSliderHandleColor(FLinearColor Color)
{
	SliderHandleColor = Color;

	UpdateSliderValues();
}

void USliderWidget::SetIndentHandle(bool Value)
{
	SliderIndentHandle = Value;

	UpdateSliderValues();
}

void USliderWidget::SetSliderLocked(bool Value)
{
	SliderLocked = Value;

	UpdateSliderValues();
}

void USliderWidget::SetSliderMouseUsesStep(bool Value)
{
	MouseUsesStep = Value;

	UpdateSliderValues();
}

void USliderWidget::SetSliderStepSize(float Value)
{
	SliderStepSize = Value;

	UpdateSliderValues();
}

void USliderWidget::SetSliderRequiresControllerLock(bool Value)
{
	RequiresControllerLock = Value;

	UpdateSliderValues();
}

void USliderWidget::SetSliderFocusable(bool Value)
{
	IsSliderFocusable = Value;

	UpdateSliderValues();
}