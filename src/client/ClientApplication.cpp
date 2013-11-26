#include <client/ClientApplication.h>
#include <client/IClientSocket.h>
#include <client/ClientTCP.h>
#include <client/ClientUDP.h>
#include <common/Drawer.h>
#include <common/SharedMemory.h>
#include <common/Camera.h>
#include <client/Communicator.h>
#include <iostream>
#include <string>
#include <common/protocol.h>

using namespace client;
using namespace common;

int main(int argc, char* argv[])
{
	std::cout << "Hello pong!" << std::endl;

	std::string host = "127.0.0.1";
	if (2 == argc)
	{
		host = argv[1];
	}

	ClientUDP clientUDP(host.c_str(), port.c_str());
	unsigned char c = 'c';
	clientUDP.send(&c, sizeof(char));
	SharedMemory sharedMemory;
	Communicator communicator(sharedMemory, clientUDP);

	Camera camera(sharedMemory);
	//camera.configure();
	//camera.run();

	Drawer drawer(sharedMemory, communicator, camera);

	ClientApplication clientApplication(sharedMemory, drawer, clientUDP, communicator);
	clientApplication.start();

	return 0;
}

ClientApplication::ClientApplication(SharedMemory& sharedMemory, Drawer& drawer, IClientSocket& clientSocket, Communicator& communicator)
	: sharedMemory(sharedMemory), drawer(drawer), clientSocket(clientSocket), communicator(communicator)
{
}


void ClientApplication::start()
{
	std::cout << "starting client application" << std::endl;

	communicator.run();
	drawer.run();

	//drawer.wait();

	communicator.wait();

	std::cout << "closing client application" << std::endl;
}
