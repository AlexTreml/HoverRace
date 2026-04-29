//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Save/AudioSave.h"

UAudioSave::UAudioSave()
{
	SaveSlotName = TEXT("Audio");
	DefaultUserIndex = 0;

	VolumeSettings.Add(1.f);
	VolumeSettings.Add(1.f);
	VolumeSettings.Add(1.f);
	VolumeSettings.Add(1.f);
}