#include "MainWindow.h"
#include "Game.h"
#include "Mat2.h"
#include "CubeSkinScene.h"
#include "CubeVertexColorScene.h"
#include "CubeSolidScene.h"
#include "VertexWaveScene.h"
#include "CubeVertexPositionColorScene.h"
#include "CubeSolidGeometryScene.h"
#include "CubeFlatIndependentScene.h"
#include "GeometryFlatScene.h"
#include "Sphere.h"
#include "GouraudScene.h"
#include "GouraudPointScene.h"
#include "PhongPointScene.h"
#include "SpecularPhongPointScene.h"
#include <sstream>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	scenes.push_back(std::make_unique<SpecularPhongPointScene>(gfx, IndexedTriangleList<SpecularPhongPointScene::Vertex>::LoadNormals("models\\suzanne.obj")));
	//scenes.push_back(std::make_unique<PhongPointScene>(gfx, IndexedTriangleList<PhongPointScene::Vertex>::LoadNormals("models\\suzanne.obj")));
	scenes.push_back(std::make_unique<PhongPointScene>(gfx, Plane::GetNormals<PhongPointScene::Vertex>()));
	//scenes.push_back(std::make_unique<GouraudPointScene>(gfx, IndexedTriangleList<GouraudPointScene::Vertex>::LoadNormals("models\\suzanne.obj")));
	//scenes.push_back(std::make_unique<GouraudScene>(gfx, IndexedTriangleList<GouraudScene::Vertex>::LoadNormals("models\\suzanne.obj")));
	//scenes.push_back(std::make_unique<GouraudScene>(gfx, Sphere::GetPlainNormals<GouraudScene::Vertex>()));
	//scenes.push_back(std::make_unique<GeometryFlatScene>(gfx, Sphere::GetPlain<GeometryFlatScene::Vertex>(1.0f,36,72)));
	scenes.push_back(std::make_unique<PhongPointScene>(gfx, IndexedTriangleList<PhongPointScene::Vertex>::LoadNormals("models\\suzanne.obj")));

	scenes.push_back(std::make_unique<GeometryFlatScene>(gfx,
		IndexedTriangleList<GeometryFlatScene::Vertex>::Load("models\\bunny.obj")));
	scenes.push_back(std::make_unique<CubeFlatIndependentScene>(gfx));
	scenes.push_back(std::make_unique<VertexWaveScene>(gfx));
	scenes.push_back(std::make_unique<CubeSolidGeometryScene>(gfx));
	scenes.push_back(std::make_unique<CubeVertexPositionColorScene>(gfx));
	scenes.push_back(std::make_unique<CubeSkinScene>(gfx, L"images\\dice_skin.png"));
	scenes.push_back(std::make_unique<CubeVertexColorScene>(gfx));
	//scenes.push_back(std::make_unique<CubeSolidScene>(gfx));
	curScene = scenes.begin();
	OutputSceneName();

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
	const float dt = ft.Mark();
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