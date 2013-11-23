#include <client/ClientApplication.h>
#include <client/ClientTCP.h>
#include <client/ClientUDP.h>
#include <client/Drawer.h>
#include <common/SharedMemory.h>
#include <client/Communicator.h>
#include <iostream>

using namespace client;
using namespace common;

int main(int argc, char* argv[])
{
	std::cout << "Hello pong!" << std::endl;

	ClientUDP clientUDP("127.0.0.1", "6060");
	unsigned char c = 'c';
	clientUDP.send(&c, sizeof(char));
	SharedMemory sharedMemory;
	Communicator communicator(sharedMemory, clientUDP);
	Drawer drawer(sharedMemory, communicator);

	ClientApplication clientApplication(sharedMemory, drawer, clientUDP, communicator);
	clientApplication.start();

	return 0;
}

ClientApplication::ClientApplication(SharedMemory& sharedMemory, Drawer& drawer, ClientUDP& clientUDP, Communicator& communicator)
	: sharedMemory(sharedMemory), drawer(drawer), clientUDP(clientUDP), communicator(communicator)
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
