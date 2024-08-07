#pragma once

#include "Graphics.h"
#include <vector>
#include "ChiliMath.h"
#include "Cube.h"
#include "ScreenTransformer.h"
#include "Mat.h"
#include <memory>
#include "Scene.h"
#include "FrameTimer.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void OutputSceneName() const;
	void CycleScenes();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	FrameTimer ft;
	float dt;
	std::vector<std::unique_ptr<Scene>> scenes;
	std::vector<std::unique_ptr<Scene>>::iterator curScene;
	/********************************/
};