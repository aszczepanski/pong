#include <client/Receiver.h>
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

Receiver::Receiver(SharedMemory& sharedMemory, ISocket& socket)
	: sharedMemory(sharedMemory), socket(socket)
{
}

void* Receiver::start_routine()
{

	bool quit = false;
	unsigned char requestCode;
	while (!quit)
	{
		socket.receive(&requestCode, 1);
		if (requestCode != BEGIN_MESSAGE)
		{
			continue;
		}

		try
		{
			socket.receiveNoBlock(&requestCode, 1);
			switch(requestCode)
			{
			case REQUEST_GAME_STATUS:
				gameStatusRequestHandler();
				break;
			case REQUEST_STATE:
				stateRequestHandler();
				break;
			default:
				std::cout << "unsupported request received" << std::endl;

			}
		}
		catch (...)
		{
			std::cout << "request code exception" << std::endl;
		}
		
		sharedMemory.getEnded(quit);

	}

	return NULL;
}

void Receiver::gameStatusRequestHandler()
{
	bool started, ended;
	try
	{
		socket.receiveNoBlock(&started, sizeof(bool));
		socket.receiveNoBlock(&ended, sizeof(bool));

		sharedMemory.setStarted(started);
		sharedMemory.setEnded(ended);

		if (ended)
		{
			std::cout << "ended\n";
		}
	}
	catch (...)
	{
		std::cout << "game status request handler exception" << std::endl;
	}
}

void Receiver::stateRequestHandler()
{
	Ball ball;
	Player player[2];

	try
	{
		ball.receive(socket);
		player[0].receive(socket);
		player[1].receive(socket);

		sharedMemory.setCurrentState(ball, player[0], player[1]);
	}
	catch (...)
	{
		std::cout << "state request handler exception" << std::endl;
	}
}

