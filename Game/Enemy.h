#pragma once

#include "Define.h"
#include "Actor.h"

class Map;

enum
{
	Left,
	Right,
	Up,
	Down
};

class Enemy extends Actor
{
private:
	static const int MOVING_INTERVAL = 16;
	static const int GRAPH_SIZE_X = 32;
	static const int GRAPH_SIZE_Y = 32;

	static const std::vector<std::string> EnemyNameList;

private:
	Vector2 target_pos;

	int move_direction;

public:
	Enemy();
	~Enemy();

	void SetTargetPosition(const Vector2& target);

	int GetMovingDirection();

	bool Update(std::vector<Enemy>& enemy, int num);

	void Render(const Vector2& screen_position, const int grid_size)override;

	void Damage(int damage)override;			// éÛÇØÇÈÉ_ÉÅÅ[ÉW
};

