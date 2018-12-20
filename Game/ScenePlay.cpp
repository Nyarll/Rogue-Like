#include "ScenePlay.h"
#include "Map.h"
#include "Player.h"
#include "MessageWindow.h"
#include "Input.h"

Scene* ScenePlay::Create()
{
	return{ new ScenePlay() };
}


ScenePlay::ScenePlay()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	this->render_map = false;
	this->render_msg = true;
	this->dng_floor = 1;


	this->map = new Map;
	this->map->LoadMapChip("Resources/Textures/debug_mapchip.png");
	this->map->CreateMapData();
	for (int i = 0; i < RL_MOB_C; i++)
	{
		mob[i].id = 0;
		mob[i].x = 0;
		mob[i].y = 0;
		mob[i].s = 1;
	}

	for (int i = 0; i < RL_MOB_C; i++)
	{
		RL_MakeMob(&this->map->dng, this->map->map_data, this->mob, i);
	}

	this->player = new Player;
	Vector2 init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(0).x),
		static_cast<float>(this->map->map_->GetInitMobPosition(0).y) };
	this->player->ChangeMap(map, init_pos.x, init_pos.y);

	init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(NumObject - 1).x),
		static_cast<float>(this->map->map_->GetInitMobPosition(NumObject - 1).y) };
	this->map->SetFloorChangePlace(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y));

	this->msg_font = CreateFontToHandle("Algerian", 32, -1);
	this->change_cnt = 0;

	this->player->SetName("Kame");
}

ScenePlay::~ScenePlay()
{
	delete this->map;
	delete this->player;
}

void ScenePlay::InitDungeons()
{
	this->map->CreateMapData();
	for (int i = 0; i < RL_MOB_C; i++)
	{
		mob[i].id = 0;
		mob[i].x = 0;
		mob[i].y = 0;
		mob[i].s = 1;
	}
	for (int i = 0; i < RL_MOB_C; i++)
	{
		RL_MakeMob(&this->map->dng, this->map->map_data, this->mob, i);
	}

	//this->player->ChangeMap(map, this->mob[0].x, this->mob[0].y);
	//this->map->SetFloorChangePlace(this->mob[RL_MOB_C - 1].x, this->mob[RL_MOB_C - 1].y);

	// ÉvÉåÉCÉÑÅ[Çê›íu
	Vector2 init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(0).x),
		static_cast<float>(this->map->map_->GetInitMobPosition(0).y) };
	if (!(this->map->IsPassable(static_cast<int>(init_pos.x - 1), static_cast<int>(init_pos.y))) &&
		!(this->map->IsPassable(static_cast<int>(init_pos.x + 1), static_cast<int>(init_pos.y))) &&
		!(this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y - 1))) &&
		!(this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y + 1))))
	{
		while (1)
		{
			this->map->map_->MobInstallTo(0);
			init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(0).x),
				static_cast<float>(this->map->map_->GetInitMobPosition(0).y) };
			if ((this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y))))
			{
				break;
			}
		}
	}

	this->player->ChangeMap(map, init_pos.x, init_pos.y);

	// â∫ÇÃäKëwÇ…ç~ÇËÇÈäKíiÇê›íu
	init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(NumObject - 1).x) - 1,
		static_cast<float>(this->map->map_->GetInitMobPosition(NumObject - 1).y) - 1 };
	if (!(this->map->IsPassable(static_cast<int>(init_pos.x - 1), static_cast<int>(init_pos.y))) &&
		!(this->map->IsPassable(static_cast<int>(init_pos.x + 1), static_cast<int>(init_pos.y))) &&
		!(this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y - 1))) &&
		!(this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y + 1))))
	{
		while (1)
		{
			this->map->map_->MobInstallTo(NumObject - 1);
			init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(NumObject - 1).x),
				static_cast<float>(this->map->map_->GetInitMobPosition(NumObject - 1).y) };
			if ((this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y))))
			{
				break;
			}
		}
	}
	this->map->SetFloorChangePlace(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y));

	// ñÇñ@êwÇê›íu
	init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(NumObject - 2).x) - 1,
		static_cast<float>(this->map->map_->GetInitMobPosition(NumObject - 2).y) - 1 };
	if (!(this->map->IsPassable(static_cast<int>(init_pos.x - 1), static_cast<int>(init_pos.y))) &&
		!(this->map->IsPassable(static_cast<int>(init_pos.x + 1), static_cast<int>(init_pos.y))) &&
		!(this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y - 1))) &&
		!(this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y + 1))))
	{
		while (1)
		{
			this->map->map_->MobInstallTo(NumObject - 2);
			init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(NumObject - 2).x),
				static_cast<float>(this->map->map_->GetInitMobPosition(NumObject - 2).y) };
			if ((this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y))))
			{
				break;
			}
		}
	}
	this->map->SetMagicCircle(init_pos.x, init_pos.y);
}

bool ScenePlay::ChangeMap()
{
	float rad = this->deg * (3.1415926535f / 180.0f);
	this->change_cnt = (cosf(rad) + 1.0f) / 2.0f;	// 1 Å` 0Å@Å`Å@1

	this->render_cnt = this->change_cnt * 255;

	if (this->deg == 180)
	{
		this->InitDungeons();
		this->dng_floor += 1;
	}

	if (this->deg == 360)
	{
		this->deg = 0;
		return true;
	}

	SetDrawBright(this->render_cnt, this->render_cnt, this->render_cnt);
	this->deg += 4;
	return false;
}

void ScenePlay::Update(void)
{
	InputManager& input = InputManager::singleton();
	input.Update();

	//if (input.key->GetInput())
	{
		if (this->player->GetMoveCount() == 0)
		{
			Vector2 p_pos = this->player->GetPosition();
			if (this->map->GetCellid(static_cast<int>(p_pos.x), static_cast<int>(p_pos.y)) == 2)
			{
				this->change_flag = true;
			}
			if (this->map->GetCellid(static_cast<int>(p_pos.x), static_cast<int>(p_pos.y)) == 3)
			{
				MessageWindow& me = MessageWindow::singleton();
				me.SetMessage(COLOR_RED, "%s ÇÕ ñÇñ@êwÇì•ÇÒÇ≈ÇµÇ‹Ç¡ÇΩ", this->player->GetName());
			}
			if (input.key->GetDown(KEY_INPUT_Z))
			{
				player->Attack();
			}
		}
	}
	{
		if (input.key->GetDown(KEY_INPUT_F4))
		{
			this->InitDungeons();
		}
		if (input.key->GetDown(KEY_INPUT_M))
		{
			if (!this->render_map)
			{
				this->render_map = true;
			}
			else
			{
				this->render_map = false;
			}
		}
		if (input.key->GetDown(KEY_INPUT_V))
		{
			if (!this->render_msg)
			{
				this->render_msg = true;
			}
			else
			{
				this->render_msg = false;
			}
		}
	}

	if (!this->change_flag)
	{
		this->player->Update();
	}
	else
	{
		if (this->ChangeMap())
		{
			this->change_flag = false;
		}
	}
	input.key->UpdateOld();
}

void ScenePlay::Render(void)
{
	Vector2 player_pos = this->player->GetPosition();

	Vector2 screen_pos;
	screen_pos.x = (player_pos.x * Map::GRID_SIZE) - SCREEN_WIDTH / 2;
	screen_pos.y = (player_pos.y * Map::GRID_SIZE) - SCREEN_HEIGHT / 2;

	if (screen_pos.x < 0)
	{
		screen_pos.x = 0;
	}
	if (screen_pos.y < 0)
	{
		screen_pos.y = 0;
	}
	/**/
	if (screen_pos.x > Map::BOUNDS.right - SCREEN_RIGHT)
	{
		screen_pos.x = Map::BOUNDS.right - SCREEN_RIGHT;
	}
	if (screen_pos.y > Map::BOUNDS.bottom - SCREEN_BOTTOM)
	{
		screen_pos.y = Map::BOUNDS.bottom - SCREEN_BOTTOM;
	}/**/

	this->map->Render(screen_pos, Map::GRID_SIZE, false);
	this->player->Render(screen_pos, Map::GRID_SIZE);
	DrawFormatStringToHandle(SCREEN_RIGHT - 5 * 20, 20, COLOR_RED, this->msg_font, "%3d F", this->dng_floor);

	if (this->render_map)
	{
		int x = static_cast<int>(((this->player->GetPosition().x + 0.5f) * 4) - 0);
		int y = static_cast<int>(((this->player->GetPosition().y + 0.5f) * 4) - 0);

		Vector2 correction = { SCREEN_CENTER_X - (16 * 16) / 2,SCREEN_CENTER_Y - (16 * 16) / 2 };

		this->map->DrawMap(correction, x, y);
	}
	SetDrawBright(255, 255, 255);
	if (this->render_msg)
	{
		MessageWindow& me = MessageWindow::singleton();
		me.Render();
	}
}