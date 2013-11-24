#ifndef ICOMMUNICATOR_H
#define ICOMMUNICATOR_H

#include <common/ICommunicator.h>
#include <common/IThread.h>
#include <common/Mutex.h>

namespace common
{

class CursorPosition;
class SharedMemory;

class ICommunicator
	: public IThread
{

public:
	ICommunicator(SharedMemory&);

	virtual void sendCursorPosition(const common::CursorPosition&) const = 0;
	virtual void sendStartRequest() const = 0;
	virtual void sendEndRequest() const = 0;
	virtual void getCurrentState() = 0;

protected:
	virtual void* start_routine() = 0;

	SharedMemory& sharedMemory;
};

}

#endif // ICOMMUNICATOR_H
