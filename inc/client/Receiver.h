#ifndef RECEIVER_H
#define RECEIVER_H

#include <common/IThread.h>

namespace common
{
	class SharedMemory;
	class ISocket;
}

namespace client
{

class Receiver
	: public common::IThread
{

public:

	Receiver(common::SharedMemory&, common::ISocket&);

private:
	
	virtual void* start_routine();

	void gameStatusRequestHandler();
	void stateRequestHandler();

	common::SharedMemory& sharedMemory;
	common::ISocket& socket;

};

}

#endif // RECEIVER_H
