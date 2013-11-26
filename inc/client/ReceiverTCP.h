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

class ReceiverTCP
	: public common::IThread
{

public:

	ReceiverTCP(common::SharedMemory&, common::ISocket&);

private:
	
	virtual void* start_routine();

	void startRequestHandler();
	void endRequestHandler();

	common::SharedMemory& sharedMemory;
	common::ISocket& socket;

};

}

#endif // RECEIVER_TCP_H
