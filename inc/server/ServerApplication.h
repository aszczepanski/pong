#ifndef SERVER_APPLICATION_H
#define SERVER_APPLICATION_H

#include <server/ServerTCPConnection.h>

namespace common
{
	class SharedMemory;
}

namespace server
{

class GameEngine;
class ServerTCP;
class ServerUDP;

class ServerApplication
{
public:

	ServerApplication(common::SharedMemory&, GameEngine&, ServerUDP&);
	void start();

	~ServerApplication();

private:
	common::SharedMemory& sharedMemory;
	GameEngine& gameEngine;
	ServerUDP& serverUDP;
	ServerTCPConnection* serverTCPConnection[2];
};

}

#endif // SERVER_APPLICATION_H
