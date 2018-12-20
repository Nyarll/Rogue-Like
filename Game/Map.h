#pragma once
#include "Vector.h"
#include "Dungeons.h"
#include "GenerateMap.h"

class MapChip;

class Map
{
public:
	static const int GRID_COLS = MapSizeX;	// 横グリッド数
	static const int GRID_ROWS = MapSizeY;	// 縦グリッド数
	static const int NUM_MAPCHIPS = 4;

	static const int GRID_SIZE;
	static const Bounds2D BOUNDS;	// マップ領域

private:
	int cells[GRID_ROWS][GRID_COLS];	// データ
	int tex_mapchip;	// マップチップ用
	MapChip* mapchip[NUM_MAPCHIPS];	// チップリスト

	

public:
	DngMap_RL dng;
	MapData_RL map_data[MX][MY];

	Map_* map_;
public:
	Map();
	~Map();

	bool LoadMapChip(const char* file_name);
	bool CreateMapData();
	void Render(const Vector2& screen_pos, const int grid_size = GRID_SIZE, bool render_grid = true)const;
	void DrawMap(const Vector2& Correction, int playerPosx, int playerPosY);

	MapChip* GetCell(int grid_x, int grid_y)const;
	int GetCellid(int grid_x, int grid_y);
	bool IsPassable(int grid_x, int grid_y)const;	// 移動先へ行けるかどうか

	void SetFloorChangePlace(int grid_x, int grid_y);
	bool IsFloorChange(int grid_x, int grid_y)const;	// 移動先がフロア移動できるやつかどうか

	void SetMagicCircle(int grid_x, int grid_y);

	void SetFloorDefault(int grid_x, int grid_y);		// 床に戻す
};