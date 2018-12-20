#pragma once
#include "Define.h"
#include "Singleton.h"

class Message
{
public:
	int x, y;			// 表示箇所
	std::string m;			// 表示内容
	bool render = true;	// 表示するかどうか
	int color;

	int font = -1;		// font;

	int cnt = 240;

public:
	void SetMessage(char* me)
	{
		this->m = me;
	}
	void SetFont(int& font)
	{
		this->font = font;
	}

	void Render()
	{
		
		if (this->render)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->cnt);
			DrawFormatStringToHandle(this->x, this->y, color, this->font, this->m.c_str());
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		if (this->cnt > -1)
		{
			this->cnt--;
		}
	}
	void SetPointX(int x)
	{
		this->y = x;
	}
	void SetPointY(int y)
	{
		this->y = y;
	}
};

class MessageWindow extends Singleton<MessageWindow>
{
private:
	static const int RenderMax = 20 * 8;

	int start_x = 0, start_y = RenderMax;
	int end_x = SCREEN_CENTER_X / 2 , end_y = SCREEN_BOTTOM;
	int font;

	friend class Singleton<MessageWindow>;
public:
	std::vector<Message> message;

public:
	MessageWindow();
	~MessageWindow();

	void SetMessage(int msgColor, std::string fmt_str, ...);
	void Render();
};

