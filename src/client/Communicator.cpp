#include <client/Communicator.h>
#include <common/SharedMemory.h>
#include <common/Ball.h>
#include <common/Player.h>
#include <common/CursorPosition.h>
#include <client/IClientSocket.h>
#include <client/ClientTCP.h>
#include <client/ClientUDP.h>
#include <common/ISocket.h>
#include <iostream>
#include <cstdio>
#include <cstddef>
#include <unistd.h>
#include <common/protocol.h>
#include <client/Receiver.h>

using namespace client;
using namespace common;

common::Mutex Communicator::mutex;

Communicator::Communicator(SharedMemory& sharedMemory, IClientSocket& clientSocket)
	: ICommunicator(sharedMemory), clientSocket(clientSocket)
{
}

void* Communicator::start_routine()
{
	std::cout << "Communicator thread" << std::endl;

	Receiver receiver(sharedMemory, clientSocket);
	receiver.run();

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
	
	clientSocket.send(&BEGIN_MESSAGE, 1);
	clientSocket.send(&REQUEST_CURSOR_POSITION, 1);
	cursorPosition.send(clientSocket);

	mutex.unlock();
}

void Communicator::getCurrentState()
{
	mutex.lock();

	clientSocket.send(&BEGIN_MESSAGE, 1);
	clientSocket.send(&REQUEST_STATE, 1);
//	static Ball ball;
//	static Player player[2];
//	static bool started, ended;

//	ball.receive(clientSocket);
//	player[0].receive(clientSocket);
//	player[1].receive(clientSocket);

	clientSocket.send(&BEGIN_MESSAGE, 1);
	clientSocket.send(&REQUEST_GAME_STATUS, 1);
//	clientSocket.receive(&started, sizeof(bool));
//	clientSocket.receive(&ended, sizeof(bool));

//	sharedMemory.setCurrentState(ball, player[0], player[1]);

//	sharedMemory.setStarted(started);
//	sharedMemory.setEnded(ended);

	mutex.unlock();

	//static int px, py;
	//player[0].getPosition(px, py);
	//printf("%d %d\n", px, py);
}

void Communicator::sendStartRequest() const
{
	mutex.lock();

	clientSocket.send(&BEGIN_MESSAGE, 1);
	clientSocket.send(&REQUEST_START, 1);

	mutex.unlock();
}

void Communicator::sendEndRequest() const
{
	mutex.lock();

	clientSocket.send(&BEGIN_MESSAGE, 1);
	clientSocket.send(&REQUEST_END, 1);

	mutex.unlock();
}

