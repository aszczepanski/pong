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
	sharedMemory.setPlayerCursorPosition(cursorPosition, 0);
}

void Communicator::sendStartRequest() const
{
	sharedMemory.setStarted(true);
}

void Communicator::sendEndRequest() const
{
	sharedMemory.setEnded(true);

	try
	{
		serverTCP.send(&REQUEST_END, 1);
	}
	catch(...)
	{
		std::cout << "Communicator sendEndRequest exception" << std::endl;
	}
}

