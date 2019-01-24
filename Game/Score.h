#pragma once
#include "Singleton.h"
#include "Player.h"

class Score : public Singleton<Score>
{
private:
	int floor;
	int level;

	struct SavePlayerData
	{
		int floor;
		int level;
		int hp_max;
		int hp_now;
		int ATK;
		int DEF;
		int exp;
		int next_exp;
		int inventry[ItemTypeNum];
	}data;

	bool load_flag = false;

public:
	friend class Singleton<Score>;

	void Init() { this->floor = (0); this->level = (1); };

	void SetScore(int sc, int lv) { this->floor = sc;	this->level = lv; }
	int GetScoreFloor() { return this->floor; }
	int GetScoreLevel() { return this->level; }

	void SetLoadFlag(bool flag) { this->load_flag = flag; }
	bool GetLoadFlag() { return this->load_flag; }

	void Save(Player* player, int floor);
	bool Load(int& floor,
		int& level,
		int& hp_max,
		int& hp_now,
		int& ATK,
		int& DEF,
		int& exp,
		int& next_exp,
		int inventry[ItemTypeNum]);

private:
	bool PlayerDataFileOutput();
	bool PlayerDataFileInput();
};