#pragma once
#include "Scene.h"
#include "Dungeons.h"
#include "Define.h"
#include "Enemy.h"
#include "Item.h"

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
	std::vector<Item> item;

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

	bool menu_flag = false;

private:
	// マップ関連
	void InitDungeons();
	bool ChangeMap();

	// 踏んだ床の種類によって判定
	void GotoNextFloor(const Vector2& playerPosition);
	void MagicCircleAction(const Vector2& actorPosition);

	// 機能など
	void GameFunction();
	void GameAction();

	// シークエンス処理
	void WaitTurnSequence();
	void PlayerTurnSequence();
	void EnemyTurnSequence();
	void TurnEndSequence();
	void GameTurnSequence();

	// 表示関連
	Vector2 GetScreenPosition();
	void RenderNowFloor();
	void RenderMap();
	void RenderOtherUI();

public:
	// 操作
	void Initialize()override {};
	void Update()override;
	void Render()override;
	void Finalize()override {};
};