#include "Actor.h"
#include "MessageWindow.h"

int Actor::Dice(int num, int side)
{
	int ans = 0;
	for (int i = 0; i < num; i++)
	{
		ans += rand() % side + 1;
	}
	return ans;
}

void Actor::ChangeMap(Map* map, int start_x, int start_y)
{
	this->map = map;
	this->position = { (float)(start_x),(float)(start_y) };
	this->render_position = this->position;
}

bool Actor::GetAlive()
{
	return this->alive;
}

char* Actor::GetName()
{
	return this->name;
}

void Actor::SetName(char* name)
{
	this->name = name;
}

Vector2 Actor::GetPosition() const
{
	return this->position;
}

Vector2 Actor::GetRenderPosition() const
{
	return this->render_position;
}

void Actor::SetPositon(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}

bool Actor::CheckTurnEnd()
{
	return this->end_flag;
}

void Actor::SetTurnEndFlag()
{
	this->end_flag = false;
}

int Actor::GetMaxHP()
{
	return this->max_hp;
}

int Actor::GetNowHP()
{
	return this->now_hp;
}

int Actor::GetATK()
{
	return this->ATK;
}

int Actor::GetDEF()
{
	return this->DEF;
}

int Actor::AttackDamage(int OpponentDEF)
{
	int damage = (this->ATK + this->Dice(2, 3)) - (OpponentDEF - this->Dice(1, 3));
	return damage;
}

void Actor::Recovery(int recovery)
{
	MessageWindow& msg = MessageWindow::singleton();
	msg.SetMessage(COLOR_AQUA, " %s ‚Í %3d ‰ñ•œ‚µ‚½", this->name, recovery);
	this->now_hp += recovery;

	if (this->now_hp > this->max_hp)
	{
		this->now_hp = this->max_hp;
	}
}
