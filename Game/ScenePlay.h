#pragma once
#include "Scene.h"
#include "Dungeons.h"

class Map;
class Player;

class ScenePlay : public Scene
{
public:
	static Scene* Create();

	// �R���X�g���N�^
	ScenePlay();
	// �f�X�g���N�^
	~ScenePlay();

private:
	Mob_RL mob[RL_MOB_C];

	Map* map;
	Player* player;

	bool render_map;
	bool render_msg;

	int dng_floor;
	int msg_font;

	float deg = 0;
	int render_cnt = 255;
	float change_cnt;
	bool change_flag = false;

public:
	void InitDungeons();
	bool ChangeMap();

	// ����
	void Initialize()override {};
	void Update()override;
	void Render()override;
	void Finalize()override {};
};