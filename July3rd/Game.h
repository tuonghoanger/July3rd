#pragma once

#include "Graphics.h"
#include <vector>
#include "ChiliMath.h"
#include "Cube.h"
#include "ScreenTransformer.h"

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
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	ScreenTransformer pst;
	Cube cube;
	/********************************/
};