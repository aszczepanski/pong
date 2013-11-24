#ifndef DRAWER_H
#define DRAWER_H

#include <common/IThread.h>

namespace common
{
	class SharedMemory;
}

namespace client
{

class Communicator;

class Drawer
	: public common::IThread
{

public:
	Drawer(common::SharedMemory&, Communicator&);

private:
	virtual void* start_routine();

	common::SharedMemory& sharedMemory;
	Communicator& communicator;
};

}

#endif // DRAWER_h
