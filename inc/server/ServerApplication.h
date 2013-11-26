#ifndef SERVER_APPLICATION_H
#define SERVER_APPLICATION_H

#include <server/ConnectionTCP.h>
#include <server/ConnectionUDP.h>

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

	ServerApplication(common::SharedMemory&, GameEngine&, ServerTCP&, ServerUDP&);
	void start();

	~ServerApplication();

private:
	common::SharedMemory& sharedMemory;
	GameEngine& gameEngine;

	ServerTCP& serverTCP;
	ConnectionTCP connectionTCP;

	ServerUDP& serverUDP;
	ConnectionUDP connectionUDP;
};

}

#endif // SERVER_APPLICATION_H
