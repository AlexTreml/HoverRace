//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/VideoSettingsWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UVideoSettingsWidget::UVideoSettingsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FSetting SLockFPS;	//Lock FPS
	SLockFPS.SettingName = FText::AsCultureInvariant("Lock FPS");
	SLockFPS.SettingCommand = "t.MaxFPS ";
	SLockFPS.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SLockFPS.ValueNames.Add(FText::AsCultureInvariant(("30")));
	SLockFPS.ValueNames.Add(FText::AsCultureInvariant(("60")));
	SLockFPS.ValueNames.Add(FText::AsCultureInvariant(("120")));
	SLockFPS.ValueNames.Add(FText::AsCultureInvariant(("144")));
	SLockFPS.ValueNames.Add(FText::AsCultureInvariant(("360")));

	FCommandOnValue F0;
	FCommandOnValue F30;
	FCommandOnValue F60;
	FCommandOnValue F120;
	FCommandOnValue F144;
	FCommandOnValue F360;

	F0.IntSettingValue = 0;
	F0.Command = "t.MaxFPS 0";
	F30.IntSettingValue = 1;
	F30.Command = "t.MaxFPS 30";
	F60.IntSettingValue = 2;
	F60.Command = "t.MaxFPS 60";
	F120.IntSettingValue = 3;
	F120.Command = "t.MaxFPS 120";
	F144.IntSettingValue = 4;
	F144.Command = "t.MaxFPS 144";
	F360.IntSettingValue = 5;
	F360.Command = "t.MaxFPS 360";

	SLockFPS.AdditionalCommandOnValue.Add(F0);
	SLockFPS.AdditionalCommandOnValue.Add(F30);
	SLockFPS.AdditionalCommandOnValue.Add(F60);
	SLockFPS.AdditionalCommandOnValue.Add(F120);
	SLockFPS.AdditionalCommandOnValue.Add(F144);
	SLockFPS.AdditionalCommandOnValue.Add(F360);

	FSetting SVSync;	//VSync
	SVSync.SettingName = FText::AsCultureInvariant("VSync");
	SVSync.SettingCommand = "r.VSync ";
	SVSync.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SVSync.ValueNames.Add(FText::AsCultureInvariant(("On")));

	FPSSettingsSave.Add(SLockFPS);
	FPSSettingsSave.Add(SVSync);

	FPSSettings = FPSSettingsSave;

	FSetting SHDRStatus;	//HDR
	SHDRStatus.SettingName = FText::AsCultureInvariant("HDR");
	SHDRStatus.SettingCommand = "r.HDR.EnableHDROutput ";
	SHDRStatus.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SHDRStatus.ValueNames.Add(FText::AsCultureInvariant(("On")));

	FSetting SHDRDisplayProfile;	//HDR Display Profile
	SHDRDisplayProfile.SettingName = FText::AsCultureInvariant("HDR");
	SHDRDisplayProfile.SettingCommand = "r.HDR.EnableHDROutput ";
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("sRGB (LDR)"))); //1
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("Rec709 (LDR)"))); //2
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("Explicit gamma mapping (LDR)"))); //3
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("ACES 1000 nit ST-2084 (Dolby PQ) (HDR)"))); //4
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("ACES 2000 nit ST-2084 (Dolby PQ) (HDR)"))); //5
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("ACES 1000 nit ScRGB (HDR)"))); //6
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("ACES 2000 nit ScRGB (HDR)"))); //7

	FSetting SHDRColorSpace;	//HDR Display Profile
	SHDRColorSpace.SettingName = FText::AsCultureInvariant("HDR Color Space");
	SHDRColorSpace.SettingCommand = "r.HDR.Display.ColorGamut ";
	SHDRColorSpace.ValueNames.Add(FText::AsCultureInvariant(("Rec709 / sRGB, D65"))); //1
	SHDRColorSpace.ValueNames.Add(FText::AsCultureInvariant(("DCI-P3, D65"))); //2
	SHDRColorSpace.ValueNames.Add(FText::AsCultureInvariant(("Rec2020 / BT2020, D65"))); //3
	SHDRColorSpace.ValueNames.Add(FText::AsCultureInvariant(("ACES, D60"))); //4
	SHDRColorSpace.ValueNames.Add(FText::AsCultureInvariant(("ACEScg, D60"))); //5

	HDRSettingsSave.Add(SHDRStatus);
	HDRSettingsSave.Add(SHDRDisplayProfile);
	HDRSettingsSave.Add(SHDRColorSpace);

	HDRSettings = HDRSettingsSave;

	bInstantApply = false;
}

void UVideoSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CheckIfCanChangeResolution(); // Check if platform is desktop. We need that to avoid crashes on mobile and other devices.

	LoadSettings();

	//General
	WindowModeWidget->OnSwitchChange.Clear();
	AspectRatioBox->OnSelectionChanged.Clear();
	WindowResolutionBox->OnSelectionChanged.Clear();
	BrightnessSlider->OnValueChanged.Clear();

	WindowModeWidget->OnSwitchChange.AddDynamic(this, &UVideoSettingsWidget::OnWindowModeChanged);
	AspectRatioBox->OnSelectionChanged.AddDynamic(this, &UVideoSettingsWidget::OnAspectRatioChange);
	WindowResolutionBox->OnSelectionChanged.AddDynamic(this, &UVideoSettingsWidget::OnWindowResolutionBoxChange);
	BrightnessSlider->OnValueChanged.AddDynamic(this, &UVideoSettingsWidget::OnBrightnessUpdate);

	//HDR
	HDRStatusWidget->OnSwitchChange.Clear();
	HDRDisplayProfileWidget->OnSwitchChange.Clear();
	HDRColorSpaceWidget->OnSwitchChange.Clear();

	HDRStatusWidget->OnSwitchChange.AddDynamic(this, &UVideoSettingsWidget::OnHDRChanged);
	HDRDisplayProfileWidget->OnSwitchChange.AddDynamic(this, &UVideoSettingsWidget::OnHDRChanged);
	HDRColorSpaceWidget->OnSwitchChange.AddDynamic(this, &UVideoSettingsWidget::OnHDRChanged);

	//Apply
	ApplyButton->OnPressed.Clear();
	ApplyButton->OnPressed.AddDynamic(this, &UVideoSettingsWidget::OnApplyPress);

	if (!ResetButton->OnPressed.IsAlreadyBound(this, &UVideoSettingsWidget::ResetSettings))
	{
		ResetButton->OnPressed.AddDynamic(this, &UVideoSettingsWidget::ResetSettings);
	}

	if (bInstantApply)
	{
		ApplyButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		ApplyButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UVideoSettingsWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	TArray<USwitchWidget*> HDRSwitches1;

	HDRSwitches1.Add(HDRStatusWidget);
	HDRSwitches1.Add(HDRDisplayProfileWidget);
	HDRSwitches1.Add(HDRColorSpaceWidget);

	for (int i = 0; i < HDRSwitches1.Num(); i++)
	{
		if (HDRSwitches1[i] && i < HDRSettings.Num())
		{
			HDRSwitches1[i]->SetTitleText(HDRSettings[i].SettingName);
			HDRSwitches1[i]->ValueNames = HDRSettings[i].ValueNames;
		}
	}

	TArray<USwitchWidget*> FPSSwitches1;

	FPSSwitches1.Add(LockFPSWidget);
	FPSSwitches1.Add(VSyncWidget);	

	for (int i = 0; i < FPSSwitches1.Num(); i++)
	{
		if (FPSSwitches1[i] && i < FPSSettings.Num())
		{
			FPSSwitches1[i]->SetTitleText(FPSSettings[i].SettingName);
			FPSSwitches1[i]->ValueNames = FPSSettings[i].ValueNames;
		}
	}

	WindowModeWidget->SetTitleText(FText::AsCultureInvariant("Window Mode"));
	WindowResolutionBox->SetTitleText(FText::AsCultureInvariant("Window Resolution"));
	AspectRatioBox->SetTitleText(FText::AsCultureInvariant("Aspect Ratio"));
	BrightnessSlider->SetTitleText(FText::AsCultureInvariant("Brightness"));

	if (HDRSettings.Num() < 3)
	{
		int NextIndex = HDRSettings.Num();

		for (int i = NextIndex; i < HDRSettingsSave.Num(); i++)
		{
			HDRSettings.Add(HDRSettingsSave[NextIndex]);
		}
	}

	if (FPSSettings.Num() < 2)
	{
		int NextIndex = FPSSettings.Num();

		for (int i = NextIndex; i < FPSSettingsSave.Num(); i++)
		{
			FPSSettings.Add(FPSSettingsSave[NextIndex]);
		}
	}

}

void UVideoSettingsWidget::CheckIfCanChangeResolution()
{
	if (IsDesktopPlatform())
	{
		WindowModeWidget->SetVisibility(ESlateVisibility::Visible);
		AspectRatioBox->SetVisibility(ESlateVisibility::Visible);
		WindowResolutionBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		WindowModeWidget->SetVisibility(ESlateVisibility::Collapsed);
		AspectRatioBox->SetVisibility(ESlateVisibility::Collapsed);
		WindowResolutionBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UVideoSettingsWidget::SetUpBrightnessValue(float Value)
{
	if (BrightnessSlider)
	{
		float V = UKismetMathLibrary::MapRangeClamped(Value, 1.f, 10.f, 0.f, 100.f);

		BrightnessSlider->SetSliderValue(V);
		BrightnessSlider->SetSliderMaxValue(100.f);
		BrightnessSlider->SetSliderMinValue(0.f);
	}
}

void UVideoSettingsWidget::SetUpWindowModes()
{
	TArray<FText> ValueNames;

	ValueNames.Add(FText::AsCultureInvariant(("Fullscreen")));
	ValueNames.Add(FText::AsCultureInvariant(("Bordeless")));
	ValueNames.Add(FText::AsCultureInvariant(("Windowed")));

	WindowModeWidget->ValueNames = ValueNames;
}

void UVideoSettingsWidget::SetUpHDRSettings()
{
	if (!HDRSwitches.Num())
	{
		HDRSwitches.Add(HDRStatusWidget);
		HDRSwitches.Add(HDRDisplayProfileWidget);
		HDRSwitches.Add(HDRColorSpaceWidget);
	}

	for (int i = 0; i < HDRSwitches.Num(); i++)
	{
		if (HDRSwitches[i] && i < HDRSettings.Num())
		{
			HDRSwitches[i]->SetTitleText(HDRSettings[i].SettingName);
			HDRSwitches[i]->ValueNames = HDRSettings[i].ValueNames;
		}
	}
}

void UVideoSettingsWidget::SetUpFPS()
{
	if (!FPSSwitches.Num())
	{
		FPSSwitches.Add(LockFPSWidget);
		FPSSwitches.Add(VSyncWidget);
	}

	for (int i = 0; i < FPSSwitches.Num(); i++)
	{
		if (FPSSwitches[i] && i < FPSSettings.Num())
		{
			FPSSwitches[i]->SetTitleText(FPSSettings[i].SettingName);
			FPSSwitches[i]->ValueNames = FPSSettings[i].ValueNames;
		}
	}
}

void UVideoSettingsWidget::OnHDRChanged(int Value)
{
	if (bInstantApply)
	{
		for (int i = 0; i < HDRSwitches.Num(); i++)
		{
			if (HDRSwitches.IsValidIndex(i))
			{
				GetOwningPlayer()->ConsoleCommand(HDRSettings[i].SettingCommand + FString::FromInt(HDRSwitches[i]->Value));
			}
		}
	}
}

void UVideoSettingsWidget::LoadSettings()
{
	TSubclassOf<UVideoSave> SaveClass;

	if (VideoSaveClass)
	{
		SaveClass = VideoSaveClass;
	}
	else
	{
		SaveClass = UVideoSave::StaticClass();
	}

	UVideoSave* VideoSave = Cast<UVideoSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

	if (VideoSave)
	{
		int WindowMode = 0;

		if (UGameplayStatics::DoesSaveGameExist(TEXT("Video"), 0))
		{
			VideoSave = Cast<UVideoSave>(UGameplayStatics::LoadGameFromSlot(TEXT("Video"), 0));

			WindowMode = VideoSave->WindowMode;
		}
		else
		{
			EWindowMode::Type InFullscreenMode = UGameUserSettings::GetGameUserSettings()->GetFullscreenMode();

			switch (InFullscreenMode)
			{
			case EWindowMode::Fullscreen:
				WindowMode = 0;
				break;
			case EWindowMode::WindowedFullscreen:
				WindowMode = 1;
				break;
			case EWindowMode::Windowed:
				WindowMode = 2;
				break;
			default:
				WindowMode = 0;
				break;
			}
		}

		SetUpWindowModes();

		SetUpFPS();

		SetUpHDRSettings();

		for (int i = 0; i < VideoSave->FPSSettings.Num(); i++)
		{
			if (FPSSwitches.IsValidIndex(i))
			{
				FPSSwitches[i]->SetTitleText(FPSSettings[i].SettingName);
				FPSSwitches[i]->Value = VideoSave->FPSSettings[i].IntValue;
				FPSSwitches[i]->UpdateTextBlock();
				FPSSwitches[i]->UpdateValueName();
			}
		}

		for (int i = 0; i < VideoSave->HDRSettings.Num(); i++)
		{
			if (HDRSwitches.IsValidIndex(i))
			{
				HDRSwitches[i]->TitleText = HDRSettings[i].SettingName;
				HDRSwitches[i]->Value = VideoSave->HDRSettings[i].IntValue;
				HDRSwitches[i]->UpdateTextBlock();
				HDRSwitches[i]->UpdateValueName();
			}
		}

		WindowModeWidget->SetTitleText(FText::AsCultureInvariant("Window Mode"));
		WindowModeWidget->Value = WindowMode;
		WindowModeWidget->UpdateTextBlock();
		WindowModeWidget->UpdateValueName();

		//If Bordeless hide resolution and aspect ratio
		if (WindowModeWidget->Value == 1)
		{
			AspectRatioBox->SetVisibility(ESlateVisibility::Collapsed);
			WindowResolutionBox->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			AspectRatioBox->SetVisibility(ESlateVisibility::Visible);
			WindowResolutionBox->SetVisibility(ESlateVisibility::Visible);
		}

		if (IsDesktopPlatform())
		{
			SetUpResolutions();
		}

		WindowResolutionBox->TitleText = FText::AsCultureInvariant("Window Resolution");
		WindowResolutionBox->UpdateTextBlock();

		AspectRatioBox->TitleText = FText::AsCultureInvariant("Aspect Ratio");
		AspectRatioBox->UpdateTextBlock();

		AspectRatioBox->UpdateComboBox();
		WindowResolutionBox->UpdateComboBox();

		BrightnessSlider->TitleText = FText::AsCultureInvariant("Brightness");
		BrightnessSlider->UpdateTextBlock();

		SetUpBrightnessValue(VideoSave->Brightness);
	}

}

void UVideoSettingsWidget::SaveSettings()
{
	if (!IsSettingsSaved())
	{
		TSubclassOf<UVideoSave> SaveClass;

		if (VideoSaveClass)
		{
			SaveClass = VideoSaveClass;
		}
		else
		{
			SaveClass = UVideoSave::StaticClass();
		}

		UVideoSave* VideoSave = Cast<UVideoSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

		if (VideoSave)
		{
			int WindowMode = 0;

			if (UGameplayStatics::DoesSaveGameExist(TEXT("Video"), 0))
			{
				VideoSave = Cast<UVideoSave>(UGameplayStatics::LoadGameFromSlot(TEXT("Video"), 0));

				WindowMode = VideoSave->WindowMode;
			}
			else
			{
				EWindowMode::Type InFullscreenMode = UGameUserSettings::GetGameUserSettings()->GetFullscreenMode();

				switch (InFullscreenMode)
				{
				case EWindowMode::Fullscreen:
					WindowMode = 0;
					break;
				case EWindowMode::WindowedFullscreen:
					WindowMode = 1;
					break;
				case EWindowMode::Windowed:
					WindowMode = 2;
					break;
				default:
					WindowMode = 0;
					break;
				}
			}
		}

		if (VideoSave)
		{
			//FPS
			for (int i = 0; i < VideoSave->FPSSettings.Num(); i++)
			{
				if (FPSSwitches.IsValidIndex(i))
				{
					VideoSave->FPSSettings[i].IntValue = FPSSwitches[i]->Value;

					if (FPSSettings[i].AdditionalCommandOnValue.Num())
					{
						for (int j = 0; j < FPSSettings[i].AdditionalCommandOnValue.Num(); j++)
						{
							if (FPSSwitches[i]->Value == FPSSettings[i].AdditionalCommandOnValue[j].IntSettingValue)
							{
								GetOwningPlayer()->ConsoleCommand(FPSSettings[i].AdditionalCommandOnValue[j].Command);
							}
						}
					}
				}
			}

			//HDR
			for (int i = 0; i < VideoSave->HDRSettings.Num(); i++)
			{
				if (HDRSwitches.IsValidIndex(i))
				{
					VideoSave->HDRSettings[i].IntValue = HDRSwitches[i]->Value;

					GetOwningPlayer()->ConsoleCommand(HDRSettings[i].SettingCommand + FString::FromInt(HDRSwitches[i]->Value));
				}
			}

			//WindowMode
			VideoSave->WindowMode = WindowModeWidget->Value;
			EWindowMode::Type InFullscreenMode;

			switch (WindowModeWidget->Value)
			{
			case 0:
				InFullscreenMode = EWindowMode::Fullscreen;
				break;
			case 1:
				InFullscreenMode = EWindowMode::WindowedFullscreen;
				break;
			case 2:
				InFullscreenMode = EWindowMode::Windowed;
				break;
			default:
				InFullscreenMode = EWindowMode::Fullscreen;
				break;
			}

			UGameUserSettings::GetGameUserSettings()->SetFullscreenMode(InFullscreenMode);

			//Brightness
			float V = UKismetMathLibrary::MapRangeClamped(BrightnessSlider->GetSliderValue(), 0.f, 100.f, 1.f, 10.f);

			GetOwningPlayer()->ConsoleCommand("r.TonemapperGamma " + FString::SanitizeFloat(V));

			VideoSave->Brightness = V;

			//Resolution
			VideoSave->Resolution = CurrentResolution;
			UGameUserSettings::GetGameUserSettings()->SetScreenResolution(CurrentResolution);

			//AspectRatio
			VideoSave->AspectRatio = CurrentAspectRatio;

			//UGameUserSettings::GetGameUserSettings()->ApplyResolutionSettings(false);
			UGameUserSettings::GetGameUserSettings()->ApplySettings(false);

			UGameplayStatics::SaveGameToSlot(VideoSave, TEXT("Video"), 0); //Finally saving the stuff to the slot. 
		}
	}
}

void UVideoSettingsWidget::SetUpResolutions()
{
	bool Success = UKismetSystemLibrary::GetSupportedFullscreenResolutions(SupportedResolutions);

	if (Success && SupportedResolutions.Num())
	{
		for (int i = 0; i < SupportedResolutions.Num(); i++)
		{
			int ResGCD = GCD(SupportedResolutions[i].X, SupportedResolutions[i].Y);
			FIntPoint Ratio;

			Ratio.X = SupportedResolutions[i].X / ResGCD;
			Ratio.Y = SupportedResolutions[i].Y / ResGCD;
			
			bool FoundAspectRatio = false;

			for (int j = 0; j < SupportedAspectRatios.Num(); j++)
			{
				if (SupportedAspectRatios[j] == Ratio)
				{
					FoundAspectRatio = true;
					break;
				}
			}

			if (!FoundAspectRatio)
			{
				SupportedAspectRatios.Add(Ratio);

				AspectRatioBox->Options.Add(FString::FromInt(Ratio.X) + ":" + FString::FromInt(Ratio.Y));
			}

		}
		FIntPoint Resolution = UGameUserSettings::GetGameUserSettings()->GetScreenResolution();

		CurrentResolution = Resolution;

		FIntPoint Ratio = GetRatioByRess(Resolution);

		CurrentAspectRatio = Ratio;

		TArray<FIntPoint> ResolutionsByRatio = GetResolutionsByRatio(Ratio);

		for (int i = 0; i < ResolutionsByRatio.Num(); i++)
		{
			WindowResolutionBox->Options.Add(FString::FromInt(ResolutionsByRatio[i].X) + "x" + FString::FromInt(ResolutionsByRatio[i].Y));
		}

		AspectRatioBox->DefaultOption = FString::FromInt(Ratio.X) + ":" + FString::FromInt(Ratio.Y);
		WindowResolutionBox->DefaultOption = FString::FromInt(Resolution.X) + "x" + FString::FromInt(Resolution.Y);

		AspectRatioBox->UpdateComboBox();
		WindowResolutionBox->UpdateComboBox();
	}
}

TArray<FIntPoint> UVideoSettingsWidget::GetResolutionsByRatio(FIntPoint Ratio)
{
	TArray<FIntPoint> Resolutions;

	for (int i = 0; i < SupportedResolutions.Num(); i++)
	{
		FIntPoint ItemRatio;
		ItemRatio = GetRatioByRess(SupportedResolutions[i]);

		if (ItemRatio.X == Ratio.X && ItemRatio.Y == Ratio.Y)
		{
			Resolutions.Add(SupportedResolutions[i]);
		}
	}

	return Resolutions;
}

FIntPoint UVideoSettingsWidget::GetRatioByRess(FIntPoint Resolution)
{
	FIntPoint Ratio;

	int ResGCD = GCD(Resolution.X, Resolution.Y);

	Ratio.X = Resolution.X / ResGCD;
	Ratio.Y = Resolution.Y / ResGCD;

	return Ratio;
}

void UVideoSettingsWidget::OnWindowModeChanged(int Value)
{
	EWindowMode::Type InFullscreenMode;

	switch (Value)
	{
	case 0:
		InFullscreenMode = EWindowMode::Fullscreen;
		break;
	case 1:
		InFullscreenMode = EWindowMode::WindowedFullscreen;
		break;
	case 2:
		InFullscreenMode = EWindowMode::Windowed;
		break;
	default:
		InFullscreenMode = EWindowMode::Fullscreen;
		break;
	}

	if (Value == 1)
	{
		AspectRatioBox->SetVisibility(ESlateVisibility::Collapsed);
		WindowResolutionBox->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		AspectRatioBox->SetVisibility(ESlateVisibility::Visible);
		WindowResolutionBox->SetVisibility(ESlateVisibility::Visible);
	}

	if (bInstantApply)
	{
		UGameUserSettings::GetGameUserSettings()->SetFullscreenMode(InFullscreenMode);
	}
}

void UVideoSettingsWidget::OnWindowResolutionBoxChange(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int Index = 0;

	for (int i = 0; i < SupportedResolutions.Num(); i++)
	{
		if (SelectedItem == (FString::FromInt(SupportedResolutions[i].X) + "x" + FString::FromInt(SupportedResolutions[i].Y)))
		{
			Index = i;
			break;
		}
	}

	CurrentResolution = SupportedResolutions[Index];

	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UVideoSettingsWidget::OnAspectRatioChange(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int Index = 0;

	for (int i = 0; i < SupportedAspectRatios.Num(); i++)
	{
		if (SelectedItem == (FString::FromInt(SupportedAspectRatios[i].X) + ":" + FString::FromInt(SupportedAspectRatios[i].Y)))
		{
			Index = i;
			break;
		}
	}

	if (SupportedAspectRatios.IsValidIndex(Index))
	{
		TArray<FIntPoint> ResolutionsByRatio = GetResolutionsByRatio(SupportedAspectRatios[Index]);

		WindowResolutionBox->Options.Empty();

		for (int i = 0; i < ResolutionsByRatio.Num(); i++)
		{
			WindowResolutionBox->Options.Add(FString::FromInt(ResolutionsByRatio[i].X) + "x" + FString::FromInt(ResolutionsByRatio[i].Y));
		}
	
		//AspectRatioBox->UpdateComboBox();
		WindowResolutionBox->UpdateComboBox();

		if (bInstantApply)
		{
			CurrentAspectRatio = ResolutionsByRatio[0];
			SaveSettings();
		}
	
	}
}

void UVideoSettingsWidget::OnBrightnessUpdate(float Value)
{
	//float V = UKismetMathLibrary::MapRangeClamped(Value, 0.f, 100.f, 1.f, 10.f);

	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UVideoSettingsWidget::OnApplyPress()
{
	SaveSettings();
}

void UVideoSettingsWidget::OnLockFPSChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UVideoSettingsWidget::OnVSyncChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UVideoSettingsWidget::ResetSettings()
{
	TSubclassOf<UVideoSave> SaveClass;

	if (VideoSaveClass)
	{
		SaveClass = VideoSaveClass;
	}
	else
	{
		SaveClass = UVideoSave::StaticClass();
	}

	UVideoSave* VideoSave = Cast<UVideoSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

	if (VideoSave)
	{
		int WindowMode = 0;

		WindowMode = VideoSave->WindowMode;

		SetUpWindowModes();

		SetUpFPS();

		SetUpHDRSettings();

		for (int i = 0; i < VideoSave->FPSSettings.Num(); i++)
		{
			if (FPSSwitches.IsValidIndex(i))
			{
				FPSSwitches[i]->SetTitleText(FPSSettings[i].SettingName);
				FPSSwitches[i]->Value = VideoSave->FPSSettings[i].IntValue;
				FPSSwitches[i]->UpdateTextBlock();
				FPSSwitches[i]->UpdateValueName();
			}
		}

		for (int i = 0; i < VideoSave->HDRSettings.Num(); i++)
		{
			if (HDRSwitches.IsValidIndex(i))
			{
				HDRSwitches[i]->TitleText = HDRSettings[i].SettingName;
				HDRSwitches[i]->Value = VideoSave->HDRSettings[i].IntValue;
				HDRSwitches[i]->UpdateTextBlock();
				HDRSwitches[i]->UpdateValueName();
			}
		}

		WindowModeWidget->SetTitleText(FText::AsCultureInvariant("Window Mode"));
		WindowModeWidget->Value = WindowMode;
		WindowModeWidget->UpdateTextBlock();
		WindowModeWidget->UpdateValueName();

		//If Bordeless hide resolution and aspect ratio
		if (WindowModeWidget->Value == 1)
		{
			AspectRatioBox->SetVisibility(ESlateVisibility::Collapsed);
			WindowResolutionBox->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			AspectRatioBox->SetVisibility(ESlateVisibility::Visible);
			WindowResolutionBox->SetVisibility(ESlateVisibility::Visible);
		}

		if (IsDesktopPlatform())
		{
			SetUpResolutions();
		}

		WindowResolutionBox->TitleText = FText::AsCultureInvariant("Window Resolution");
		WindowResolutionBox->UpdateTextBlock();

		AspectRatioBox->TitleText = FText::AsCultureInvariant("Aspect Ratio");
		AspectRatioBox->UpdateTextBlock();

		AspectRatioBox->UpdateComboBox();
		WindowResolutionBox->UpdateComboBox();

		BrightnessSlider->TitleText = FText::AsCultureInvariant("Brightness");
		BrightnessSlider->UpdateTextBlock();

		SetUpBrightnessValue(VideoSave->Brightness);
	}
}

bool UVideoSettingsWidget::IsSettingsSaved()
{
	TSubclassOf<UVideoSave> SaveClass;

	if (VideoSaveClass)
	{
		SaveClass = VideoSaveClass;
	}
	else
	{
		SaveClass = UVideoSave::StaticClass();
	}

	UVideoSave* LastVideoSave = Cast<UVideoSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

	bool IsSaved = true;

	if (LastVideoSave)
	{
		if (UGameplayStatics::DoesSaveGameExist(TEXT("Video"), 0))
		{
			LastVideoSave = Cast<UVideoSave>(UGameplayStatics::LoadGameFromSlot(TEXT("Video"), 0));
		}

		for (int i = 0; i < LastVideoSave->FPSSettings.Num(); i++)
		{
			if (FPSSwitches.IsValidIndex(i))
			{
				if (FPSSwitches[i]->Value != LastVideoSave->FPSSettings[i].IntValue)
				{
					IsSaved = false;

					break;
				}
			}
		}

		for (int i = 0; i < LastVideoSave->HDRSettings.Num(); i++)
		{
			if (!IsSaved)
			{
				break;
			}

			if (HDRSwitches.IsValidIndex(i))
			{
				if (HDRSwitches[i]->Value != LastVideoSave->HDRSettings[i].IntValue)
				{
					IsSaved = false;
				}
			}
		}

		if (IsSaved && WindowModeWidget->Value != LastVideoSave->WindowMode)
		{
			IsSaved = false;
		}

		if (IsDesktopPlatform() && IsSaved)
		{

			if (CurrentResolution != LastVideoSave->Resolution)
			{
				IsSaved = false;
			}

			if (CurrentAspectRatio != LastVideoSave->AspectRatio)
			{
				IsSaved = false;
			}
		}

		float F = UKismetMathLibrary::MapRangeClamped(BrightnessSlider->GetSliderValue(), 0.f, 100.f, 1.f, 10.f);
		float B = LastVideoSave->Brightness;

		if (IsSaved && B != F)
		{
			IsSaved = false;
		}
	}

	return IsSaved;
}