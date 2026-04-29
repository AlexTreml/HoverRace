//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#include "Widgets/MenuBaseWidget.h"
#include "Widgets/MenuSettingsWidget.h"
#include "Widgets/QuitGameWindowWidget.h"

UMenuBaseWidget::UMenuBaseWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bOpenTabFullScreen = true;

	bHasSettings = true;
	bHasQuitGame = true;
	
}

void UMenuBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (bHasStartButton)
	{
		StartButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		StartButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (bHasSettings)
	{
		SettingsButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SettingsButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (bHasQuitGame)
	{
		QuitGameButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		QuitGameButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	StartButton->OnPressed.Clear();
	SettingsButton->OnPressed.Clear();
	QuitGameButton->OnPressed.Clear();

	StartButton->OnClicked.Clear();
	SettingsButton->OnClicked.Clear();
	QuitGameButton->OnClicked.Clear();

	StartButton->OnReleased.Clear();
	SettingsButton->OnReleased.Clear();
	QuitGameButton->OnReleased.Clear();

	StartButton->OnHovered.Clear();
	SettingsButton->OnHovered.Clear();
	QuitGameButton->OnHovered.Clear();

	StartButton->OnUnhovered.Clear();
	SettingsButton->OnUnhovered.Clear();
	QuitGameButton->OnUnhovered.Clear();

	StartButton->OnPressed.AddDynamic(this, &UMenuBaseWidget::Start_Pressed);
	SettingsButton->OnPressed.AddDynamic(this, &UMenuBaseWidget::Settings_Pressed);
	QuitGameButton->OnPressed.AddDynamic(this, &UMenuBaseWidget::QuitGame_Pressed);

	StartButton->OnClicked.AddDynamic(this, &UMenuBaseWidget::Start_Clicked);
	SettingsButton->OnClicked.AddDynamic(this, &UMenuBaseWidget::Settings_Clicked);
	QuitGameButton->OnClicked.AddDynamic(this, &UMenuBaseWidget::QuitGame_Clicked);

	StartButton->OnReleased.AddDynamic(this, &UMenuBaseWidget::Start_Released);
	SettingsButton->OnReleased.AddDynamic(this, &UMenuBaseWidget::Settings_Released);
	QuitGameButton->OnReleased.AddDynamic(this, &UMenuBaseWidget::QuitGame_Released);

	StartButton->OnHovered.AddDynamic(this, &UMenuBaseWidget::Start_Hovered);
	SettingsButton->OnHovered.AddDynamic(this, &UMenuBaseWidget::Settings_Hovered);
	QuitGameButton->OnHovered.AddDynamic(this, &UMenuBaseWidget::QuitGame_Hovered);

	StartButton->OnUnhovered.AddDynamic(this, &UMenuBaseWidget::Start_UnHovered);
	SettingsButton->OnUnhovered.AddDynamic(this, &UMenuBaseWidget::Settings_UnHovered);
	QuitGameButton->OnUnhovered.AddDynamic(this, &UMenuBaseWidget::QuitGame_UnHovered);
}

void UMenuBaseWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

}

void UMenuBaseWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

UCommonActivatableWidget* UMenuBaseWidget::OpenWidget(TSubclassOf<UCommonActivatableWidget> Widget, bool OpenInTab)
{
	if (!OpenInTab)
	{
		if (ActivatableWidget)
		{
			ActivatableWidget->ClearWidgets();

			UCommonActivatableWidget* CurrentActivatableWidget = ActivatableWidget->AddWidget(Widget);

			return CurrentActivatableWidget;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		if (TabActivatableWidget)
		{
			TabActivatableWidget->ClearWidgets();

			UCommonActivatableWidget* CurrentActivatableWidget = TabActivatableWidget->AddWidget(Widget);

			return CurrentActivatableWidget;
		}
		else
		{
			return nullptr;
		}
	}
}

UCommonActivatableWidget* UMenuBaseWidget::ShowDialogWindow(TSubclassOf<UCommonActivatableWidget> Widget, FText Message)
{
	UCommonActivatableWidget* CurrentActivatableWidget = nullptr;

	if (WindowActivatableWidget)
	{
		WindowActivatableWidget->ClearWidgets();

		CurrentActivatableWidget = WindowActivatableWidget->AddWidget(Widget);

		if (CurrentActivatableWidget)
		{
			if (CurrentActivatableWidget->GetClass()->IsChildOf(UQuestionWindowBaseWidget::StaticClass()))
			{
				UQuestionWindowBaseWidget* N_Widget = Cast<UQuestionWindowBaseWidget>(CurrentActivatableWidget);

				N_Widget->SetMessageText(Message);
			}
		}
	}

	return CurrentActivatableWidget;
}

void UMenuBaseWidget::RemoveDialogWindow()
{
	WindowActivatableWidget->ClearWidgets();
}

void UMenuBaseWidget::Settings_Pressed()
{
	OnSettingsPressed.Broadcast();

	if (DoOnSettingsType == EOpenWidgetTypes::OpenWidget)
	{
		if (bOpenTabFullScreen)
		{
			if (ActivatableWidget)
			{
				ActivatableWidget->ClearWidgets();

				SettingsActivatableWidget = ActivatableWidget->AddWidget(SettingsWidget);

				if (SettingsActivatableWidget)
				{
					if (SettingsActivatableWidget->GetClass()->IsChildOf(UMenuSettingsWidget::StaticClass()))
					{
						UMenuSettingsWidget* MenuSettingsWidget = Cast<UMenuSettingsWidget>(SettingsActivatableWidget);

						MenuSettingsWidget->MainMenuActivatableWidget = ActivatableWidget;

						MenuSettingsWidget->bIsInFullscreen = true;
					}
				}
			}
		}
		else
		{
			if (TabActivatableWidget)
			{
				if (!bSettingsOpened)
				{
					TabActivatableWidget->ClearWidgets();

					SettingsActivatableWidget = TabActivatableWidget->AddWidget(SettingsWidget);

					if (SettingsActivatableWidget)
					{
						if (SettingsActivatableWidget->GetClass()->IsChildOf(UMenuSettingsWidget::StaticClass()))
						{
							UMenuSettingsWidget* MenuSettingsWidget = Cast<UMenuSettingsWidget>(SettingsActivatableWidget);

							MenuSettingsWidget->MainMenuActivatableWidget = ActivatableWidget;
							MenuSettingsWidget->bIsInFullscreen = false;
							MenuSettingsWidget->ParentMenu = this;
							MenuSettingsWidget->SaveWindowActivatedWidget = WindowActivatableWidget;
						}
					}

					bSettingsOpened = true;
				}
				else
				{
					if (SettingsActivatableWidget)
					{
						if (SettingsActivatableWidget->GetClass()->IsChildOf(UMenuSettingsWidget::StaticClass()))
						{
							UMenuSettingsWidget* MenuSettingsWidget = Cast<UMenuSettingsWidget>(SettingsActivatableWidget);

							MenuSettingsWidget->CloseSettings();
						}
					}
				}
			}
		}
	}
}

void UMenuBaseWidget::Start_Pressed()
{
	OnStartPressed.Broadcast();

	if (DoOnStartType == EOpenWidgetTypes::OpenWidget)
	{
		if (bHasStartButton)
		{
			if (ActivatableWidget)
			{
				ActivatableWidget->ClearWidgets();

				UCommonActivatableWidget* CurrentActivatableWidget = ActivatableWidget->AddWidget(StartWidget);
			}
		}
		else
		{
			if (TabActivatableWidget)
			{
				TabActivatableWidget->ClearWidgets();

				if (!bStartOpened)
				{
					UCommonActivatableWidget* CurrentActivatableWidget = TabActivatableWidget->AddWidget(StartWidget);

					bStartOpened = true;
				}
				else
				{
					bStartOpened = false;
				}
			}
		}
	}
}

void UMenuBaseWidget::QuitGame_Pressed()
{
	OnQuitPressed.Broadcast();

	if (DoOnQuitGameType == EOpenWidgetTypes::OpenWidget)
	{
		if (WindowActivatableWidget)
		{
			WindowActivatableWidget->ClearWidgets();

			UCommonActivatableWidget* CurrentActivatableWidget = WindowActivatableWidget->AddWidget(QuitGameWidget);

			if (CurrentActivatableWidget)
			{
				if (CurrentActivatableWidget->GetClass()->IsChildOf(UQuitGameWindowWidget::StaticClass()))
				{
					UQuitGameWindowWidget* QuitWidget = Cast<UQuitGameWindowWidget>(CurrentActivatableWidget);

					QuitWidget->ThisActivatableWidget = WindowActivatableWidget;
				}
			}
		}
	}
}

void UMenuBaseWidget::Start_Clicked()
{
	OnStartClicked.Broadcast();
}

void UMenuBaseWidget::Start_Released()
{
	OnStartReleased.Broadcast();
}

void UMenuBaseWidget::Start_Hovered()
{
	OnStartHovered.Broadcast();
}

void UMenuBaseWidget::Start_UnHovered()
{
	OnStartUnHovered.Broadcast();
}

void UMenuBaseWidget::Settings_Clicked()
{
	OnSettingsClicked.Broadcast();
}

void UMenuBaseWidget::Settings_Released()
{
	OnSettingsReleased.Broadcast();
}

void UMenuBaseWidget::Settings_Hovered()
{
	OnSettingsHovered.Broadcast();
}

void UMenuBaseWidget::Settings_UnHovered()
{
	OnSettingsUnHovered.Broadcast();
}

void UMenuBaseWidget::QuitGame_Clicked()
{
	OnQuitClicked.Broadcast();
}

void UMenuBaseWidget::QuitGame_Released()
{
	OnQuitReleased.Broadcast();
}

void UMenuBaseWidget::QuitGame_Hovered()
{
	OnQuitHovered.Broadcast();
}

void UMenuBaseWidget::QuitGame_UnHovered()
{
	OnQuitUnHovered.Broadcast();
}


void UMenuBaseWidget::UpdateSettingOpened()
{
	if (bSettingsOpened)
	{
		bSettingsOpened = false;
	}
}