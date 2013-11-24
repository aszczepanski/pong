#ifndef SERVER_APPLICATION_H
#define SERVER_APPLICATION_H

#include <server/ServerConnection.h>

namespace common
{
	class SharedMemory;
}

namespace server
{

class GameEngine;
class IServerSocket;

class ServerApplication
{
public:

	ServerApplication(common::SharedMemory&, GameEngine&, IServerSocket&);
	void start();

	~ServerApplication();

private:
	common::SharedMemory& sharedMemory;
	GameEngine& gameEngine;
	IServerSocket& serverSocket;
	ServerConnection* serverConnection;
};

}

#endif // SERVER_APPLICATION_H
