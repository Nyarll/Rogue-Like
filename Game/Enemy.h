#pragma once

#include "Define.h"
#include "Actor.h"

class Map;

class Enemy extends Actor
{
private:
	static const int MOVING_INTERVAL = 16;
	static const int GRAPH_SIZE_X = 32;
	static const int GRAPH_SIZE_Y = 32;

	static const std::vector<std::string> EnemyNameList;

private:
	std::string name;



public:
	Enemy();
	~Enemy();
};

