#include "MainWindow.h"
#include "Game.h"
#include "Mat2.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	const float dTheta = 2.0f * PI / float(nflares * 2);
	for (int i = 0; i < nflares * 2; i++)
	{
		const float rad = (i % 2 == 0) ? radOuter : radInner;
		star.emplace_back(
			rad * cos(float(i) * dTheta),
			rad * sin(float(i) * dTheta)
		);
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		theta += vRot;
	}
}

void Game::ComposeFrame()
{
	//gfx.PutPixel(100, 100, 255, 255, 255);
	const Vec2 trl = { float(gfx.ScreenWidth) / 2.0f,float(gfx.ScreenHeight) / 2.0f };
	const Mat2 trf = Mat2::Rotation(theta) * Mat2::Scaling(size);
	auto vtx(star);
	for (auto& v : vtx)
	{
		v *= trf;
		v += trl;
	}
	for (auto i = vtx.cbegin(), end = std::prev(vtx.cend()); i != end; i++)
	{
		gfx.DrawLine(*i, *std::next(i), Colors::Red);
	}
	gfx.DrawLine(vtx.front(), vtx.back(), Colors::Red);
}