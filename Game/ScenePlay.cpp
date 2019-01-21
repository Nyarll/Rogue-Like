#include "ScenePlay.h"
#include "SceneManager.h"
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
	this->render_msg = false;
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
	this->ui_font = CreateFontToHandle("Cooper Black", 20, -1);

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
		Enemy enemy(this->player->GetLevel(), this->dng_floor);

		int type = rand() % EnemyTypeNum;
		switch (type)
		{
		case Slime:
		{
			enemy.CreateSlime();
		}
		break;
		}
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

}

bool ScenePlay::ChangeMap()
{
	float rad = this->deg * (3.1415926535f / 180.0f);
	this->change_cnt = (cosf(rad) + 1.0f) / 2.0f;	// 1 ～ 0　～　1

	this->render_cnt = this->change_cnt * 255;

	if (this->deg == 180)
	{
		this->InitDungeons();
		//this->dng_floor += 1;
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

	static bool flag = false;

	if (this->map->GetCellid(static_cast<int>(playerPosition.x), static_cast<int>(playerPosition.y)) == 2)
	{
		this->change_flag = true;
		if (!flag)
		{
			msg.SetMessage(COLOR_WHITE, "下の階層へ...");
			this->dng_floor += 1;
			flag = true;
		}
	}
	else
	{
		flag = false;
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

void ScenePlay::GameFunction()
{
	InputManager& input = InputManager::singleton();
	if (input.key->GetDown(KEY_INPUT_F4))
	{
		MessageWindow& me = MessageWindow::singleton();
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
	if (input.key->GetDown(KEY_INPUT_T))
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
	if (input.key->GetDown(KEY_INPUT_X))
	{
		if (!this->menu_flag)
		{
			this->menu_flag = true;
		}
		else
		{
			this->menu_flag = false;
		}
	}
}
void ScenePlay::GameAction()
{
	Vector2 p_pos = this->player->GetPosition();
	MessageWindow& msg = MessageWindow::singleton();
	this->GotoNextFloor(p_pos);
	this->MagicCircleAction(p_pos);

	for (int i = 0; i < this->item.size(); i++)
	{
		{
			if (static_cast<int>(p_pos.x) == this->item[i].GetPosition().x &&
				static_cast<int>(p_pos.y) == this->item[i].GetPosition().y)
			{
				if (this->player->GetItemNum(i) < 16)
				{
					this->player->AddItem(this->item[i].GetItemType());
					msg.SetMessage(COLOR_WHITE, "%s は %s を拾った", this->player->GetName(), this->item[i].GetItemName());
					this->item.erase(this->item.begin() + i);
				}
				break;
			}
		}
	}
}

void ScenePlay::WaitTurnSequence()
{
	this->playerAttackPoint = { -1,-1 };
	this->enemyAttackPoint = { -1,-1 };
	this->act = PlayerTurn;
}
void ScenePlay::PlayerTurnSequence()
{
	InputManager& input = InputManager::singleton();
	MessageWindow& msg = MessageWindow::singleton();
	for (int i = 0; i < ItemTypeNum; i++)
	{
		if (input.key->GetDown(this->player->GetNumberKey(i + 1)))
		{
			switch (i)
			{
			case RecoveryPortion:
				if (this->player->GetItemNum(RecoveryPortion) > 0)
				{
					msg.SetMessage(COLOR_AQUA, "%s は ポーションを使用した", this->player->GetName());
					this->player->UseItem(RecoveryPortion);
					int recovery = rand() % 6 + 1 + this->player->GetLevel() * 2;
					this->player->Recovery(recovery);
					msg.SetMessage(COLOR_LIME, "%s は %d HPが回復した", this->player->GetName(), recovery);
					this->act = EnemyTurn;
				}
				break;
			}
		}
	}
	if (input.key->GetDown(KEY_INPUT_Z) && (!this->action_flag))
	{
		this->playerAttackPoint = player->Attack();
		this->act = EnemyTurn;
	}
	if (this->player->Update(this->enemy))
	{
		//me.SetMessage(0xffffff00, "Debug Log : PlayerTurn Sequence");
		this->act = EnemyTurn;
	}
}
void ScenePlay::EnemyTurnSequence()
{
	MessageWindow& msg = MessageWindow::singleton();
	// エネミーがプレイヤーから攻撃されたかどうか
	if (static_cast<int>(this->playerAttackPoint.x) != (-1) &&
		static_cast<int>(this->playerAttackPoint.y) != (-1))
	{
		for (int i = 0; i < this->enemy.size(); i++)
		{
			if (this->enemy[i].GetPosition() == this->playerAttackPoint)
			{
				this->enemy[i].Damage(this->player->AttackDamage(this->enemy[i].GetDEF()));
				if (!enemy[i].GetAlive())
				{
					msg.SetMessage(COLOR_WHITE, "%s は 倒された", enemy[i].GetName());
					msg.SetMessage(COLOR_AQUA, "%s は %d の経験値を獲得", this->player->GetName(), this->enemy[i].GetExp());
					this->player->AddExp(this->enemy[i].GetExp());

					if (!(rand() % 3))
					{
						IntVector2 drop_point = { static_cast<int>(enemy[i].GetPosition().x), static_cast<int>(enemy[i].GetPosition().y) };
						for (int i = 0; i < this->item.size(); i++)
						{
							if (this->item[i].GetPosition().x == drop_point.x && this->item[i].GetPosition().y == drop_point.y)
							{
								drop_point.x += 1;
								break;
							}
						}

						Item drop_item(drop_point.x, drop_point.y);
						switch (rand() % ItemTypeNum)
						{
						case RecoveryPortion:
							drop_item.CreateRecoveryPortion();
							break;
						}
						msg.SetMessage(COLOR_WHITE, "%s は %s を落とした", enemy[i].GetName(), drop_item.GetItemName());
						this->item.push_back(drop_item);
					}

					this->enemy.erase(this->enemy.begin() + i);
				}
			}
		}
	}
	// すべてのエネミーにプレイヤーの座標を登録
	for (int i = 0; i < this->enemy.size(); i++)
	{
		this->enemy[i].SetTargetPosition(this->player->GetPosition());
		this->enemy[i].SetAttackFlag(false);
	}

	for (int i = 0; i < this->enemy.size(); i++)
	{
		Vector2 epos = { this->enemy[i].GetPosition().x,this->enemy[i].GetPosition().y };
		Vector2 atk = epos;
		int ex = static_cast<int>(epos.x);
		int ey = static_cast<int>(epos.y);
		int px = static_cast<int>(this->player->GetPosition().x);
		int py = static_cast<int>(this->player->GetPosition().y);

		int damage = this->enemy[i].GetATK() - this->player->GetDEF();

		if (ey == py)
		{
			if ((ex - 1 == px))	// enemy の左
			{
				atk = this->enemy[i].Attack();
				this->enemy[i].SetAttackFlag(true);
				this->player->Damage(damage);
			}
			if ((ex + 1 == px))	// 右
			{
				atk = this->enemy[i].Attack();
				this->enemy[i].SetAttackFlag(true);
				this->player->Damage(damage);
			}
		}
		if (ex == px)
		{
			if ((ey - 1 == py))	// enemy の上
			{
				atk = this->enemy[i].Attack();
				this->enemy[i].SetAttackFlag(true);
				this->player->Damage(damage);
			}
			if ((ey + 1 == py))	// 下
			{
				atk = this->enemy[i].Attack();
				this->enemy[i].SetAttackFlag(true);
				this->player->Damage(damage);
			}
		}
	}

	for (int i = 0; i < this->enemy.size(); i++)
	{
		if (!this->enemy[i].GetAttackFlag())
		{
			this->enemy[i].Update(this->enemy, i);
		}
	}
	this->act = TurnEnd;
	return;
}
void ScenePlay::TurnEndSequence()
{
	this->act = Wait;
}

void ScenePlay::GameTurnSequence()
{
	InputManager& input = InputManager::singleton();
	MessageWindow& msg = MessageWindow::singleton();

	if (!this->change_flag)
	{
		// シークエンス処理
		switch (this->act)
		{
		case Wait:
			this->WaitTurnSequence();
			break;

		case PlayerTurn:
			this->PlayerTurnSequence();
			break;

		case EnemyTurn:
			this->EnemyTurnSequence();
			break;

		case TurnEnd:	// 全シークエンス終了
			this->TurnEndSequence();
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
}

void ScenePlay::Update(void)
{
	InputManager& input = InputManager::singleton();
	input.Update();
	MessageWindow& me = MessageWindow::singleton();

	// 機能 / ターンには直接影響を及ぼさないもの
	this->GameAction();
	this->GameFunction();

	if (!this->menu_flag)
	{
		this->GameTurnSequence();
	}
	else
	{

	}

	if (this->player->GetAlive() == false)
	{
		// this->action_flag = false;
		SceneManager& manager = SceneManager::singleton();
		manager.RequestScene(SCENE_RESULT);
		me.DeleteAll();
	}

	input.key->UpdateOld();
	this->action_flag_old = this->action_flag;
}

Vector2 ScenePlay::GetScreenPosition()
{
	Vector2 player_pos = this->player->GetRenderPosition();
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
	}
	return screen_pos;
}
void ScenePlay::RenderNowFloor()
{
	DrawFormatStringToHandle(SCREEN_RIGHT - 5 * 20 + 3, 3, COLOR_BLACK, this->msg_font, "%3d F", this->dng_floor);
	DrawFormatStringToHandle(SCREEN_RIGHT - 5 * 20, 0, COLOR_AQUA, this->msg_font, "%3d F", this->dng_floor);
}
void ScenePlay::RenderMap()
{
	if (this->render_map)
	{
		int x = static_cast<int>(((this->player->GetPosition().x + 0.5f) * 4) - 0);
		int y = static_cast<int>(((this->player->GetPosition().y + 0.5f) * 4) - 0);

		Vector2 correction = { SCREEN_CENTER_X - (16 * 16) / 2 + SCREEN_RIGHT / 4,
			SCREEN_CENTER_Y - (16 * 16) / 2 - SCREEN_BOTTOM / 4 };

		this->map->DrawMap(correction, x, y);

		for (int i = 0; i < this->enemy.size(); i++)
		{
			int ex = static_cast<int>(((this->enemy[i].GetPosition().x + 0.5f) * 4) - 0);
			int ey = static_cast<int>(((this->enemy[i].GetPosition().y + 0.5f) * 4) - 0);

			DrawCircle(ex + correction.x, ey + correction.y, 2, COLOR_RED, TRUE);
		}
	}
}
void ScenePlay::RenderOtherUI()
{
	DrawFormatStringFToHandle(SCREEN_RIGHT - 7 * 34, SCREEN_BOTTOM - 20,
		COLOR_BLACK, this->ui_font, "Message Log : T key");
	DrawFormatStringFToHandle(SCREEN_RIGHT - 7 * 34 - 3, SCREEN_BOTTOM - 20 - 3,
		COLOR_YELLOW, this->ui_font, "Message Log : T key");
	DrawFormatStringFToHandle(SCREEN_RIGHT - 7 * 20, SCREEN_BOTTOM - 40,
		COLOR_BLACK, this->ui_font, "Map : M key");
	DrawFormatStringFToHandle(SCREEN_RIGHT - 7 * 20 - 3, SCREEN_BOTTOM - 40 - 3,
		COLOR_YELLOW, this->ui_font, "Map : M key");
}

void ScenePlay::RenderPlayerStatus()
{
	DrawFormatStringToHandle(40, 40, COLOR_WHITE, this->msg_font, "Level : %d", this->player->GetLevel());
	DrawFormatStringToHandle(40, 75, COLOR_WHITE, this->msg_font, "Name : %s", this->player->GetName());
	
	DrawFormatStringToHandle(40, 140, COLOR_WHITE, this->msg_font, "HP : %d / %d", this->player->GetNowHP(), this->player->GetMaxHP());
	
	DrawFormatStringToHandle(40, 175, COLOR_WHITE, this->msg_font, "ATK : %d", this->player->GetATK());
	DrawFormatStringToHandle(40, 220, COLOR_WHITE, this->msg_font, "DEF : %d", this->player->GetDEF());

}

void ScenePlay::Render(void)
{
	Vector2 screen_pos = this->GetScreenPosition();

	this->map->Render(screen_pos, Map::GRID_SIZE, false);

	for (int i = 0; i < this->item.size(); i++)
	{
		this->item[i].Render(screen_pos, Map::GRID_SIZE);
	}

	this->player->Render(screen_pos, Map::GRID_SIZE);
	for (int i = 0; i < this->enemy.size(); i++)
	{
		this->enemy[i].Render(screen_pos, Map::GRID_SIZE);
	}
	this->RenderNowFloor();
	this->RenderMap();
	SetDrawBright(255, 255, 255);
	this->player->DrawPlayerStatus();

	if (this->render_msg)
	{
		MessageWindow& me = MessageWindow::singleton();
		me.Render();
	}
	else
	{
		this->player->DrawPlayerExp();
	}
	this->RenderOtherUI();

	this->player->DrawInventoryList();
	if (this->menu_flag)
	{
		int x1 = 0;
		int y1 = 0;
		int x2 = 800;
		int y2 = 800;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(x1, y1, x2, y2, COLOR_BLACK, true);
		DrawBox(x1, y1, x2, y2, COLOR_LIME, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		this->RenderPlayerStatus();
	}
}