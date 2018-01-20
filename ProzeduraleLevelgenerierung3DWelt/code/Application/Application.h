#pragma once
#include <irrlicht.h>

/* WorldGenerator */
#include "WorldGenerator\WorldGenerator.h"

/* For loading config file */
#include <fstream>

class Application
{
	public:

		void Create();

		void Run();

	private:

		/* Create window */
		irr::IrrlichtDevice *_Device;
		irr::video::IVideoDriver *_Driver;
		irr::scene::ISceneManager *_Manager;

		/* User */
		irr::scene::ICameraSceneNode *_Camera;
		irr::scene::ITerrainSceneNode *_Terrain;
		irr::scene::ILightSceneNode *_Light;
		irr::scene::IAnimatedMesh *_HillMesh;
		irr::scene::ISceneNode *_WaterSurface;

		/* Config */
		
		/* Water */
		int _WaterTileSizeX, _WaterTileSizeY;
		int _WaterTileAmountX, _WaterTileAmountY;
		int _WaterScaleX, _WaterScaleY;
		int _WaterWaveLength, _WaterWaveHeight, _WaterWaveSpeed;

		/* Camera */
		float _CameraTargetX, _CameraTargetY, _CameraTargetZ;
		float _CameraDistance;

		/* Light */
		int _LightRadius;

		/* World */
		int _WorldMapSizeX, _WorldMapSizeY;
		int _WorldScaleX, _WorldScaleY, _WorldScaleZ;
		int _WorldPeakDistance;
		int _WorldSmoothFactor;
		

};