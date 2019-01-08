#pragma once

#define _USE_MATH_DEFINES
//#include <math.h>

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <utility>
#include <ctime>
#include <queue>

template<class T> T Min(const T& a, const T& b)
{
	return a < b ? a : b;
}
template<class T> T Max(const T& a, const T& b)
{
	return a > b ? a : b;
}
template<class T> T Clamp(const T& now, const T& min, const T& max)
{
	T m = Max(now, min);
	T n = Min(m, max);
	return n;
}

class IntVector2
{
public:
	int x, y;
};

// <システム> ----------------------------------------------------------
const char* const GAME_TITLE = "Block Breaking";    // ゲームタイトル

#define extends : public

#define INT_CAST	(int)
#define FLOAT_CAST	(float)

// <画面> --------------------------------------------------------------
const int SCREEN_WIDTH = 800;    // 画面の幅[pixel]
const int SCREEN_HEIGHT = 800;    // 画面の高さ[pixel]

const int SCREEN_TOP = 0;                    // 画面の上端
const int SCREEN_BOTTOM = SCREEN_HEIGHT;        // 画面の下端
const int SCREEN_LEFT = 0;                    // 画面の左端
const int SCREEN_RIGHT = SCREEN_WIDTH;         // 画面の右端

const int SCREEN_CENTER_X = SCREEN_WIDTH / 2;    // 画面の中央(X座標)
const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;    // 画面の中央(Y座標)

// <Game Screen>
const int GAME_SCREEN_WIDTH = (SCREEN_WIDTH / 2);
const int GAME_SCREEN_HEIGHT = (SCREEN_HEIGHT);
const int GAME_SCREEN_TOP = (0);
const int GAME_SCREEN_BOTTOM = (GAME_SCREEN_HEIGHT);
const int GAME_SCREEN_LEFT = (GAME_SCREEN_WIDTH / 2);
const int GAME_SCREEN_RIGHT = (GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2);
const int GAME_SCREEN_CENTER_X = (GAME_SCREEN_WIDTH / 2 + GAME_SCREEN_LEFT);
const int GAME_SCREEN_CENTER_Y = (GAME_SCREEN_HEIGHT / 2 + GAME_SCREEN_TOP);


//メッセージボックス
#define MSG(m)	{	MessageBox(NULL,m,"Message Info",MB_OK);}
#define EXIT	{	MSG("ゲームを終了します") PostQuitMessage(0);}

#define DEG_TO_RAD(DEG)	((DEG) * (M_PI / 180.0))
#define RAD_TO_DEG(RAD)	((RAD) * (180.0 / M_PI))