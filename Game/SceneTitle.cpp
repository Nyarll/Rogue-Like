#include "SceneManager.h"
#include "SceneTitle.h"
#include "Input.h"
#include "SoundManager.h"

#include "Score.h"

Scene* SceneTitle::Create()
{
	return{ new SceneTitle() };
}

SceneTitle::SceneTitle()
{
	this->title_gh = LoadGraph("Resources/Textures/Title.png");
	this->cursor_gh = LoadGraph("Resources/Textures/cursor.png");
	this-> font = CreateFontToHandle("HGS‘n‰pÌßÚ¾ÞÝ½EB", 32, -1);

	SoundManager::singleton().SoundStop(TitleBGM);
	SoundManager::singleton().SoundPlay(TitleBGM, DX_PLAYTYPE_LOOP);

	this->cursor.x = SCREEN_CENTER_X - SCREEN_CENTER_X / 2;
	this->cursor.y = SCREEN_CENTER_Y;
}


SceneTitle::~SceneTitle()
{
}

void SceneTitle::Update()
{
	InputManager& input = InputManager::singleton();
	if (!this->menu)
	{
		if (input.key->GetDown(KEY_INPUT_SPACE))
		{
			SoundManager::singleton().SoundPlay(Decision, DX_PLAYTYPE_BACK);
			this->menu = true;
			//SceneManager& manager = SceneManager::singleton();
			//manager.RequestScene(SCENE_PLAY);
		}
	}
	else
	{
		if (input.key->GetDown(KEY_INPUT_UP))
		{
			this->cursor.y = SCREEN_CENTER_Y;
		}
		else if (input.key->GetDown(KEY_INPUT_DOWN))
		{
			this->cursor.y = SCREEN_CENTER_Y + 64;
		}

		if (input.key->GetDown(KEY_INPUT_RETURN))
		{
			Score& sc = Score::singleton();
			if (this->cursor.y == SCREEN_CENTER_Y)
				sc.SetLoadFlag(true);

			SceneManager& manager = SceneManager::singleton();
			manager.RequestScene(SCENE_PLAY);
		}
	}
	cnt++;
}

void SceneTitle::Render()
{
	SetDrawBright(255, 255, 255);
	DrawGraph(0, 0, this->title_gh, true);

	if (cnt % 60 > 10)
	{
		if (!this->menu)
		{
			DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Push to Space Key") - 4),
				SCREEN_CENTER_Y + SCREEN_CENTER_Y / 2 + 4,
				COLOR_BLACK, this->font, "Push to Space Key");
			DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Push to Space Key")),
				SCREEN_CENTER_Y + SCREEN_CENTER_Y / 2,
				COLOR_YELLOW, this->font, "Push to Space Key");
		}
		else
		{
			DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Push to Enter Key") - 4),
				SCREEN_CENTER_Y + SCREEN_CENTER_Y / 2 + 4,
				COLOR_BLACK, this->font, "Push to Enter Key");
			DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Push to Enter Key")),
				SCREEN_CENTER_Y + SCREEN_CENTER_Y / 2,
				COLOR_YELLOW, this->font, "Push to Enter Key");
		}
	}
	if (this->menu)
	{
		UINT color1 = COLOR_WHITE, color2 = COLOR_WHITE;
		DrawRotaGraph(this->cursor.x, this->cursor.y, 1.0, (270.0 * (3.141592653589793238 / 180.0)), this->cursor_gh, true);

		if (this->cursor.y == SCREEN_CENTER_Y)
			color1 = COLOR_YELLOW;
		if (this->cursor.y == SCREEN_CENTER_Y + 64)
			color2 = COLOR_YELLOW;

		DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("‘±‚«‚©‚ç") - 4),
			SCREEN_CENTER_Y + 4 - 16,
			COLOR_BLACK, this->font, "‘±‚«‚©‚ç");
		DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("‘±‚«‚©‚ç")),
			SCREEN_CENTER_Y - 16,
			color1, this->font, "‘±‚«‚©‚ç");

		DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Å‰‚©‚ç") - 4),
			SCREEN_CENTER_Y + 4 - 16 + 64,
			COLOR_BLACK, this->font, "Å‰‚©‚ç");
		DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Å‰‚©‚ç")),
			SCREEN_CENTER_Y - 16 + 64,
			color2, this->font, "Å‰‚©‚ç");

	}
}
