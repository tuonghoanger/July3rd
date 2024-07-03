#include "MainWindow.h"
#include "Game.h"
#include "Mat2.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	cube(1.0f)
{
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

	}
}

void Game::ComposeFrame()
{
	IndexedLineList lines = cube.GetLines();
	for (Vec3& v : lines.vertices)
	{
		v += {0.0f, 0.0f, 1.0f};
		pst.Transform(v);
	}
	for (auto i = lines.indices.cbegin(),
		end = lines.indices.cend();
		i != end; std::advance(i, 2))
	{
		gfx.DrawLine(lines.vertices[*i], lines.vertices[*std::next(i)], Colors::White);
	}

}