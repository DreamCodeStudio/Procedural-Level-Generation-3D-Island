#pragma once
#include <irrlicht.h>

/* WorldGenerator */
#include "WorldGenerator\WorldGenerator.h"

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
};