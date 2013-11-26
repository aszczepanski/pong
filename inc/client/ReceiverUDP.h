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

class ReceiverUDP
	: public common::IThread
{

public:

	ReceiverUDP(common::SharedMemory&, common::ISocket&);

private:
	
	virtual void* start_routine();

	void stateRequestHandler(unsigned char* buf);

	common::SharedMemory& sharedMemory;
	common::ISocket& socket;

};

}

#endif // RECEIVER_UDP_H
