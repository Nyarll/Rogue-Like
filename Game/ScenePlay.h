#pragma once
#include "Scene.h"
#include "Dungeons.h"
#include "Define.h"
#include "Enemy.h"

class Map;
class Player;

typedef enum 
{
	Wait, // キー入力待ち。もしくは待機中

	PlayerTurn,

	EnemyTurn,

	TurnEnd,   // ターン終了
}Action;

class ScenePlay : public Scene
{
public:
	static Scene* Create();

	// コンストラクタ
	ScenePlay();
	// デストラクタ
	~ScenePlay();

private:

	Vector2 playerAttackPoint = { -1,-1 };
	Vector2 enemyAttackPoint = { -1,-1 };

	Mob_RL mob[RL_MOB_C];

	Map* map;
	Player* player;
	
	std::vector<Enemy> enemy;

	Action act;

	bool render_map;
	bool render_msg;

	int dng_floor;
	int msg_font;

	int ui_font;

	int Sequence_count;

	float deg = 0;
	int render_cnt = 255;
	float change_cnt;
	bool change_flag = false;

	bool action_flag = false;
	bool action_flag_old = false;

	int wait_time = 0;

public:
	void InitDungeons();
	bool ChangeMap();

	void GotoNextFloor(const Vector2& playerPosition);
	void MagicCircleAction(const Vector2& actorPosition);


	// 操作
	void Initialize()override {};
	void Update()override;
	void Render()override;
	void Finalize()override {};
};