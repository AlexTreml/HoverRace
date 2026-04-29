// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/SettingsFunctionLibrary.h"
#include "Save/GraphicsSave.h"
#include "Kismet/GameplayStatics.h"
#include "Save/AudioSave.h"
#include "Save/VideoSave.h"
#include "Save/ControlsSave.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

void USettingsFunctionLibrary::UpdateGraphics()
{
	UWorld* World = GEngine->GetWorld();

	UGraphicsSave* SaveGraphics = Cast<UGraphicsSave>(UGameplayStatics::CreateSaveGameObject(UGraphicsSave::StaticClass()));

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
				if (SaveGraphics->GeneralSettings.IsValidIndex(i))
				{
					World->Exec(World, *(SaveGraphics->GeneralSettings[i].SettingCommand + FString::FromInt(SaveGraphics->GeneralSettings[i].IntValue)));
				}
			}

			for (int i = 0; i < SaveGraphics->AdvancedSettings.Num(); i++)
			{
				if (SaveGraphics->AdvancedSettings.IsValidIndex(i))
				{
					if (!SaveGraphics->AdvancedSettings[i].SettingCommand.IsEmpty())
					{
						World->Exec(World, *(SaveGraphics->AdvancedSettings[i].SettingCommand + FString::FromInt(SaveGraphics->AdvancedSettings[i].IntValue)));
					}

					if (SaveGraphics->AdvancedSettings[i].AdditionalCommandOnValue.Num())
					{
						for (int j = 0; j < SaveGraphics->AdvancedSettings[i].AdditionalCommandOnValue.Num(); j++)
						{
							World->Exec(World, *(SaveGraphics->AdvancedSettings[i].AdditionalCommandOnValue[j].Command));
						}
					}
				}
			}
		}
	}
}

void USettingsFunctionLibrary::UpdateVideo()
{
	UWorld* World = GEngine->GetWorld();

	UVideoSave* VideoSave = Cast<UVideoSave>(UGameplayStatics::CreateSaveGameObject(UVideoSave::StaticClass()));

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
			if (VideoSave->FPSSettings.IsValidIndex(i))
			{
				if (VideoSave->FPSSettings[i].AdditionalCommandOnValue.Num())
				{
					for (int j = 0; j < VideoSave->FPSSettings[i].AdditionalCommandOnValue.Num(); j++)
					{
						if (VideoSave->FPSSettings[i].IntValue == VideoSave->FPSSettings[i].AdditionalCommandOnValue[j].IntSettingValue)
						{
							World->Exec(World, *(VideoSave->FPSSettings[i].AdditionalCommandOnValue[j].Command));
						}
					}
				}
			}
		}

		//HDR
		for (int i = 0; i < VideoSave->HDRSettings.Num(); i++)
		{
			if (VideoSave->HDRSettings.IsValidIndex(i))
			{
				World->Exec(World, *(VideoSave->HDRSettings[i].SettingCommand + FString::FromInt(VideoSave->HDRSettings[i].IntValue)));
			}
		}

		//WindowMode
		EWindowMode::Type InFullscreenMode;

		switch (VideoSave->WindowMode)
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

		World->Exec(World, *("r.TonemapperGamma " + FString::SanitizeFloat(VideoSave->Brightness)));


		UGameUserSettings::GetGameUserSettings()->SetScreenResolution(VideoSave->Resolution);

		//UGameUserSettings::GetGameUserSettings()->ApplyResolutionSettings(false);
		UGameUserSettings::GetGameUserSettings()->ApplySettings(false);
	}
}

void USettingsFunctionLibrary::UpdateAudio(TArray<USoundClass*> SoundClassArray)
{
	UAudioSave* AudioSave = Cast<UAudioSave>(UGameplayStatics::CreateSaveGameObject(UAudioSave::StaticClass()));

	if (AudioSave)
	{
		if (UGameplayStatics::DoesSaveGameExist(TEXT("Audio"), 0))
		{
			AudioSave = Cast<UAudioSave>(UGameplayStatics::LoadGameFromSlot(TEXT("Audio"), 0));
		}

		for (int i = 0; i < AudioSave->VolumeSettings.Num(); i++)
		{
			if (AudioSave->VolumeSettings.IsValidIndex(i) && SoundClassArray.IsValidIndex(i))
			{
				SoundClassArray[i]->Properties.Volume = AudioSave->VolumeSettings[i];
			}
		}
	}
}

void USettingsFunctionLibrary::UpdateControls(UInputMappingContext* PlayerInputMapping)
{

	UControlsSave* ControlsSave = Cast<UControlsSave>(UGameplayStatics::CreateSaveGameObject(UControlsSave::StaticClass()));

	if (ControlsSave)
	{
		if (UGameplayStatics::DoesSaveGameExist("Controls", 0))
		{
			ControlsSave = Cast<UControlsSave>(UGameplayStatics::LoadGameFromSlot("Controls", 0));

			if (ControlsSave)
			{
				if (PlayerInputMapping)
				{
					for (int i = 0; i < ControlsSave->KeyArray.Num(); i++)
					{
						PlayerInputMapping->UnmapAllKeysFromAction(ControlsSave->KeyArray[i].Action);
						PlayerInputMapping->MapKey(ControlsSave->KeyArray[i].Action, ControlsSave->KeyArray[i].Key);
					}
				}
			}
		}
	}
}