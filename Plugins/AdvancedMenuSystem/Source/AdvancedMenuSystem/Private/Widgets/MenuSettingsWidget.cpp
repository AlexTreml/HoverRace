//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/MenuSettingsWidget.h"
#include "Widgets/MenuBaseWidget.h"
#include "Widgets/GraphicsSettingsWidget.h"
#include "Widgets/VideoSettingsWidget.h"
#include "Widgets/SaveSettingsWindowBaseWidget.h"
#include "Widgets/ControlsSettingsWidget.h"
#include "Widgets/AudioSettingsWidget.h"

UMenuSettingsWidget::UMenuSettingsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SaveWindowActivatedWidget = QuestionActivatableWidget;
}

void UMenuSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BackButton->OnPressed.Clear();

	VideoButton->OnPressed.Clear();
	GraphicsButton->OnPressed.Clear();
	AudioButton->OnPressed.Clear();
	ControlsButton->OnPressed.Clear();

	BackButton->OnPressed.AddDynamic(this, &UMenuSettingsWidget::Back_Pressed);

	VideoButton->OnPressed.AddDynamic(this, &UMenuSettingsWidget::Video_Pressed);
	GraphicsButton->OnPressed.AddDynamic(this, &UMenuSettingsWidget::Graphics_Pressed);
	AudioButton->OnPressed.AddDynamic(this, &UMenuSettingsWidget::Audio_Pressed);
	ControlsButton->OnPressed.AddDynamic(this, &UMenuSettingsWidget::Controls_Pressed);

	if (!SaveWindowActivatedWidget)
	{
		SaveWindowActivatedWidget = QuestionActivatableWidget;
	}

	if (SettingsActivatableWidget && VideoSettingsWidget)
	{
		CurrentActivatedWidget = SettingsActivatableWidget->AddWidget(VideoSettingsWidget);
	}
}

void UMenuSettingsWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

}

void UMenuSettingsWidget::Back_Pressed()
{
	CloseSettings();
}

void UMenuSettingsWidget::Video_Pressed()
{
	if (!CurrentActivatedWidget->GetClass()->IsChildOf(UVideoSettingsWidget::StaticClass()))
	{
		bool NeedToSave = CheckSettingsChanged();

		if (NeedToSave)
		{
			OnMoveToWidgetEvent.Clear();
			OnMoveToWidgetEvent.AddDynamic(this, &UMenuSettingsWidget::OpenVideo);

			OpenSaveChangesDialog(false);
		}
		else
		{
			OpenVideo();
		}
	}
}

void UMenuSettingsWidget::Graphics_Pressed()
{
	if (!CurrentActivatedWidget->GetClass()->IsChildOf(UGraphicsSettingsWidget::StaticClass()))
	{
		bool NeedToSave = CheckSettingsChanged();

		if (NeedToSave)
		{
			OnMoveToWidgetEvent.Clear();
			OnMoveToWidgetEvent.AddDynamic(this, &UMenuSettingsWidget::OpenGraphics);

			OpenSaveChangesDialog(false);
		}
		else
		{
			OpenGraphics();
		}
	}
}

void UMenuSettingsWidget::Audio_Pressed()
{
	if (!CurrentActivatedWidget->GetClass()->IsChildOf(UAudioSettingsWidget::StaticClass()))
	{
		bool NeedToSave = CheckSettingsChanged();

		if (NeedToSave)
		{
			OnMoveToWidgetEvent.Clear();
			OnMoveToWidgetEvent.AddDynamic(this, &UMenuSettingsWidget::OpenAudio);

			OpenSaveChangesDialog(false);
		}
		else
		{
			OpenAudio();
		}
	}
}

void UMenuSettingsWidget::Controls_Pressed()
{
	if (!CurrentActivatedWidget->GetClass()->IsChildOf(UControlsSettingsWidget::StaticClass()))
	{
		bool NeedToSave = CheckSettingsChanged();

		if (NeedToSave)
		{
			OnMoveToWidgetEvent.Clear();
			OnMoveToWidgetEvent.AddDynamic(this, &UMenuSettingsWidget::OpenControls);

			OpenSaveChangesDialog(false);
		}
		else
		{
			OpenControls();
		}
	}
}

void UMenuSettingsWidget::CloseSettings()
{
	bool NeedToSave = CheckSettingsChanged();

	if (NeedToSave)
	{
		OpenSaveChangesDialog(true);
	}
	else
	{
		if (bIsInFullscreen)
		{
			CloseSettingsFullScreen();
		}
		else
		{
			CloseSettingsTab();
		}
	}
}

bool UMenuSettingsWidget::CheckSettingsChanged()
{
	bool bSettingsChanged = false;

	if (CurrentActivatedWidget)
	{
		if (CurrentActivatedWidget->GetClass()->IsChildOf(UGraphicsSettingsWidget::StaticClass()))
		{
			UGraphicsSettingsWidget* GraphicsSettings = Cast<UGraphicsSettingsWidget>(CurrentActivatedWidget);

			if (GraphicsSettings)
			{
				bSettingsChanged = !GraphicsSettings->IsSettingsSaved();
			}
		}
		else if (CurrentActivatedWidget->GetClass()->IsChildOf(UVideoSettingsWidget::StaticClass()))
		{
			UVideoSettingsWidget* VideoSettings = Cast<UVideoSettingsWidget>(CurrentActivatedWidget);

			if (VideoSettings)
			{
				bSettingsChanged = !VideoSettings->IsSettingsSaved();
			}
		}
		else if (CurrentActivatedWidget->GetClass()->IsChildOf(UAudioSettingsWidget::StaticClass()))
		{
			UAudioSettingsWidget* AudioSettings = Cast<UAudioSettingsWidget>(CurrentActivatedWidget);

			if (AudioSettings)
			{
				bSettingsChanged = !AudioSettings->IsSettingsSaved();
			}
		}
		else if (CurrentActivatedWidget->GetClass()->IsChildOf(UControlsSettingsWidget::StaticClass()))
		{
			UControlsSettingsWidget* ControlsSettings = Cast<UControlsSettingsWidget>(CurrentActivatedWidget);

			if (ControlsSettings)
			{
				bSettingsChanged = !ControlsSettings->IsSettingsSaved();
			}
		}
	}

	return bSettingsChanged;
}

void UMenuSettingsWidget::OpenSaveChangesDialog(bool AutoClouse)
{
	if (MainMenuActivatableWidget && SaveWindowActivatedWidget)
	{
		SaveWindowActivatedWidget->ClearWidgets();
		SaveActivatedWidget = SaveWindowActivatedWidget->AddWidget(WindowSaveWidget);

		if (SaveActivatedWidget && SaveActivatedWidget->GetClass()->IsChildOf(USaveSettingsWindowBaseWidget::StaticClass()))
		{
			USaveSettingsWindowBaseWidget* Window = Cast<USaveSettingsWindowBaseWidget>(SaveActivatedWidget);

			if (Window)
			{
				Window->MenuSettingsWidget = this;
				Window->MenuBaseWidget = Cast<UMenuBaseWidget>(ParentMenu);
				Window->ThisActivatableWidget = SaveWindowActivatedWidget;
				Window->bAutoClouse = AutoClouse;

				Window->OnCloseSettings.Clear();

				if (AutoClouse)
				{
					if (bIsInFullscreen)
					{
						Window->OnCloseSettings.AddDynamic(this, &UMenuSettingsWidget::CloseSettingsFullScreen);
					}
					else
					{
						Window->OnCloseSettings.AddDynamic(this, &UMenuSettingsWidget::CloseSettingsTab);
					}
				}
				else
				{
					Window->OnCloseSettings.AddDynamic(this, &UMenuSettingsWidget::CloseSaveWindow);
				}
			}
		}
	}
}

void UMenuSettingsWidget::SaveChanges(bool CloseSettings)
{
	if (CurrentActivatedWidget)
	{
		if(CurrentActivatedWidget->GetClass()->IsChildOf(UGraphicsSettingsWidget::StaticClass()))
		{
			UGraphicsSettingsWidget* GraphicsSettings = Cast<UGraphicsSettingsWidget>(CurrentActivatedWidget);

			if (GraphicsSettings)
			{
				GraphicsSettings->SaveSettings();
			}
		}
		else if (CurrentActivatedWidget->GetClass()->IsChildOf(UVideoSettingsWidget::StaticClass()))
		{
			UVideoSettingsWidget* VideoSettings = Cast<UVideoSettingsWidget>(CurrentActivatedWidget);

			if (VideoSettings)
			{
				VideoSettings->SaveSettings();
			}
		}
		else if (CurrentActivatedWidget->GetClass()->IsChildOf(UAudioSettingsWidget::StaticClass()))
		{
			UAudioSettingsWidget* AudioSettings = Cast<UAudioSettingsWidget>(CurrentActivatedWidget);

			if (AudioSettings)
			{
				AudioSettings->SaveSettings();
			}
		}
		else if (CurrentActivatedWidget->GetClass()->IsChildOf(UControlsSettingsWidget::StaticClass()))
		{
			UControlsSettingsWidget* ControlsSettings = Cast<UControlsSettingsWidget>(CurrentActivatedWidget);

			if (ControlsSettings)
			{
				ControlsSettings->SaveInputMappings();
			}
		}
	}
}

void UMenuSettingsWidget::CloseSettingsForce()
{
	if (ParentMenu && ParentMenu->GetClass()->IsChildOf(UMenuBaseWidget::StaticClass()))
	{
		UMenuBaseWidget* MenuBox = Cast<UMenuBaseWidget>(ParentMenu);

		MenuBox->TabActivatableWidget->ClearWidgets();
	}
}

void UMenuSettingsWidget::CloseSettingsFullScreen()
{
	if (bIsInFullscreen && MainMenuActivatableWidget)
	{
		MainMenuActivatableWidget->ClearWidgets();
		UCommonActivatableWidget* ActivatedWidget = MainMenuActivatableWidget->AddWidget(MainMenuWidget);

		if (ActivatedWidget && ActivatedWidget->GetClass()->IsChildOf(UMenuBaseWidget::StaticClass()))
		{
			UMenuBaseWidget* MenuBox = Cast<UMenuBaseWidget>(ActivatedWidget);

			MenuBox->ActivatableWidget = MainMenuActivatableWidget;

		}

	}
}

void UMenuSettingsWidget::CloseSettingsTab()
{
	SaveWindowActivatedWidget->ClearWidgets();

	if (ParentMenu && ParentMenu->GetClass()->IsChildOf(UMenuBaseWidget::StaticClass()))
	{
		UMenuBaseWidget* MenuBox = Cast<UMenuBaseWidget>(ParentMenu);

		MenuBox->UpdateSettingOpened();

		MenuBox->TabActivatableWidget->ClearWidgets();
	}
}

void UMenuSettingsWidget::CloseSaveWindow()
{
	SaveWindowActivatedWidget->ClearWidgets();

	OnMoveToWidgetEvent.Broadcast();

	OnMoveToWidgetEvent.Clear();
}

void UMenuSettingsWidget::OpenVideo()
{
	if (SettingsActivatableWidget && VideoSettingsWidget)
	{
		SettingsActivatableWidget->ClearWidgets();
		CurrentActivatedWidget = SettingsActivatableWidget->AddWidget(VideoSettingsWidget);
	}
}

void UMenuSettingsWidget::OpenGraphics()
{
	if (SettingsActivatableWidget && GraphicsSettingsWidget)
	{
		SettingsActivatableWidget->ClearWidgets();
		CurrentActivatedWidget = SettingsActivatableWidget->AddWidget(GraphicsSettingsWidget);
	}
}

void UMenuSettingsWidget::OpenControls()
{
	if (SettingsActivatableWidget && ControlsSettingsWidget)
	{
		SettingsActivatableWidget->ClearWidgets();
		CurrentActivatedWidget = SettingsActivatableWidget->AddWidget(ControlsSettingsWidget);
	}
}

void UMenuSettingsWidget::OpenAudio()
{
	if (SettingsActivatableWidget && AudioSettingsWidget)
	{
		SettingsActivatableWidget->ClearWidgets();
		CurrentActivatedWidget = SettingsActivatableWidget->AddWidget(AudioSettingsWidget);
	}
}