#pragma once
#include "Vector.h"
#include "Define.h"
#include "Actor.h"
#include "Enemy.h"
#include "Item.h"

class Map;

class Player : public Actor
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

	int Inventory[ItemTypeNum];

public:
	Player();
	~Player();

	void SetFont(int font);

	void SetLevel(int lv) { this->level = lv; }
	int GetLevel();
	void SetHP(int max, int now) { this->max_hp = max; this->now_hp = now; }

	bool Update(std::vector<Enemy> enemy);

	void Render(const Vector2& screen_position, const int grid_size)override;
	void DrawPlayerStatus();
	void DrawPlayerExp();

	int GetMoveCount()const;

	int GetExp();
	void SetExp(int exp) { this->Exp = exp; }
	void AddExp(int exp);
	int GetNextExp();
	void SetNextExp(int next_exp) { this->next_exp = this->Exp; }

	void SetStatus(int atk, int def) { this->ATK = atk; this->DEF = def; }
	void SetInventory(int item_id, int num)
	{
		this->Inventory[item_id] = num;
	}

	void LevelUp();								// ���x���A�b�v
	Vector2 Attack()override;
	void Damage(int damage)override;			// �v���C���[���󂯂�_���[�W

	void Healing();							// ��(�����������ƂP�񕜂�����)

	int GetNumberKey(int num);

	int GetItemNum(int itemType);
	void AddItem(int itemType);
	void UseItem(int itemType);
	void DrawInventoryList();
};