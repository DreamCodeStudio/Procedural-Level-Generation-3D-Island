#include "IVoxelTerrainSceneNode.h"

IVoxelTerrainSceneNode::IVoxelTerrainSceneNode(irr::scene::ISceneManager *Manager, irr::core::vector3df Scale, std::string HeightmapPath, int MapSizeX, int MapSizeZ, float CubeSize)
{
	sf::Image Heightmap;
	Heightmap.loadFromFile(HeightmapPath);

	for (unsigned int z = 0; z < Heightmap.getSize().y; z = z + 4)
	{
		for (unsigned int x = 0; x < Heightmap.getSize().x; x = x + 4)
		{
			if (z > Heightmap.getSize().y || x > Heightmap.getSize().x)
			{
				break;
			}

			irr::scene::ISceneNode *cube = Manager->addCubeSceneNode(CubeSize, 0, -1, irr::core::vector3df((x * Scale.X) - (MapSizeX * Scale.X) / 2, static_cast<float>(static_cast<int>(Heightmap.getPixel(x, z).r) * Scale.Y), (z * Scale.Z) - (MapSizeZ * Scale.Z) / 2));
			cube->setMaterialTexture(0, Manager->getVideoDriver()->getTexture("Data\\hill_texture.jpg"));
		}
	}
}