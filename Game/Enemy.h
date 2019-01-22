#pragma once

#include "Define.h"
#include "Actor.h"

class Map;

typedef enum
{
	Slime,
	EnemyTypeNum,
	EnemyTypeNull
}EnemyType;

class Enemy : public Actor
{
private:
	static const int MOVING_INTERVAL = 16;
	static const int GRAPH_SIZE_X = 32;
	static const int GRAPH_SIZE_Y = 32;

private:

	Vector2 target_pos;

	int move_direction;

	int exp;

	bool atk_flag = false;
protected:
	int type;

public:
	Enemy(int player_level, int now_floor);
	~Enemy();

	void SetTargetPosition(const Vector2& target);

	int GetMovingDirection();	// 基本的な移動
	int CloggedMovingDirection(std::vector<Enemy>& enemy, int num);	// モブ同士で詰まってしまった場合

	bool Update(std::vector<Enemy>& enemy, int num);

	void Render(const Vector2& screen_position, const int grid_size)override;

	int GetExp();

	Vector2 Attack()override;
	void Damage(int damage)override;			// 受けるダメージ

	void UpdateStatus(int player_level, int now_floor);

	bool GetAttackFlag();
	void SetAttackFlag(bool f);

public:
	void CreateSlime()
	{
		this->gh = LoadGraph("Resources/Textures/Slime.png");
		this->name = "Slime";
		this->type = Slime;
	}
};
