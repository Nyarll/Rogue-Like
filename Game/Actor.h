#pragma once
#include "Vector.h"

#include "Define.h"

class Map;

class Actor
{
protected:
	int gh;				// グラフィックハンドル

	Map* map;

	Vector2 position;
	Vector2 velocity;

	int direction;	// 向いている方向
	int x_now = 0, y_now = 0;
	int x_passable = 0, y_passable = 0;	// 移動したい方向の１マス先を見るためのやつ

	int now_hp;
	int max_hp;
};