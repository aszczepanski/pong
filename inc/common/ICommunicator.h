#ifndef ICOMMUNICATOR_H
#define ICOMMUNICATOR_H

namespace common
{

class CursorPosition;
class SharedMemory;

/**
 * Interfejs komunikatora
 */
class ICommunicator
{

public:
/**
 * Konstuktor inicjalizuje komunikator
 */
	ICommunicator(SharedMemory&);

/**
 * Wysyła pozycję kursora
 * @param cursorPosition aktualna pozycja kursora
 */
	virtual void sendCursorPosition(const common::CursorPosition& cursorPosition) const = 0;
/**
 * Wysyła żądanie startu
 */
	virtual void sendStartRequest() const = 0;
/**
 * Wysyła żądanie zakończenia
 */
	virtual void sendEndRequest() const = 0;

protected:

/**
 * Umożliwia wykorzystanie sharedMemory w klasach implementujących ICommunicator
 */
	SharedMemory& sharedMemory;
};

}

#endif // ICOMMUNICATOR_H
