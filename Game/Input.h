#pragma once
#include "Define.h"
#include "Vector.h"
#include "Singleton.h"

class InputKeyBoard
{
private:
	char key[256] = { 0 };
	char key_old[256] = { 0 };

public:
	InputKeyBoard() {};
	~InputKeyBoard() {};

	void Update();
	void UpdateOld();
	bool GetDown(int key_id);
	bool GetNow(int key_id);
	bool GetUp(int key_id);

	bool GetInput();
};

class InputMouse
{
private:
	Vector2 position;
	int now;
	int old;

public:
	InputMouse();
	~InputMouse() {};

	void Update();
	bool GetDown(int bottun);
	bool GetNow(int bottun);
	bool GetUp(int bottun);

	Vector2 GetPosition();
};

class InputJoypad
{
private:
	int id;
	int now;
	int old;

public:
	// コンストラクタ
	InputJoypad(int pad_id = DX_INPUT_KEY_PAD1);
	// デストラクタ
	~InputJoypad();

	// 操作
	void Update();    // 更新

	bool GetDown(int bottun);
	bool GetNow(int bottun);
	bool GetUp(int bottun);
};


class InputManager extends Singleton<InputManager>
{
public:
	friend class Singleton<InputManager>;
	InputManager();
	~InputManager();

public:
	InputKeyBoard* key;
	InputMouse* mouse;
	InputJoypad* joypad;

public:
	void Update();
};