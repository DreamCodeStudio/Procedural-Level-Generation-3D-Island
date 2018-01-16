#include "Application.h"

void Application::Create()
{
	/* Create window */
	_Device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 16U, false, false, true, 0);
	_Driver = _Device->getVideoDriver();		//Get video driver
	_Manager = _Device->getSceneManager();		//Get scene manager

	/* Create camera */
	_Camera = _Manager->addCameraSceneNodeFPS();

	/* Create Heightmap */
	WorldGenerator::Create(100, 100, "Heightmap.png", 10);
}

void Application::Run()
{
	while (_Device->run())
	{
		_Driver->beginScene(true, true, irr::video::SColor(100, 100, 100, 100));

		_Manager->drawAll();

		_Driver->endScene();
	}
}