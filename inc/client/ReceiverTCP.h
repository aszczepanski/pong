#ifndef RECEIVER_TCP_H
#define RECEIVER_TCP_H

#include <common/IThread.h>

namespace common
{
	class SharedMemory;
	class ISocket;
}

namespace client
{

/**
 * Klasa odbierająca dane od serwera wykorzystująca klienta TCP
 */
class ReceiverTCP
	: public common::IThread
{

public:
/**
 * Konstruktor
 * @param isocket Referencja do klienta TCP
 */
	ReceiverTCP(common::SharedMemory&, common::ISocket& isocket);

private:
	
	virtual void* start_routine();

	void startRequestHandler();
	void endRequestHandler();

	common::SharedMemory& sharedMemory;
	common::ISocket& socket;

};

}

#endif // RECEIVER_TCP_H
