#include "SoundManager.h"



SoundManager::SoundManager()
{
	for (int i = 0; i < SoundNum; i++)
	{
		this->sh[i] = (-1);
	}
}


SoundManager::~SoundManager()
{
}

bool SoundManager::SoundRegister(int sound_id, char * file_name)
{
	if (this->sh[sound_id] == (-1))
	{
		this->sh[sound_id] = LoadSoundMem(file_name);
		return true;
	}
	return false;
}

bool SoundManager::SoundPlay(int sound_id, int play_type)
{
	if (this->sh[sound_id] != (-1))
	{
		PlaySoundMem(this->sh[sound_id], play_type);
		return true;
	}

	return false;
}

void SoundManager::SoundStop(int sound_id)
{
	StopSoundMem(this->sh[sound_id]);
}
