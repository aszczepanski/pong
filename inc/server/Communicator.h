#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <common/ICommunicator.h>
#include <common/Mutex.h>

namespace common
{
	class CursorPosition;
	class SharedMemory;
}

namespace server
{

class ServerTCP;

/**
 * Komunikator serwera. Nie wysyła danych a jedynie zapisuje je w pamięci współdzielonej.
 */
class Communicator
	: public common::ICommunicator
{

public:
/**
 * Konstuktor inicjalizuje komunikator
 */
	Communicator(common::SharedMemory&, ServerTCP&);

	void sendCursorPosition(const common::CursorPosition& cursorPosition) const;
	void sendStartRequest() const;
	void sendEndRequest() const;

private:

	ServerTCP& serverTCP;

	mutable common::Mutex mutex;

};

}

#endif // COMMUNICATOR_H
