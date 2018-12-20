#pragma once
#include "Vector.h"
#include "Dungeons.h"
#include "GenerateMap.h"

class MapChip;

class Map
{
public:
	static const int GRID_COLS = MapSizeX;	// ���O���b�h��
	static const int GRID_ROWS = MapSizeY;	// �c�O���b�h��
	static const int NUM_MAPCHIPS = 4;

	static const int GRID_SIZE;
	static const Bounds2D BOUNDS;	// �}�b�v�̈�

private:
	int cells[GRID_ROWS][GRID_COLS];	// �f�[�^
	int tex_mapchip;	// �}�b�v�`�b�v�p
	MapChip* mapchip[NUM_MAPCHIPS];	// �`�b�v���X�g

	

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
	bool IsPassable(int grid_x, int grid_y)const;	// �ړ���֍s���邩�ǂ���

	void SetFloorChangePlace(int grid_x, int grid_y);
	bool IsFloorChange(int grid_x, int grid_y)const;	// �ړ��悪�t���A�ړ��ł������ǂ���

	void SetMagicCircle(int grid_x, int grid_y);

	void SetFloorDefault(int grid_x, int grid_y);		// ���ɖ߂�
};