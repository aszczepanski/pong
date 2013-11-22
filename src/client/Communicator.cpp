#include <client/Communicator.h>
#include <client/SharedMemory.h>
#include <client/ClientTCP.h>
#include <iostream>
#include <cstddef>

using namespace client;

Communicator::Communicator(SharedMemory& sharedMemory, ClientTCP& clientTCP)
	: sharedMemory(sharedMemory), clientTCP(clientTCP)
{
}

void* Communicator::start_routine()
{
	std::cout << "Communicator thread" << std::endl;

	return NULL;
}
