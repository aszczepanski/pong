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

/**
 * Odpowiada za wysyłanie danych do serwera
 */
class Communicator
	: public common::ICommunicator, public common::IThread
{

public:
/**
 * Inicjalizuje komunikator
 */
	Communicator(common::SharedMemory&, IClientSocket& clientTCP, IClientSocket& clientUDP);

	void sendCursorPosition(const common::CursorPosition&) const;

	void sendStartRequest() const;
	void sendEndRequest() const;

private:
	virtual void* start_routine();

	IClientSocket& clientTCP;
	IClientSocket& clientUDP;

	static common::Mutex mutex;
};

}

#endif // COMMUNICATOR_H
