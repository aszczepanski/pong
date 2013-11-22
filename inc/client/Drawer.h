#ifndef DRAWER_H
#define DRAWER_H

#include <common/IThread.h>

namespace client
{

class SharedMemory;
class Communicator;

class Drawer
	: public common::IThread
{

public:
	Drawer(SharedMemory&, Communicator&);

private:
	virtual void* start_routine();
	
	SharedMemory& sharedMemory;
	Communicator& communicator;
};

}

#endif // DRAWER_h
