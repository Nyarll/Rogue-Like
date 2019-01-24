#include "SceneManager.h"
#include "SceneResult.h"
#include "Input.h"
#include "SoundManager.h"

#include "Score.h"


Scene* SceneResult::Create()
{
	return{ new SceneResult() };
}

SceneResult::SceneResult()
{
	this->gh = LoadGraph("Resources/Textures/Result.png");
	this->font = CreateFontToHandle("HGS‘n‰pÌßÚ¾ÞÝ½EB", 32, -1);
	SoundManager::singleton().SoundStop(GameBGM);
	SoundManager::singleton().SoundPlay(TitleBGM, DX_PLAYTYPE_LOOP);
}


SceneResult::~SceneResult()
{
}

void SceneResult::Update()
{
	InputManager& input = InputManager::singleton();
	
	if (input.key->GetDown(KEY_INPUT_RETURN))
	{
		SceneManager& manager = SceneManager::singleton();
		SoundManager::singleton().SoundPlay(Decision, DX_PLAYTYPE_BACK);
		manager.RequestScene(SCENE_TITLE);
	}

	cnt++;
}

void SceneResult::Render()
{
	DrawGraph(0, 0, this->gh, true);

	DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Floor : ")) + 4, SCREEN_CENTER_Y + 4,
		COLOR_BLACK, this->font, "Floor : %d", Score::singleton().GetScoreFloor());
	DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Floor :")), SCREEN_CENTER_Y,
		COLOR_WHITE, this->font, "Floor : %d", Score::singleton().GetScoreFloor());

	DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Level : ")) + 4, SCREEN_CENTER_Y + 40 + 4,
		COLOR_BLACK, this->font, "Level : %d", Score::singleton().GetScoreLevel());
	DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Level :")), SCREEN_CENTER_Y + 40,
		COLOR_WHITE, this->font, "Level : %d", Score::singleton().GetScoreLevel());

	if (cnt % 60 > 10)
	{
		DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Push to Enter Key") - 4),
			SCREEN_CENTER_Y + SCREEN_CENTER_Y / 2 + 4,
			COLOR_BLACK, this->font, "Push to Enter Key");
		DrawFormatStringToHandle(SCREEN_CENTER_X - (7 * sizeof("Push to Enter Key")),
			SCREEN_CENTER_Y + SCREEN_CENTER_Y / 2,
			COLOR_YELLOW, this->font, "Push to Enter Key");
	}
}
