#ifndef ICOMMUNICATOR_H
#define ICOMMUNICATOR_H

namespace common
{

class CursorPosition;
class SharedMemory;

class ICommunicator
{

public:
	ICommunicator(SharedMemory&);

	virtual void sendCursorPosition(const common::CursorPosition&) const = 0;
	virtual void sendStartRequest() const = 0;
	virtual void sendEndRequest() const = 0;

protected:

	SharedMemory& sharedMemory;
};

}

#endif // ICOMMUNICATOR_H
