#pragma warning(disable : 4244)
#include "Application.h"

void Application::Create()
{
	/* Create window */
	_Device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 16U, false, false, true, 0);
	_Driver = _Device->getVideoDriver();		//Get video driver
	_Manager = _Device->getSceneManager();		//Get scene manager

	/* Load config */
	this->LoadConfig();

	/* Create camera */
	_Camera = _Manager->addCameraSceneNodeMaya(0, -1500, 200, 1500, -1, _CameraDistance, true);
	_Camera->setFarValue(500000);
	_Camera->setTarget(irr::core::vector3df(_CameraTargetX, _CameraTargetY, _CameraTargetZ));

	/* Create Heightmap */
	WorldGenerator::Create(_WorldMapSizeX, _WorldMapSizeZ, "Data\\Heightmap.png", _WorldPeakDistance);

	_Terrain = _Manager->addTerrainSceneNode("Data\\Heightmap.png", 0, -1, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(_WorldScaleX, _WorldScaleY, _WorldScaleZ), irr::video::SColor(255, 255, 255, 255), 5, irr::scene::E_TERRAIN_PATCH_SIZE::ETPS_129, _WorldSmoothFactor, false);
	_Terrain->setPosition(irr::core::vector3df(_Terrain->getPosition().X + (_Terrain->getPosition().X - _Terrain->getBoundingBox().getCenter().X), 0, _Terrain->getPosition().Z + (_Terrain->getPosition().Z - _Terrain->getBoundingBox().getCenter().Z)));
	_Terrain->setMaterialTexture(0, _Driver->getTexture("Data\\hill_texture.jpg"));
	_Light = _Manager->addLightSceneNode(0, irr::core::vector3df(200, 1000, 200), irr::video::SColor(255, 255, 255, 255), _LightRadius, -1);

	/* Create ocean */
	_HillMesh = _Manager->addHillPlaneMesh("HillMesh", irr::core::dimension2d<irr::f32>(_WaterTileSizeX, _WaterTileSizeZ), irr::core::dimension2d<irr::u32>(_WaterTileAmountX, _WaterTileAmountZ), 0, 0, irr::core::dimension2d<irr::f32>(0, 0));
	_WaterSurface = _Manager->addWaterSurfaceSceneNode(_HillMesh, _WaterWaveHeight, _WaterWaveSpeed, _WaterWaveLength, 0, -1, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(_WaterScaleX, 1, _WaterScaleZ));
	_WaterSurface->setMaterialTexture(0, _Driver->getTexture("Data\\water_texture.jpg"));
	_WaterSurface->setPosition(irr::core::vector3df(_WaterSurface->getPosition().X + (_WaterSurface->getPosition().X - _WaterSurface->getBoundingBox().getCenter().X), _WaterHeight, _WaterSurface->getPosition().Z - (_WaterSurface->getPosition().Z - _WaterSurface->getBoundingBox().getCenter().Z)));
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

void Application::LoadConfig()
{
	std::cout << "Loading config: " << std::endl;
	std::vector<std::string> File;

	std::ifstream read("Data\\Config.txt");
	while (read.good()) //Read the whole config file
	{
		std::string line;		//Read the file line by line
		getline(read, line);	
		if (line[0] != '#' && line.find(' ') != std::string::npos)		//If a line is not a comment or an empty line
		{
			line.erase(line.begin(), line.begin() + line.find(' ') + 1);	//Erase the text
			File.push_back(line);											//Store it in the vector
			std::cout << line << std::endl;									//Print
		}
	}

	/* ################################ Ocean settings ################################ */

	/* The ocean consists of several tiles.How big should one tile be ? */
	_WaterTileSizeX = atoi(File[0].c_str());
	_WaterTileSizeZ = atoi(File[1].c_str());

	/* The amount of tiles the ocean should consist of */
	_WaterTileAmountX = atoi(File[2].c_str());
	_WaterTileAmountZ = atoi(File[3].c_str());

	/* Scale of the ocean */
	_WaterScaleX = atoi(File[4].c_str());
	_WaterScaleZ = atoi(File[5].c_str());

	/* The height where the ocean spawns.If the value is higher more landscape will be underwater */
	_WaterHeight = atoi(File[6].c_str());

	/* Wave settings */
	_WaterWaveLength = atoi(File[7].c_str());
	_WaterWaveHeight = atoi(File[8].c_str());
	_WaterWaveSpeed = atoi(File[9].c_str());

	/* ################################ Light ################################ */
	/* The light follows the camera.You can adjust how far it lights.The light has also a natural fall of. */
	_LightRadius = atoi(File[10].c_str());

	/* ################################ Camera ################################ */
	/* The target point of the camera */
	_CameraTargetX = atoi(File[11].c_str());
	_CameraTargetY = atoi(File[12].c_str());
	_CameraTargetZ = atoi(File[13].c_str());

	/* Defines how big the distance is between camera and target point */
	_CameraDistance = atoi(File[14].c_str());

	/* ################################ World ################################ */
	/* Defines how big the generated heightmap is(in pixels) */
	_WorldMapSizeX = atoi(File[15].c_str());
	_WorldMapSizeZ = atoi(File[16].c_str());

	/* Scale of the world */
	_WorldScaleX = atoi(File[17].c_str());
	_WorldScaleY = atoi(File[18].c_str());
	_WorldScaleZ = atoi(File[19].c_str());

	/* The minimal distance between two hills.Lower this value to get a fissured landscape. */
	_WorldPeakDistance = atoi(File[20].c_str());

	/* For smoothing the world edges  */
	_WorldSmoothFactor = atoi(File[21].c_str());
}