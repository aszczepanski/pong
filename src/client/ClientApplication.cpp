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
#include <boost/program_options.hpp>

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


	Drawer drawer(sharedMemory, communicator, camera);

	ClientApplication clientApplication(sharedMemory, drawer, clientUDP, communicator);
	clientApplication.start();

	delete camera;

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

	communicator.wait();

	std::cout << "closing client application" << std::endl;
}
