#pragma once

class MapChip
{
public:
	static const int SIZE;		// サイズ
	static const int OFFSET;	// オフセット
	static const int PADDING;	// パディング

private:
	int gh;				// グラフィックハンドル
	bool isPassable;	// 通行できるかどうか

public:
	MapChip(int tex, int rowNum, int colNum, bool is_passable);
	~MapChip();

	void Render(int x, int y, int grid_size)const;
	bool IsPassable()const;
};