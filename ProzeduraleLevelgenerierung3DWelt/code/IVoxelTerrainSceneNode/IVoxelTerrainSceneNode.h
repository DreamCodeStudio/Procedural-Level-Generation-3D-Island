#pragma once
#include <iostream>
#include <vector>

/* Engine */
#include <irrlicht.h>
#include <SFML\Graphics.hpp>

class IVoxelTerrainSceneNode
{
	public:

		IVoxelTerrainSceneNode(irr::scene::ISceneManager *Manager, irr::core::vector3df Scale, std::string HeightmapPath, int MapSizeX, int MapSizeZ, float CubeSize);

	private:

};