#include <server/ServerConnection.h>
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

ServerConnection::ServerConnection(IServerSocket& serverSocket, SharedMemory& sharedMemory, int playerNumber)
	: serverSocket(serverSocket), sharedMemory(sharedMemory), playerNumber(playerNumber)
{
	assert(playerNumber == 0 || playerNumber == 1);
}

void* ServerConnection::start_routine()
{

	bool quit = false;
	bool informedAboutQuit = false;
	while (!quit || !informedAboutQuit)
	{
		unsigned char requestCode;
		serverSocket.receive(&requestCode, sizeof(char));
		if (requestCode != BEGIN_MESSAGE)
		{
			continue;
		}

		try
		{
			serverSocket.receiveNoBlock(&requestCode, sizeof(char));

			switch (requestCode)
			{
			case REQUEST_START:
				startRequestHandler();
				break;
			case REQUEST_CURSOR_POSITION:
				cursorPositionRequestHandler();
				break;
			case REQUEST_STATE:
				currentStateRequestHandler();
				break;
			case REQUEST_GAME_STATUS:
				quit = gameStatusRequestHandler();
				if (quit)
				{
					informedAboutQuit = true;
					std::cout << "informed\n";
				}
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

	return NULL;
}

void ServerConnection::startRequestHandler()
{
	std::cout << "REQUEST_START received" << std::endl;

	sharedMemory.setStarted(true);
}

void ServerConnection::endRequestHandler()
{
	std::cout << "REQUEST_END received" << std::endl;

	sharedMemory.setEnded(true);
}

void ServerConnection::cursorPositionRequestHandler()
{
	try
	{
		//std::cout << "REQUEST_CURSOR_POSITION received" << std::endl;
		CursorPosition cursorPosition;
		cursorPosition.receive(serverSocket); // TODO
		//std::cout << "x = " << cursorPosition.x << " y = " << cursorPosition.y << std::endl;

		sharedMemory.setPlayerCursorPosition(cursorPosition, playerNumber);
	}
	catch (...)
	{
		std::cout << "cursor position request handler exception" << std::endl;
	}
}

void ServerConnection::currentStateRequestHandler()
{
	//std::cout << "REQUEST_STATE received" << std::endl;
	Ball ball;
	Player player[2];
	
	sharedMemory.getCurrentState(ball, player[0], player[1]);

	serverSocket.send(&BEGIN_MESSAGE, 1);
	serverSocket.send(&REQUEST_STATE, 1);
	ball.send(serverSocket);
	player[0].send(serverSocket);
	player[1].send(serverSocket);

}

bool ServerConnection::gameStatusRequestHandler()
{
	//std::cout << "\t\tREQUEST_GAME_STATUS received" << std::endl;
	bool started, ended;
	sharedMemory.getStarted(started);
	sharedMemory.getEnded(ended);

	serverSocket.send(&BEGIN_MESSAGE, 1);	
	serverSocket.send(&REQUEST_GAME_STATUS, 1);

	serverSocket.send(&started, sizeof(bool));
	serverSocket.send(&ended, sizeof(bool));

	if (ended)
		std::cout << "quit" << std::endl;

	return ended;
}
