#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <common/ICommunicator.h>
#include <common/IThread.h>
#include <common/Mutex.h>

namespace common
{
	class CursorPosition;
	class SharedMemory;
}

namespace client
{

class IClientSocket;

class Communicator
	: public common::ICommunicator
{

public:
	Communicator(common::SharedMemory&, IClientSocket&);

	void sendCursorPosition(const common::CursorPosition&) const;
	void sendStartRequest() const;
	void sendEndRequest() const;
	void getCurrentState();

private:
	virtual void* start_routine();

	IClientSocket& clientSocket;

	static common::Mutex mutex;
};

}

#endif // COMMUNICATOR_H
