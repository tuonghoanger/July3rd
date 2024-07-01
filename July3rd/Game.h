#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include <vector>
#include "ChiliMath.h"

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
	std::vector<Vec2> star;
	float theta = 0.0f;
	static constexpr float vRot = PI / 270.0f;
	static constexpr float radInner = 1.0f;
	static constexpr float radOuter = 2.0f;
	static constexpr int nflares = 5;
	static constexpr float size = 100.0f;
	/********************************/
};