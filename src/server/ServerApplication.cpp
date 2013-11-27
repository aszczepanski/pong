#include <server/ServerApplication.h>
#include <server/IServerSocket.h>
#include <server/ServerTCP.h>
#include <server/ServerUDP.h>
#include <server/ConnectionTCP.h>
#include <server/ConnectionUDP.h>
#include <server/GameEngine.h>
#include <server/Communicator.h>
#include <common/SharedMemory.h>
#include <common/Drawer.h>
#include <common/Camera.h>
#include <iostream>
#include <cstddef>
#include <unistd.h>
#include <common/protocol.h>

using namespace server;
using namespace common;

#define SERVER_ONLY

int main(int argc, char* argv[])
{
	std::cout << "Hello pong!" << std::endl;

	ServerTCP serverTCP(port.c_str());

#ifndef SERVER_ONLY
	ServerTCP acceptedServerTCP = serverTCP.waitForSocket();
#else
	ServerTCP acceptedServerTCP = serverTCP;
#endif
	ServerUDP serverUDP(port.c_str());
	SharedMemory sharedMemory;
	GameEngine gameEngine(sharedMemory);

	ServerApplication serverApplication(sharedMemory, gameEngine, acceptedServerTCP, serverUDP);
	serverApplication.start();

	return 0;
}

ServerApplication::ServerApplication(SharedMemory& sharedMemory, GameEngine& gameEngine, ServerTCP& serverTCP, ServerUDP& serverUDP)
	: sharedMemory(sharedMemory), gameEngine(gameEngine),
		serverTCP(serverTCP), connectionTCP(serverTCP, sharedMemory, 1),
		serverUDP(serverUDP), connectionUDP(serverUDP, sharedMemory, 1)
{
}

void ServerApplication::start()
{
	std::cout << "starting server application" << std::endl;

#ifndef SERVER_ONLY
	connectionTCP.run();
	connectionUDP.run();
#endif

	Camera camera(sharedMemory);
	camera.configure();


	 Communicator communicator(sharedMemory, serverTCP);

	 Drawer drawer(sharedMemory, communicator, camera);

	 gameEngine.run();

	 drawer.run();

	 gameEngine.wait();

#ifndef SERVER_ONLY
	connectionTCP.wait();
	std::cout << "after tcp" << std::endl;
	connectionUDP.wait();
	std::cout << "after udp" << std::endl;
#endif

	std::cout << "stopping server application" << std::endl;
}

ServerApplication::~ServerApplication()
{
}
