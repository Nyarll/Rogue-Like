#pragma once

#include "Define.h"
#include "Vector.h"
#include "Singleton.h"

typedef enum
{
	RecoveryPortion,
	ItemTypeNum,
	ItemTypeNull
}ItemType;

const int ItemTextureSize = 32;

class ItemTextures : public Singleton<ItemTextures>
{
private:
	int gh[ItemTypeNum];
	friend class Singleton<ItemTextures>;

public:
	static const int TextureNotFound = (-1);

public:
	ItemTextures()
	{
		this->gh[RecoveryPortion] = LoadGraph("Resources/Textures/Portion.png");
	}

	int GetTexture(int itemType)
	{
		if (itemType < ItemTypeNum)
		{
			return this->gh[itemType];
		}
		else
		{
			return (TextureNotFound);
		}
	}
};

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
	void DrawItem(int x, int y);

public:
	void CreateRecoveryPortion();
};
