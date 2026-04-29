//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/MenuScreenWidget.h"
#include "Widgets/MenuBaseWidget.h"
#include "Widgets/IntroWidget.h"

UMenuScreenWidget::UMenuScreenWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UMenuScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (bHasIntro && IntroWidget)
	{
		CurrentActivatableWidget = MainMenuActivatableWidget->AddWidget(IntroWidget);

		if (CurrentActivatableWidget && CurrentActivatableWidget->GetClass()->IsChildOf(UIntroWidget::StaticClass()))
		{
			UIntroWidget* Intro = Cast<UIntroWidget>(CurrentActivatableWidget);

			Intro->ActivatableWidget = MainMenuActivatableWidget;
			Intro->MainMenuWidget = MainMenuWidget;
		}
	}
	else
	{
		if (MainMenuWidget)
		{
			CurrentActivatableWidget = MainMenuActivatableWidget->AddWidget(MainMenuWidget);

			if (CurrentActivatableWidget && CurrentActivatableWidget->GetClass()->IsChildOf(UMenuBaseWidget::StaticClass()))
			{
				UMenuBaseWidget* Menu = Cast<UMenuBaseWidget>(CurrentActivatableWidget);

				Menu->ActivatableWidget = MainMenuActivatableWidget;
			}
		}
	}
}

void UMenuScreenWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

}

void UMenuScreenWidget::SetMainScreen(TSubclassOf<UCommonActivatableWidget> Class)
{
	if (Class)
	{
		CurrentActivatableWidget = MainMenuActivatableWidget->AddWidget(Class);
	}
}

UCommonActivatableWidget* UMenuScreenWidget::OpenWidget(TSubclassOf<UCommonActivatableWidget> Widget, bool OpenInTab)
{
	if (MainMenuActivatableWidget)
	{
		MainMenuActivatableWidget->ClearWidgets();

		UCommonActivatableWidget* CActivatableWidget = MainMenuActivatableWidget->AddWidget(Widget);

		return CActivatableWidget;
	}
	else
	{
		return nullptr;
	}

}