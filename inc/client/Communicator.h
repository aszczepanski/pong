#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <common/IThread.h>

namespace common
{
	class CursorPosition;
}

namespace client
{

class SharedMemory;
class ClientTCP;

class Communicator
	: public common::IThread
{

public:
	Communicator(SharedMemory&, ClientTCP&);

	void sendCursorPosition(common::CursorPosition&) const;
	void sendStartRequest() const;
	void sendEndRequest() const;
	void getCurrentState();

private:
	virtual void* start_routine();

	SharedMemory& sharedMemory;
	ClientTCP& clientTCP;

};

}

#endif // COMMUNICATOR_H
