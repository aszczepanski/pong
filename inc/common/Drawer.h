#ifndef DRAWER_H
#define DRAWER_H

#include <common/IThread.h>
#include <common/Camera.h>
namespace common
{

class ICommunicator;
class SharedMemory;

class Drawer
	: public common::IThread
{

public:
	Drawer(common::SharedMemory&, ICommunicator&);

private:
	virtual void* start_routine();
	common::SharedMemory& sharedMemory;
	ICommunicator& communicator;
};

}

#endif // DRAWER_h
