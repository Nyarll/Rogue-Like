#include "Dungeons.h"

int RL_Create(DngMap_RL* dng, MapData_RL maprl[][MY], Mob_RL* mob) {

	for (int i = 0; i < RL_MOB_C; i++) {
		mob[i].id = 0;
		mob[i].x = 0;
		mob[i].y = 0;
		mob[i].s = 1;
	}

	RL_Make(dng, maprl);

	for (int i = 0; i < RL_MOB_C; i++) {
		RL_MakeMob(dng, maprl, mob, i);
	}

	return 0;
}

int RL_Make(DngMap_RL* dng, MapData_RL maprl[][MY])
{
	//初期化
	for (int i = 0; i < MX; i++) {
		for (int j = 0; j < MY; j++) {
			maprl[i][j].mapData = 1;
		}
	}

	dng->mapDivCount = dng->divCountMin + GetRand(dng->divCountRand); //マップの区分け数 (部屋の個数) 0~nまでの部屋ID
	if (dng->mapDivCount > 7) return -1;

	for (int i = 0; i < dng->mapDivCount; i++) {
		dng->mapRoomArea[i] = 0;
	}
	dng->mapTotalArea = 0;
	dng->mapRoomCount = 0;

	dng->mapDiv[0][0] = (MX - 1); //マップの区分け初期サイズX終点 (マップの大きさX軸)
	dng->mapDiv[0][1] = (MY - 1); //マップの区分け初期サイズY終点 (マップの大きさY軸)
	dng->mapDiv[0][2] = 1; //マップの区分け初期サイズX始点 (マップの大きさX軸)
	dng->mapDiv[0][3] = 1; //マップの区分け初期サイズY始点 (マップの大きさY軸)

	dng->mapRoad[0][0] = 255;
	dng->mapRoad[0][1] = 255;

	/*マップを区分けしていく処理(区域を分割する処理)*/
	int divAfter;
	int count; //(0:X, 1:Y) X軸で分けるかY軸で分けるか決める

	for (int i = 1; i < dng->mapDivCount; i++) {

		//今まで作った区分けをランダムに指定(指定した区域をさらに区分けする)
		divAfter = GetRand(i - 1);

		//指定した区域のXとYの長さによって、分割する向きを決める(長いほうを分割する)
		if (dng->mapDiv[divAfter][0] - dng->mapDiv[divAfter][2] > dng->mapDiv[divAfter][1] - dng->mapDiv[divAfter][3]) count = RL_COUNT_X;
		else count = RL_COUNT_Y;

		if (dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2] < dng->divCountRand * 2 + 8) {
			int k = 0;
			for (int j = 1; j < dng->mapDivCount; j++) {
				if (dng->mapDiv[j][0] - dng->mapDiv[j][2] > k) {
					k = dng->mapDiv[j][0] - dng->mapDiv[j][2];
					divAfter = j;
					count = RL_COUNT_X;
				}
				if (dng->mapDiv[j][1] - dng->mapDiv[j][3] > k) {
					k = dng->mapDiv[j][1] - dng->mapDiv[j][3];
					divAfter = j;
					count = RL_COUNT_Y;
				}
			}
		}

		dng->mapRoad[i][0] = divAfter;
		dng->mapRoad[i][1] = count;

		for (int j = 1; j < i; j++)
			if (dng->mapRoad[j][0] == divAfter) dng->mapRoad[j][0] = i;

		//count軸の設定
		dng->mapDiv[i][count] = dng->mapDiv[divAfter][count + 2] + (dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2]) / 3 + GetRand((dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2]) / 3); //0.軸の右端(iR)の座標(divAfter*R/3~2divAfter*R/3)
		dng->mapDiv[i][count + 2] = dng->mapDiv[divAfter][count + 2]; //0.軸の左端(iL)の座標(divAfterL)
		dng->mapDiv[divAfter][count + 2] = dng->mapDiv[i][count]; //divAfter軸の左端(divAfterL)の座標(iR)

																  //countとは逆の軸の設定
		dng->mapDiv[i][abs(count - 1)] = dng->mapDiv[divAfter][abs(count - 1)]; //軸の右端(iR)の座標(divAfterR)
		dng->mapDiv[i][abs(count - 1) + 2] = dng->mapDiv[divAfter][abs(count - 1) + 2]; //軸の左端(iL)の座標(divAfterL)
	}

	/*部屋を生成する処理*/
	for (int i = 0; i < dng->mapDivCount; i++) {//区分け
		dng->mapRoomPlayer[i] = 0;//プレイヤー侵入初期化
		dng->mapRoom[i][2] = dng->mapDiv[i][2]; //区分けX始点をマップX始点へ代入
		dng->mapRoom[i][3] = dng->mapDiv[i][3]; //区分けY始点をマップY始点へ代入

												//X座標の部屋の長さを指定
		dng->mapRoom[i][0] = dng->mapDiv[i][2] + dng->divCountRand + GetRand(dng->roomLengthRandX);
		if (dng->mapDiv[i][0] - dng->mapDiv[i][2] < dng->mapRoom[i][0] - dng->mapRoom[i][2] + 5) {
			dng->mapRoom[i][0] = dng->mapDiv[i][0] - 4;
			if (dng->mapDiv[i][0] - dng->mapDiv[i][2] < dng->mapRoom[i][0] - dng->mapRoom[i][2] + 5) {
				dng->mapRoom[i][0] = dng->mapDiv[i][2] + 1;
			}
		}

		dng->mapRoom[i][1] = dng->mapDiv[i][3] + dng->roomLengthMinY + GetRand(dng->roomLengthRandY);
		if (dng->mapDiv[i][1] - dng->mapDiv[i][3] < dng->mapRoom[i][1] - dng->mapRoom[i][3] + 5) {
			dng->mapRoom[i][1] = dng->mapDiv[i][1] - 4;
			if (dng->mapDiv[i][1] - dng->mapDiv[i][3] < dng->mapRoom[i][1] - dng->mapRoom[i][3] + 5) {
				dng->mapRoom[i][1] = dng->mapDiv[i][3] + 1;
			}
		}

		if (dng->mapRoom[i][0] - dng->mapDiv[i][2] <= 1 || dng->mapRoom[i][1] - dng->mapDiv[i][3] <= 1) {
			dng->mapRoom[i][0] = dng->mapDiv[i][2] + 1;
			dng->mapRoom[i][1] = dng->mapDiv[i][3] + 1;
		}
		int l = GetRand(dng->mapDiv[i][0] - dng->mapRoom[i][0] - 5) + 2;
		int m = GetRand(dng->mapDiv[i][1] - dng->mapRoom[i][1] - 5) + 2;
		dng->mapRoom[i][0] += l;
		dng->mapRoom[i][2] += l;
		dng->mapRoom[i][1] += m;
		dng->mapRoom[i][3] += m;

		for (int j = dng->mapRoom[i][2]; j < dng->mapRoom[i][0]; j++) {
			for (int k = dng->mapRoom[i][3]; k < dng->mapRoom[i][1]; k++) {
				maprl[j][k].mapData = 0;
				dng->mapRoomArea[i]++;
			}
		}

		if (dng->mapRoomArea[i] > 1) {
			dng->mapRoom2[dng->mapRoomCount] = i;
			dng->mapRoomCount++;
			dng->mapTotalArea += dng->mapRoomArea[i];
		}

	}




	/*通路を生成する処理*/
	/*通路は２部屋間の細い道のことを指す。
	通路を作るために２部屋をそれぞれ前(Before)と後(After)で分ける。
	for文で全ての部屋をチェックし、前後の部屋を繋ぐ通路を作る。
	まず、前の通路を作り、次に後の通路を作る。
	最後に前と後の通路を繋げる。
	*/
	int roomAfter;
	for (int roomBefore = 0; roomBefore < dng->mapDivCount; roomBefore++) {
		roomAfter = dng->mapRoad[roomBefore][0];

		//X座標の通路
		switch (dng->mapRoad[roomBefore][1]) {
		case RL_COUNT_X:
			dng->mapRoad[roomBefore][2] = GetRand(dng->mapRoom[roomBefore][1] - dng->mapRoom[roomBefore][3] - 2); //前側の通路の位置
			dng->mapRoad[roomBefore][3] = GetRand(dng->mapRoom[roomAfter][1] - dng->mapRoom[roomAfter][3] - 2); //後側の通路の位置
			//前の通路
			for (int j = dng->mapRoom[roomBefore][0]; j < dng->mapDiv[roomBefore][0]; j++)
				maprl[j][dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]].mapData = 0; //通路をマップチップに線画

			 //後の通路
			for (int j = dng->mapDiv[roomAfter][2]; j < dng->mapRoom[roomAfter][2]; j++)
				maprl[j][dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]].mapData = 0; //通路をマップチップに線画

			//通路をつなぐ
			for (int j = dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]; j <= dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]; j++)
				maprl[dng->mapDiv[roomBefore][0]][j].mapData = 0; //通路をマップチップに線画 2から5(上から下)
			for (int j = dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]; j <= dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]; j++)
				maprl[dng->mapDiv[roomBefore][0]][j].mapData = 0; //通路をマップチップに線画 5から2(下から上)
			break;

		case RL_COUNT_Y:
			dng->mapRoad[roomBefore][2] = GetRand(dng->mapRoom[roomBefore][0] - dng->mapRoom[roomBefore][2] - 2); //前側の通路の位置
			dng->mapRoad[roomBefore][3] = GetRand(dng->mapRoom[roomAfter][0] - dng->mapRoom[roomAfter][2] - 2); //後側の通路の位置
																												//前の通路
			for (int j = dng->mapRoom[roomBefore][1]; j < dng->mapDiv[roomBefore][1]; j++)
				maprl[dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]][j].mapData = 0; //通路をマップチップに線画

																								 //後の通路
			for (int j = dng->mapDiv[roomAfter][3]; j < dng->mapRoom[roomAfter][3]; j++)
				maprl[dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]][j].mapData = 0; //通路をマップチップに線画

																								//通路をつなぐ
			for (int j = dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]; j <= dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]; j++)
				maprl[j][dng->mapDiv[roomBefore][1]].mapData = 0; //通路をマップチップに線画
			for (int j = dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]; j <= dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]; j++)
				maprl[j][dng->mapDiv[roomBefore][1]].mapData = 0; //通路をマップチップに線画
			break;
		}

	}

	//エラーチェック
	if (!dng->mapDivCount)return -1;
	if (dng->mapTotalArea < 5)return -1;

	return 0;
}

int RL_MakeMob(DngMap_RL* dngMap, MapData_RL maprl[][MY], Mob_RL* mob, int id)
{

	//プレイヤーを設置する
	int a = dngMap->mapRoom2[GetRand(dngMap->mapRoomCount - 1)]; //マップ上の部屋をランダムに指定する
	int b = GetRand(dngMap->mapRoom[a][0] - dngMap->mapRoom[a][2] - 1); //マップのX座標の長さの中からランダムに指定
	int c = GetRand(dngMap->mapRoom[a][1] - dngMap->mapRoom[a][3] - 1); //マップのY座標の長さの中からランダムに指定

	mob[id].x = dngMap->mapRoom[a][2] + b;
	mob[id].y = dngMap->mapRoom[a][3] + c;

	if (!id) dngMap->mapRoomPlayer[a] = 1; //部屋にプレイヤー侵入

	mob[id].id = 1;

	//他のmobと重なっていたら消す
	for (int i = 0; i < RL_MOB_C; i++) {
		if (id != i && mob[i].id && mob[id].x == mob[i].x && mob[id].y == mob[i].y) {

			mob[id].id = 0;
			break;

		}
	}


	return 0;
}

