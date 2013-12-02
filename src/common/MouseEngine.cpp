#include <common/MouseEngine.h>
#include <common/IControllerEngine.h>
#include <common/SharedMemory.h>
#include <common/GameBoardDrawer.h>
#include <common/ICommunicator.h>
#include <iostream>
#include <unistd.h>

using namespace common;
using namespace std;

MouseEngine::MouseEngine(SharedMemory& sharedMemory, ICommunicator& communicator)
	: IControllerEngine(sharedMemory, communicator)
{
}

void MouseEngine::run()
{
	cout << "MouseEngine starting" << endl;

	bool quit = false;

	GameBoardDrawer gameBoardDrawer(sharedMemory);

	gameBoardDrawer.init();

	while (!quit)
	{
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
