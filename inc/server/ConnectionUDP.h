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

/**
 * Wątek odpowiedzialny za odbiór komunikatów UDP
 */
class ConnectionUDP
	: public common::IThread
{
public:
/**
 * Konstruktor
 * @param playerNumber Numer gracza z którym się komunikuje
 */
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
