#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <common/IThread.h>
#include <server/IServerSocket.h>

namespace common
{
	class SharedMemory;
}

namespace server
{

class ServerConnection
	: public common::IThread
{
public:
	ServerConnection(IServerSocket&, common::SharedMemory&, int playerNumber);

private:
	virtual void* start_routine();

	void startRequestHandler();
	void endRequestHandler();
	void cursorPositionRequestHandler();
	void currentStateRequestHandler();
	bool gameStatusRequestHandler();

	IServerSocket& serverSocket;
	common::SharedMemory& sharedMemory;

	const int playerNumber;
};

}

#endif // SERVER_CONNECTION_H
