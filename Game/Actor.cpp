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

Vector2 Actor::Attack()
{
	MessageWindow& msg = MessageWindow::singleton();

	msg.SetMessage(this->msg_color, " %s ‚ÌUŒ‚", this->name);

	return{ static_cast<float>(this->x_passable), static_cast<float>(this->y_passable) };
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
