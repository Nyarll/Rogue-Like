#pragma once
#include "Vector.h"
#include "Define.h"
#include "Actor.h"

class Map;

class Player extends Actor
{
public:
	static const int MOVING_INTERVAL;
	static const int GRAPH_SIZE_X;
	static const int GRAPH_SIZE_Y;

private:
	char* name;

	int level;

	bool alive = true;

	int move_count;
	int stop_count;

	int animation_cnt;	// アニメーション用カウンタ
	Vector2 graph_p;

	int font;

	int msg_color;

public:
	Player();
	~Player();

	void SetName(char* name);
	char* GetName();

	void SetFont(int font);

	bool GetAlive();
	int GetLevel();

	void ChangeMap(Map* map, int start_x, int start_y);
	bool Update();
	void Render(const Vector2& screen_position, const int grid_size);
	void DrawPlayerStatus();

	Vector2 GetPosition()const;
	int GetMoveCount()const;

	void LevelUp();
	Vector2 Attack();
	void Damage(int damage);
	void Recovery(int recovery);

	
};