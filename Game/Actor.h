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
	int gh;				// グラフィックハンドル

	Map* map;


	bool alive = true;

	Vector2 position;
	Vector2 render_position;
	Vector2 velocity;

	int move_count;
	int direction;	// 向いている方向
	int x_now = 0, y_now = 0;
	int x_passable = 0, y_passable = 0;	// 移動したい方向の１マス先を見るためのやつ

	char* name;

	bool end_flag = false;

	int msg_color = 0xffffffff;	// デフォルトは白

	int now_hp;
	int max_hp;

	int ATK;
	int DEF;

	int Dice(int num, int side);

public:
	void ChangeMap(Map* map, int start_x, int start_y);

	bool GetAlive();

	char* GetName();				// 名前の取得
	void SetName(char* name);		// 名前のセット

	Vector2 GetPosition()const;
	Vector2 GetRenderPosition()const;
	void SetPositon(int x, int y);

	bool CheckTurnEnd();
	void SetTurnEndFlag();

	int GetDEF();

	virtual void Render(const Vector2& screen_position, const int grid_size) = 0;

	virtual Vector2 Attack() = 0;					// 攻撃
	int AttackDamage(int OpponentDEF);	// 引数 : 攻撃先の守備力 , 戻り値 : ダメージ
	virtual void Damage(int damage) = 0;			// 受けるダメージ
	void Recovery(int recovery);			// 回復
};