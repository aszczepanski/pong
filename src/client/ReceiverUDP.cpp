#include <client/ReceiverUDP.h>
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

ReceiverUDP::ReceiverUDP(SharedMemory& sharedMemory, ISocket& socket)
	: sharedMemory(sharedMemory), socket(socket)
{
}

void* ReceiverUDP::start_routine()
{

	bool quit = false;
	unsigned char request[33];
	while (!quit)
	{
		try
		{
			socket.receiveNoBlock(request, 33);
		}
		catch(...)
		{
			sharedMemory.getEnded(quit);
			continue;
		}
		if (request[0] != BEGIN_MESSAGE)
		{
			continue;
		}

		stateRequestHandler(request);
		
		sharedMemory.getEnded(quit);

	}

	return NULL;
}

void ReceiverUDP::stateRequestHandler(unsigned char* request)
{
	Ball ball;
	Player player[2];

	try
	{
		
		ball.receive(request, 1);
		player[0].receive(request, 9);
		player[1].receive(request, 21);

		sharedMemory.setCurrentState(ball, player[0], player[1]);
	}
	catch (...)
	{
		std::cout << "state request handler exception" << std::endl;
	}
}

