#pragma once
#include "Define.h"

const int MapSizeX = 64;
const int MapSizeY = 64;

const int NumObject = 10;
const int NumMobs = 40;

enum
{
	WALK,
	WALL
};
enum
{
	RIGHT,
	LEFT,
	DOWN,
	UP
};

typedef struct
{

	unsigned char x = 0;

	unsigned char y = 0;

	unsigned char s = 1;

	unsigned char id = 0;
}MobData;

class Point2i
{
public:
	int x, y;

public:
	Point2i() { this->x = 0; this->y = 0; };
	Point2i(int _x, int _y) :x(_x), y(_y) {};
};

class Room
{
public:
	Point2i start, end;
	Point2i random_point;
	Point2i cross[4];

	bool state;
public:
	Room() {};
	Room(Point2i _start, Point2i _end) :start(_start), end(_end) {};

	int sizeX()
	{
		return (end.x - start.x);
	}
	int sizeY()
	{
		return (end.y - start.y);
	}
};

class Area
{
public:
	Point2i start, end;
	Room room;

public:
	Area() {};
	Area(Point2i _start, Point2i _end) :start(_start), end(_end) {};
};

class Map_
{
public:
	int map[MapSizeY][MapSizeX];
	Area area[64];

	MobData ObjectPoint[NumObject];

private:
	void MapDataFillWall()
	{
		for (int y = 0; y < MapSizeY; y++)
		{
			for (int x = 0; x < MapSizeX; x++)
			{
				this->map[y][x] = WALL;
			}
		}
	}
	void AreaSlice()
	{
		const int RoomSize = 16;
		Point2i start = Point2i(0, 0);
		Point2i end = Point2i(RoomSize, RoomSize);
		for (int i = 0; i < 64 / 4; i++)
		{
			area[i] = Area(start, end);
			start.x += RoomSize;
			if (start.x >= 64)
			{
				start.x = 0;
				start.y += RoomSize;
			}
			end.x = start.x + RoomSize;
			end.y = start.y + RoomSize;
		}
	}
	void CreateRoom()
	{
		const int padding = 3;
		for (int i = 0; i < 64 / 4; i++)
		{
			for (int n = 0; n < 4; n++)
			{
				this->area[i].room.cross[n].x = (-1);
				this->area[i].room.cross[n].y = (-1);
			}
			if (rand() % 3 || true)
			{
				this->area[i].room.state = true;

				this->area[i].room.start.x = (this->area[i].start.x + padding);
				this->area[i].room.end.x = (this->area[i].end.x - padding);
				this->area[i].room.start.y = (this->area[i].start.y + padding);
				this->area[i].room.end.y = (this->area[i].end.y - padding);

				this->area[i].room.random_point.x = rand() % this->area[i].room.sizeX() + this->area[i].room.start.x;
				this->area[i].room.random_point.y = rand() % this->area[i].room.sizeY() + this->area[i].room.start.y;

				for (int y = this->area[i].room.start.y; y < this->area[i].room.end.y; y++)
				{
					for (int x = this->area[i].room.start.x; x < this->area[i].room.end.x; x++)
					{
						this->map[y][x] = WALK;
					}
				}
			}
			else
			{
				this->area[i].room.state = false;
			}
		}
	}
	void CreateRoute()
	{
		// 部屋から他の部屋に向かって通路をArea端まで伸ばす
		for (int i = 0; i < 64 / 4; i++)
		{
			if (this->area[i].room.state == true)
			{
				int x = this->area[i].room.random_point.x;
				int y = this->area[i].room.random_point.y;
				// 部屋の右側
				{
					if (area[i].end.x < MapSizeX)
					{
						int target_x = area[i].end.x;
						while (x != target_x)
						{
							map[y][x] = WALK;
							x++;
						}
						area[i].room.cross[RIGHT] = Point2i(x, y);
					}
				}
				// 部屋の左側
				x = this->area[i].room.random_point.x;
				y = this->area[i].room.random_point.y;
				{
					if (area[i].start.x > 0)
					{
						int target_x = area[i].start.x;
						while (x != target_x)
						{
							map[y][x] = WALK;
							x--;
						}
						area[i].room.cross[LEFT] = Point2i(x, y);
					}
				}
				// 部屋の下側
				x = this->area[i].room.random_point.x;
				y = this->area[i].room.random_point.y;
				{
					if (area[i].end.y < MapSizeY)
					{
						int target_y = area[i].end.y;
						while (y != target_y)
						{
							map[y][x] = WALK;
							y++;
						}
						area[i].room.cross[DOWN] = Point2i(x, y);
					}
				}
				// 部屋の上側
				x = this->area[i].room.random_point.x;
				y = this->area[i].room.random_point.y;
				{
					if (area[i].start.y > 0)
					{
						int target_y = area[i].start.y;
						while (y != target_y)
						{
							map[y][x] = WALK;
							y--;
						}
						area[i].room.cross[UP] = Point2i(x, y);
					}
				}
			}
		}

		// 伸ばした通路をつなげる
		for (int i = 0; i < 64 / 4; i++)
		{
			for (int k = 0; k < 64 / 4; k++)
			{
				if (i != k)
				{
					if (area[i].room.cross[RIGHT].x != (-1) && area[k].room.cross[LEFT].x != (-1))
					{
						if (area[i].room.cross[RIGHT].x == area[k].room.cross[LEFT].x)
						{
							int x = area[i].room.cross[RIGHT].x;

							for (int y = Min(area[i].room.cross[RIGHT].y, area[k].room.cross[LEFT].y);
								y <= Max(area[i].room.cross[RIGHT].y, area[k].room.cross[LEFT].y);
								y++)
							{
								map[y][x] = WALK;
							}
						}
					}
					if (area[i].room.cross[DOWN].y != (-1) && area[k].room.cross[UP].y != (-1))
					{
						if (area[i].room.cross[DOWN].y == area[k].room.cross[UP].y)
						{
							int y = area[i].room.cross[DOWN].y;

							for (int x = Min(area[i].room.cross[DOWN].x, area[k].room.cross[UP].x);
								x <= Max(area[i].room.cross[DOWN].x, area[k].room.cross[UP].x);
								x++)
							{
								map[y][x] = WALK;
							}
						}
					}
				}
			}
		}
	}
	void MobInstall()
	{
		// モブを設置する
		for (int id = 0; id < NumObject; id++)
		{
			int ActiveRoom;
			while (1)
			{
				int i = rand() % (64 / 4);
				if (this->area[i].room.state)
				{
					ActiveRoom = i;
					break;
				}
			}

			if (this->area[ActiveRoom].room.state == true)
			{
				int b = GetRand((this->area[ActiveRoom].room.end.x - 1) - this->area[ActiveRoom].room.start.x); //マップのX座標の長さの中からランダムに指定
				int c = GetRand((this->area[ActiveRoom].room.end.y - 1) - this->area[ActiveRoom].room.start.y); //マップのY座標の長さの中からランダムに指定

				int tx = this->area[ActiveRoom].room.start.x + 1 + b;
				int ty = this->area[ActiveRoom].room.start.y + 1 + c;

				if (map[ty][tx] == 1)
				{
					while (1)
					{
						b = GetRand((this->area[ActiveRoom].room.end.x - 1) - this->area[ActiveRoom].room.start.x);
						c = GetRand((this->area[ActiveRoom].room.end.y - 1) - this->area[ActiveRoom].room.start.y);
						tx = this->area[ActiveRoom].room.start.x + 1 + b;
						ty = this->area[ActiveRoom].room.start.y + 1 + c;

						if (map[ty][tx] == 0)
						{
							break;
						}
					}
				}

				this->ObjectPoint[id].x = tx;
				this->ObjectPoint[id].y = ty;

				this->ObjectPoint[id].id = 1;

				//他のmobと重なっていたら消す
				for (int i = 0; i < NumObject; i++)
				{
					if (id != i && ObjectPoint[i].id && ObjectPoint[id].x == ObjectPoint[i].x && ObjectPoint[id].y == ObjectPoint[i].y)
					{
						ObjectPoint[id].id = 0;
						break;
					}
				}
			}
		}
	}

public:
	void GenerateMapData()
	{
		this->MapDataFillWall();
		this->AreaSlice();
		this->CreateRoom();
		this->CreateRoute();
		this->MobInstall();
	}
	void MobInstallTo(int id)
	{
		int ActiveRoom;
		while (1)
		{
			int i = rand() % (64 / 4);
			if (this->area[i].room.state)
			{
				ActiveRoom = i;
				break;
			}
		}

		if (this->area[ActiveRoom].room.state == true)
		{
			int b = GetRand((this->area[ActiveRoom].room.end.x - 1) - this->area[ActiveRoom].room.start.x); //マップのX座標の長さの中からランダムに指定
			int c = GetRand((this->area[ActiveRoom].room.end.y - 1) - this->area[ActiveRoom].room.start.y); //マップのY座標の長さの中からランダムに指定

			int tx = this->area[ActiveRoom].room.start.x + 1 + b;
			int ty = this->area[ActiveRoom].room.start.y + 1 + c;

			if (map[ty][tx] == 1)
			{
				while (1)
				{
					b = GetRand((this->area[ActiveRoom].room.end.x - 1) - this->area[ActiveRoom].room.start.x);
					c = GetRand((this->area[ActiveRoom].room.end.y - 1) - this->area[ActiveRoom].room.start.y);
					tx = this->area[ActiveRoom].room.start.x + 1 + b;
					ty = this->area[ActiveRoom].room.start.y + 1 + c;

					if (map[ty][tx] == 0)
					{
						break;
					}
				}
			}

			this->ObjectPoint[id].x = tx;
			this->ObjectPoint[id].y = ty;

			this->ObjectPoint[id].id = 1;

			//他のmobと重なっていたら消す
			for (int i = 0; i < NumObject; i++)
			{
				if (id != i && ObjectPoint[i].id && ObjectPoint[id].x == ObjectPoint[i].x && ObjectPoint[id].y == ObjectPoint[i].y)
				{
					ObjectPoint[id].id = 0;
					break;
				}
			}
		}
	}
	int GetMapData(int x, int y)
	{
		if (x >= 0 && y >= 0 && x < MapSizeX && y < MapSizeY)
		{
			return this->map[y][x];
		}
		return (-1);
	}
	Point2i GetInitMobPosition(int id)
	{
		return Point2i{ this->ObjectPoint[id].x,this->ObjectPoint[id].y };
	}

};