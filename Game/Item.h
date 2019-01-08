#pragma once

#include "Define.h"
#include "Vector.h"

typedef enum
{
	RecoveryPortion,
	ItemTypeNum,
	ItemTypeNull
}ItemType;

class Item
{
private:
	int gh;				// Graph Handle
	IntVector2 pos;		// Position

	int type;			// Item type
	char* name;			// Item name

public:
	Item(int x, int y);
	~Item();

	int GetItemType();
	char* GetItemName();
	IntVector2 GetPosition();

	void Render(const Vector2& screen_pos, const int grid_size);

public:
	void CreateRecoveryPortion();
};

