#pragma once
#include "Vector.h"
#include "Define.h"
#include "Actor.h"
#include "Enemy.h"
#include "Item.h"

class Map;

class Player extends Actor
{
public:
	static const int MOVING_INTERVAL;
	static const int GRAPH_SIZE_X;
	static const int GRAPH_SIZE_Y;

	static const int MAX_ITEM_INVENTORY;

private:

	int level;

	int stop_count;

	int step_count;		// 歩数

	int animation_cnt;	// アニメーション用カウンタ
	Vector2 graph_p;

	int font;
	int menu_font;

	int Exp;	// 累計獲得経験値
	int next_exp;

	std::vector<Item> inventory;

public:
	Player();
	~Player();

	void SetFont(int font);

	int GetLevel();

	bool Update(std::vector<Enemy> enemy);

	void Render(const Vector2& screen_position, const int grid_size)override;
	void DrawPlayerStatus();
	void DrawPlayerExp();

	int GetMoveCount()const;

	int GetExp();
	void AddExp(int exp);

	void LevelUp();								// レベルアップ
	Vector2 Attack()override;
	void Damage(int damage)override;			// プレイヤーが受けるダメージ

	void Healing();							// 回復(何歩か歩くと１回復するやつ)

	void GettingItem(const Item& item);
	int GetInventoryInItemNum();
	void DrawInventoryList();
};