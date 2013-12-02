#include <common/Drawer.h>
#include <common/SharedMemory.h>
#include <common/ICommunicator.h>
#include <common/CursorPosition.h>
#include <common/Camera.h>
#include <common/dimmensions.h>
#include <iostream>
#include <cstddef>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <common/GameBoardDrawer.h>

using namespace common;

Drawer::Drawer(SharedMemory& sharedMemory, ICommunicator& communicator, Camera* camera)
	: sharedMemory(sharedMemory), communicator(communicator), camera(camera)
{
}

void Drawer::setCamera(Camera* camera)
{
	this->camera = camera;
}

void Drawer::run()
{
	std::cout << "Drawer thread" << std::endl;

	GameBoardDrawer gameBoardDrawer(sharedMemory);

	gameBoardDrawer.init();

 	bool quit = false;
 	float tmp_position;

 	while (!quit)
 	{
/*		sf::Vector2i mpos = sf::Mouse::getPosition(window);
		if (camera)
		{
			camera->getPosition(tmp_position);
			mpos.x = int(tmp_position * windowWidth);
		}

		mpos.x = std::max(mpos.x, 0);
		mpos.x = std::min(mpos.x, windowWidth-1);
*/
		int mousePositionX, mousePositionY;
		gameBoardDrawer.getMousePosition(mousePositionX, mousePositionY);

		communicator.sendCursorPosition(CursorPosition(mousePositionX, mousePositionY));

#ifndef __APPLE__
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			std::cout << "escape" << std::endl;
			communicator.sendEndRequest();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			std::cout << "space" << std::endl;
			communicator.sendStartRequest();
		}
#endif

		gameBoardDrawer.drawBoard();

		usleep(25000);

 		sharedMemory.getEnded(quit);
 	}
}
