#include "Enemy.h"
#include "Map.h"

#include "MessageWindow.h"
#include "SoundManager.h"
#include "Astar.hpp"

Enemy::Enemy(int player_level, int now_floor)
{
	this->move_count = 0;
	this->direction = rand() % DirectionNum;
	this->move_direction = this->direction;

	this->name = "Null Enemy";
	this->type = EnemyTypeNull;

	this->UpdateStatus(player_level, now_floor);
}


Enemy::~Enemy()
{
}

void Enemy::SetTargetPosition(const Vector2& target)
{
	this->target_pos = target;
}

int Enemy::GetMovingDirection()
{
	int search_area = 3;
	int ex = static_cast<int>(this->position.x);
	int ey = static_cast<int>(this->position.y);
	int tx = static_cast<int>(this->target_pos.x);
	int ty = static_cast<int>(this->target_pos.y);

	// サーチ範囲内にプレイヤーがいるかどうか
	if ((ex - search_area <= tx) && (ex + search_area >= tx) &&
		(ey - search_area <= ty) && (ey + search_area >= ty))
	{
		AStar::Generator generator;
		generator.setWorldSize({ MapSizeX, MapSizeY });
		generator.setHeuristic(AStar::Heuristic::euclidean);
		generator.setDiagonalMovement(false);	// 今回は斜め移動しないので false

		// 壁を Astar アルゴリズムへ登録する
		for (int y = 0; y < MapSizeY; y++)
		{
			for (int x = 0; x < MapSizeX; x++)
			{
				if (this->map->GetCellid(x, y))
				{
					generator.addCollision({ x,y });
				}
			}
		}

		std::vector<Vector2> data;	// ルート情報
		{
			auto path = generator.findPath({ static_cast<int>(this->position.x), static_cast<int>(this->position.y) },
			{ static_cast<int>(this->target_pos.x), static_cast<int>(this->target_pos.y) });

			for (auto& coordinate : path)
			{
				Vector2 back;
				back.Set(coordinate.x, coordinate.y);
				data.push_back(back);
			}
		}
		// 移動方向の決定
		for (int i = 0; i < data.size(); i++)
		{
			// 終端
			if (static_cast<int>(data[i].x) == static_cast<int>(this->position.x) &&
				static_cast<int>(data[i].y) == static_cast<int>(this->position.y))
			{
				break;
			}

			if (static_cast<int>(data[i].x) == (static_cast<int>(this->position.x) - 1) &&
				static_cast<int>(data[i].y) == static_cast<int>(this->position.y))
			{
				return Left;
			}
			if (static_cast<int>(data[i].x) == (static_cast<int>(this->position.x) + 1) &&
				static_cast<int>(data[i].y) == static_cast<int>(this->position.y))
			{
				return Right;
			}
			if ((static_cast<int>(data[i].x)) == static_cast<int>(this->position.x) &&
				static_cast<int>(data[i].y) == (static_cast<int>(this->position.y) - 1))
			{
				return Up;
			}
			if ((static_cast<int>(data[i].x)) == static_cast<int>(this->position.x) &&
				static_cast<int>(data[i].y) == (static_cast<int>(this->position.y) + 1))
			{
				return Down;
			}
		}

	}
	else
	{
		int GotoDirection = Left;
		switch (this->move_direction)
		{
		case Left:
			if (this->map->IsPassable(ex - 1, ey))
			{
				GotoDirection = Left;
				break;
			}
			if (this->map->IsPassable(ex, ey + 1))
			{
				GotoDirection = Down;
				break;
			}
			if (this->map->IsPassable(ex, ey - 1))
			{
				GotoDirection = Up;
				break;
			}


		case Right:
			if (this->map->IsPassable(ex + 1, ey))
			{
				GotoDirection = Right;
				break;
			}
			if (this->map->IsPassable(ex, ey - 1))
			{
				GotoDirection = Up;
				break;
			}
			if (this->map->IsPassable(ex, ey + 1))
			{
				GotoDirection = Down;
				break;
			}


		case Up:
			if (this->map->IsPassable(ex + 1, ey))
			{
				GotoDirection = Right;
				break;
			}
			if (this->map->IsPassable(ex, ey - 1))
			{
				GotoDirection = Up;
				break;
			}
			if (this->map->IsPassable(ex - 1, ey))
			{
				GotoDirection = Left;
				break;
			}


		case Down:
			if (this->map->IsPassable(ex - 1, ey))
			{
				GotoDirection = Left;
				break;
			}
			if (this->map->IsPassable(ex, ey + 1))
			{
				GotoDirection = Down;
				break;
			}
			if (this->map->IsPassable(ex + 1, ey))
			{
				GotoDirection = Right;
				break;
			}
		}
		return GotoDirection;
	}
}

int Enemy::CloggedMovingDirection(std::vector<Enemy>& enemy, int num)
{
	int ex = static_cast<int>(this->position.x);
	int ey = static_cast<int>(this->position.y);

	int GotoMovingDirection = this->move_direction;;

	for (int i = 0; i < enemy.size(); i++)
	{
		if (i != num)
		{
			int tx = static_cast<int>(enemy[i].GetPosition().x);
			int ty = static_cast<int>(enemy[i].GetPosition().y);

			if (tx == ex - 1)	// Left
			{
				GotoMovingDirection = Down;
				break;
			}
			if (tx == ex + 1)	// Right
			{
				GotoMovingDirection = Up;
				break;
			}
			if (ty == ey - 1)
			{
				GotoMovingDirection = Left;
				break;
			}
			if (ty == ey + 1)
			{
				GotoMovingDirection = Right;
				break;
			}
		}
	}

	return GotoMovingDirection;
}


bool Enemy::Update(std::vector<Enemy>& enemy, int num)
{
	static bool act_flag = false;

	if (this->move_count == 0)
	{
		act_flag = false;
		this->end_flag = false;
		this->move_direction = this->GetMovingDirection();
		this->velocity = { 0,0 };

		float vel = (1.0f);

		{
			switch (this->move_direction)
			{
			case Left:
				this->velocity.x = (-vel);
				this->velocity.y = (0.0f);
				break;

			case Right:
				this->velocity.x = (vel);
				this->velocity.y = (0.0f);
				break;

			case Up:
				this->velocity.x = (0.0f);
				this->velocity.y = (-vel);
				break;

			case Down:
				this->velocity.x = (0.0f);
				this->velocity.y = (vel);
				break;
			}

			this->x_now = static_cast<int>(this->position.x);
			this->y_now = static_cast<int>(this->position.y);
			this->x_passable = this->x_now + static_cast<int>(this->velocity.x);
			this->y_passable = this->y_now + static_cast<int>(this->velocity.y);

			for (int i = 0; i < enemy.size(); i++)
			{
				if (i != num)
				{
					int ex = static_cast<int>(enemy[i].GetPosition().x);
					int ey = static_cast<int>(enemy[i].GetPosition().y);
					if ((ex == this->x_passable) && (ey == this->y_passable))
					{
						this->move_direction = this->CloggedMovingDirection(enemy, num);
						break;
					}
				}
			}
		}
		if (FloatEquals(this->velocity.x, 0.0f) == false || FloatEquals(this->velocity.y, 0.0f) == false)
		{
			this->move_count = MOVING_INTERVAL;
			this->render_position = this->position;
			// 行きたい方向へ行けるかどうかチェック
			if ((static_cast<int>(this->target_pos.x) == this->x_passable) &&
				(static_cast<int>(this->target_pos.y) == this->y_passable))
			{
				this->velocity.x = 0;
				this->velocity.y = 0;
			}

			// 他のモブが居たらそこへ行けない
			for (int i = 0; i < enemy.size(); i++)
			{
				if (i != num)
				{
					int ex = static_cast<int>(enemy[i].GetPosition().x);
					int ey = static_cast<int>(enemy[i].GetPosition().y);
					if ((ex == this->x_passable) && (ey == this->y_passable))
					{
						this->velocity.x = 0;
						this->velocity.y = 0;
						break;
					}
				}
			}

			{
				if (this->map->IsPassable(x_passable, y_passable))
				{
					if (!((static_cast<int>(this->target_pos.x) == x_passable) &&
						(static_cast<int>(this->target_pos.y) == y_passable)))
					{
						this->position.x += this->velocity.x;
						this->position.y += this->velocity.y;
					}
				}
			}
			act_flag = true;
		}
	}
	else
	{
		act_flag = false;
	}

	// ワールドから出ないようにしておく
	{
		if (this->position.x < 0.0f)
		{
			this->position.x = 0.0f;
		}
		if (this->position.y < 0.0f)
		{
			this->position.y = 0.0f;
		}
		if (this->position.x > (float)(Map::GRID_COLS - 1))
		{
			this->position.x = (float)(Map::GRID_COLS - 1);
		}
		if (this->position.y > (float)(Map::GRID_ROWS * 2 - 1))
		{
			this->position.y = (float)(Map::GRID_ROWS * 2 - 1);
		}
	}
	return act_flag;
}

void Enemy::Render(const Vector2 & screen_position, const int grid_size)
{
	if (this->move_count > 0)
	{
		this->move_count--;

		this->render_position = Vector2().TranslateTowards(this->render_position,
			this->position, 1.0f / 16.0f);
	}

	if (this->alive)
	{
		if (this->type == EnemyTypeNull)
		{
			int x = static_cast<int>(((this->render_position.x + 0.5f) * grid_size) - screen_position.x);
			int y = static_cast<int>(((this->render_position.y + 0.5f) * grid_size) - screen_position.y);

			int x1 = static_cast<int>(((this->render_position.x) * grid_size) - screen_position.x);
			int y1 = static_cast<int>(((this->render_position.y) * grid_size) - screen_position.y);
			int x2 = x1 + grid_size;
			int y2 = y1 + grid_size;
			DrawBox(x1, y1, x2, y2, COLOR_RED, true);
			DrawCircle(x, y, 2, COLOR_BLUE, TRUE);

			x1 = static_cast<int>(((this->position.x) * grid_size) - screen_position.x);
			y1 = static_cast<int>(((this->position.y) * grid_size) - screen_position.y);
			x2 = x1 + grid_size;
			y2 = y1 + grid_size;
			DrawBox(x1, y1, x2, y2, COLOR_AQUA, false);

			switch (this->move_direction)
			{
			case Left:
				DrawLine(x, y, x - 10, y, COLOR_BLUE);
				break;

			case Right:
				DrawLine(x, y, x + 10, y, COLOR_BLUE);
				break;

			case Up:
				DrawLine(x, y, x, y - 10, COLOR_BLUE);
				break;

			case Down:
				DrawLine(x, y, x, y + 10, COLOR_BLUE);
				break;
			}

			//DrawFormatString(10, 10, COLOR_WHITE, "プレーヤーの座標 = (%.2f, %.2f)", this->position.x, this->position.y);
		}
		else
		{
			int x = static_cast<int>(((this->render_position.x + 0.5f) * grid_size) - screen_position.x);
			int y = static_cast<int>(((this->render_position.y + 0.5f) * grid_size) - screen_position.y);

			int x1 = static_cast<int>(((this->position.x) * grid_size) - screen_position.x);
			int y1 = static_cast<int>(((this->position.y) * grid_size) - screen_position.y);
			int x2 = x1 + grid_size;
			int y2 = y1 + grid_size;

			DrawRectRotaGraph(x, y, this->move_direction * 32, 0, 32, 32, 1.25, 0.0, this->gh, true);
			DrawBox(x1, y1, x2, y2, COLOR_AQUA, false);
		}
	}
}

void Enemy::Damage(int damage)
{
	int Damage = damage;
	if (Damage <= 0)
	{
		Damage = 0;
	}
	this->now_hp = this->now_hp - Damage;
	MessageWindow& msg = MessageWindow::singleton();
	msg.SetMessage(COLOR_WHITE, "%s に %d のダメージ！", this->name, Damage);

	if (this->now_hp <= 0)
	{
		this->alive = false;
	}
}

Vector2 Enemy::Attack()
{
	Vector2 attack;
	attack.x = this->position.x + this->move_direction * 1;
	attack.y = this->position.y + this->move_direction * 1;
	MessageWindow& msg = MessageWindow::singleton();
	msg.SetMessage(0xffff4040, "%s の攻撃！", this->name);
	SoundManager& sm = SoundManager::singleton();
	sm.SoundPlay(AttackSE, DX_PLAYTYPE_BACK);
	
	return attack;
}

int Enemy::GetExp()
{
	return this->exp;
}

void Enemy::UpdateStatus(int player_level, int now_floor)
{
	this->max_hp = this->Dice(3 + (player_level), 6) + this->Dice(1 + now_floor, 4) + (player_level);
	this->now_hp = this->max_hp;
	this->ATK = this->Dice(2 + (player_level), 6) + (player_level)+this->Dice(now_floor, 3);
	this->DEF = (player_level)+this->Dice(now_floor, 3);
	this->exp = this->max_hp / 2 + Dice(player_level, 6);
}

bool Enemy::GetAttackFlag()
{
	return this->atk_flag;
}

void Enemy::SetAttackFlag(bool f)
{
	this->atk_flag = f;
}
