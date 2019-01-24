#pragma once

#include "Scene.h"

class SceneTitle : public Scene
{
private:
	int title_gh;
	int cursor_gh;

	int font;

	int cnt = 0;

	bool menu = false;

	struct
	{
		int x, y;
	}cursor;

public:
	static Scene* Create();

	SceneTitle();
	~SceneTitle();

public:
	// ëÄçÏ
	void Initialize()override {};
	void Update()override;
	void Render()override;
	void Finalize()override {};
};

