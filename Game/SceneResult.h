#pragma once
#include "Scene.h"

class SceneResult : public Scene
{
private:
	int gh;

	int font;

	int cnt = 0;

public:
	static Scene* Create();

	SceneResult();
	~SceneResult();

public:
	// ‘€ì
	void Initialize()override {};
	void Update()override;
	void Render()override;
	void Finalize()override {};
};

