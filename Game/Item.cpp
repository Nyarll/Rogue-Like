#include "Item.h"

Item::Item(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;

	this->type = ItemTypeNull;	// ‚Æ‚è‚ ‚¦‚¸Null Item ‚É‚µ‚Ä‚¨‚­
	this->name = "Null Item";
}


Item::~Item()
{
}

int Item::GetItemType()
{
	return this->type;
}

char * Item::GetItemName()
{
	return this->name;
}

IntVector2 Item::GetPosition()
{
	return this->pos;
}

void Item::Render(const Vector2& screen_pos, const int grid_size)
{
	int x = static_cast<int>(((this->pos.x + 0.5f) * grid_size) - screen_pos.x);
	int y = static_cast<int>(((this->pos.y + 0.5f) * grid_size) - screen_pos.y);

	int x1 = static_cast<int>(((this->pos.x) * grid_size) - screen_pos.x);
	int y1 = static_cast<int>(((this->pos.y) * grid_size) - screen_pos.y);
	int x2 = x1 + grid_size;
	int y2 = y1 + grid_size;

	if (this->type == ItemTypeNull || this->gh == ItemTextures::TextureNotFound)
	{
		DrawCircle(x, y, 10, COLOR_RED);
		DrawBox(x1, y1, x2, y2, COLOR_LIME, false);
	}
	else
	{
		DrawRectRotaGraph(x, y, 0, 0, 32, 32, 1.5, 0.0, this->gh, true);
		DrawBox(x1, y1, x2, y2, COLOR_AQUA, false);
	}
}

void Item::DrawItem(int x, int y)
{
	int x1 = x - (32 / 2) * 0.75;
	int y1 = y - (32 / 2) * 0.75;
	int x2 = x1 + (32) * 0.75;
	int y2 = y1 + (32) * 0.75;

	DrawRectRotaGraph(x, y, 0, 0, 32, 32, 0.75, 0.0, this->gh, true);
	DrawBox(x1, y1, x2, y2, COLOR_AQUA, false);
}

void Item::CreateRecoveryPortion()
{
	ItemTextures& t = ItemTextures::singleton();
	this->type = RecoveryPortion;
	this->name = "ƒ|[ƒVƒ‡ƒ“";
	this->gh = t.GetTexture(RecoveryPortion);
}
