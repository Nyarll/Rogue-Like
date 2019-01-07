#include "Enemy.h"
#include "Map.h"

#include "MessageWindow.h"

const std::vector<std::string> Enemy::EnemyNameList =
{
	"スライム",
	"バット"
};

Enemy::Enemy()
{
	this->move_count = 0;
	this->direction = Down;
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
	int dx, dy;
	dx = this->target_pos.x - this->position.x;
	dy = this->target_pos.y - this->position.y;

	if (abs(dx) > abs(dy))
	{
		// X方向への距離の方が遠いのでそっちに進む
		if (dx < 0) { return Left; } // 左
		else { return Right; } // 右
	}
	else
	{
		// Y方向へ進む
		if (dy < 0) { return Up; } // 上
		else { return Down; } // 下
	}
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

		if (FloatEquals(this->velocity.x, 0.0f) == false || FloatEquals(this->velocity.y, 0.0f) == false)
		{
			this->move_count = MOVING_INTERVAL;
			// 行きたい方向へ行けるかどうかチェック
			if ((static_cast<int>(this->target_pos.x) == this->x_passable) &&
				(static_cast<int>(this->target_pos.y) == this->y_passable))
			{
				this->velocity.x = 0;
				this->velocity.y = 0;
			}
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
					if ((static_cast<int>(this->target_pos.x) != x_passable))
					{
						this->position.x += this->velocity.x;
					}
					if ((static_cast<int>(this->target_pos.y) != y_passable))
					{
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
	// デバッグ用
	bool debug_mode = true;

	if (this->move_count > 0)
	{
		this->move_count--;
		if (this->velocity.x != 0 && this->velocity.y != 0)
		{
			if (this->map->IsPassable(x_passable, y_passable))
			{
				if ((this->map->IsPassable(this->x_passable, this->y_now)))
				{
					this->render_position.x += this->velocity.x / (MOVING_INTERVAL);

				}
				if ((this->map->IsPassable(this->x_now, this->y_passable)))
				{
					this->render_position.y += this->velocity.y / (MOVING_INTERVAL);
				}
			}
		}
		else
		{
			if ((this->map->IsPassable(this->x_passable, this->y_now)))
			{
				this->render_position.x += this->velocity.x / (MOVING_INTERVAL);
			}
			if ((this->map->IsPassable(this->x_now, this->y_passable)))
			{
				this->render_position.y += this->velocity.y / (MOVING_INTERVAL);
			}
		}

		if (this->move_count == 0)
		{
			this->render_position.x = static_cast<float>(static_cast<int>(this->render_position.x));
			this->render_position.y = static_cast<float>(static_cast<int>(this->render_position.y));
		}
	}

	if (this->alive)
	{
		if (debug_mode)
		{
			int x = static_cast<int>(((this->render_position.x + 0.5f) * grid_size) - screen_position.x);
			int y = static_cast<int>(((this->render_position.y + 0.5f) * grid_size) - screen_position.y);

			int x1 = static_cast<int>(((this->position.x) * grid_size) - screen_position.x);
			int y1 = static_cast<int>(((this->position.y) * grid_size) - screen_position.y);
			int x2 = x1 + grid_size;
			int y2 = y1 + grid_size;
			DrawBox(x1, y1, x2, y2, COLOR_RED, true);
			DrawCircle(x, y, 2, COLOR_BLUE, TRUE);

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

			int x1 = static_cast<int>(((this->render_position.x) * grid_size) - screen_position.x);
			int y1 = static_cast<int>(((this->render_position.y) * grid_size) - screen_position.y);
			int x2 = x1 + grid_size;
			int y2 = y1 + grid_size;

		}
	}
}

void Enemy::Damage(int damage)
{
}

