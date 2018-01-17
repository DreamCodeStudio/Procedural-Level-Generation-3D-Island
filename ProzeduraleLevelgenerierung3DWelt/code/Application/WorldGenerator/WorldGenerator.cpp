#pragma warning(disable : 4244)
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

	for (unsigned int y = StartPeakDistance; y < Height; y = y + StartPeakDistance)			//Set some random values
	{
		for (unsigned int x = StartPeakDistance; x < Width; x = x + StartPeakDistance)
		{
			if (y >= Height || x >= Width) //Check if x or y is out of range
			{
				break;
			}

			int RandomHeight = rand() % 255;
			HeightMap.setPixel(x, y, sf::Color(RandomHeight, RandomHeight, RandomHeight));
		}
	}

	/* Interpolation on X-axis */
	for (unsigned int y = StartPeakDistance; y < Height; y = y + StartPeakDistance)			//Set some random values
	{
		for (unsigned int x = StartPeakDistance; x < Width; x = x + StartPeakDistance)
		{
			if (y >= Height || x >= Width) //Check if x or y is out of range
			{
				break;
			}

			float InterplationValue = (static_cast<int>(HeightMap.getPixel(x, y).r) - static_cast<int>(HeightMap.getPixel(x - StartPeakDistance, y).r)) / static_cast<float>(StartPeakDistance);

			for (unsigned int c = StartPeakDistance - 1; c > 0; c--)
			{
				HeightMap.setPixel(x - c, y, sf::Color(static_cast<int>(HeightMap.getPixel(x - StartPeakDistance, y).r) + InterplationValue * (StartPeakDistance - c), 
													   static_cast<int>(HeightMap.getPixel(x - StartPeakDistance, y).r) + InterplationValue * (StartPeakDistance - c), 
													   static_cast<int>(HeightMap.getPixel(x - StartPeakDistance, y).r) + InterplationValue * (StartPeakDistance - c)));
			}
		}
	}

	for (unsigned int y = StartPeakDistance; y < Height; y = y + StartPeakDistance)			//Set some random values
	{
		float counter = 1;
		for (unsigned int x = Width - StartPeakDistance + 1; x < Width; x++)
		{
			float InterpolationValue = (static_cast<int>(HeightMap.getPixel(Width - StartPeakDistance, y).r) * -1) / static_cast<float>((StartPeakDistance - 1));
			HeightMap.setPixel(x, y, sf::Color(static_cast<int>(HeightMap.getPixel(Width - StartPeakDistance, y).r) + InterpolationValue * counter,
											   static_cast<int>(HeightMap.getPixel(Width - StartPeakDistance, y).r) + InterpolationValue * counter,
											   static_cast<int>(HeightMap.getPixel(Width - StartPeakDistance, y).r) + InterpolationValue * counter));

			counter++;
		}
	}

	/* Interpolation on Y-axis */
	for (unsigned int y = StartPeakDistance; y < Height; y = y + StartPeakDistance)			//Set some random values
	{
		for (unsigned int x = 0; x < Width; x++)
		{
			if (y >= Height || x >= Width) //Check if x or y is out of range
			{
				break;
			}

			float InterplationValue = (static_cast<int>(HeightMap.getPixel(x, y).r) - static_cast<int>(HeightMap.getPixel(x, y - StartPeakDistance).r)) / static_cast<float>(StartPeakDistance);

			for (unsigned int c = StartPeakDistance - 1; c > 0; c--)
			{
				HeightMap.setPixel(x, y - c, sf::Color(static_cast<int>(HeightMap.getPixel(x, y - StartPeakDistance).r) + InterplationValue * (StartPeakDistance - c),
													   static_cast<int>(HeightMap.getPixel(x, y - StartPeakDistance).r) + InterplationValue * (StartPeakDistance - c),
													   static_cast<int>(HeightMap.getPixel(x, y - StartPeakDistance).r) + InterplationValue * (StartPeakDistance - c)));
			}
		}
	} 

	for (unsigned int x = 0; x < Width; x++)
	{
		float counter = 1;
		for (unsigned int y = Height - StartPeakDistance + 1; y < Height; y++)			//Set some random values
		{
			float InterpolationValue = (static_cast<int>(HeightMap.getPixel(x, Height - StartPeakDistance).r) * -1) / static_cast<float>((StartPeakDistance - 1));

			HeightMap.setPixel(x, y, sf::Color(static_cast<int>(HeightMap.getPixel(x, Height - StartPeakDistance).r) + InterpolationValue * counter,
											   static_cast<int>(HeightMap.getPixel(x, Height - StartPeakDistance).r) + InterpolationValue * counter,
											   static_cast<int>(HeightMap.getPixel(x, Height - StartPeakDistance).r) + InterpolationValue * counter));

			counter++;
		}
	}


	HeightMap.saveToFile(Filename.c_str());
}