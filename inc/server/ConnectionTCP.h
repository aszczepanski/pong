#ifndef CONNECTION_TCP_H
#define CONNECTION_TCP_H

#include <common/IThread.h>
#include <server/IServerSocket.h>

namespace common
{
	class SharedMemory;
}

namespace server
{

class ConnectionTCP
	: public common::IThread
{
public:
	ConnectionTCP(IServerSocket&, common::SharedMemory&, int playerNumber);

private:
	virtual void* start_routine();

	void startRequestHandler();
	void endRequestHandler();

	IServerSocket& serverSocket;
	common::SharedMemory& sharedMemory;

	const int playerNumber;
};

}

#endif // CONNECTION_TCP_H
