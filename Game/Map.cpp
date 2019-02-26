#include "Map.h"

#include "MapChip.h"
#include <cassert>

const int      Map::GRID_SIZE = 64;    // グリッドの大きさ
const Bounds2D Map::BOUNDS =           // マップの領域
{
	0.0f,                              // 左端                      
	0.0f,                              // 上端
	Map::GRID_SIZE * Map::GRID_COLS,   // 右端
	Map::GRID_SIZE * Map::GRID_ROWS    // 下端
};

Map::Map() : tex_mapchip(0)
{
	for (int i = 0; i < GRID_ROWS; i++)
	{
		for (int j = 0; j < GRID_COLS; j++)
		{
			this->cells[i][j] = 0;
		}
	}

	for (int i = 0; i < NUM_MAPCHIPS; i++)
	{
		this->mapchip[i] = nullptr;
	}

	this->map_ = new Map_;
}

Map::~Map()
{
	for (int i = 0; i < NUM_MAPCHIPS; i++)
	{
		delete this->mapchip[i];
	}
}

bool Map::LoadMapChip(const char* file_name)
{
	this->tex_mapchip = LoadGraph(file_name);
	if (tex_mapchip == (-1))
	{
		return false;
	}

	for (int i = 0; i < NUM_MAPCHIPS; i++)
	{
		int  row_number = i / 12;
		int  col_number = i % 12;
		bool is_passable;
		if ((i == 0) || (i == 2) || (i == 3))
		{
			is_passable = true;
		}
		else
		{
			is_passable = false;
		}

		this->mapchip[i] = new MapChip(this->tex_mapchip, row_number, col_number, is_passable);
	}
	return true;
}

bool Map::CreateMapData()
{
	RL_Make(&this->dng, this->map_data);
	this->map_->GenerateMapData();

	for (int i = 0; i < GRID_ROWS; i++)
	{
		for (int j = 0; j < GRID_COLS; j++)
		{
			//this->cells[i][j] = this->map_data[j][i].mapData;
			this->cells[i][j] = this->map_->GetMapData(i, j);
		}
	}

	return true;
}

void Map::Render(const Vector2& screen_pos, const int grid_size, bool render_grid)const
{
	for (int i = 0; i < GRID_ROWS; i++)
	{
		for (int j = 0; j < GRID_COLS; j++)
		{
			int x = j * grid_size - static_cast<int>(screen_pos.x);
			int y = i * grid_size - static_cast<int>(screen_pos.y);
			int id = this->cells[i][j];

			if (mapchip[id] != nullptr)
			{
				mapchip[id]->Render(x, y, grid_size);
			}
		}
	}

	// グリッドの描画(Debug用)
	if (render_grid)
	{
		for (int i = 0; i < GRID_ROWS; i++)
		{
			for (int j = 0; j < GRID_COLS; j++)
			{
				int x1 = j * GRID_SIZE - static_cast<int>(screen_pos.x);
				int y1 = i * GRID_SIZE - static_cast<int>(screen_pos.y);
				int x2 = x1 + GRID_SIZE;
				int y2 = y1 + GRID_SIZE;
				DrawBox(x1, y1, x2, y2, COLOR_GRAY, FALSE);
				//DrawFormatString(x1, y1, COLOR_BLUE, "%d,%d", i, j);
			}
		}
	}
}

void Map::DrawMap(const Vector2& Correction, int playerPosX, int playerPosY)
{
	DrawBox(0 + Correction.x, 0 + Correction.y, 16 * 16 + Correction.x, 16 * 16 + Correction.y, COLOR_LIME, false);
	DrawBox(0 + Correction.x + 1, 0 + Correction.y + 1, 16 * 16 + Correction.x - 1, 16 * 16 + Correction.y - 1, COLOR_LIME, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0 + Correction.x, 0 + Correction.y, 16 * 16 + Correction.x, 16 * 16 + Correction.y, COLOR_BLACK, true);

	for (int i = 0; i < GRID_ROWS; i++)
	{
		for (int j = 0; j < GRID_COLS; j++)
		{
			int x = j * 4 + static_cast<int>(Correction.x);
			int y = i * 4 + static_cast<int>(Correction.y);
			int id = this->cells[i][j];

			switch (id)
			{
			case 0:
				DrawBox(x, y, x + 4, y + 4, 0xff808080, true);
				DrawBox(x, y, x + 4, y + 4, 0xff848484, false);
				break;

			case 1:
				break;

			case 2:
				DrawBox(x, y, x + 4, y + 4, 0xff888888, true);
				DrawBox(x, y, x + 4, y + 4, 0xff000000, false);
				break;

			case 3:
				DrawBox(x, y, x + 4, y + 4, 0xff808080, true);
				DrawBox(x, y, x + 4, y + 4, 0xff00ffff, false);
				break;
			}
		}
	}

	DrawCircle(playerPosX + Correction.x, playerPosY + Correction.y, 2, 0xff00ff0f, TRUE);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

MapChip* Map::GetCell(int grid_x, int grid_y)const
{
	if ((grid_x >= 0) && (grid_x < GRID_COLS) &&
		(grid_y >= 0) && (grid_y < GRID_ROWS))
	{
		assert("アクセス違反");
	}
	int id = this->cells[grid_y][grid_x];

	return this->mapchip[id];
}

int Map::GetCellid(int grid_x, int grid_y)
{
	return this->cells[grid_y][grid_x];
}

bool Map::IsPassable(int grid_x, int grid_y)const
{
	MapChip* map_chip = GetCell(grid_x, grid_y);
	return map_chip->IsPassable();
}

void Map::SetFloorChangePlace(int grid_x, int grid_y)
{
	this->map_data[grid_x][grid_y].mapData = 2;
	this->cells[grid_y][grid_x] = 2;
}

bool Map::IsFloorChange(int grid_x, int grid_y) const
{
	if (this->cells[grid_y][grid_x] == 2)
	{
		return true;
	}
	return false;
}

void Map::SetMagicCircle(int grid_x, int grid_y)
{
	this->map_data[grid_x][grid_y].mapData = 3;
	this->cells[grid_y][grid_x] = 3;
}

void Map::SetFloorDefault(int grid_x, int grid_y)
{
	this->map_data[grid_x][grid_y].mapData = 0;
	this->cells[grid_y][grid_x] = 0;
}
