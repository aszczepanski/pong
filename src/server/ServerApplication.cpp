#include <server/ServerApplication.h>
#include <server/IServerSocket.h>
#include <server/ServerTCP.h>
#include <server/ServerUDP.h>
#include <server/ServerConnection.h>
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

	//ServerTCP serverTCP(port.c_str());
	ServerUDP serverUDP(port.c_str());
	SharedMemory sharedMemory;
	GameEngine gameEngine(sharedMemory);

	ServerApplication serverApplication(sharedMemory, gameEngine, serverUDP);
	serverApplication.start();

	return 0;
}

ServerApplication::ServerApplication(SharedMemory& sharedMemory, GameEngine& gameEngine, IServerSocket& serverSocket)
	: sharedMemory(sharedMemory), gameEngine(gameEngine),
		serverSocket(serverSocket), serverConnection (NULL)
{
}

void ServerApplication::start()
{
	std::cout << "starting server application" << std::endl;

#ifndef SERVER_ONLY
	IServerSocket* tmpServer = serverSocket.waitForSocket();
	serverConnection = new ServerConnection(*tmpServer, sharedMemory, 1);
	serverConnection->run();
#endif

	Camera camera;
//	camera.configure();

	Communicator communicator(sharedMemory);
	Drawer drawer(sharedMemory, communicator, camera);

	drawer.run();

	gameEngine.run();

	gameEngine.wait();

#ifndef SERVER_ONLY
	serverConnection->wait();
#endif

	drawer.wait();

#ifndef SERVER_ONLY
	delete tmpServer;
	tmpServer = NULL;
#endif

	std::cout << "stopping server application" << std::endl;
}

ServerApplication::~ServerApplication()
{
	delete serverConnection;
	serverConnection = NULL;
}
