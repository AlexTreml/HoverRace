//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Save/VideoSave.h"

UVideoSave::UVideoSave()
{
	SaveSlotName = TEXT("Video");
	DefaultUserIndex = 0;

	FSavedSetting SLockFPS;	//Lock FPS
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

	SLockFPS.IntValue = 0;

	FSavedSetting SVSync;	//VSync
	SVSync.SettingName = FText::AsCultureInvariant("VSync");
	SVSync.SettingCommand = "r.VSync ";
	SVSync.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SVSync.ValueNames.Add(FText::AsCultureInvariant(("On")));

	SVSync.IntValue = 0;

	FPSSettings.Add(SLockFPS);
	FPSSettings.Add(SVSync);

	FSavedSetting SHDRStatus;	//HDR
	SHDRStatus.SettingName = FText::AsCultureInvariant("HDR");
	SHDRStatus.SettingCommand = "r.HDR.EnableHDROutput ";
	SHDRStatus.ValueNames.Add(FText::AsCultureInvariant(("Off")));
	SHDRStatus.ValueNames.Add(FText::AsCultureInvariant(("On")));
	SHDRStatus.IntValue = 0;

	FSavedSetting SHDRDisplayProfile;	//HDR Display Profile
	SHDRDisplayProfile.SettingName = FText::AsCultureInvariant("HDR");
	SHDRDisplayProfile.SettingCommand = "r.HDR.EnableHDROutput ";
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("sRGB (LDR)"))); //1
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("Rec709 (LDR)"))); //2
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("Explicit gamma mapping (LDR)"))); //3
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("ACES 1000 nit ST-2084 (Dolby PQ) (HDR)"))); //4
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("ACES 2000 nit ST-2084 (Dolby PQ) (HDR)"))); //5
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("ACES 1000 nit ScRGB (HDR)"))); //6
	SHDRDisplayProfile.ValueNames.Add(FText::AsCultureInvariant(("ACES 2000 nit ScRGB (HDR)"))); //7
	SHDRDisplayProfile.IntValue = 0;

	FSavedSetting SHDRColorSpace;	//HDR Display Profile
	SHDRColorSpace.SettingName = FText::AsCultureInvariant("HDR Color Space");
	SHDRColorSpace.SettingCommand = "r.HDR.Display.ColorGamut ";
	SHDRColorSpace.ValueNames.Add(FText::AsCultureInvariant(("Rec709 / sRGB, D65"))); //1
	SHDRColorSpace.ValueNames.Add(FText::AsCultureInvariant(("DCI-P3, D65"))); //2
	SHDRColorSpace.ValueNames.Add(FText::AsCultureInvariant(("Rec2020 / BT2020, D65"))); //3
	SHDRColorSpace.ValueNames.Add(FText::AsCultureInvariant(("ACES, D60"))); //4
	SHDRColorSpace.ValueNames.Add(FText::AsCultureInvariant(("ACEScg, D60"))); //5
	SHDRColorSpace.IntValue = 0;

	HDRSettings.Add(SHDRStatus); // 0
	HDRSettings.Add(SHDRDisplayProfile); // 1
	HDRSettings.Add(SHDRColorSpace); // 2

	WindowMode = 0;
	Brightness = 2.f;
}