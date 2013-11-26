#include <server/ConnectionUDP.h>
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

ConnectionUDP::ConnectionUDP(IServerSocket& serverSocket, SharedMemory& sharedMemory, int playerNumber)
	: serverSocket(serverSocket), sharedMemory(sharedMemory), playerNumber(playerNumber)
{
	assert(playerNumber == 0 || playerNumber == 1);
}

void* ConnectionUDP::start_routine()
{

	bool quit = false;
	unsigned char request[9];
	while (!quit)
	{
		try
		{
			serverSocket.receiveNoBlock(request, 9);
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

		cursorPositionRequestHandler(request);

		sharedMemory.getEnded(quit);
	}

	return NULL;
}

void ConnectionUDP::cursorPositionRequestHandler(unsigned char* request)
{
	try
	{
		//std::cout << "REQUEST_CURSOR_POSITION received" << std::endl;
		CursorPosition cursorPosition;
		cursorPosition.receive(request, 1);
		//std::cout << "x = " << cursorPosition.x << " y = " << cursorPosition.y << std::endl;

		sharedMemory.setPlayerCursorPosition(cursorPosition, playerNumber);

		Ball ball;
		Player player[2];
		unsigned char buf[33];

		sharedMemory.getCurrentState(ball, player[0], player[1]);

		buf[0] = BEGIN_MESSAGE;
		ball.send(buf, 1);
		player[0].send(buf, 9);
		player[1].send(buf, 21);
		serverSocket.send(buf, 33);
	}
	catch (...)
	{
		std::cout << "cursor position request handler exception" << std::endl;
	}
}

