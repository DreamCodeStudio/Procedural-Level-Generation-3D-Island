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

		void LoadConfig();
		void CreateWorld();

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
		int _WaterTileSizeX, _WaterTileSizeZ;
		int _WaterTileAmountX, _WaterTileAmountZ;
		int _WaterScaleX, _WaterScaleZ;
		int _WaterWaveLength, _WaterWaveHeight, _WaterWaveSpeed;
		int _WaterHeight;

		/* Camera */
		float _CameraTargetX, _CameraTargetY, _CameraTargetZ;
		float _CameraDistance;

		/* Light */
		int _LightRadius;
		int _LightPositionX, _LightPositionY, _LightPositionZ;
		bool _LightIsFollowing;

		/* World */
		int _WorldMapSizeX, _WorldMapSizeZ;
		int _WorldScaleX, _WorldScaleY, _WorldScaleZ;
		int _WorldPeakDistance;
		int _WorldSmoothFactor;
		

};