#pragma once

#include "Define.h"
#include "Actor.h"

class Map;

typedef enum
{
	Slime,
	TypeNum
}EnemyType;

class Enemy extends Actor
{
private:
	static const int MOVING_INTERVAL = 16;
	static const int GRAPH_SIZE_X = 32;
	static const int GRAPH_SIZE_Y = 32; 

private:
	int type;

	Vector2 target_pos;

	int move_direction;

	int exp;

public:
	Enemy(int player_level);
	~Enemy();

	void SetTargetPosition(const Vector2& target);

	int GetMovingDirection();	// ��{�I�Ȉړ�
	int CloggedMovingDirection(std::vector<Enemy>& enemy, int num);	// ���u���m�ŋl�܂��Ă��܂����ꍇ

	bool Update(std::vector<Enemy>& enemy, int num);

	void Render(const Vector2& screen_position, const int grid_size)override;

	int GetExp();

	Vector2 Attack()override;
	void Damage(int damage)override;			// �󂯂�_���[�W
};

