#include "Score.h"
#include "Define.h"
#include "MessageWindow.h"

void Score::Save(Player* player, int floor)
{
	this->data.floor = floor;
	this->data.level = player->GetLevel();
	this->data.hp_max = player->GetMaxHP();
	this->data.hp_now = player->GetNowHP();
	this->data.ATK = player->GetATK();
	this->data.DEF = player->GetDEF();
	this->data.exp = player->GetExp();
	this->data.next_exp = player->GetNextExp();

	for (int i = 0; i < ItemTypeNum; i++)
	{
		this->data.inventry[i] = player->GetItemNum(i);
	}

	if (!this->PlayerDataFileOutput())
	{
		MessageWindow::singleton().SetMessage(0xffff0000, "セーブに失敗しました...");
	}
	else
	{
		MessageWindow::singleton().SetMessage(0xff00ffff, "セーブに成功しました...");
	}
}

bool Score::Load(int & floor, int & level, int & hp_max, int & hp_now, int & ATK, int & DEF, int & exp, int & next_exp, int inventry[ItemTypeNum])
{
	if (!this->PlayerDataFileInput())
	{
		MessageWindow::singleton().SetMessage(0xffff0000, "ファイルを読み込めませんでした...");
		return false;
	}
	floor = this->data.floor;
	level = this->data.level;
	hp_max = this->data.hp_max;
	hp_now = this->data.hp_now;
	ATK = this->data.ATK;
	DEF = this->data.DEF;
	exp = this->data.exp;
	next_exp = this->data.next_exp;
	for (int i = 0; i < ItemTypeNum; i++)
	{
		inventry[i] = this->data.inventry[i];
	}
	MessageWindow::singleton().SetMessage(0xff00ffff, "データをロードしました...");
	return true;
}


bool Score::PlayerDataFileOutput()
{
	std::ofstream ofs;
	ofs.open("Resources/SaveData.dat");

	if (!ofs)	// 開けなかった場合
	{
		std::ofstream create;
		create.open("Resources/SaveData.dat");
		create.close();
		ofs.open("Resources/SaveData.dat");
		if (!ofs)
		{
			return false;
		}
	}
	ofs << this->data.floor << std::endl;
	ofs << this->data.level << std::endl;
	ofs << this->data.hp_max << std::endl;
	ofs << this->data.hp_now << std::endl;
	ofs << this->data.ATK << std::endl;
	ofs << this->data.DEF << std::endl;
	ofs << this->data.exp << std::endl;
	ofs << this->data.next_exp << std::endl;
	for (int i = 0; i < ItemTypeNum; i++)
	{
		ofs << this->data.inventry[i] << std::endl;
	}
	ofs.close();
	return true;
}

bool Score::PlayerDataFileInput()
{
	std::ifstream ifs;
	ifs.open("Resources/SaveData.dat");
	if (!ifs)
	{
		return false;
	}
	std::string line;
	int in_data = 0;

	std::getline(ifs, line);
	this->data.floor = std::stoi(line);
	std::getline(ifs, line);
	this->data.level = std::stoi(line);
	std::getline(ifs, line);
	this->data.hp_max = std::stoi(line);
	std::getline(ifs, line);
	this->data.hp_now = std::stoi(line);
	std::getline(ifs, line);
	this->data.ATK = std::stoi(line);
	std::getline(ifs, line);
	this->data.DEF = std::stoi(line);
	std::getline(ifs, line);
	this->data.exp = std::stoi(line);
	std::getline(ifs, line);
	this->data.next_exp = std::stoi(line);
	for (int i = 0; i < ItemTypeNum; i++)
	{
		std::getline(ifs, line);
		this->data.inventry[i] = std::stoi(line);
	}
	return true;
}
