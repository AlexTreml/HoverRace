// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SaveSettingsWindowBaseWidget.h"

USaveSettingsWindowBaseWidget::USaveSettingsWindowBaseWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void USaveSettingsWindowBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnYesPressed.Clear();

	OnNoPressed.Clear();

	OnYesPressed.AddDynamic(this, &USaveSettingsWindowBaseWidget::YesPressed);

	OnNoPressed.AddDynamic(this, &USaveSettingsWindowBaseWidget::NoPressed);


}

void USaveSettingsWindowBaseWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (Message)
	{
		Message->SetText(MessageText);
		Message->SetColorAndOpacity(MessageTextColor);
		Message->SetFont(MessageTextFont);
	}
}

void USaveSettingsWindowBaseWidget::YesPressed()
{
	if (MenuSettingsWidget)
	{
		MenuSettingsWidget->SaveChanges(true);
	}

	OnCloseSettings.Broadcast();
}

void USaveSettingsWindowBaseWidget::NoPressed()
{
	OnCloseSettings.Broadcast();
}

void USaveSettingsWindowBaseWidget::SetSettingsWidget(UMenuSettingsWidget* Widget)
{
	if (Widget)
	{
		MenuSettingsWidget = Widget;
	}
}