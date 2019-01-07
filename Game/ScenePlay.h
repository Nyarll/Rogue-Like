#pragma once
#include "Scene.h"
#include "Dungeons.h"
#include "Define.h"
#include "Enemy.h"

class Map;
class Player;

typedef enum 
{
	Wait, // �L�[���͑҂��B�������͑ҋ@��

	PlayerTurn,

	EnemyTurn,

	TurnEnd,   // �^�[���I��
}Action;

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
	
	std::vector<Enemy> enemy;

	Action act;

	bool render_map;
	bool render_msg;

	int dng_floor;
	int msg_font;

	int Sequence_count;

	float deg = 0;
	int render_cnt = 255;
	float change_cnt;
	bool change_flag = false;

	bool action_flag = false;
	bool action_flag_old = false;

public:
	void InitDungeons();
	bool ChangeMap();

	void GotoNextFloor(const Vector2& playerPosition);
	void MagicCircleAction(const Vector2& actorPosition);


	// ����
	void Initialize()override {};
	void Update()override;
	void Render()override;
	void Finalize()override {};
};