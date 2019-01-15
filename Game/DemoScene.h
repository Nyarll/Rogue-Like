#pragma once
#include "Scene.h"

class DemoScene : public Scene
{
public:
	static Scene* Create();

	DemoScene();
	~DemoScene();

private:
	int gh;
	float rotate = 0;

	float bright = 0;

public:
	// ëÄçÏ
	void Initialize()override {};
	void Update()override;
	void Render()override;
	void Finalize()override {};
};

