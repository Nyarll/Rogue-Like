#pragma once

#include "Scene.h"

class SceneTitle : public Scene
{
private:
	int title_gh;

	int font;

	int cnt = 0;

public:
	static Scene* Create();

	SceneTitle();
	~SceneTitle();

public:
	// ‘€ì
	void Initialize()override {};
	void Update()override;
	void Render()override;
	void Finalize()override {};
};

