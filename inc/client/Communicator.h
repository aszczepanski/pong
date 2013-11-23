#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <common/IThread.h>
#include <common/Mutex.h>

namespace common
{
	class CursorPosition;
	class SharedMemory;
}

namespace client
{

class ClientTCP;
class ClientUDP;

class Communicator
	: public common::IThread
{

public:
	//Communicator(common::SharedMemory&, ClientTCP&);
	Communicator(common::SharedMemory&, ClientUDP&);

	void sendCursorPosition(const common::CursorPosition&) const;
	void sendStartRequest() const;
	void sendEndRequest() const;
	void getCurrentState();

private:
	virtual void* start_routine();

	common::SharedMemory& sharedMemory;
	//ClientTCP& clientTCP;
	ClientUDP& clientUDP;

	mutable common::Mutex mutex;
};

}

#endif // COMMUNICATOR_H
