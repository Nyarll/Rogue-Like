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

	int step_count;		// ����

	int animation_cnt;	// �A�j���[�V�����p�J�E���^
	Vector2 graph_p;

	int font;
	int menu_font;

	int Exp;	// �݌v�l���o���l
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

	void LevelUp();								// ���x���A�b�v
	Vector2 Attack()override;
	void Damage(int damage)override;			// �v���C���[���󂯂�_���[�W

	void Healing();							// ��(�����������ƂP�񕜂�����)

	void GettingItem(const Item& item);
	int GetInventoryInItemNum();
	void DrawInventoryList();
};