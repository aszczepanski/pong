#include <client/Communicator.h>
#include <common/SharedMemory.h>
#include <common/Ball.h>
#include <common/Player.h>
#include <common/CursorPosition.h>
#include <client/ClientTCP.h>
#include <client/ClientUDP.h>
#include <common/ISocket.h>
#include <iostream>
#include <cstdio>
#include <cstddef>
#include <unistd.h>
#include <common/protocol.h>

using namespace client;
using namespace common;

Communicator::Communicator(SharedMemory& sharedMemory, ClientUDP& clientUDP)
	: sharedMemory(sharedMemory), clientUDP(clientUDP)
{
}

void* Communicator::start_routine()
{
	std::cout << "Communicator thread" << std::endl;

	bool quit = false;
	while (!quit)
	{
		getCurrentState();
		usleep(25000); // 40 fps

		sharedMemory.getEnded(quit);
	}

	return NULL;
}

void Communicator::sendCursorPosition(const CursorPosition& cursorPosition) const
{
	mutex.lock();

	clientUDP.send(&REQUEST_CURSOR_POSITION, sizeof(char));
	cursorPosition.send(clientUDP);

	mutex.unlock();
}

void Communicator::getCurrentState()
{
	mutex.lock();

	clientUDP.send(&REQUEST_STATE, sizeof(char));
	static Ball ball;
	static Player player[2];
	static bool started, ended;

	ball.receive(clientUDP);
	player[0].receive(clientUDP);
	player[1].receive(clientUDP);

	clientUDP.send(&REQUEST_GAME_STATUS, sizeof(char));
	clientUDP.receive(&started, sizeof(bool));
	clientUDP.receive(&ended, sizeof(bool));

	sharedMemory.setCurrentState(ball, player[0], player[1]);

	sharedMemory.setStarted(started);
	sharedMemory.setEnded(ended);

	mutex.unlock();

	//static int px, py;
	//player[0].getPosition(px, py);
	//printf("%d %d\n", px, py);
}

void Communicator::sendStartRequest() const
{
	mutex.lock();

	clientUDP.send(&REQUEST_START, sizeof(char));

	mutex.unlock();
}

void Communicator::sendEndRequest() const
{
	mutex.lock();

	clientUDP.send(&REQUEST_END, sizeof(char));

	mutex.unlock();
}

