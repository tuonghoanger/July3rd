#include "MainWindow.h"
#include "Game.h"
#include "Mat2.h"
#include "CubeSkinnedScene.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	scenes.push_back(std::make_unique<CubeSkinnedScene>(L"images\\dice_skin.png"));
	scenes.push_back(std::make_unique<TexCubeScene>());
	scenes.push_back(std::make_unique<SolidCubeScene>());
	curScene = scenes.begin();

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
	const float dt = 1.0f / 60.0f;
		// cycle through scenes when tab is pressed
		while (!wnd.kbd.KeyIsEmpty()) {
			// update scene
			const auto e = wnd.kbd.ReadKey();
			if (e.GetCode() == VK_TAB && e.IsPress())
			{
				CycleScenes();
			}
		}
		(*curScene)->Update(wnd.kbd, wnd.mouse, dt);
}

void Game::ComposeFrame()
{
	(*curScene)->Draw(gfx);
}

void Game::CycleScenes()
{
	if (++curScene == scenes.end())
	{
		curScene = scenes.begin();
	}
}