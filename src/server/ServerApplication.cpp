#include <server/ServerApplication.h>
#include <server/ServerTCP.h>
#include <server/ServerUDP.h>
#include <server/ServerTCPConnection.h>
#include <server/GameEngine.h>
#include <common/SharedMemory.h>
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

ServerApplication::ServerApplication(SharedMemory& sharedMemory, GameEngine& gameEngine, ServerUDP& serverUDP)
	: sharedMemory(sharedMemory), gameEngine(gameEngine),
		serverUDP(serverUDP), serverTCPConnection { NULL, NULL }
{
}

void ServerApplication::start()
{
	std::cout << "starting server application" << std::endl;

	unsigned char c;
	ServerUDP tmpServerUDP = serverUDP.waitForSocket(&c, sizeof(char));
	serverTCPConnection[0] = new ServerTCPConnection(tmpServerUDP, sharedMemory);
	serverTCPConnection[0]->run();
/*	
	tmpServerTCP = serverTCP.waitForSocket();
	serverTCPConnection[1] = new ServerTCPConnection(tmpServerTCP, sharedMemory);
	serverTCPConnection[1]->run();
*/

	gameEngine.run();

	gameEngine.wait();

	serverTCPConnection[0]->wait();

	std::cout << "stopping server application" << std::endl;
}

ServerApplication::~ServerApplication()
{
	for (int i=0; i<2; i++)
	{
		delete serverTCPConnection[i];
		serverTCPConnection[i] = NULL;
	}
}
