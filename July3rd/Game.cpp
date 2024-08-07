#include "MainWindow.h"
#include "Game.h"
#include "SpecularPhongPointScene.h"
#include "TestTriangle.h"
#include <sstream>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	scenes.push_back(std::make_unique<SpecularPhongPointScene>(gfx));
	curScene = scenes.begin();
	dt = ft.Mark();
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();

	dt = ft.Mark();
	std::wostringstream woss;
	int fps = static_cast<int>(1.0f / dt);
	woss << L"Hoang DirectX Framework  FPS: " << fps;
	std::wstring title = woss.str();

	// Set the window title
	SetWindowText(wnd.hWnd, title.c_str());
}

void Game::UpdateModel()
{
	// cycle through scenes when tab is pressed
	while (!wnd.kbd.KeyIsEmpty()) {
		// update scene
		const auto e = wnd.kbd.ReadKey();
		if (e.GetCode() == VK_ESCAPE && e.IsPress())
		{
			wnd.Kill();
		}
	}
	(*curScene)->Update(wnd.kbd, wnd.mouse, dt);
}

void Game::ComposeFrame()
{
	(*curScene)->Draw();
}

void Game::CycleScenes()
{
	if (++curScene == scenes.end())
	{
		curScene = scenes.begin();
	}
}

void Game::OutputSceneName() const
{
	std::stringstream ss;
	const std::string stars((*curScene)->GetName().size() + 4, '*');

	ss << stars << std::endl
		<< "* " << (*curScene)->GetName() << " *" << std::endl
		<< stars << std::endl;
	OutputDebugStringA(ss.str().c_str());
}