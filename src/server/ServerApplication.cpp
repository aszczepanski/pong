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
#include <boost/program_options.hpp>

namespace po = boost::program_options;

using namespace server;
using namespace common;

#define SERVER_ONLY

int main(int argc, char* argv[])
{
	std::cout << "Hello pong!" << std::endl;

	po::options_description optionsDescription("Allowed options");
	optionsDescription.add_options()
		("help", "produce help message")
		("camera", "enables camera")
	;

	po::variables_map variablesMap;
	po::store(po::parse_command_line(argc, argv, optionsDescription), variablesMap);
	po::notify(variablesMap);    

	if (variablesMap.count("help"))
	{
		std::cout << optionsDescription << std::endl;
		return 1;
	}



	ServerTCP serverTCP(port.c_str());

#ifndef SERVER_ONLY
	ServerTCP acceptedServerTCP = serverTCP.waitForSocket();
#else
	ServerTCP acceptedServerTCP = serverTCP;
#endif
	ServerUDP serverUDP(port.c_str());
	SharedMemory sharedMemory;
	GameEngine gameEngine(sharedMemory);

	Camera* camera;

	if (variablesMap.count("camera"))
	{
		std::cout << "Camera enabled" << std::endl;
		camera = new Camera(sharedMemory);
		camera->configure();
	}
	else
	{
		std::cout << "Camera disabled" << std::endl;
		camera = NULL;
	}

	Communicator communicator(sharedMemory, acceptedServerTCP);

	Drawer drawer(sharedMemory, communicator, camera);

	ServerApplication serverApplication(sharedMemory, drawer, gameEngine, acceptedServerTCP, serverUDP);
	serverApplication.start();

	delete camera;

	return 0;
}

ServerApplication::ServerApplication(SharedMemory& sharedMemory, Drawer& drawer,
	GameEngine& gameEngine,	ServerTCP& serverTCP, ServerUDP& serverUDP)
: sharedMemory(sharedMemory), drawer(drawer), gameEngine(gameEngine),
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
