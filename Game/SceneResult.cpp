#include "SceneManager.h"
#include "SceneResult.h"
#include "Input.h"


Scene* SceneResult::Create()
{
	return{ new SceneResult() };
}

SceneResult::SceneResult()
{
	this->gh = LoadGraph("Resources/Textures/Result.png");
	this->font = CreateFontToHandle("HGS‘n‰pÌßÚ¾ÞÝ½EB", 32, -1);
}


SceneResult::~SceneResult()
{
}

void SceneResult::Update()
{
	InputManager& input = InputManager::singleton();
	if (input.key->GetDown(KEY_INPUT_SPACE))
	{
		SceneManager& manager = SceneManager::singleton();
		manager.RequestScene(SCENE_TITLE);
	}

	cnt++;
}

void SceneResult::Render()
{
	DrawGraph(0, 0, this->gh, true);

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
