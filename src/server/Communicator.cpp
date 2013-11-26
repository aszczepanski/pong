#include <server/Communicator.h>
#include <server/ServerTCP.h>
#include <common/SharedMemory.h>
#include <common/Ball.h>
#include <common/Player.h>
#include <common/CursorPosition.h>
#include <iostream>
#include <cstdio>
#include <cstddef>
#include <unistd.h>
#include <common/protocol.h>

using namespace server;
using namespace common;

Communicator::Communicator(SharedMemory& sharedMemory, ServerTCP& serverTCP)
	: ICommunicator(sharedMemory), serverTCP(serverTCP)
{
}

void Communicator::sendCursorPosition(const CursorPosition& cursorPosition) const
{
	sharedMemory.setPlayerCursorPosition(cursorPosition, 0); // TODO
}

void Communicator::getCurrentState()
{
/*	clientSocket.send(&REQUEST_STATE, sizeof(char));
	static Ball ball;
	static Player player[2];
	static bool started, ended;

	ball.receive(clientSocket);
	player[0].receive(clientSocket);
	player[1].receive(clientSocket);

	clientSocket.send(&REQUEST_GAME_STATUS, sizeof(char));
	clientSocket.receive(&started, sizeof(bool));
	clientSocket.receive(&ended, sizeof(bool));

	sharedMemory.setCurrentState(ball, player[0], player[1]);

	sharedMemory.setStarted(started);
	sharedMemory.setEnded(ended);

	std::cout << "after\n";

	mutex.unlock();

	//static int px, py;
	//player[0].getPosition(px, py);
	//printf("%d %d\n", px, py);
*/
}

void Communicator::sendStartRequest() const
{
	sharedMemory.setStarted(true);
}

void Communicator::sendEndRequest() const
{
	sharedMemory.setEnded(true);

//	serverTCP.send(&BEGIN_MESSAGE, 1);
	serverTCP.send(&REQUEST_END, 1);
}

