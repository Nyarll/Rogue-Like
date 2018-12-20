#pragma once

const int MX = (64); //マップ縦サイズ
const int MY = (32); //マップ横サイズ
#define RL_COUNT_X (0)
#define RL_COUNT_Y (1)

#define RL_MOB_C 20

struct Mob_RL
{

	unsigned char x = 0;

	unsigned char y = 0;

	unsigned char s = 1;

	unsigned char id = 0;
};

struct System_RL
{
	int turn = 0;
};

struct DngMap_RL
{

	//生成される部屋の数 (正確に言うと生成される区域の数)
	unsigned char divCountMin = 5; //マップの区分け最小数
	unsigned char divCountRand = 4; //マップの区分け数加算

									//生成される部屋のサイズ
	unsigned char roomLengthMinX = 5; //部屋のX座標の最小サイズ
	unsigned char roomLengthMinY = 5; //部屋のY座標の最小サイズ
	unsigned char roomLengthRandX = 2; //部屋のX座標のサイズ加算
	unsigned char roomLengthRandY = 2; //部屋のY座標のサイズ加算

	unsigned char mapDivCount; //マップの区分け数 (部屋の個数) 0~nまでの部屋ID
	unsigned char mapDiv[8][4] = { 0 }; //マップの区域 [部屋ID][X終点 , Y終点 , X始点 , Y始点]

	unsigned char mapRoomCount = 0; //部屋数
	unsigned char mapRoom2[8] = { 0 }; //部屋のID
	unsigned char mapRoom[8][4] = { 0 }; //マップの部屋 [部屋ID][X終点 , Y終点 , X始点 , Y始点]
	unsigned char mapRoad[8][4] = { 0 }; //マップの道 [部屋ID(前)][繋がる先の部屋ID(後) , (0.X座標 , 1.Y座標) , (前)側の通路の位置 , (後)側の通路の位置]
	unsigned char mapRoomPlayer[8] = { 0 };
	unsigned char mapRoomArea[8] = { 0 }; //部屋の面積
	unsigned char mapTotalArea = 0; //部屋の総面積
};

struct MapData_RL
{
	unsigned short mapData = 1; //マップ
};

int RL_Create(DngMap_RL* dngMap, MapData_RL maprl[][MY], Mob_RL* mob);

int RL_Make(DngMap_RL* dng, MapData_RL maprl[][MY]);

int RL_MakeMob(DngMap_RL* dngMap, MapData_RL maprl[][MY], Mob_RL* mob, int id);