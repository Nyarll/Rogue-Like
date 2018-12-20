#include "Player.h"
#include "Map.h"
#include "Input.h"
#include "MessageWindow.h"

const int Player::MOVING_INTERVAL = 16;
const int Player::GRAPH_SIZE_X = 32;
const int Player::GRAPH_SIZE_Y = 48;

Player::Player()
{
	this->map = nullptr;
	this->position = { 0,0 };
	this->velocity = { 0,0 };
	this->move_count = 0;

	this->font = CreateFontToHandle("HGS創英ﾌﾟﾚｾﾞﾝｽEB", 32, -1);

	this->direction = 1;

	this->level = 1;

	this->gh = LoadGraph("Resources/Textures/Characters_32_48.png");
	this->animation_cnt = 0;
	this->graph_p.x = 0;
	this->graph_p.y = 0;

	this->msg_color = 0xff00ff0f;

	this->max_hp = rand() % 20 + 10;
	this->now_hp = this->max_hp;
}

Player::~Player()
{

}

void Player::SetName(char * name)
{
	this->name = name;
}

char * Player::GetName()
{
	return this->name;
}

void Player::SetFont(int font)
{
	this->font = font;
}

bool Player::GetAlive()
{
	return this->alive;
}

int Player::GetLevel()
{
	return this->level;
}

void Player::ChangeMap(Map* map, int start_x, int start_y)
{
	this->map = map;
	this->position = { (float)(start_x),(float)(start_y) };
}

bool Player::Update()
{
	static bool act_flag = false;
	if (this->alive)
	{
		// 移動中ではないなら
		if (this->move_count == 0)
		{
			act_flag = false;
			this->velocity = { 0,0 };
			InputManager& input = InputManager::singleton();
			InputKeyBoard* key = input.key;

			if ((key->GetNow(KEY_INPUT_UP)) || key->GetNow(KEY_INPUT_W))
			{
				this->velocity.y += -1.0f;
				this->direction = 4;

			}
			if ((key->GetNow(KEY_INPUT_DOWN)) || key->GetNow(KEY_INPUT_S))
			{
				this->velocity.y += 1.0f;
				this->direction = 1;

			}
			if ((key->GetNow(KEY_INPUT_LEFT)) || key->GetNow(KEY_INPUT_A))
			{
				this->velocity.x += -1.0f;
				this->direction = 2;

			}
			if (key->GetNow(KEY_INPUT_RIGHT) || key->GetNow(KEY_INPUT_D))
			{
				this->velocity.x += 1.0f;
				this->direction = 3;
			}

			if (FloatEquals(this->velocity.x, 0.0f) == false || FloatEquals(this->velocity.y, 0.0f) == false)
			{
				this->move_count = MOVING_INTERVAL;
			}

			this->x_now = static_cast<int>(this->position.x);
			this->y_now = static_cast<int>(this->position.y);
			this->x_passable = static_cast<int>(this->position.x + this->velocity.x);
			this->y_passable = static_cast<int>(this->position.y + this->velocity.y);

		}

		if (this->move_count > 0)
		{
			this->move_count--;

			// 行きたい方向へ行けるかどうかチェック
			if (this->velocity.x != 0 && this->velocity.y != 0)
			{
				if (this->map->IsPassable(x_passable, y_passable))
				{
					if ((this->map->IsPassable(this->x_passable, this->y_now)))
					{
						if (!act_flag)
						{
							act_flag = true;
						}
						this->position.x += this->velocity.x / (MOVING_INTERVAL);

					}
					if ((this->map->IsPassable(this->x_now, this->y_passable)))
					{
						if (!act_flag)
						{
							act_flag = true;
						}
						this->position.y += this->velocity.y / (MOVING_INTERVAL);
					}
				}
			}
			else
			{
				if ((this->map->IsPassable(this->x_passable, this->y_now)))
				{
					this->position.x += this->velocity.x / (MOVING_INTERVAL);
					if (!act_flag)
					{
						act_flag = true;
					}
				}
				if ((this->map->IsPassable(this->x_now, this->y_passable)))
				{
					this->position.y += this->velocity.y / (MOVING_INTERVAL);
					if (!act_flag)
					{
						act_flag = true;
					}
				}
			}

			if (this->move_count == 0)
			{
				this->position.x = static_cast<float>(static_cast<int>(this->position.x));
				this->position.y = static_cast<float>(static_cast<int>(this->position.y));
			}
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
	}
	return act_flag;
}

void Player::Render(const Vector2& screen_position, const int grid_size)
{
	// デバッグ用
	bool debug_mode = false;

	if (this->alive)
	{
		if (debug_mode)
		{
			int x = static_cast<int>(((this->position.x + 0.5f) * grid_size) - screen_position.x);
			int y = static_cast<int>(((this->position.y + 0.5f) * grid_size) - screen_position.y);

			int x1 = static_cast<int>(((this->position.x) * grid_size) - screen_position.x);
			int y1 = static_cast<int>(((this->position.y) * grid_size) - screen_position.y);
			int x2 = x1 + grid_size;
			int y2 = y1 + grid_size;
			DrawBox(x1, y1, x2, y2, COLOR_AQUA, true);
			DrawCircle(x, y, 2, COLOR_RED, TRUE);

			DrawFormatString(10, 10, COLOR_WHITE, "プレーヤーの座標 = (%.2f, %.2f)", this->position.x, this->position.y);
		}
		else
		{
			int x = static_cast<int>(((this->position.x + 0.5f) * grid_size) - screen_position.x);
			int y = static_cast<int>(((this->position.y + 0.5f) * grid_size) - screen_position.y);

			int x1 = static_cast<int>(((this->position.x) * grid_size) - screen_position.x);
			int y1 = static_cast<int>(((this->position.y) * grid_size) - screen_position.y);
			int x2 = x1 + grid_size;
			int y2 = y1 + grid_size;
			if (this->move_count > 0)
			{
				int temp = this->animation_cnt % 40 / 10;
				if (temp == 3)
				{
					temp = 1;
				}
				this->graph_p.x = Player::GRAPH_SIZE_X * temp;
				this->animation_cnt++;
			}
			else
			{
				this->graph_p.x = Player::GRAPH_SIZE_X;
			}
			DrawRectRotaGraph(x, y, static_cast<int>(this->graph_p.x), (static_cast<int>(this->graph_p.y) - Player::GRAPH_SIZE_Y + Player::GRAPH_SIZE_Y * this->direction), 32, 48, 1.25, 0.0, this->gh, true);
			DrawBox(x1, y1, x2, y2, COLOR_AQUA, false);
		}
	}
	else
	{
		int x = static_cast<int>(((this->position.x + 0.5f) * grid_size) - screen_position.x);
		int y = static_cast<int>(((this->position.y + 0.5f) * grid_size) - screen_position.y);

		int x1 = static_cast<int>(((this->position.x) * grid_size) - screen_position.x);
		int y1 = static_cast<int>(((this->position.y) * grid_size) - screen_position.y);
		int x2 = x1 + grid_size;
		int y2 = y1 + grid_size;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawRectRotaGraph(x, y, static_cast<int>(this->graph_p.x), (static_cast<int>(this->graph_p.y) - Player::GRAPH_SIZE_Y + Player::GRAPH_SIZE_Y * this->direction), 32, 48, 1.25, 0.0, this->gh, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Player::DrawPlayerStatus()
{
	SetDrawBright(255, 255, 255);
	DrawFormatStringFToHandle(3, 3, COLOR_BLACK, this->font, "Lv :%3d", this->level);
	DrawFormatStringFToHandle(0, 0, COLOR_AQUA, this->font, "Lv :%3d", this->level);
	DrawFormatStringFToHandle(14 * 9 + 3, 3, COLOR_BLACK, this->font, "HP(%4d / %4d)", this->now_hp, this->max_hp);
	DrawFormatStringFToHandle(14 * 9, 0, COLOR_AQUA, this->font, "HP(%4d / %4d)", this->now_hp, this->max_hp);
}

Vector2 Player::GetPosition()const
{
	return this->position;
}

int Player::GetMoveCount() const
{
	return this->move_count;
}

void Player::LevelUp()
{
	MessageWindow& msg = MessageWindow::singleton();
	msg.SetMessage(COLOR_YELLOW, " %s のレベルが上がった", this->name);
	this->level += 1;
	msg.SetMessage(COLOR_YELLOW, " %s は %d レベルになった", this->name, this->level);
	int next_hp = this->max_hp + rand() % 20 + 10;
	this->max_hp = next_hp;
	this->now_hp = next_hp;
}

Vector2 Player::Attack()
{
	MessageWindow& msg = MessageWindow::singleton();

	msg.SetMessage(this->msg_color, " %s の攻撃", this->name);

	return{ static_cast<float>(this->x_passable), static_cast<float>(this->y_passable) };
}

void Player::Damage(int damage)
{
	MessageWindow& msg = MessageWindow::singleton();
	msg.SetMessage(COLOR_RED, " %s に %3d のダメージ", this->name, damage);
	this->now_hp -= damage;

	if (this->now_hp <= 0)
	{
		this->now_hp = 0;
		msg.SetMessage(COLOR_RED, " %s は死んでしまった...", this->name);
		this->alive = false;
	}
}

void Player::Recovery(int recovery)
{
	MessageWindow& msg = MessageWindow::singleton();
	msg.SetMessage(COLOR_AQUA, " %s は %3d 回復した", this->name, recovery);
	this->now_hp += recovery;

	if (this->now_hp > this->max_hp)
	{
		this->now_hp = this->max_hp;
	}
}
