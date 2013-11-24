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

using namespace server;
using namespace common;

int main(int argc, char* argv[])
{
	std::cout << "Hello pong!" << std::endl;

	//ServerTCP serverTCP("6060");
	ServerUDP serverUDP("6060");
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

	// IServerSocket* tmpServer = serverSocket.waitForSocket();
	// serverConnection = new ServerConnection(*tmpServer, sharedMemory, 1);
	// serverConnection->run();

	Camera camera;
	camera.configure();

	Communicator communicator(sharedMemory);
	Drawer drawer(sharedMemory, communicator, camera);

	drawer.run();

	gameEngine.run();

	gameEngine.wait();

	serverConnection->wait();

	drawer.wait();

	// delete tmpServer;
	// tmpServer = NULL;

	std::cout << "stopping server application" << std::endl;
}

ServerApplication::~ServerApplication()
{
	delete serverConnection;
	serverConnection = NULL;
}
