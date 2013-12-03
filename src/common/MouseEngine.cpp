#include <common/MouseEngine.h>
#include <common/IControllerEngine.h>
#include <common/SharedMemory.h>
#include <common/GameBoardDrawer.h>
#include <common/ICommunicator.h>
#include <iostream>
#include <unistd.h>
#include <common/dimmensions.h>

using namespace common;
using namespace std;

MouseEngine::MouseEngine(SharedMemory& sharedMemory, ICommunicator& communicator, GameBoardDrawer& drawer)
	: IControllerEngine(sharedMemory, communicator), drawer(drawer)
{
}

void MouseEngine::run()
{
	cout << "MouseEngine starting" << endl;

	bool quit = false;

	while (!quit)
	{
		
		sf::Event event;
		while (drawer.getWindow()->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				//window.close();
				cout << "escape" << endl;
				communicator.sendEndRequest();

			}
			if (event.type == sf::Event::MouseMoved)
			{
				communicator.sendCursorPosition(CursorPosition(event.mouseMove.x, event.mouseMove.y));
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					cout << "escape" << endl;
					communicator.sendEndRequest();
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					cout << "space" << endl;
					communicator.sendStartRequest();
				}
			}
		}

		usleep(25000);

 		sharedMemory.getEnded(quit);

	}
}
