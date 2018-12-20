#pragma once
#include "Scene.h"
#include "Dungeons.h"

class Map;
class Player;

typedef enum 
{
	Wait, // キー入力待ち。もしくは待機中

	// アクション
	ActBegin, // 開始
	Act,      // 実行中
	ActEnd,   // 終了

	// 移動
	MoveBegin, // 開始
	Move,      // 移動中
	MoveEnd,   // 完了

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
	Mob_RL mob[RL_MOB_C];

	Map* map;
	Player* player;

	Action act;

	bool render_map;
	bool render_msg;

	int dng_floor;
	int msg_font;

	float deg = 0;
	int render_cnt = 255;
	float change_cnt;
	bool change_flag = false;

	bool action_flag = false;
	bool action_flag_old = false;

public:
	void InitDungeons();
	bool ChangeMap();

	// 操作
	void Initialize()override {};
	void Update()override;
	void Render()override;
	void Finalize()override {};
};