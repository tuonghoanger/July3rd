#pragma once

#include "Graphics.h"
#include <vector>
#include "ChiliMath.h"
#include "Cube.h"
#include "ScreenTransformer.h"
#include "Mat3.h"
#include <memory>
#include "Scene.h"
#include "SolidCubeScene.h"
#include "TexCubeScene.h"

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
	void CycleScenes();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::vector<std::unique_ptr<Scene>> scenes;
	std::vector<std::unique_ptr<Scene>>::iterator curScene;
	/********************************/
};