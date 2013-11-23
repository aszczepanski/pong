#include <server/ServerTCPConnection.h>
#include <server/ServerTCP.h>
#include <server/ServerUDP.h>
#include <common/SharedMemory.h>
#include <common/CursorPosition.h>
#include <common/Ball.h>
#include <common/Player.h>
#include <cstddef>
#include <common/protocol.h>
#include <iostream>

using namespace server;
using namespace common;

ServerTCPConnection::ServerTCPConnection(ServerUDP serverUDP, SharedMemory& sharedMemory)
	: serverUDP(serverUDP), sharedMemory(sharedMemory)
{
}

void* ServerTCPConnection::start_routine()
{

	// TODO
	bool quit = false;
	bool informedAboutQuit = false;
	while (!quit || !informedAboutQuit)
	{
		unsigned char requestCode;
		serverUDP.receive(&requestCode, sizeof(char));

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
			gameStatusRequestHandler();
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

		sharedMemory.getEnded(quit);
	}

	return NULL;
}

void ServerTCPConnection::startRequestHandler()
{
	std::cout << "REQUEST_START received" << std::endl;

	sharedMemory.setStarted(true);
}

void ServerTCPConnection::endRequestHandler()
{
	std::cout << "REQUEST_END received" << std::endl;

	sharedMemory.setEnded(true);
}

void ServerTCPConnection::cursorPositionRequestHandler()
{
	//std::cout << "REQUEST_CURSOR_POSITION received" << std::endl;
	CursorPosition cursorPosition;
	cursorPosition.receive(serverUDP);
	//std::cout << "x = " << cursorPosition.x << " y = " << cursorPosition.y << std::endl;

	sharedMemory.setPlayerCursorPosition(cursorPosition, 0);
}

void ServerTCPConnection::currentStateRequestHandler()
{
	//std::cout << "REQUEST_STATE received" << std::endl;
	static Ball ball;
	static Player player[2];
	
	sharedMemory.getCurrentState(ball, player[0], player[1]);

	int px, py;
//	ball.getPosition(px, py);

//	serverTCP.send(&px, sizeof(int));
//	serverTCP.send(&py, sizeof(int));

	ball.send(serverUDP);
	player[0].send(serverUDP);
	player[1].send(serverUDP);

}

void ServerTCPConnection::gameStatusRequestHandler()
{
	//std::cout << "REQUEST_GAME_STATUS received" << std::endl;
	bool started;
	sharedMemory.getStarted(started);

	serverUDP.send(&started, sizeof(bool));

	bool ended;
	sharedMemory.getEnded(ended);

	serverUDP.send(&ended, sizeof(bool));

	if (ended)
		std::cout << "quit" << std::endl;
}
