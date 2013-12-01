#ifndef ICLIENT_SOCKET_H
#define ICLIENT_SOCKET_H

#include <common/ISocket.h>
#include <stdexcept>

namespace client
{

/**
 * Interfejs klienta w połączeniu klient-serwer
 */
class IClientSocket
	: public common::ISocket
{

public:
	virtual void send(const void*, size_t) const = 0;
	virtual void receive(void*, size_t) const = 0;
/**
 * Wirtualny destruktor umożliwia dziedziczenie
 */
	virtual ~IClientSocket() { }

/**
 * Wyjątek rzucany gdy wystąpi błąd socketu
 */
	class SocketError : public std::exception {};
/**
 * Wyjątek rzucany gdy wystąpi błąd aton
 */
	class AtonError : public std::exception {};
/**
 * Wyjątek rzucany gdy wystąpi błąd połączenia z serwerem
 */
	class ConnectError : public std::exception {};
/**
 * Wyjątek rzucany gdy nie uda się wysłać danych do serwera
 */
	class WriteError : public std::exception {};
/**
 * Wyjątek rzucany gdy nie uda się odebrać danych od serwera
 */
	class ReadError : public std::exception {};
/**
 * Wyjątek rzucany gdy wystąpi błąd hosta
 */
	class HostError : public std::exception {};
/**
 * Wyjątek rzucany gdu nie uda się wysłać danych do serwera
 */
	class SendtoError : public std::exception {};
/**
 * Wyjątek rzucany gdy nie uda się odebrać danych od serwera
 */
	class RecvfromError : public std::exception {};
/**
 * Wyjątek rzucany gdy nie uda się odebrać danych od serwera
 */
	class SelectError : public std::exception {};
/** 
 * Wyjątek rzucany gdy w czasie 1000ms nie uda się odebrać danych od serwera
 */
	class TimeoutError : public std::exception {};

};

}

#endif // ICLIENT_SOCKET_H
