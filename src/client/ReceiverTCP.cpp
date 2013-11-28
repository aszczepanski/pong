#include <client/ReceiverTCP.h>
#include <common/SharedMemory.h>
#include <common/Ball.h>
#include <common/Player.h>
#include <common/ISocket.h>
#include <cstddef>
#include <common/protocol.h>
#include <iostream>
#include <unistd.h>

using namespace common;
using namespace client;

ReceiverTCP::ReceiverTCP(SharedMemory& sharedMemory, ISocket& socket)
	: sharedMemory(sharedMemory), socket(socket)
{
}

void* ReceiverTCP::start_routine()
{

	bool quit = false;
	unsigned char requestCode;
	while (!quit)
	{
		try
		{
			socket.receiveNoBlock(&requestCode, 1);
			switch(requestCode)
			{
			case REQUEST_END:
				endRequestHandler();
				break;
			default:
				std::cout << "unsupported tcp request received" << std::endl;

			}
		}
		catch (...)
		{
			std::cout << "tcp request code exception" << std::endl;
		}
		
		sharedMemory.getEnded(quit);

	}

	return NULL;
}

void ReceiverTCP::endRequestHandler()
{
	std::cout << "end request received" << std::endl;
	sharedMemory.setEnded(true);
}
