#include "WorldGenerator.h"

void WorldGenerator::Create(unsigned int Width, int unsigned Height, std::string Filename, unsigned int StartPeakDistance)
{
	if (Width < 100 || Height < 100)
	{
		std::cout << "Heightmap should be at least 100 pixel wide and high" << std::endl;
		return;
	}
	if (StartPeakDistance >= Width)
	{
		std::cout << "StartPeakDistance can not be bigger than the heightmap" << std::endl;
		return;
	}

	srand(static_cast<unsigned int>(time(NULL)));

	sf::Image HeightMap;
	HeightMap.create(Width, Height);

	for (unsigned int y = 5; y < Height; y = y + StartPeakDistance)			//Set some random values
	{
		for (unsigned int x = 5; x < Width; x = x + StartPeakDistance)
		{
			if (y >= Height || x >= Width) //Check if x or y is out of range
			{
				return;
			}

			int RandomHeight = rand() % 255;
			HeightMap.setPixel(x, y, sf::Color(RandomHeight));
		}
	}

	HeightMap.saveToFile(Filename.c_str());
}