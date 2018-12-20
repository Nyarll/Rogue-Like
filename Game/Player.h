#pragma once
#include "Vector.h"
#include "Define.h"

class Map;

class Player
{
public:
	static const int MOVING_INTERVAL;
	static const int GRAPH_SIZE_X;
	static const int GRAPH_SIZE_Y;

private:
	char* name;

	Map* map;	// ���݂̃}�b�v
	Vector2 position;
	Vector2 velocity;

	int direction;	// �����Ă������

	int move_count;
	int stop_count;

	int x_now = 0, y_now = 0;
	int x_passable = 0, y_passable = 0;	// �ړ������������̂P�}�X������邽�߂̂��

	int gh;	// �O���t�B�b�N�n���h��
	int animation_cnt;	// �A�j���[�V�����p�J�E���^
	Vector2 graph_p;

	int msg_color;

public:
	Player();
	~Player();

	void SetName(char* name);
	char* GetName();

	void ChangeMap(Map* map, int start_x, int start_y);
	void Update();
	void Render(const Vector2& screen_position, const int grid_size);

	Vector2 GetPosition()const;
	int GetMoveCount()const;

	Vector2 Attack();

	
};