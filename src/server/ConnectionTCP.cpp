#include <server/ConnectionTCP.h>
#include <server/IServerSocket.h>
#include <server/ServerTCP.h>
#include <server/ServerUDP.h>
#include <common/SharedMemory.h>
#include <common/CursorPosition.h>
#include <common/Ball.h>
#include <common/Player.h>
#include <cstddef>
#include <common/protocol.h>
#include <iostream>
#include <cassert>

using namespace server;
using namespace common;

ConnectionTCP::ConnectionTCP(IServerSocket& serverSocket, SharedMemory& sharedMemory, int playerNumber)
	: serverSocket(serverSocket), sharedMemory(sharedMemory), playerNumber(playerNumber)
{
	assert(playerNumber == 0 || playerNumber == 1);
}

void* ConnectionTCP::start_routine()
{

	bool quit = false;
	unsigned char requestCode;
	while (!quit)
	{
		try
		{
			serverSocket.receiveNoBlock(&requestCode, sizeof(char));

			switch (requestCode)
			{
			case REQUEST_START:
				startRequestHandler();
				break;
			case REQUEST_END:
				endRequestHandler();
				break;
			default:
				std::cout << "unsupported request received" << std::endl;
			}

		}
		catch(...)
		{
			std::cout << "request code exception" << std::endl;
		}

		sharedMemory.getEnded(quit);
	}

	std::cout << "leaving connection tcp" << std::endl;

	return NULL;
}

void ConnectionTCP::startRequestHandler()
{
	std::cout << "REQUEST_START received" << std::endl;

	sharedMemory.setStarted(true);
}

void ConnectionTCP::endRequestHandler()
{
	std::cout << "REQUEST_END received" << std::endl;

	sharedMemory.setEnded(true);

	serverSocket.send(&BEGIN_MESSAGE, 1);
	serverSocket.send(&REQUEST_END, 1);
}

