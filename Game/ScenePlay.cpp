#include "ScenePlay.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
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

	this->act = Wait;

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

	this->InitDungeons();

	this->msg_font = CreateFontToHandle("HGS創英ﾌﾟﾚｾﾞﾝｽEB", 32, -1);
	this->change_cnt = 0;

	this->player->SetName("Player");

	this->act = Wait;

	this->Sequence_count = 0;
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

	// プレイヤーを設置
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

	// 下の階層に降りる階段を設置
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

	// 魔法陣を設置
	for (int i = 1; i < NumObject - NumMobs; i++)
	{
		init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(i).x) - 1,
			static_cast<float>(this->map->map_->GetInitMobPosition(i).y) - 1 };
		if (!(this->map->IsPassable(static_cast<int>(init_pos.x - 1), static_cast<int>(init_pos.y))) &&
			!(this->map->IsPassable(static_cast<int>(init_pos.x + 1), static_cast<int>(init_pos.y))) &&
			!(this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y - 1))) &&
			!(this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y + 1))))
		{
			while (1)
			{
				this->map->map_->MobInstallTo(i);
				init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(i).x),
					static_cast<float>(this->map->map_->GetInitMobPosition(i).y) };
				if ((this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y))))
				{
					break;
				}
			}
		}
		this->map->SetMagicCircle(init_pos.x, init_pos.y);
	}

	// エネミーを設置
	for (int i = 0; i < this->enemy.size(); i++)
	{
		this->enemy.erase(this->enemy.begin() + i);
	}
	for (int i = NumObject - NumMobs; i < NumObject - 2; i++)
	{
		Enemy enemy;
		init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(i).x) - 1,
			static_cast<float>(this->map->map_->GetInitMobPosition(i).y) - 1 };
		if (!(this->map->IsPassable(static_cast<int>(init_pos.x - 1), static_cast<int>(init_pos.y))) &&
			!(this->map->IsPassable(static_cast<int>(init_pos.x + 1), static_cast<int>(init_pos.y))) &&
			!(this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y - 1))) &&
			!(this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y + 1))))
		{
			while (1)
			{
				this->map->map_->MobInstallTo(i);
				init_pos = { static_cast<float>(this->map->map_->GetInitMobPosition(i).x),
					static_cast<float>(this->map->map_->GetInitMobPosition(i).y) };
				if ((this->map->IsPassable(static_cast<int>(init_pos.x), static_cast<int>(init_pos.y))))
				{
					break;
				}
			}
		}
		enemy.SetPositon(init_pos.x, init_pos.y);
		enemy.ChangeMap(this->map, init_pos.x, init_pos.y);
		this->enemy.push_back(enemy);
	}
}

bool ScenePlay::ChangeMap()
{
	float rad = this->deg * (3.1415926535f / 180.0f);
	this->change_cnt = (cosf(rad) + 1.0f) / 2.0f;	// 1 ～ 0　～　1

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

void ScenePlay::GotoNextFloor(const Vector2 & playerPosition)
{
	MessageWindow& msg = MessageWindow::singleton();
	if (this->map->GetCellid(static_cast<int>(playerPosition.x), static_cast<int>(playerPosition.y)) == 2)
	{
		this->change_flag = true;
		msg.SetMessage(COLOR_WHITE, "下の階層へ...");
	}
}

void ScenePlay::MagicCircleAction(const Vector2 & actorPosition)
{
	MessageWindow& msg = MessageWindow::singleton();
	if (this->map->GetCellid(static_cast<int>(actorPosition.x), static_cast<int>(actorPosition.y)) == 3)
	{
		int info_color = 0xffff8800;
		msg.SetMessage(COLOR_WHITE, " %s は 魔法陣を踏んだ", this->player->GetName());

		if (rand() % 2)
		{

			msg.SetMessage(info_color, "魔法陣の効果が発動！");
			switch (rand() % 2)
			{
			case 0:
				msg.SetMessage(info_color, "魔法陣はダメージトラップだった");
				this->player->Damage(rand() % 10 + 1);
				break;

			case 1:
				msg.SetMessage(info_color, "魔法陣は回復魔法陣だった");
				this->player->Recovery(rand() % 30 + 2);
				break;
			}
		}
		else
		{
			msg.SetMessage(info_color, "何も起こらなかった");
		}
		this->map->SetFloorDefault(static_cast<int>(actorPosition.x), static_cast<int>(actorPosition.y));
	}
}

void ScenePlay::Update(void)
{
	InputManager& input = InputManager::singleton();
	input.Update();
	MessageWindow& me = MessageWindow::singleton();

	if (!this->change_flag)
	{
		// シークエンス処理
		switch (this->act)
		{
		case Wait:
		{
			this->act = PlayerTurnBegin;
		}
		me.SetMessage(0xffff00ff, "Debug Log : Wait Sequence");
		break;

		case PlayerTurnBegin:
		{
			if (input.key->GetDown(KEY_INPUT_Z) && (!this->action_flag))
			{
				player->Attack();
				this->act = EnemyTurnBegin;
			}
			if (this->player->Update())
			{
				me.SetMessage(0xffffff00, "Debug Log : PlayerTurnBegin Sequence");
				this->act = PlayerTurnNow;
			}
		}
		break;
		case PlayerTurnNow:
		{
			this->player->Update();
			if (this->player->CheckTurnEnd())
			{
				this->act = PlayerTurnEnd;
				me.SetMessage(0xffffff00, "Debug Log : PlayerTurnNow Sequence");
				this->player->SetTurnEndFlag();
			}
		}
		break;
		case PlayerTurnEnd:
		{
			this->player->Update();
			this->act = EnemyTurnBegin;
			me.SetMessage(0xffffff00, "Debug Log : PlayerTurnEnd Sequence");
		}
		break;

		case EnemyTurnBegin:
			// すべてのエネミーにプレイヤーの座標を登録
			for (int i = 0; i < this->enemy.size(); i++)
			{
				this->enemy[i].SetTargetPosition(this->player->GetPosition());
			}
			this->act = EnemyTurnNow;
			me.SetMessage(0xffff00ff, "Debug Log : EnemyTurnBegin Sequence");
			break;

		case EnemyTurnNow:
		{
			int end_cnt = 0;
			for (int i = 0; i < this->enemy.size(); i++)
			{
				this->enemy[i].Update(this->enemy, i);
				if (this->enemy[i].CheckTurnEnd())
				{
					end_cnt++;
				}
				if (end_cnt == enemy.size())	// すべてのエネミーObject行動完了したらエンドシークエンスへ
				{
					this->act = EnemyTurnEnd;
					me.SetMessage(0xffff00ff, "Debug Log : EnemyTurnNow Sequence");
					for (int k = 0; k < this->enemy.size(); k++)
					{
						this->enemy[k].SetTurnEndFlag();
					}
				}
			}
		}
		break;

		case EnemyTurnEnd:
			/*for (int i = 0; i < this->enemy.size(); i++)
			{
				this->enemy[i].Update();
			}*/
			this->act = TurnEnd;
			me.SetMessage(0xffff00ff, "Debug Log : EnemyTurnEnd Sequence");
			break;

		case TurnEnd:	// 全シークエンス終了
			this->act = Wait;
			me.SetMessage(0xffff00ff, "Debug Log : TurnEnd Sequence");
			break;
		}
	}
	else
	{
		if (this->ChangeMap())	// マップチェンジ
		{
			this->change_flag = false;
		}
	}
	//if (input.key->GetInput())
	{
		if (this->player->GetMoveCount() == 0)
		{

		}
	}

	// 機能 / ターンには直接影響を及ぼさないもの
	{
		Vector2 p_pos = this->player->GetPosition();

		this->GotoNextFloor(p_pos);
		this->MagicCircleAction(p_pos);
		if (input.key->GetDown(KEY_INPUT_F4))
		{
			me.SetMessage(COLOR_YELLOW, "Debug Function : Map Reset");
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

	if (this->player->GetAlive() == false)
	{
		this->action_flag = false;
	}

	input.key->UpdateOld();
	this->action_flag_old = this->action_flag;
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
	for (int i = 0; i < this->enemy.size(); i++)
	{
		this->enemy[i].Render(screen_pos, Map::GRID_SIZE);
	}

	DrawFormatStringToHandle(SCREEN_RIGHT - 5 * 20 + 3, 3, COLOR_BLACK, this->msg_font, "%3d F", this->dng_floor);
	DrawFormatStringToHandle(SCREEN_RIGHT - 5 * 20, 0, COLOR_AQUA, this->msg_font, "%3d F", this->dng_floor);

	if (this->render_map)
	{
		int x = static_cast<int>(((this->player->GetPosition().x + 0.5f) * 4) - 0);
		int y = static_cast<int>(((this->player->GetPosition().y + 0.5f) * 4) - 0);

		Vector2 correction = { SCREEN_CENTER_X - (16 * 16) / 2,SCREEN_CENTER_Y - (16 * 16) / 2 };

		this->map->DrawMap(correction, x, y);

		for (int i = 0; i < this->enemy.size(); i++)
		{
			int ex = static_cast<int>(((this->enemy[i].GetPosition().x + 0.5f) * 4) - 0);
			int ey = static_cast<int>(((this->enemy[i].GetPosition().y + 0.5f) * 4) - 0);

			DrawCircle(ex + correction.x, ey + correction.y, 2, COLOR_RED, TRUE);
		}
	}
	SetDrawBright(255, 255, 255);
	if (this->render_msg)
	{
		MessageWindow& me = MessageWindow::singleton();
		me.Render();
	}
	this->player->DrawPlayerStatus();
}