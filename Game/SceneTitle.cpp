#include "SceneManager.h"
#include "SceneTitle.h"
#include "Input.h"
#include "SoundManager.h"

Scene* SceneTitle::Create()
{
	return{ new SceneTitle() };
}

SceneTitle::SceneTitle()
{
	this->title_gh = LoadGraph("Resources/Textures/Title.png");
	this-> font = CreateFontToHandle("HGS‘n‰pÌßÚ¾ÞÝ½EB", 32, -1);

	SoundManager::singleton().SoundStop(TitleBGM);
	SoundManager::singleton().SoundPlay(TitleBGM, DX_PLAYTYPE_LOOP);
}


SceneTitle::~SceneTitle()
{
}

void SceneTitle::Update()
{
	InputManager& input = InputManager::singleton();
	if (input.key->GetDown(KEY_INPUT_SPACE))
	{
		SoundManager::singleton().SoundPlay(Decision, DX_PLAYTYPE_BACK);
		SceneManager& manager = SceneManager::singleton();
		manager.RequestScene(SCENE_PLAY);
	}
	cnt++;
}

void SceneTitle::Render()
{
	SetDrawBright(255, 255, 255);
	DrawGraph(0, 0, this->title_gh, true);

	if (cnt % 60 > 10)
	{
		DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Push to Space Key") - 4),
			SCREEN_CENTER_Y + SCREEN_CENTER_Y / 2 + 4,
			COLOR_BLACK, this->font, "Push to Space Key");
		DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Push to Space Key")),
			SCREEN_CENTER_Y + SCREEN_CENTER_Y / 2,
			COLOR_YELLOW, this->font, "Push to Space Key");
	}
}
