#ifndef CONNECTION_UDP_H
#define CONNECTION_UDP_H

#include <common/IThread.h>
#include <server/IServerSocket.h>

namespace common
{
	class SharedMemory;
}

namespace server
{

class ConnectionUDP
	: public common::IThread
{
public:
	ConnectionUDP(IServerSocket&, common::SharedMemory&, int playerNumber);

private:
	virtual void* start_routine();

	void cursorPositionRequestHandler(unsigned char* buf);

	IServerSocket& serverSocket;
	common::SharedMemory& sharedMemory;

	const int playerNumber;
};

}

#endif // CONNECTION_UDP_H
