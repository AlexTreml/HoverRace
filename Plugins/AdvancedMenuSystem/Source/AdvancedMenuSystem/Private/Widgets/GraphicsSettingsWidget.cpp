//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/GraphicsSettingsWidget.h"
#include "Kismet/GameplayStatics.h"

UGraphicsSettingsWidget::UGraphicsSettingsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{

	}

	FSetting SShadows;	//Shadow Quality
	SShadows.SettingName = FText::AsCultureInvariant("Shadows");
	SShadows.SettingCommand="sg.ShadowQuality ";
	SShadows.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SShadows.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SShadows.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SShadows.ValueNames.Add(FText::AsCultureInvariant(("Ultra")));

	FSetting STexture;	//Texture Quality
	STexture.SettingName = FText::AsCultureInvariant("Textures");
	STexture.SettingCommand="sg.TextureQuality ";
	STexture.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	STexture.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	STexture.ValueNames.Add(FText::AsCultureInvariant(("High")));
	STexture.ValueNames.Add(FText::AsCultureInvariant(("Ultra")));

	FSetting SEffects;	//Effects Quality
	SEffects.SettingName = FText::AsCultureInvariant("Effects");
	SEffects.SettingCommand="sg.EffectsQuality ";
	SEffects.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SEffects.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SEffects.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SEffects.ValueNames.Add(FText::AsCultureInvariant(("Ultra")));

	FSetting SFoliage;	//Foliage Quality
	SFoliage.SettingName = FText::AsCultureInvariant("Foliage");
	SFoliage.SettingCommand="sg.FoliageQuality ";
	SFoliage.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SFoliage.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SFoliage.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SFoliage.ValueNames.Add(FText::AsCultureInvariant("Ultra"));

	FSetting SViewDistance;	//View Distance Quality
	SViewDistance.SettingName = FText::AsCultureInvariant("View Distance");
	SViewDistance.SettingCommand="sg.ViewDistanceQuality ";
	SViewDistance.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SViewDistance.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SViewDistance.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SViewDistance.ValueNames.Add(FText::AsCultureInvariant("Ultra"));

	FSetting SAntiAliasingQuality;	//Anti Aliasing Quality
	SAntiAliasingQuality.SettingName = FText::AsCultureInvariant("Anti Aliasing Quality");
	SAntiAliasingQuality.SettingCommand="sg.AntiAliasingQuality ";
	SAntiAliasingQuality.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SAntiAliasingQuality.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SAntiAliasingQuality.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SAntiAliasingQuality.ValueNames.Add(FText::AsCultureInvariant("Ultra"));

	FSetting SGlobalIlluminationQuality;	//Global Illumination Quality
	SGlobalIlluminationQuality.SettingName = FText::AsCultureInvariant("Global Illumination Quality");
	SGlobalIlluminationQuality.SettingCommand="sg.GlobalIlluminationQuality ";
	SGlobalIlluminationQuality.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SGlobalIlluminationQuality.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SGlobalIlluminationQuality.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SGlobalIlluminationQuality.ValueNames.Add(FText::AsCultureInvariant("Ultra"));

	FSetting SReflectionQuality;	//Reflection Quality
	SReflectionQuality.SettingName = FText::AsCultureInvariant("Reflection Quality");
	SReflectionQuality.SettingCommand="sg.ReflectionQuality ";
	SReflectionQuality.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SReflectionQuality.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SReflectionQuality.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SReflectionQuality.ValueNames.Add(FText::AsCultureInvariant("Ultra"));

	FSetting SPostProcessQuality;	//Post Process Quality
	SPostProcessQuality.SettingName = FText::AsCultureInvariant("Post Process Quality");
	SPostProcessQuality.SettingCommand="sg.PostProcessQuality ";
	SPostProcessQuality.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SPostProcessQuality.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SPostProcessQuality.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SPostProcessQuality.ValueNames.Add(FText::AsCultureInvariant("Ultra"));

	FSetting SShadingQuality;	//Shading Quality
	SShadingQuality.SettingName = FText::AsCultureInvariant("Shading Quality");
	SShadingQuality.SettingCommand="sg.ShadingQuality ";
	SShadingQuality.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SShadingQuality.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SShadingQuality.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SShadingQuality.ValueNames.Add(FText::AsCultureInvariant("Ultra"));

	SettingsSave.Add(SShadows); //0
	SettingsSave.Add(STexture); //1
	SettingsSave.Add(SEffects); //2
	SettingsSave.Add(SFoliage); //3
	SettingsSave.Add(SViewDistance); //4
	SettingsSave.Add(SAntiAliasingQuality); //5
	SettingsSave.Add(SGlobalIlluminationQuality); //6
	SettingsSave.Add(SReflectionQuality); //7
	SettingsSave.Add(SPostProcessQuality); //8
	SettingsSave.Add(SShadingQuality); //9

	Settings = SettingsSave;

	FSetting SGIM;	//Global Illumination Method
	SGIM.SettingName = FText::AsCultureInvariant("Global Illumination Method");
	SGIM.SettingCommand="r.DynamicGlobalIlluminationMethod ";
	//SShadingQuality.SettingCommands.Add("r.DynamicGlobalIlluminationMethod 3");
	SGIM.ValueNames.Add(FText::AsCultureInvariant(("None")));
	SGIM.ValueNames.Add(FText::AsCultureInvariant(("Lumen")));
	SGIM.ValueNames.Add(FText::AsCultureInvariant(("Screen Space")));
	//SShadingQuality.ValueNames.Add(FText::AsCultureInvariant("Plugin"));

	FSetting SReflectionMethod;	//Reflection Method
	SReflectionMethod.SettingName = FText::AsCultureInvariant("Reflection Method");
	SReflectionMethod.SettingCommand="r.ReflectionMethod ";
	SReflectionMethod.ValueNames.Add(FText::AsCultureInvariant(("None")));
	SReflectionMethod.ValueNames.Add(FText::AsCultureInvariant(("Lumen")));
	SReflectionMethod.ValueNames.Add(FText::AsCultureInvariant(("Screen Space")));

	FSetting SMotionBlur;	//Motion Blur
	SMotionBlur.SettingName = FText::AsCultureInvariant("Motion Blur");
	SMotionBlur.SettingCommand="";
	SMotionBlur.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SMotionBlur.ValueNames.Add(FText::AsCultureInvariant(("On")));

	FCommandOnValue MBOff;
	FCommandOnValue MBOn;

	MBOff.IntSettingValue = 0;
	MBOff.Command = "r.MotionBlurQuality 0";
	MBOn.IntSettingValue = 1;
	MBOn.Command = "r.MotionBlurQuality 3";

	SMotionBlur.AdditionalCommandOnValue.Add(MBOff);
	SMotionBlur.AdditionalCommandOnValue.Add(MBOn);

	FSetting SLensFlare;	//Lens Flare
	SLensFlare.SettingName = FText::AsCultureInvariant("Lens Flare");
	SLensFlare.SettingCommand="";
	SLensFlare.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SLensFlare.ValueNames.Add(FText::AsCultureInvariant(("On")));

	FCommandOnValue LOff;
	FCommandOnValue LOn;

	LOff.IntSettingValue = 0;
	LOff.Command = "r.LensFlareQuality 0";
	LOn.IntSettingValue = 1;
	LOn.Command = "r.LensFlareQuality 3";

	SLensFlare.AdditionalCommandOnValue.Add(LOff);
	SLensFlare.AdditionalCommandOnValue.Add(LOn);

	FSetting SBloom;	//Bloom
	SBloom.SettingName = FText::AsCultureInvariant("Bloom");
	SBloom.SettingCommand = "";
	SBloom.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SBloom.ValueNames.Add(FText::AsCultureInvariant(("On")));

	FCommandOnValue BOff;
	FCommandOnValue BOn;

	BOff.IntSettingValue = 0;
	BOff.Command = "r.BloomQuality 0";
	BOn.IntSettingValue = 1;
	BOn.Command = "r.BloomQuality 5";

	SBloom.AdditionalCommandOnValue.Add(BOff);
	SBloom.AdditionalCommandOnValue.Add(BOn);

	FSetting SAmbientOcclusion;	//Ambient Occlusion
	SAmbientOcclusion.SettingName = FText::AsCultureInvariant("Ambient Occlusion");
	SAmbientOcclusion.SettingCommand="r.DefaultFeature.AmbientOcclusion ";
	SAmbientOcclusion.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SAmbientOcclusion.ValueNames.Add(FText::AsCultureInvariant(("On")));

	FSetting SAntiAliasingMethod;	//AntiAliasingMethod
	SAntiAliasingMethod.SettingName = FText::AsCultureInvariant("Anti Aliasing Method");
	SAntiAliasingMethod.SettingCommand = "r.AntiAliasingMethod ";
	SAntiAliasingMethod.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SAntiAliasingMethod.ValueNames.Add(FText::AsCultureInvariant(("FXAA")));
	SAntiAliasingMethod.ValueNames.Add(FText::AsCultureInvariant(("TAA")));
	SAntiAliasingMethod.ValueNames.Add(FText::AsCultureInvariant(("MSAA")));
	SAntiAliasingMethod.ValueNames.Add(FText::AsCultureInvariant(("TSR")));

	FSetting SMSAACount;	//MSAA Count
	SMSAACount.SettingName = FText::AsCultureInvariant("MSAA Count");
	SMSAACount.SettingCommand = "";
	SMSAACount.ValueNames.Add(FText::AsCultureInvariant(("X2")));
	SMSAACount.ValueNames.Add(FText::AsCultureInvariant(("X4")));
	SMSAACount.ValueNames.Add(FText::AsCultureInvariant(("X8")));

	FCommandOnValue X2;
	FCommandOnValue X4;
	FCommandOnValue X8;

	X2.IntSettingValue = 0;
	X2.Command = "r.MSAACount 2";
	X4.IntSettingValue = 1;
	X4.Command = "r.MSAACount 4";
	X8.IntSettingValue = 2;
	X8.Command = "r.MSAACount 8";

	SMSAACount.AdditionalCommandOnValue.Add(X2);
	SMSAACount.AdditionalCommandOnValue.Add(X4);
	SMSAACount.AdditionalCommandOnValue.Add(X8);

	AdvancedSettingsSave.Add(SGIM); // 0
	AdvancedSettingsSave.Add(SReflectionMethod); // 1
	AdvancedSettingsSave.Add(SMotionBlur); // 2
	AdvancedSettingsSave.Add(SLensFlare); // 3
	AdvancedSettingsSave.Add(SBloom); // 4
	AdvancedSettingsSave.Add(SAmbientOcclusion); // 5
	AdvancedSettingsSave.Add(SAntiAliasingMethod); // 6
	AdvancedSettingsSave.Add(SMSAACount); // 7

	AdvancedSettings = AdvancedSettingsSave;

}


void UGraphicsSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// General — only add non-null widgets
	GeneralSwitches.Add(ShadowQualityWidget);
	GeneralSwitches.Add(TextureQualityWidget);
	GeneralSwitches.Add(EffectsQualityWidget);
	GeneralSwitches.Add(FoliageQualityWidget);
	GeneralSwitches.Add(ViewDistanceQualityWidget);
	GeneralSwitches.Add(AntiAliasingQualityWidget);
	GeneralSwitches.Add(GlobalIlluminationQualityWidget);
	GeneralSwitches.Add(ReflectionQualityWidget);
	GeneralSwitches.Add(PostProcessQualityWidget);
	GeneralSwitches.Add(ShadingQualityWidget);

	// Advanced — only add non-null widgets
	AdvancedSwitches.Add(GIMWidget);
	AdvancedSwitches.Add(ReflectionMethodWidget);
	AdvancedSwitches.Add(MotionBlurWidget);
	AdvancedSwitches.Add(LensFlaresWidget);
	AdvancedSwitches.Add(BloomWidget);
	AdvancedSwitches.Add(AmbientOcclusionWidget);
	AdvancedSwitches.Add(AntiAliasingMethodWidget);
	AdvancedSwitches.Add(MSAACountWidget);

	// General — bind delegates with null checks
	if (ShadowQualityWidget) { ShadowQualityWidget->OnSwitchChange.Clear(); ShadowQualityWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnShadowQualityChanged); }
	if (TextureQualityWidget) { TextureQualityWidget->OnSwitchChange.Clear(); TextureQualityWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnTextureQualityChanged); }
	if (EffectsQualityWidget) { EffectsQualityWidget->OnSwitchChange.Clear(); EffectsQualityWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnEffectsQualityChanged); }
	if (FoliageQualityWidget) { FoliageQualityWidget->OnSwitchChange.Clear(); FoliageQualityWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnFoliageQualityChanged); }
	if (ViewDistanceQualityWidget) { ViewDistanceQualityWidget->OnSwitchChange.Clear(); ViewDistanceQualityWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnViewDistanceQualityChanged); }
	if (AntiAliasingQualityWidget) { AntiAliasingQualityWidget->OnSwitchChange.Clear(); AntiAliasingQualityWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnAntiAliasingQualityChanged); }
	if (GlobalIlluminationQualityWidget) { GlobalIlluminationQualityWidget->OnSwitchChange.Clear(); GlobalIlluminationQualityWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnGlobalIlluminationQualityChanged); }
	if (ReflectionQualityWidget) { ReflectionQualityWidget->OnSwitchChange.Clear(); ReflectionQualityWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnReflectionQualityChanged); }
	if (PostProcessQualityWidget) { PostProcessQualityWidget->OnSwitchChange.Clear(); PostProcessQualityWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnPostProcessQualityChanged); }
	if (ShadingQualityWidget) { ShadingQualityWidget->OnSwitchChange.Clear(); ShadingQualityWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnShadingQualityChanged); }

	// Advanced — bind delegates with null checks
	if (GIMWidget) { GIMWidget->OnSwitchChange.Clear(); GIMWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnGIMChanged); }
	if (ReflectionMethodWidget) { ReflectionMethodWidget->OnSwitchChange.Clear(); ReflectionMethodWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnReflectionMethodChanged); }
	if (MotionBlurWidget) { MotionBlurWidget->OnSwitchChange.Clear(); MotionBlurWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnMotionBlurChanged); }
	if (LensFlaresWidget) { LensFlaresWidget->OnSwitchChange.Clear(); LensFlaresWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnLensFlaresChanged); }
	if (BloomWidget) { BloomWidget->OnSwitchChange.Clear(); BloomWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnBloomChanged); }
	if (AmbientOcclusionWidget) { AmbientOcclusionWidget->OnSwitchChange.Clear(); AmbientOcclusionWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnAmbientOcclusionChanged); }
	if (AntiAliasingMethodWidget) { AntiAliasingMethodWidget->OnSwitchChange.Clear(); AntiAliasingMethodWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnAntiAliasingMethodChanged); }
	if (MSAACountWidget) { MSAACountWidget->OnSwitchChange.Clear(); MSAACountWidget->OnSwitchChange.AddDynamic(this, &UGraphicsSettingsWidget::OnMSAACountChanged); }

	for (int i = 0; i < GeneralSwitches.Num(); i++)
	{
		if (GeneralSwitches.IsValidIndex(i) && GeneralSwitches[i] && i < Settings.Num())
		{
			GeneralSwitches[i]->SetTitleText(Settings[i].SettingName);
			GeneralSwitches[i]->ValueNames = Settings[i].ValueNames;
		}
	}

	for (int i = 0; i < AdvancedSwitches.Num(); i++)
	{
		if (AdvancedSwitches.IsValidIndex(i) && AdvancedSwitches[i] && i < AdvancedSettings.Num())
		{
			AdvancedSwitches[i]->SetTitleText(AdvancedSettings[i].SettingName);
			AdvancedSwitches[i]->ValueNames = AdvancedSettings[i].ValueNames;
		}
	}

	if (bInstantApply)
	{
		ApplyButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ApplyButton->SetVisibility(ESlateVisibility::Visible);
	}

	LoadSettings();

	if (!ApplyButton->OnPressed.IsAlreadyBound(this, &UGraphicsSettingsWidget::OnApplyPress))
	{
		ApplyButton->OnPressed.AddDynamic(this, &UGraphicsSettingsWidget::OnApplyPress);
	}

	if (!ResetButton->OnPressed.IsAlreadyBound(this, &UGraphicsSettingsWidget::ResetSettings))
	{
		ResetButton->OnPressed.AddDynamic(this, &UGraphicsSettingsWidget::ResetSettings);
	}
}

void UGraphicsSettingsWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	CheckValuesNum();

	TArray<USwitchWidget*> GeneralSwitches1;
	TArray<USwitchWidget*> AdvancedSwitches1;

	GeneralSwitches1.Add(ShadowQualityWidget);
	GeneralSwitches1.Add(TextureQualityWidget);
	GeneralSwitches1.Add(EffectsQualityWidget);
	GeneralSwitches1.Add(FoliageQualityWidget);
	GeneralSwitches1.Add(ViewDistanceQualityWidget);
	GeneralSwitches1.Add(AntiAliasingQualityWidget);
	GeneralSwitches1.Add(GlobalIlluminationQualityWidget);
	GeneralSwitches1.Add(ReflectionQualityWidget);
	GeneralSwitches1.Add(PostProcessQualityWidget);
	GeneralSwitches1.Add(ShadingQualityWidget);

	AdvancedSwitches1.Add(GIMWidget); // 0
	AdvancedSwitches1.Add(ReflectionMethodWidget); // 1
	AdvancedSwitches1.Add(MotionBlurWidget); // 2
	AdvancedSwitches1.Add(LensFlaresWidget); // 3
	AdvancedSwitches1.Add(BloomWidget); // 4
	AdvancedSwitches1.Add(AmbientOcclusionWidget); // 5
	AdvancedSwitches1.Add(AntiAliasingMethodWidget); // 6
	AdvancedSwitches1.Add(MSAACountWidget); // 7

	for (int i = 0; i < GeneralSwitches1.Num(); i++)
	{
		if (GeneralSwitches1[i] && Settings.IsValidIndex(i) && i < Settings.Num())
		{
			GeneralSwitches1[i]->SetTitleText(Settings[i].SettingName);
			GeneralSwitches1[i]->ValueNames = Settings[i].ValueNames;
		}
	}

	for (int i = 0; i < AdvancedSwitches1.Num(); i++)
	{
		if (AdvancedSwitches1.IsValidIndex(i) && AdvancedSettings.IsValidIndex(i) && i < AdvancedSettings.Num())
		{
			if (AdvancedSwitches1[i])
			{
				AdvancedSwitches1[i]->SetTitleText(AdvancedSettings[i].SettingName);
				AdvancedSwitches1[i]->ValueNames = AdvancedSettings[i].ValueNames;
			}
		}
	}

	if (Settings.Num() < 10)
	{
		int NextIndex = Settings.Num();

		for (int i = NextIndex; i < SettingsSave.Num(); i++)
		{
			Settings.Add(SettingsSave[NextIndex]);
		}
	}

	if (AdvancedSettings.Num() < 10)
	{
		int NextIndex = AdvancedSettings.Num();

		for (int i = NextIndex; i < AdvancedSettingsSave.Num(); i++)
		{
			AdvancedSettings.Add(AdvancedSettingsSave[NextIndex]);
		}
	}
}

void UGraphicsSettingsWidget::CheckValuesNum()
{

}

void UGraphicsSettingsWidget::OnApplyPress()
{
	SaveSettings();
}

void UGraphicsSettingsWidget::OnShadowQualityChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnTextureQualityChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnEffectsQualityChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnFoliageQualityChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnViewDistanceQualityChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnAntiAliasingQualityChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnGlobalIlluminationQualityChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnReflectionQualityChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnPostProcessQualityChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnShadingQualityChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnGIMChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnReflectionMethodChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnMotionBlurChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnLensFlaresChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnBloomChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnAmbientOcclusionChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::OnAntiAliasingMethodChanged(int Value)
{
	if (AntiAliasingMethodWidget && MSAACountWidget)
	{
		if (AntiAliasingMethodWidget->Value == 3)
		{
			MSAACountWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			MSAACountWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (bInstantApply)
	{
		SaveSettings();
	}
}

void  UGraphicsSettingsWidget::OnMSAACountChanged(int Value)
{
	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UGraphicsSettingsWidget::LoadSettings()
{
	UGraphicsSave* SaveGraphics = Cast<UGraphicsSave>(UGameplayStatics::CreateSaveGameObject(GraphicsSaveClass));

	if (IsValid(SaveGraphics))
	{
		if (UGameplayStatics::DoesSaveGameExist("Graphics", 0))
		{
			SaveGraphics = Cast<UGraphicsSave>(UGameplayStatics::LoadGameFromSlot("Graphics", 0));
		}

		for (int i = 0; i < SaveGraphics->GeneralSettings.Num(); i++)
		{
			if (GeneralSwitches.IsValidIndex(i) && GeneralSwitches[i])
			{
				GeneralSwitches[i]->Value = SaveGraphics->GeneralSettings[i].IntValue;
				GeneralSwitches[i]->UpdateTextBlock();
				GeneralSwitches[i]->UpdateValueName();
			}
		}

		for (int i = 0; i < SaveGraphics->AdvancedSettings.Num(); i++)
		{
			if (AdvancedSwitches.IsValidIndex(i) && AdvancedSwitches[i])
			{
				AdvancedSwitches[i]->Value = SaveGraphics->AdvancedSettings[i].IntValue;
				AdvancedSwitches[i]->UpdateTextBlock();
				AdvancedSwitches[i]->UpdateValueName();
			}
		}

		if (AntiAliasingMethodWidget && MSAACountWidget)
		{
			if (AntiAliasingMethodWidget->Value == 3)
			{
				MSAACountWidget->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				MSAACountWidget->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UGraphicsSettingsWidget::SaveSettings()
{
	if (!IsSettingsSaved())
	{
		UGraphicsSave* SaveGraphics = Cast<UGraphicsSave>(UGameplayStatics::CreateSaveGameObject(GraphicsSaveClass));

		if (IsValid(SaveGraphics))
		{
			if (UGameplayStatics::DoesSaveGameExist("Graphics", 0))
			{
				SaveGraphics = Cast<UGraphicsSave>(UGameplayStatics::LoadGameFromSlot("Graphics", 0));
			}

			if (IsValid(SaveGraphics) && SaveGraphics->GetName() != "None")
			{

				for (int i = 0; i < SaveGraphics->GeneralSettings.Num(); i++)
				{
					if (GeneralSwitches.IsValidIndex(i) && GeneralSwitches[i])
					{
						SaveGraphics->GeneralSettings[i].IntValue = GeneralSwitches[i]->Value;

						GetOwningPlayer()->ConsoleCommand(Settings[i].SettingCommand + FString::FromInt(GeneralSwitches[i]->Value));
					}
				}

				for (int i = 0; i < SaveGraphics->AdvancedSettings.Num(); i++)
				{
					if (AdvancedSwitches.IsValidIndex(i) && AdvancedSwitches[i])
					{
						SaveGraphics->AdvancedSettings[i].IntValue = AdvancedSwitches[i]->Value;

						if (!AdvancedSettings[i].SettingCommand.IsEmpty())
						{
							GetOwningPlayer()->ConsoleCommand(AdvancedSettings[i].SettingCommand + FString::FromInt(AdvancedSwitches[i]->Value));
						}

						if (AdvancedSettings[i].AdditionalCommandOnValue.Num())
						{
							for (int j = 0; j < AdvancedSettings[i].AdditionalCommandOnValue.Num(); j++)
							{
								if (AdvancedSwitches[i]->Value == AdvancedSettings[i].AdditionalCommandOnValue[j].IntSettingValue)
								{
									GetOwningPlayer()->ConsoleCommand(AdvancedSettings[i].AdditionalCommandOnValue[j].Command);
								}
							}
						}
					}
				}

				UGameplayStatics::SaveGameToSlot(SaveGraphics, TEXT("Graphics"), 0);
			}
		}
	}
}

void UGraphicsSettingsWidget::ResetSettings()
{
	UGraphicsSave* SaveGraphics = Cast<UGraphicsSave>(UGameplayStatics::CreateSaveGameObject(GraphicsSaveClass));

	if (IsValid(SaveGraphics))
	{
		for (int i = 0; i < SaveGraphics->GeneralSettings.Num(); i++)
		{
			if (GeneralSwitches.IsValidIndex(i) && GeneralSwitches[i])
			{
				GeneralSwitches[i]->Value = SaveGraphics->GeneralSettings[i].IntValue;
				GeneralSwitches[i]->UpdateTextBlock();
				GeneralSwitches[i]->UpdateValueName();
			}
		}

		for (int i = 0; i < SaveGraphics->AdvancedSettings.Num(); i++)
		{
			if (AdvancedSwitches.IsValidIndex(i) && AdvancedSwitches[i])
			{
				AdvancedSwitches[i]->Value = SaveGraphics->AdvancedSettings[i].IntValue;
				AdvancedSwitches[i]->UpdateTextBlock();
				AdvancedSwitches[i]->UpdateValueName();
			}
		}

		if (AntiAliasingMethodWidget && MSAACountWidget)
		{
			if (AntiAliasingMethodWidget->Value == 3)
			{
				MSAACountWidget->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				MSAACountWidget->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

bool UGraphicsSettingsWidget::IsSettingsSaved()
{
	bool IsSaved = true;

	UGraphicsSave* LatestSaveGraphics = Cast<UGraphicsSave>(UGameplayStatics::CreateSaveGameObject(GraphicsSaveClass));

	if (IsValid(LatestSaveGraphics))
	{
		if (UGameplayStatics::DoesSaveGameExist(TEXT("Graphics"), 0))
		{
			LatestSaveGraphics = Cast<UGraphicsSave>(UGameplayStatics::LoadGameFromSlot(TEXT("Graphics"), 0));
		}

		for (int i = 0; i < LatestSaveGraphics->GeneralSettings.Num(); i++)
		{
			if (GeneralSwitches.IsValidIndex(i) && GeneralSwitches[i])
			{
				if (LatestSaveGraphics->GeneralSettings[i].IntValue != GeneralSwitches[i]->Value)
				{
					IsSaved = false;
				}
			}
		}

		for (int i = 0; i < LatestSaveGraphics->AdvancedSettings.Num(); i++)
		{
			if (AdvancedSwitches.IsValidIndex(i) && AdvancedSwitches[i])
			{
				if (LatestSaveGraphics->AdvancedSettings[i].IntValue != AdvancedSwitches[i]->Value)
				{
					IsSaved = false;
				}
			}
		}
	}

	return IsSaved;
}