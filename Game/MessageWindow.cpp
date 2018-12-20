#include "MessageWindow.h"



MessageWindow::MessageWindow()
{
	this->font = CreateFontToHandle("HGS�n�p��ھ�ݽEB", 16, -1);
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
	me.m = result;
	me.x = this->start_x;
	me.y = this->end_y - 20;
	me.SetFont(this->font);
	me.color = msgColor;

	for (int i = 0; i < this->message.size(); i++)
	{
		this->message[i].y -= 20;
	}

	this->message.push_back(me);
}

void MessageWindow::Render()
{
	for (int i = 0; i < this->message.size(); i++)
	{
		int y = message[i].y;
		if (y >= MessageWindow::RenderMax)
		{
			this->message[i].Render();
		}
		else
		{
			this->message.erase(this->message.begin() + i);
		}
	}

}
