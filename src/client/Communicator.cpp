#include <client/Communicator.h>
#include <common/IThread.h>
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
#include <client/ReceiverTCP.h>
#include <client/ReceiverUDP.h>

using namespace client;
using namespace common;

common::Mutex Communicator::mutex;

Communicator::Communicator(SharedMemory& sharedMemory, IClientSocket& clientTCP, IClientSocket& clientUDP)
	: ICommunicator(sharedMemory), IThread(), clientTCP(clientTCP), clientUDP(clientUDP)
{
}

void* Communicator::start_routine()
{
	std::cout << "Communicator thread" << std::endl;

	ReceiverTCP receiverTCP(sharedMemory, clientTCP);
	ReceiverUDP receiverUDP(sharedMemory, clientUDP);

	receiverTCP.run();
	receiverUDP.run();

	bool quit = false;
	while (!quit)
	{
		usleep(25000); // 40 fps

		sharedMemory.getEnded(quit);
	}

	receiverTCP.wait();
	std::cout << "after tcp" << std::endl;
	receiverUDP.wait();
	std::cout << "After udp" << std::endl;

	return NULL;
}

void Communicator::sendCursorPosition(const CursorPosition& cursorPosition) const
{
	mutex.lock();

	unsigned char buf[9];
	buf[0] = BEGIN_MESSAGE;
	
	cursorPosition.send(buf, 1);

	try
	{
		clientUDP.send(buf, 9);
	}
	catch (...)
	{
		std::cout << "Communicator sendCursorPosition exception" << std::endl;
	}

	mutex.unlock();
}

void Communicator::sendStartRequest() const
{
	mutex.lock();

	try
	{
		clientTCP.send(&REQUEST_START, 1);
	}
	catch (...)
	{
		std::cout << "Communicator sendStartRequest exception" << std::endl;
	}

	mutex.unlock();
}

void Communicator::sendEndRequest() const
{
	mutex.lock();

	try
	{
		clientTCP.send(&REQUEST_END, 1);
	}
	catch (...)
	{
		std::cout << "Communicator sendEndRequest exception" << std::endl;
	}

	sharedMemory.setEnded(true);

	mutex.unlock();
}

