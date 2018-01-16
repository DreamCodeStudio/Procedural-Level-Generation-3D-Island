#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class WorldGenerator
{
	public:

		static void Create(unsigned int Width, unsigned int Height, std::string Filename, unsigned int StartPeakDistance);
};