#include "Input.h"


// <Key Board>

void InputKeyBoard::Update()
{
	GetHitKeyStateAll(key);
}

void InputKeyBoard::UpdateOld()
{
	GetHitKeyStateAll(key_old);
}

bool InputKeyBoard::GetDown(int key_id)
{
	if ((this->key[key_id] == 1) && (this->key_old[key_id] == 0))
	{
		return true;
	}
	return false;
}

bool InputKeyBoard::GetNow(int key_id)
{
	if (this->key[key_id])
	{
		return true;
	}
	return false;
}

bool InputKeyBoard::GetUp(int key_id)
{
	if (!this->key[key_id] && this->key_old[key_id])
	{
		return true;
	}
	return false;
}

bool InputKeyBoard::GetInput()
{
	for (int i = 0; i < 256; i++)
	{
		if (this->key[i] == 1)
		{
			return true;
		}
	}
	return false;
}


// <Mouse>

InputMouse::InputMouse()
{
	this->now = 0;
	this->old = 0;
}

void InputMouse::Update()
{
	old = now;
	now = GetMouseInput();

	int x, y;
	GetMousePoint(&x, &y);
	this->position.Set((float)x, (float)y);
}

bool InputMouse::GetDown(int bottun)
{
	if (((now & bottun) == bottun) && ((old & bottun) != bottun))
	{
		return true;
	}
	return false;
}

bool InputMouse::GetNow(int bottun)
{
	if ((now & bottun) == bottun)
	{
		return true;
	}
	return false;
}

bool InputMouse::GetUp(int bottun)
{
	if (((now & bottun) != bottun) && ((old & bottun) == bottun))
	{
		return true;
	}
	return false;
}

Vector2 InputMouse::GetPosition()
{
	return this->position;
}


// <Joypad>
InputJoypad::InputJoypad(int pad_id)
{
	this->id = pad_id;
	now = 0;
	old = 0;
}

InputJoypad::~InputJoypad()
{

}

void InputJoypad::Update()
{
	old = now;
	now = GetJoypadInputState(this->id);
}

bool InputJoypad::GetDown(int bottun)
{
	if (((now & bottun) == bottun) && ((old & bottun) != bottun))
	{
		return true;
	}
	return false;
}

bool InputJoypad::GetNow(int bottun)
{
	if ((now & bottun) == bottun)
	{
		return true;
	}
	return false;
}

bool InputJoypad::GetUp(int bottun)
{
	if (((now & bottun) != bottun) && ((old & bottun) == bottun))
	{
		return true;
	}
	return false;
}


// <Input>
InputManager::InputManager()
{
	key = new InputKeyBoard;
	mouse = new InputMouse;
	joypad = new InputJoypad;
}

InputManager::~InputManager()
{
	delete key;
	delete mouse;
	delete joypad;
}

void InputManager::Update()
{
	key->Update();
	mouse->Update();
	joypad->Update();
}