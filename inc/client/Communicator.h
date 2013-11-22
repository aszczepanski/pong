#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <common/IThread.h>

namespace client
{

class SharedMemory;
class ClientTCP;

class Communicator
	: public common::IThread
{

public:
	Communicator(SharedMemory&, ClientTCP&);

private:
	virtual void* start_routine();

	SharedMemory& sharedMemory;
	ClientTCP& clientTCP;

};

}

#endif // COMMUNICATOR_H
