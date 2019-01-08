#pragma once
#include "Vector.h"

#include "Define.h"

enum
{
	Left,
	Right,
	Up,
	Down,
	DirectionNum
};

class Map;

class Actor
{
protected:
	int gh;				// �O���t�B�b�N�n���h��

	Map* map;


	bool alive = true;

	Vector2 position;
	Vector2 render_position;
	Vector2 velocity;

	int move_count;
	int direction;	// �����Ă������
	int x_now = 0, y_now = 0;
	int x_passable = 0, y_passable = 0;	// �ړ������������̂P�}�X������邽�߂̂��

	char* name;

	bool end_flag = false;

	int msg_color = 0xffffffff;	// �f�t�H���g�͔�

	int now_hp;
	int max_hp;

	int ATK;
	int DEF;

	int Dice(int num, int side);

public:
	void ChangeMap(Map* map, int start_x, int start_y);

	bool GetAlive();

	char* GetName();				// ���O�̎擾
	void SetName(char* name);		// ���O�̃Z�b�g

	Vector2 GetPosition()const;
	Vector2 GetRenderPosition()const;
	void SetPositon(int x, int y);

	bool CheckTurnEnd();
	void SetTurnEndFlag();

	int GetDEF();

	virtual void Render(const Vector2& screen_position, const int grid_size) = 0;

	virtual Vector2 Attack() = 0;					// �U��
	int AttackDamage(int OpponentDEF);	// ���� : �U����̎���� , �߂�l : �_���[�W
	virtual void Damage(int damage) = 0;			// �󂯂�_���[�W
	void Recovery(int recovery);			// ��
};