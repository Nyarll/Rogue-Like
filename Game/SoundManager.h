#pragma once
#include "Singleton.h"

enum
{
	Demo,
	GameBGM,
	TitleBGM,
	AttackSE,
	FloorChange,
	Decision,
	SoundNum
};

class SoundManager : public Singleton<SoundManager>
{
private:
	int sh[SoundNum];

	bool play_mode = false;
public:
	friend class Singleton<SoundManager>;

	SoundManager();
	~SoundManager();

	bool SoundRegister(int sound_id, char* file_name);
	bool SoundPlay(int sound_id, int play_type);
	void SoundStop(int sound_id);

	void SetSoundPlayMode(bool mode);
};

