#ifndef ISOCKET_H
#define ISOCKET_H

#include <cstddef>

namespace common
{

/**
 * Interfejs socketu
 */
class ISocket
{

public:
/**
 * Wysyła dane
 */
	virtual void send(const void*, size_t) const = 0;
/**
 * Odbiera dane. Jeśli nie ma danych to blokuje.
 */
	virtual void receive(void*, size_t) const = 0;
/**
 * Odbiera dane. Jeśli nie ma danych to rzuca wyjątek.
 */
	virtual void receiveNoBlock(void*, size_t) const = 0;

/**
 * Wirtualny destruktor umożliwia dziedziczenie
 */
	virtual ~ISocket() { }
};

}

#endif // ISOCKET_H
