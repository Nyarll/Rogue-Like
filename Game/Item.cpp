#include "Item.h"



Item::Item(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;

	this->type = ItemTypeNull;	// Ç∆ÇËÇ†Ç¶Ç∏Null Item Ç…ÇµÇƒÇ®Ç≠
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

	bool debug_mode = true;

	if (debug_mode)
	{
		DrawCircle(x, y, 10, COLOR_AQUA);
		DrawBox(x1, y1, x2, y2, COLOR_LIME, false);
	}
}

void Item::CreateRecoveryPortion()
{
	this->type = RecoveryPortion;
	this->name = "É|Å[ÉVÉáÉì";
}
