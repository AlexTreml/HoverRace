//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/AudioSettingsWidget.h"

UAudioSettingsWidget::UAudioSettingsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MasterVolume = 1.f;
	SFXVolume = 1.f;
	MusicVolume = 1.f;
	VoiceVolume = 1.f;
}

void UAudioSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Sliders
	if (!MasterSlider->OnValueChanged.IsAlreadyBound(this, &UAudioSettingsWidget::OnMasterUpdate))
	{
		MasterSlider->OnValueChanged.AddDynamic(this, &UAudioSettingsWidget::OnMasterUpdate);
	}

	if (!SFXSlider->OnValueChanged.IsAlreadyBound(this, &UAudioSettingsWidget::OnSFXUpdate))
	{
		SFXSlider->OnValueChanged.AddDynamic(this, &UAudioSettingsWidget::OnSFXUpdate);
	}

	if (!MusicSlider->OnValueChanged.IsAlreadyBound(this, &UAudioSettingsWidget::OnMusicUpdate))
	{
		MusicSlider->OnValueChanged.AddDynamic(this, &UAudioSettingsWidget::OnMusicUpdate);
	}

	if (VoiceSlider && !VoiceSlider->OnValueChanged.IsAlreadyBound(this, &UAudioSettingsWidget::OnVoiceUpdate))
	{
		VoiceSlider->OnValueChanged.AddDynamic(this, &UAudioSettingsWidget::OnVoiceUpdate);
	}

	//Apply
	if (!ApplyButton->OnPressed.IsAlreadyBound(this, &UAudioSettingsWidget::OnApplyPress))
	{
		ApplyButton->OnPressed.AddDynamic(this, &UAudioSettingsWidget::OnApplyPress);
	}

	if (!ResetButton->OnPressed.IsAlreadyBound(this, &UAudioSettingsWidget::ResetSettings))
	{
		ResetButton->OnPressed.AddDynamic(this, &UAudioSettingsWidget::ResetSettings);
	}

	if (bInstantApply)
	{
		ApplyButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		ApplyButton->SetVisibility(ESlateVisibility::Visible);
	}

	LoadSettings();

}

void UAudioSettingsWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
}

void UAudioSettingsWidget::OnMasterUpdate(float Value)
{
	MasterVolume = Value / 100.f;

	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UAudioSettingsWidget::OnSFXUpdate(float Value)
{
	SFXVolume = Value / 100.f;

	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UAudioSettingsWidget::OnMusicUpdate(float Value)
{
	MusicVolume = Value / 100.f;

	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UAudioSettingsWidget::OnVoiceUpdate(float Value)
{
	VoiceVolume = Value / 100.f;

	if (bInstantApply)
	{
		SaveSettings();
	}
}

void UAudioSettingsWidget::OnApplyPress()
{
	SaveSettings();
}

void UAudioSettingsWidget::LoadSettings()
{
	TSubclassOf<UAudioSave> SaveClass;

	if (AudioSaveClass)
	{
		SaveClass = AudioSaveClass;
	}
	else
	{
		SaveClass = UAudioSave::StaticClass();
	}

	UAudioSave* AudioSave = Cast<UAudioSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

	if (AudioSave)
	{
		if (UGameplayStatics::DoesSaveGameExist(TEXT("Audio"), 0))
		{
			AudioSave = Cast<UAudioSave>(UGameplayStatics::LoadGameFromSlot(TEXT("Audio"), 0));
		}

		MasterVolume = AudioSave->VolumeSettings[0];
		SFXVolume = AudioSave->VolumeSettings[1];
		MusicVolume = AudioSave->VolumeSettings[2];
		VoiceVolume = AudioSave->VolumeSettings[3];

		MasterSlider->SetSliderValue(MasterVolume * 100.f);
		SFXSlider->SetSliderValue(SFXVolume * 100.f);
		MusicSlider->SetSliderValue(MusicVolume * 100.f);
		if (VoiceSlider) VoiceSlider->SetSliderValue(VoiceVolume * 100.f);
	}
}

void UAudioSettingsWidget::SaveSettings()
{
	if (!IsSettingsSaved())
	{
		if (MasterSoundClass)
		{
			MasterSoundClass->Properties.Volume = MasterVolume;
		}

		if (SFXSoundClass)
		{
			SFXSoundClass->Properties.Volume = SFXVolume;
		}

		if (MusicSoundClass)
		{
			MusicSoundClass->Properties.Volume = MusicVolume;
		}

		if (VoiceSoundClass)
		{
			VoiceSoundClass->Properties.Volume = VoiceVolume;
		}

		TSubclassOf<UAudioSave> SaveClass;

		if (AudioSaveClass)
		{
			SaveClass = AudioSaveClass;
		}
		else
		{
			SaveClass = UAudioSave::StaticClass();
		}

		UAudioSave* AudioSave = Cast<UAudioSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

		if (AudioSave)
		{
			if (UGameplayStatics::DoesSaveGameExist(AudioSave->SaveSlotName, AudioSave->DefaultUserIndex))
			{
				AudioSave = Cast<UAudioSave>(UGameplayStatics::LoadGameFromSlot(AudioSave->SaveSlotName, AudioSave->DefaultUserIndex));
			}
		}

		if (AudioSave)
		{
			if (AudioSave->VolumeSettings.IsValidIndex(0))
			{
				AudioSave->VolumeSettings[0] = MasterVolume;
			}

			if (AudioSave->VolumeSettings.IsValidIndex(1))
			{
				AudioSave->VolumeSettings[1] = SFXVolume;
			}

			if (AudioSave->VolumeSettings.IsValidIndex(2))
			{
				AudioSave->VolumeSettings[2] = MusicVolume;
			}

			if (AudioSave->VolumeSettings.IsValidIndex(3))
			{
				AudioSave->VolumeSettings[3] = VoiceVolume;
			}

			UGameplayStatics::SaveGameToSlot(AudioSave, TEXT("Audio"), 0); //Finally saving the stuff to the slot. 
		}
	}
}

void UAudioSettingsWidget::ResetSettings()
{
	TSubclassOf<UAudioSave> SaveClass;

	if (AudioSaveClass)
	{
		SaveClass = AudioSaveClass;
	}
	else
	{
		SaveClass = UAudioSave::StaticClass();
	}

	UAudioSave* AudioSave = Cast<UAudioSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

	if (AudioSave)
	{
		MasterVolume = AudioSave->VolumeSettings[0];
		SFXVolume = AudioSave->VolumeSettings[1];
		MusicVolume = AudioSave->VolumeSettings[2];
		VoiceVolume = AudioSave->VolumeSettings[3];

		MasterSlider->SetSliderValue(MasterVolume * 100.f);
		SFXSlider->SetSliderValue(SFXVolume * 100.f);
		MusicSlider->SetSliderValue(MusicVolume * 100.f);
		if (VoiceSlider) VoiceSlider->SetSliderValue(VoiceVolume * 100.f);
	}
}

bool UAudioSettingsWidget::IsSettingsSaved()
{
	bool IsSaved = true;

	TSubclassOf<UAudioSave> SaveClass;

	if (AudioSaveClass)
	{
		SaveClass = AudioSaveClass;
	}
	else
	{
		SaveClass = UAudioSave::StaticClass();
	}

	UAudioSave* LastAudioSave = Cast<UAudioSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

	if (LastAudioSave)
	{
		if (UGameplayStatics::DoesSaveGameExist(TEXT("Audio"), 0))
		{
			LastAudioSave = Cast<UAudioSave>(UGameplayStatics::LoadGameFromSlot(TEXT("Audio"), 0));
		}

		if (LastAudioSave->VolumeSettings[0] != MasterVolume)
		{
			IsSaved = false;
		}

		if (IsSaved && LastAudioSave->VolumeSettings[1] != SFXVolume)
		{
			IsSaved = false;
		}

		if (IsSaved && LastAudioSave->VolumeSettings[2] != MusicVolume)
		{
			IsSaved = false;
		}

		if (IsSaved && LastAudioSave->VolumeSettings[3] != VoiceVolume)
		{
			IsSaved = false;
		}
	}

	return IsSaved;
}