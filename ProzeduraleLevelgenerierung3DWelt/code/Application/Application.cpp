#include "Application.h"

void Application::Create()
{
	/* Create window */
	_Device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 16U, false, false, true, 0);
	_Driver = _Device->getVideoDriver();		//Get video driver
	_Manager = _Device->getSceneManager();		//Get scene manager

	/* Create camera */
	_Camera = _Manager->addCameraSceneNodeMaya(0, -1500, 200, 1500, -1, 5000, true);
	_Camera->setFarValue(500000);
	_Camera->setTarget(irr::core::vector3df(0, 50, 0));

	/* Create Heightmap */
	WorldGenerator::Create(2000, 2000, "Heightmap.png", 190);

	_Terrain = _Manager->addTerrainSceneNode("Heightmap.png", 0, -1, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 6, 3), irr::video::SColor(255, 255, 255, 255), 5, irr::scene::E_TERRAIN_PATCH_SIZE::ETPS_129, 10, false);
	_Terrain->setPosition(irr::core::vector3df(_Terrain->getPosition().X + (_Terrain->getPosition().X - _Terrain->getBoundingBox().getCenter().X), 0, _Terrain->getPosition().Z + (_Terrain->getPosition().Z - _Terrain->getBoundingBox().getCenter().Z)));
	_Light = _Manager->addLightSceneNode(0, irr::core::vector3df(200, 1000, 200), irr::video::SColor(255, 255, 255, 255), 5000, -1);

	/* Create ocean */
	_HillMesh = _Manager->addHillPlaneMesh("HillMesh", irr::core::dimension2d<irr::f32>(500, 500), irr::core::dimension2d<irr::u32>(200, 200), 0, 0, irr::core::dimension2d<irr::f32>(0, 0));
	_WaterSurface = _Manager->addWaterSurfaceSceneNode(_HillMesh, 50.0, 800, 100, 0, -1, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 1, 1));
	_WaterSurface->setMaterialTexture(0, _Driver->getTexture("water_texture.jpg"));
	_WaterSurface->setPosition(irr::core::vector3df(_WaterSurface->getPosition().X + (_WaterSurface->getPosition().X - _WaterSurface->getBoundingBox().getCenter().X), 10, _WaterSurface->getPosition().Z - (_WaterSurface->getPosition().Z - _WaterSurface->getBoundingBox().getCenter().Z)));
}

void Application::Run()
{
	while (_Device->run())
	{
		_Driver->beginScene(true, true, irr::video::SColor(100, 100, 100, 100));

		_Manager->drawAll();
		_Light->setPosition(_Camera->getPosition());

		_Driver->endScene();
	}
}