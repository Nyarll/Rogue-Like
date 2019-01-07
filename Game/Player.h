#pragma once
#include "Vector.h"
#include "Define.h"
#include "Actor.h"
#include "Enemy.h"

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

	int step_count;		// ����

	int animation_cnt;	// �A�j���[�V�����p�J�E���^
	Vector2 graph_p;

	int font;

public:
	Player();
	~Player();

	void SetFont(int font);

	int GetLevel();

	bool Update(std::vector<Enemy> enemy);

	void Render(const Vector2& screen_position, const int grid_size)override;
	void DrawPlayerStatus();


	int GetMoveCount()const;

	void LevelUp();								// ���x���A�b�v
	void Damage(int damage)override;			// �v���C���[���󂯂�_���[�W

	void Healing();							// ��(�����������ƂP�񕜂�����)


};