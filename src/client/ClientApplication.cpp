#include <client/ClientApplication.h>
#include <client/IClientSocket.h>
#include <client/ClientTCP.h>
#include <client/ClientUDP.h>
#include <common/GameBoardDrawer.h>
#include <common/SharedMemory.h>
#include <common/CameraEngine.h>
#include <common/MouseEngine.h>
#include <client/Communicator.h>
#include <iostream>
#include <string>
#include <common/protocol.h>
#include <boost/program_options.hpp>

#include <X11/Xlib.h>

namespace po = boost::program_options;

using namespace client;
using namespace common;

int main(int argc, char* argv[])
{
	std::cout << "Hello pong!" << std::endl;

	po::options_description optionsDescription("Allowed options");
	optionsDescription.add_options()
		("help", "produce help message")
		("camera", "enables camera")
		("host", po::value<std::string>(), "set host ip address")
	;

	po::variables_map variablesMap;
	po::store(po::parse_command_line(argc, argv, optionsDescription), variablesMap);
	po::notify(variablesMap);    

	if (variablesMap.count("help"))
	{
		std::cout << optionsDescription << std::endl;
		return 1;
	}

	XInitThreads();

	std::string host = "127.0.0.1";
	if (variablesMap.count("host"))
	{
		std::cout << "Host ip address was set to " << variablesMap["host"].as<std::string>() << std::endl;
		host = variablesMap["host"].as<std::string>();
	}

	ClientTCP clientTCP(host.c_str(), port.c_str());

	ClientUDP clientUDP(host.c_str(), port.c_str());
	SharedMemory sharedMemory;
	Communicator communicator(sharedMemory, clientTCP, clientUDP);

	GameBoardDrawer drawer(sharedMemory);

	IControllerEngine* controllerEngine;
//	Camera* camera;

	if (variablesMap.count("camera"))
	{
		std::cout << "Camera enabled" << std::endl;
//		camera = new Camera(sharedMemory);
//		camera->configure();
		controllerEngine = new CameraEngine(sharedMemory, communicator);
	}
	else
	{
		std::cout << "Camera disabled" << std::endl;
//		camera = NULL;
		controllerEngine = new MouseEngine(sharedMemory, communicator, drawer);
	}


//	Drawer drawer(sharedMemory, communicator, camera);
	drawer.init();

	ClientApplication clientApplication(sharedMemory, drawer, controllerEngine, clientUDP, communicator);
	clientApplication.start();

//	delete camera;

	return 0;
}

ClientApplication::ClientApplication(SharedMemory& sharedMemory, GameBoardDrawer& drawer, IControllerEngine* controllerEngine, IClientSocket& clientSocket, Communicator& communicator)
	: sharedMemory(sharedMemory), drawer(drawer), controllerEngine(controllerEngine), clientSocket(clientSocket), communicator(communicator)
{
}


void ClientApplication::start()
{
	std::cout << "starting client application" << std::endl;

	communicator.run();
	drawer.run();

	controllerEngine->run();

	communicator.wait();

	std::cout << "closing client application" << std::endl;
}
