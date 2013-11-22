#include <client/ClientApplication.h>
#include <client/ClientTCP.h>
#include <client/Drawer.h>
#include <client/SharedMemory.h>
#include <client/Communicator.h>
#include <iostream>
#include <common/Mutex.h>

using namespace client;

int main(int argc, char* argv[])
{
	std::cout << "Hello pong!" << std::endl;

	ClientTCP clientTCP("127.0.0.1", "6060");
	SharedMemory sharedMemory;
	Communicator communicator(sharedMemory, clientTCP);
	Drawer drawer(sharedMemory, communicator);

	ClientApplication clientApplication(sharedMemory, drawer, clientTCP, communicator);
	clientApplication.start();

	return 0;
}

ClientApplication::ClientApplication(SharedMemory& sharedMemory, Drawer& drawer, ClientTCP& clientTCP, Communicator& communicator)
	: sharedMemory(sharedMemory), drawer(drawer), clientTCP(clientTCP), communicator(communicator)
{
}


void ClientApplication::start()
{
	std::cout << "starting client application" << std::endl;

	communicator.run();
	drawer.run();

	drawer.wait();
	communicator.wait();

	std::cout << "closing client application" << std::endl;
}
