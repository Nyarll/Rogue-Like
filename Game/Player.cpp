#include "Player.h"
#include "Map.h"
#include "Input.h"
#include "MessageWindow.h"
#include "SoundManager.h"

const int Player::MOVING_INTERVAL = 16;
const int Player::GRAPH_SIZE_X = 32;
const int Player::GRAPH_SIZE_Y = 48;

const int Player::MAX_ITEM_INVENTORY = 32;

Player::Player()
{
	this->map = nullptr;
	this->position = { 0,0 };
	this->velocity = { 0,0 };
	this->move_count = 0;
	this->stop_count = 0;
	this->step_count = 0;

	this->font = CreateFontToHandle("HGS創英ﾌﾟﾚｾﾞﾝｽEB", 32, -1);
	this->menu_font = CreateFontToHandle("HGS創英ﾌﾟﾚｾﾞﾝｽEB", 20, -1);

	this->direction = 1;

	this->level = 1;
	this->Exp = 0;
	this->next_exp = 100 * this->level;

	this->gh = LoadGraph("Resources/Textures/Characters_32_48.png");
	this->animation_cnt = 0;
	this->graph_p.x = 0;
	this->graph_p.y = 0;

	this->msg_color = 0xff00ff0f;

	this->max_hp = rand() % 20 + 10;
	this->now_hp = this->max_hp;

	this->ATK = Dice(3, 6);
	this->DEF = Dice(3, 6);

	for (int i = 0; i < ItemTypeNum; i++)
	{
		this->Inventory[i] = 0;
	}
}

Player::~Player()
{

}

void Player::SetFont(int font)
{
	this->font = font;
}


int Player::GetLevel()
{
	return this->level;
}

bool Player::Update(std::vector<Enemy> enemy)
{
	static bool act_flag = false;
	if (this->alive)
	{
		if (this->move_count == 1)
		{
			this->end_flag = true;
		}

		if (this->Exp >= this->next_exp)
		{
			this->next_exp += 75 * this->level;
			this->LevelUp();
		}

		// 移動中ではないなら
		if (this->move_count == 0)
		{
			act_flag = false;
			this->end_flag = false;
			this->velocity = { 0,0 };
			InputManager& input = InputManager::singleton();
			InputKeyBoard* key = input.key;

			if ((key->GetNow(KEY_INPUT_UP)) || key->GetNow(KEY_INPUT_W))
			{
				this->velocity.y += -1.0f;
				this->direction = 4;
				this->step_count += 1;
			}
			if ((key->GetNow(KEY_INPUT_DOWN)) || key->GetNow(KEY_INPUT_S))
			{
				this->velocity.y += 1.0f;
				this->direction = 1;
				this->step_count += 1;
			}
			if ((key->GetNow(KEY_INPUT_LEFT)) || key->GetNow(KEY_INPUT_A))
			{
				this->velocity.x += -1.0f;
				this->direction = 2;
				this->step_count += 1;
			}
			if (key->GetNow(KEY_INPUT_RIGHT) || key->GetNow(KEY_INPUT_D))
			{
				this->velocity.x += 1.0f;
				this->direction = 3;
				this->step_count += 1;
			}

			this->x_now = static_cast<int>(this->position.x);
			this->y_now = static_cast<int>(this->position.y);
			this->x_passable = static_cast<int>(this->position.x + this->velocity.x);
			this->y_passable = static_cast<int>(this->position.y + this->velocity.y);

			if (FloatEquals(this->velocity.x, 0.0f) == false || FloatEquals(this->velocity.y, 0.0f) == false)
			{
				this->move_count = MOVING_INTERVAL;
				this->render_position = this->position;
				// 行きたい方向へ行けるかどうかチェック
				for (int i = 0; i < enemy.size(); i++)
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

				if (this->map->IsPassable(x_passable, y_passable))
				{
					if ((this->map->IsPassable(this->x_passable, this->y_now)))
					{
						this->position.x += this->velocity.x;
					}
					if ((this->map->IsPassable(this->x_now, this->y_passable)))
					{
						this->position.y += this->velocity.y;
					}
				}
				else
				{
					if ((this->map->IsPassable(this->x_passable, this->y_now)))
					{
						this->position.x += this->velocity.x;
					}
					if ((this->map->IsPassable(this->x_now, this->y_passable)))
					{
						this->position.y += this->velocity.y;
					}
				}
				act_flag = true;
			}

			if (this->step_count > 5)
			{
				this->Healing();
				this->step_count = 0;
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
	}
	return act_flag;
}

void Player::Render(const Vector2& screen_position, const int grid_size)
{
	// デバッグ用
	bool debug_mode = false;

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

			//this->render_position = this->position;
		}
	}

	if (this->alive)
	{
		if (debug_mode)
		{
			int x = static_cast<int>(((this->position.x + 0.5f) * grid_size) - screen_position.x);
			int y = static_cast<int>(((this->position.y + 0.5f) * grid_size) - screen_position.y);

			int x1 = static_cast<int>(((this->render_position.x) * grid_size) - screen_position.x);
			int y1 = static_cast<int>(((this->render_position.y) * grid_size) - screen_position.y);
			int x2 = x1 + grid_size;
			int y2 = y1 + grid_size;
			DrawBox(x1, y1, x2, y2, COLOR_AQUA, true);
			DrawCircle(x, y, 2, COLOR_RED, TRUE);

			DrawFormatString(10, 10, COLOR_WHITE, "プレーヤーの座標 = (%.2f, %.2f)", this->position.x, this->position.y);
		}
		else
		{
			int x = static_cast<int>(((this->render_position.x + 0.5f) * grid_size) - screen_position.x);
			int y = static_cast<int>(((this->render_position.y + 0.5f) * grid_size) - screen_position.y);

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
		int x = static_cast<int>(((this->render_position.x + 0.5f) * grid_size) - screen_position.x);
		int y = static_cast<int>(((this->render_position.y + 0.5f) * grid_size) - screen_position.y);

		int x1 = static_cast<int>(((this->render_position.x) * grid_size) - screen_position.x);
		int y1 = static_cast<int>(((this->render_position.y) * grid_size) - screen_position.y);
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

	float hx = 14.0f * 9.0f + (14.0f * 18.0f) * (float)((float)this->now_hp / (float)this->max_hp);
	DrawBox(14 * 9 + 3, 3, 14 * 9 + (14 * 18) + 3, 34 + 3, COLOR_BLACK, true);
	DrawBox(14 * 9, 0, hx, 34, COLOR_LIME, true);
	DrawBox(14 * 9, 0, 14 * 9 + (14 * 18) + 3, 34 + 3, COLOR_BLACK, false);
	DrawFormatStringFToHandle(14 * 9 + 3, 3, COLOR_BLACK, this->font, "HP(%4d / %4d)", this->now_hp, this->max_hp);
	DrawFormatStringFToHandle(14 * 9, 0, COLOR_RED, this->font, "HP(%4d / %4d)", this->now_hp, this->max_hp);
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

	// ステータスアップ
	int next_hp = this->max_hp + this->Dice(3, 3) + 1;
	msg.SetMessage(COLOR_WHITE, " HP : %d → %d", this->max_hp, next_hp);
	this->max_hp = next_hp;
	this->now_hp = next_hp;

	int next_ATK = this->ATK + this->Dice(1, 6) + 2;
	msg.SetMessage(COLOR_WHITE, "ATK : %d → %d", this->ATK, next_ATK);
	this->ATK = next_ATK;

	int next_DEF = this->DEF + this->Dice(1, 6) + 2;
	msg.SetMessage(COLOR_WHITE, "DEF : %d → %d", this->DEF, next_DEF);
	this->DEF = next_DEF;
}

Vector2 Player::Attack()
{
	MessageWindow& msg = MessageWindow::singleton();
	SoundManager& sm = SoundManager::singleton();

	msg.SetMessage(this->msg_color, " %s の攻撃", this->name);
	sm.SoundPlay(AttackSE, DX_PLAYTYPE_BACK);

	int atk_x = static_cast<int>(this->position.x), atk_y = static_cast<int>(this->position.y);

	switch (this->direction)
	{
	case 2:
		atk_x -= 1;
		break;

	case 3:
		atk_x += 1;
		break;

	case 4:
		atk_y -= 1;
		break;

	case 1:
		atk_y += 1;
		break;
	}
	return{ static_cast<float>(atk_x), static_cast<float>(atk_y) };
}

void Player::Damage(int damage)
{
	MessageWindow& msg = MessageWindow::singleton();
	int d = damage;

	if (d < 0)
	{
		d = 0;
	}

	msg.SetMessage(COLOR_RED, " %s に %3d のダメージ", this->name, d);

	this->now_hp -= d;

	if (this->now_hp <= 0)
	{
		this->now_hp = 0;
		msg.SetMessage(COLOR_RED, " %s は死んでしまった...", this->name);
		this->alive = false;
	}
}

void Player::Healing()
{
	this->now_hp += 1;
	if (this->now_hp > this->max_hp)
	{
		this->now_hp = this->max_hp;
	}
}

int Player::GetExp()
{
	return this->Exp;
}

void Player::AddExp(int exp)
{
	this->Exp += exp;
}

int Player::GetNextExp()
{
	return this->next_exp;
}

void Player::DrawPlayerExp()
{
	SetDrawBright(255, 255, 255);
	DrawFormatStringFToHandle(3, SCREEN_BOTTOM - 32 + 3, COLOR_BLACK, this->font, "EXP : %d", this->Exp);
	DrawFormatStringFToHandle(0, SCREEN_BOTTOM - 32, COLOR_AQUA, this->font, "EXP : %d", this->Exp);
}

int Player::GetItemNum(int itemType)
{
	return this->Inventory[itemType];
}
void Player::AddItem(int itemType)
{
	this->Inventory[itemType] += 1;
}
void Player::UseItem(int itemType)
{
	this->Inventory[itemType] -= 1;
}
void Player::DrawInventoryList()
{
	double scale = 2.0;
	for (int i = 0; i < ItemTypeNum; i++)
	{
		int x1 = (SCREEN_RIGHT - (ItemTextureSize * scale * ItemTypeNum) + (ItemTextureSize * scale * i));
		int y1 = (SCREEN_BOTTOM - (ItemTextureSize * scale)) - SCREEN_CENTER_Y / 4;
		int x2 = x1 + ItemTextureSize * scale;
		int y2 = y1 + ItemTextureSize * scale;

		int x = x1 + (ItemTextureSize * scale) / 2;
		int y = y1 + (ItemTextureSize * scale) / 2;

		DrawRotaGraph(x, y, scale, 0.0, ItemTextures::singleton().GetTexture(i), true);
		DrawBox(x1 + 1, y1 + 1, x2 + 1, y2 + 1, COLOR_BLACK, false);
		DrawBox(x1, y1, x2, y2, COLOR_LIME, false);

		DrawFormatStringToHandle(x2 - 20 + 2, y2 - 20 + 2, COLOR_BLACK, this->menu_font, "%d", this->Inventory[i]);
		DrawFormatStringToHandle(x2 - 20, y2 - 20, COLOR_WHITE, this->menu_font, "%d", this->Inventory[i]);

		DrawFormatStringToHandle(x1 + 2, y1 + 2, COLOR_BLACK, this->menu_font, "%d", i + 1);
		DrawFormatStringToHandle(x1, y1, COLOR_YELLOW, this->menu_font, "%d", i + 1);
	}
}

int Player::GetNumberKey(int num)
{
	switch (num)
	{
	case 0:
		return KEY_INPUT_0;
		break;

	case 1:
		return KEY_INPUT_1;
		break;
	case 2:
		return KEY_INPUT_2;
		break;
	case 3:
		return KEY_INPUT_3;
		break;
	case 4:
		return KEY_INPUT_4;
		break;
	case 5:
		return KEY_INPUT_5;
		break;
	case 6:
		return KEY_INPUT_6;
		break;
	case 7:
		return KEY_INPUT_7;
		break;
	case 8:
		return KEY_INPUT_8;
		break;
	case 9:
		return KEY_INPUT_9;
		break;
	}
	return 0;
}
