#include "DemoScene.h"

#include "SceneManager.h"
#include "SoundManager.h"

Scene * DemoScene::Create()
{
	return{ new DemoScene() };
}

DemoScene::DemoScene()
{
	this->gh = LoadGraph("Resources/Textures/MyIcon.png");
	
	this->rotate = 0;
}


DemoScene::~DemoScene()
{
}

void DemoScene::Update()
{
	if (this->rotate < 180)
	{
		this->bright += (255.0f / 180.0f);
	}
	else if (this->rotate >= 180)
	{
		this->bright -= (255.0f / 180.0f);
	}

	if (static_cast<int>(this->rotate) == 2)
	{
		SoundManager::singleton().SoundPlay(Demo, DX_PLAYTYPE_BACK);
	}

	this->rotate += 2.0f;
	if (this->rotate > 360.0f)
	{
		SceneManager& manager = SceneManager::singleton();
		manager.RequestScene(SCENE_TITLE);
		
	}
}

void DemoScene::Render()
{
	SetDrawBright(this->bright, this->bright, this->bright);
	DrawBox(0, 0, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_WHITE, true);
	DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y, 2.0, (DEG_TO_RAD(this->rotate)), this->gh, true);
}
