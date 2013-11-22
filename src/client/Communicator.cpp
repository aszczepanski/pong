#include <client/Communicator.h>
#include <client/SharedMemory.h>
#include <client/ClientTCP.h>
#include <iostream>
#include <cstddef>
#include <unistd.h>
#include <common/protocol.h>

using namespace client;

Communicator::Communicator(SharedMemory& sharedMemory, ClientTCP& clientTCP)
	: sharedMemory(sharedMemory), clientTCP(clientTCP)
{
}

void* Communicator::start_routine()
{
	std::cout << "Communicator thread" << std::endl;
/*
	bool quit = false; // TODO
	//while (!quit)
	for (int i=0; i<100; i++)
	{
		getCurrentState();
		usleep(40000); // 25 fps
	}
*/
	return NULL;
}

void Communicator::sendCursorPosition(int x, int y) const
{
	CursorPosition cursorPosition;
	cursorPosition.x = x;
	cursorPosition.y = y;

	clientTCP.send(&CURSOR_POSITION, sizeof(char));
	clientTCP.send(&cursorPosition, sizeof(CursorPosition));
}

void Communicator::getCurrentState()
{
	StateInfo stateInfo;

	clientTCP.send(&STATE, sizeof(char));
	clientTCP.receive(&stateInfo, sizeof(StateInfo));

	sharedMemory.ball.setPosition(stateInfo.ballX, stateInfo.ballY);
	sharedMemory.player[0].setPosition(stateInfo.curPlayerX, stateInfo.curPlayerY);
	sharedMemory.player[1].setPosition(stateInfo.opPlayerX, stateInfo.opPlayerY);
}

void Communicator::sendStartRequest() const
{
	clientTCP.send(&START, sizeof(char));
}

void Communicator::sendEndRequest() const
{
	clientTCP.send(&END, sizeof(char));
}
