#include "Application.h"

void Application::Create()
{
	/* Create window */
	_Device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 16U, false, false, true, 0);
	_Driver = _Device->getVideoDriver();		//Get video driver
	_Manager = _Device->getSceneManager();		//Get scene manager

	/* Create camera */
	_Camera = _Manager->addCameraSceneNodeFPS();
	_Camera->setFarValue(1000000);

	/* Create Heightmap */
	WorldGenerator::Create(1213, 1729, "Heightmap.png", 150);

	_Terrain = _Manager->addTerrainSceneNode("Heightmap.png", 0, -1, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 5, 3));
	_Light = _Manager->addLightSceneNode(0, irr::core::vector3df(0, 1000, 0), irr::video::SColor(255, 255, 255, 255), 2000, -1);
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