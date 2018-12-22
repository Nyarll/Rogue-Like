#pragma once
#include "Vector.h"
#include "Define.h"
#include "Actor.h"

class Map;

class Player extends Actor
{
public:
	static const int MOVING_INTERVAL;
	static const int GRAPH_SIZE_X;
	static const int GRAPH_SIZE_Y;

private:

	int level;

	int stop_count;

	int step_count;		// 歩数

	int animation_cnt;	// アニメーション用カウンタ
	Vector2 graph_p;

	int font;

public:
	Player();
	~Player();

	void SetFont(int font);

	int GetLevel();

	bool Update()override;

	void Render(const Vector2& screen_position, const int grid_size)override;
	void DrawPlayerStatus();

	
	int GetMoveCount()const;

	void LevelUp();								// レベルアップ
	void Damage(int damage)override;			// プレイヤーが受けるダメージ

	void Healing();							// 回復(何歩か歩くと１回復するやつ)

	
};