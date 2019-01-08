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

// <�V�X�e��> ----------------------------------------------------------
const char* const GAME_TITLE = "Block Breaking";    // �Q�[���^�C�g��

#define extends : public

#define INT_CAST	(int)
#define FLOAT_CAST	(float)

// <���> --------------------------------------------------------------
const int SCREEN_WIDTH = 800;    // ��ʂ̕�[pixel]
const int SCREEN_HEIGHT = 800;    // ��ʂ̍���[pixel]

const int SCREEN_TOP = 0;                    // ��ʂ̏�[
const int SCREEN_BOTTOM = SCREEN_HEIGHT;        // ��ʂ̉��[
const int SCREEN_LEFT = 0;                    // ��ʂ̍��[
const int SCREEN_RIGHT = SCREEN_WIDTH;         // ��ʂ̉E�[

const int SCREEN_CENTER_X = SCREEN_WIDTH / 2;    // ��ʂ̒���(X���W)
const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;    // ��ʂ̒���(Y���W)

// <Game Screen>
const int GAME_SCREEN_WIDTH = (SCREEN_WIDTH / 2);
const int GAME_SCREEN_HEIGHT = (SCREEN_HEIGHT);
const int GAME_SCREEN_TOP = (0);
const int GAME_SCREEN_BOTTOM = (GAME_SCREEN_HEIGHT);
const int GAME_SCREEN_LEFT = (GAME_SCREEN_WIDTH / 2);
const int GAME_SCREEN_RIGHT = (GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2);
const int GAME_SCREEN_CENTER_X = (GAME_SCREEN_WIDTH / 2 + GAME_SCREEN_LEFT);
const int GAME_SCREEN_CENTER_Y = (GAME_SCREEN_HEIGHT / 2 + GAME_SCREEN_TOP);


//���b�Z�[�W�{�b�N�X
#define MSG(m)	{	MessageBox(NULL,m,"Message Info",MB_OK);}
#define EXIT	{	MSG("�Q�[�����I�����܂�") PostQuitMessage(0);}

#define DEG_TO_RAD(DEG)	((DEG) * (M_PI / 180.0))
#define RAD_TO_DEG(RAD)	((RAD) * (180.0 / M_PI))