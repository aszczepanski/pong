#include <client/Communicator.h>
#include <client/SharedMemory.h>
#include <common/Ball.h>
#include <common/Player.h>
#include <common/CursorPosition.h>
#include <client/ClientTCP.h>
#include <common/ISocket.h>
#include <iostream>
#include <cstddef>
#include <unistd.h>
#include <common/protocol.h>

using namespace client;
using namespace common;

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

void Communicator::sendCursorPosition(CursorPosition& cursorPosition) const
{
	clientTCP.send(&CURSOR_POSITION, sizeof(char));
	cursorPosition.send(clientTCP);
}

void Communicator::getCurrentState()
{
	clientTCP.send(&STATE, sizeof(char));
	sharedMemory.ball.receive(clientTCP);
	sharedMemory.player[0].receive(clientTCP);
	sharedMemory.player[1].receive(clientTCP);
}

void Communicator::sendStartRequest() const
{
	clientTCP.send(&START, sizeof(char));
}

void Communicator::sendEndRequest() const
{
	clientTCP.send(&END, sizeof(char));
}
