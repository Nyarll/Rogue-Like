#include "MessageWindow.h"



MessageWindow::MessageWindow()
{
	this->font = CreateFontToHandle("HGS‘n‰pÌßÚ¾ÞÝ½EB", 16, -1);
}


MessageWindow::~MessageWindow()
{
}

void MessageWindow::SetMessage(int msgColor, std::string fmt_str, ...)
{
	int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
	std::unique_ptr<char[]> formatted;
	va_list ap;
	while (1)
	{
		formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
		strcpy(&formatted[0], fmt_str.c_str());
		va_start(ap, fmt_str);
		final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
		va_end(ap);
		if (final_n < 0 || final_n >= n)
			n += abs(final_n - n + 1);
		else
			break;
	}
	std::string result = std::string(formatted.get());

	Message me;
	me.SetMessage(result);
	me.SetPointX(this->start_x);
	me.SetPointY(this->end_y - 20);
	me.SetFont(this->font);
	me.SetColor(msgColor);

	for (int i = 0; i < this->message.size(); i++)
	{
		this->message[i].SetPointY(this->message[i].GetPointY() - 20);
	}

	this->message.push_back(me);
}

void MessageWindow::Render()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(this->start_x, this->start_y, 400, this->end_y, COLOR_BLACK, true);
	DrawBox(this->start_x, this->start_y, 400, this->end_y, COLOR_RED, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0; i < this->message.size(); i++)
	{
		int y = message[i].GetPointY();
		if (y >= MessageWindow::RenderMax)
		{
			this->message[i].Render();
		}
		else
		{
			this->message.erase(this->message.begin() + i);
		}

		if (this->message[i].GetAlive() == false)
		{
			this->message.erase(this->message.begin() + i);
		}
	}

}
