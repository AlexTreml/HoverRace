//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Save/GraphicsSave.h"

UGraphicsSave::UGraphicsSave()
{
	SaveSlotName = TEXT("Graphics");
	DefaultUserIndex = 0;

	FSavedSetting SShadows;	//Shadow Quality
	SShadows.SettingName = FText::AsCultureInvariant("Shadows");
	SShadows.SettingCommand="sg.ShadowQuality ";
	SShadows.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SShadows.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SShadows.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SShadows.ValueNames.Add(FText::AsCultureInvariant(("Ultra")));
	SShadows.IntValue = 3;

	FSavedSetting STexture;	//Texture Quality
	STexture.SettingName = FText::AsCultureInvariant("Textures");
	STexture.SettingCommand="sg.TextureQuality ";
	STexture.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	STexture.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	STexture.ValueNames.Add(FText::AsCultureInvariant(("High")));
	STexture.ValueNames.Add(FText::AsCultureInvariant(("Ultra")));
	STexture.IntValue = 3;

	FSavedSetting SEffects;	//Effects Quality
	SEffects.SettingName = FText::AsCultureInvariant("Effects");
	SEffects.SettingCommand="sg.EffectsQuality ";
	SEffects.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SEffects.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SEffects.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SEffects.ValueNames.Add(FText::AsCultureInvariant(("Ultra")));
	SEffects.IntValue = 3;

	FSavedSetting SFoliage;	//Foliage Quality
	SFoliage.SettingName = FText::AsCultureInvariant("Foliage");
	SFoliage.SettingCommand="sg.FoliageQuality ";
	SFoliage.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SFoliage.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SFoliage.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SFoliage.ValueNames.Add(FText::AsCultureInvariant("Ultra"));
	SFoliage.IntValue = 3;

	FSavedSetting SViewDistance;	//View Distance Quality
	SViewDistance.SettingName = FText::AsCultureInvariant("View Distance");
	SViewDistance.SettingCommand="sg.ViewDistanceQuality ";
	SViewDistance.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SViewDistance.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SViewDistance.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SViewDistance.ValueNames.Add(FText::AsCultureInvariant("Ultra"));
	SViewDistance.IntValue = 3;

	FSavedSetting SAntiAliasingQuality;	//Anti Aliasing Quality
	SAntiAliasingQuality.SettingName = FText::AsCultureInvariant("Anti Aliasing Quality");
	SAntiAliasingQuality.SettingCommand="sg.AntiAliasingQuality ";
	SAntiAliasingQuality.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SAntiAliasingQuality.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SAntiAliasingQuality.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SAntiAliasingQuality.ValueNames.Add(FText::AsCultureInvariant("Ultra"));
	SAntiAliasingQuality.IntValue = 3;

	FSavedSetting SGlobalIlluminationQuality;	//Global Illumination Quality
	SGlobalIlluminationQuality.SettingName = FText::AsCultureInvariant("Global Illumination Quality");
	SGlobalIlluminationQuality.SettingCommand = "sg.GlobalIlluminationQuality ";
	SGlobalIlluminationQuality.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SGlobalIlluminationQuality.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SGlobalIlluminationQuality.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SGlobalIlluminationQuality.ValueNames.Add(FText::AsCultureInvariant("Ultra"));
	SGlobalIlluminationQuality.IntValue = 3;

	FSavedSetting SReflectionQuality;	//Reflection Quality
	SReflectionQuality.SettingName = FText::AsCultureInvariant("Reflection Quality");
	SReflectionQuality.SettingCommand = "sg.ReflectionQuality ";
	SReflectionQuality.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SReflectionQuality.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SReflectionQuality.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SReflectionQuality.ValueNames.Add(FText::AsCultureInvariant("Ultra"));
	SReflectionQuality.IntValue = 3;

	FSavedSetting SPostProcessQuality;	//Post Process Quality
	SPostProcessQuality.SettingName = FText::AsCultureInvariant("Post Process Quality");
	SPostProcessQuality.SettingCommand = "sg.PostProcessQuality ";
	SPostProcessQuality.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SPostProcessQuality.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SPostProcessQuality.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SPostProcessQuality.ValueNames.Add(FText::AsCultureInvariant("Ultra"));
	SPostProcessQuality.IntValue = 3;

	FSavedSetting SShadingQuality;	//Shading Quality
	SShadingQuality.SettingName = FText::AsCultureInvariant("Shading Quality");
	SShadingQuality.SettingCommand = "sg.ShadingQuality ";
	SShadingQuality.ValueNames.Add(FText::AsCultureInvariant(("Low")));
	SShadingQuality.ValueNames.Add(FText::AsCultureInvariant(("Medium")));
	SShadingQuality.ValueNames.Add(FText::AsCultureInvariant(("High")));
	SShadingQuality.ValueNames.Add(FText::AsCultureInvariant("Ultra"));
	SShadingQuality.IntValue = 3;

	GeneralSettings.Add(SShadows); //0
	GeneralSettings.Add(STexture); //1
	GeneralSettings.Add(SEffects); //2
	GeneralSettings.Add(SFoliage); //3
	GeneralSettings.Add(SViewDistance); //4
	GeneralSettings.Add(SAntiAliasingQuality); //5
	GeneralSettings.Add(SGlobalIlluminationQuality); //6
	GeneralSettings.Add(SReflectionQuality); //7
	GeneralSettings.Add(SPostProcessQuality); //8
	GeneralSettings.Add(SShadingQuality); //9

	FSavedSetting SGIM;	//Global Illumination Method
	SGIM.SettingName = FText::AsCultureInvariant("Global Illumination Method");
	SGIM.SettingCommand = "r.DynamicGlobalIlluminationMethod ";
	SGIM.ValueNames.Add(FText::AsCultureInvariant(("None")));
	SGIM.ValueNames.Add(FText::AsCultureInvariant(("Lumen")));
	SGIM.ValueNames.Add(FText::AsCultureInvariant(("Screen Space")));
	SGIM.IntValue = 1;

	FSavedSetting SReflectionMethod;	//Reflection Method
	SReflectionMethod.SettingName = FText::AsCultureInvariant("Reflection Method");
	SReflectionMethod.SettingCommand = "r.ReflectionMethod ";
	SReflectionMethod.ValueNames.Add(FText::AsCultureInvariant(("None")));
	SReflectionMethod.ValueNames.Add(FText::AsCultureInvariant(("Lumen")));
	SReflectionMethod.ValueNames.Add(FText::AsCultureInvariant(("Screen Space")));
	SReflectionMethod.IntValue = 1;

	FSavedSetting SMotionBlur;	//Motion Blur
	SMotionBlur.SettingName = FText::AsCultureInvariant("Motion Blur");
	SMotionBlur.SettingCommand = "";
	SMotionBlur.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SMotionBlur.ValueNames.Add(FText::AsCultureInvariant(("On")));
	SMotionBlur.IntValue = 1;

	FCommandOnValue MBOff;
	FCommandOnValue MBOn;

	MBOff.IntSettingValue = 0;
	MBOff.Command = "r.MotionBlurQuality 0";
	MBOn.IntSettingValue = 1;
	MBOn.Command = "r.MotionBlurQuality 3";

	SMotionBlur.AdditionalCommandOnValue.Add(MBOff);
	SMotionBlur.AdditionalCommandOnValue.Add(MBOn);


	FSavedSetting SLensFlare;	//Lens Flare
	SLensFlare.SettingName = FText::AsCultureInvariant("Lens Flare");
	SLensFlare.SettingCommand = "";
	SLensFlare.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SLensFlare.ValueNames.Add(FText::AsCultureInvariant(("On")));
	SLensFlare.IntValue = 1;

	FCommandOnValue LOff;
	FCommandOnValue LOn;

	LOff.IntSettingValue = 0;
	LOff.Command = "r.LensFlareQuality 0";
	LOn.IntSettingValue = 1;
	LOn.Command = "r.LensFlareQuality 3";

	SLensFlare.AdditionalCommandOnValue.Add(LOff);
	SLensFlare.AdditionalCommandOnValue.Add(LOn);

	FSavedSetting SBloom;	//Bloom
	SBloom.SettingName = FText::AsCultureInvariant("Bloom");
	SBloom.SettingCommand = "";
	SBloom.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SBloom.ValueNames.Add(FText::AsCultureInvariant(("On")));
	SBloom.IntValue = 1;

	FCommandOnValue BOff;
	FCommandOnValue BOn;

	BOff.IntSettingValue = 0;
	BOff.Command = "r.BloomQuality 0";
	BOn.IntSettingValue = 1;
	BOn.Command = "r.BloomQuality 5";

	SBloom.AdditionalCommandOnValue.Add(BOff);
	SBloom.AdditionalCommandOnValue.Add(BOn);

	FSavedSetting SAmbientOcclusion;	//Ambient Occlusion
	SAmbientOcclusion.SettingName = FText::AsCultureInvariant("Ambient Occlusion");
	SAmbientOcclusion.SettingCommand="r.DefaultFeature.AmbientOcclusion ";
	SAmbientOcclusion.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SAmbientOcclusion.ValueNames.Add(FText::AsCultureInvariant(("On")));
	SAmbientOcclusion.IntValue = 1;

	FSavedSetting SAntiAliasingMethod;	//AntiAliasingMethod
	SAntiAliasingMethod.SettingName = FText::AsCultureInvariant("Anti Aliasing Method");
	SAntiAliasingMethod.SettingCommand = "r.AntiAliasingMethod ";
	SAntiAliasingMethod.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SAntiAliasingMethod.ValueNames.Add(FText::AsCultureInvariant(("FXAA")));
	SAntiAliasingMethod.ValueNames.Add(FText::AsCultureInvariant(("TAA")));
	SAntiAliasingMethod.ValueNames.Add(FText::AsCultureInvariant(("MSAA")));
	SAntiAliasingMethod.ValueNames.Add(FText::AsCultureInvariant(("TSR")));
	SAntiAliasingMethod.IntValue = 4;
	
	FSavedSetting SMSAACount;	//MSAA Count
	SMSAACount.SettingName = FText::AsCultureInvariant("MSAA Count");
	SMSAACount.SettingCommand = "";
	SMSAACount.ValueNames.Add(FText::AsCultureInvariant(("X2")));
	SMSAACount.ValueNames.Add(FText::AsCultureInvariant(("X4")));
	SMSAACount.ValueNames.Add(FText::AsCultureInvariant(("X8")));
	SMSAACount.IntValue = 2;

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

	AdvancedSettings.Add(SGIM); // 0
	AdvancedSettings.Add(SReflectionMethod); // 1
	AdvancedSettings.Add(SMotionBlur); // 2
	AdvancedSettings.Add(SLensFlare); // 3
	AdvancedSettings.Add(SBloom); // 4
	AdvancedSettings.Add(SAmbientOcclusion); // 5
	AdvancedSettings.Add(SAntiAliasingMethod); // 6
	AdvancedSettings.Add(SMSAACount); // 7
}