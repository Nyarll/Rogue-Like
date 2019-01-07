#pragma once
#include "Define.h"
#include "Singleton.h"

class Message
{
private:
	int x, y;			// 表示箇所
	std::string m;			// 表示内容
	bool render = true;	// 表示するかどうか
	int color;

	int font = -1;		// font;

	float cnt = 240;

public:
	void SetMessage(std::string& me)
	{
		this->m = me;
	}
	void SetFont(int& font)
	{
		this->font = font;
	}

	bool GetAlive() { return this->render; }

	void Render()
	{

		if (this->render)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->cnt);
			DrawFormatStringToHandle(this->x + 3, this->y + 3, COLOR_BLACK, this->font, this->m.c_str());
			DrawFormatStringToHandle(this->x, this->y, color, this->font, this->m.c_str());
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		if (this->cnt > -1)
		{
			this->cnt -= 0.5;
		}
	}
	void SetPointX(const int& x) { this->x = x; }
	void SetPointY(const int& y) { this->y = y; }
	int GetPointX() { return this->x; }
	int GetPointY() { return this->y; }

	void SetColor(const int& color) { this->color = color; };
};

class MessageWindow extends Singleton<MessageWindow>
{
private:
	static const int RenderMax = 20 * 8;

	int start_x = 0, start_y = RenderMax;
	int end_x = SCREEN_CENTER_X, end_y = SCREEN_BOTTOM;
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

