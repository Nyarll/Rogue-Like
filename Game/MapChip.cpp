#include "MapChip.h"

const int MapChip::SIZE = 16;
const int MapChip::OFFSET = 0;    
const int MapChip::PADDING = 0;

// < コンストラクタ >
MapChip::MapChip(int tex, int rowNum, int colNum, bool is_passable)
{
	int left = OFFSET + colNum * (SIZE + PADDING);
	int top = OFFSET + rowNum * (SIZE + PADDING);

	this->gh = DerivationGraph(left, top, SIZE, SIZE, tex);
	this->isPassable = is_passable;
}

// < デストラクタ >
MapChip::~MapChip()
{

}

// < 描画 >
void MapChip::Render(int x, int y, int grid_size)const
{
	int x1 = x;
	int y1 = y;
	int x2 = x + grid_size;
	int y2 = y + grid_size;

	DrawExtendGraph(x1, y1, x2, y2, this->gh, TRUE);
}

// < 通行可能かどうかを返す >
bool MapChip::IsPassable()const
{
	return this->isPassable;
}