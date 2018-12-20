#pragma once
#include "Vector.h"

#include "Define.h"

class Map;

class Actor
{
protected:
	int gh;				// �O���t�B�b�N�n���h��

	Map* map;

	Vector2 position;
	Vector2 velocity;

	int direction;	// �����Ă������
	int x_now = 0, y_now = 0;
	int x_passable = 0, y_passable = 0;	// �ړ������������̂P�}�X������邽�߂̂��

	int now_hp;
	int max_hp;
};