#ifndef RECEIVER_UDP_H
#define RECEIVER_UDP_H

#include <common/IThread.h>

namespace common
{
	class SharedMemory;
	class ISocket;
}

namespace client
{

/**
 * Klasa odbierająca dane od serwera wykorzystująca klienta UDP
 */
class ReceiverUDP
	: public common::IThread
{

public:

/**
 * Konstruktor
 * @param isocket Referencja do klienta UDP
 */
	ReceiverUDP(common::SharedMemory&, common::ISocket& isocket);

private:
	
	virtual void* start_routine();

	void stateRequestHandler(unsigned char* buf);

	common::SharedMemory& sharedMemory;
	common::ISocket& socket;

};

}

#endif // RECEIVER_UDP_H
