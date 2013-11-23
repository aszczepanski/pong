#ifndef SERVER_TCP_CONNECTION_H
#define SERVER_TCP_CONNECTION_H

#include <common/IThread.h>
#include <server/ServerTCP.h>
#include <server/ServerUDP.h>

namespace common
{
	class SharedMemory;
}

namespace server
{

class ServerTCPConnection
	: public common::IThread
{
public:
	ServerTCPConnection(ServerUDP, common::SharedMemory&);

private:
	virtual void* start_routine();

	void startRequestHandler();
	void endRequestHandler();
	void cursorPositionRequestHandler();
	void currentStateRequestHandler();
	void gameStatusRequestHandler();

	ServerUDP serverUDP;
	common::SharedMemory& sharedMemory;
};

}

#endif // SERVER_TCP_CONNECTION_H
