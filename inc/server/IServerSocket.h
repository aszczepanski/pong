#ifndef ISERVER_SOCKET_H
#define ISERVER_SOCKET_H

#include <common/ISocket.h>
#include <stdexcept>

namespace server
{

/**
 * Interfejs serwera w połączeniu klient-serwer
 */
class IServerSocket
	: public common::ISocket
{

public:
	virtual void send(const void*, size_t) const = 0;
	virtual void receive(void*, size_t) const = 0;

	virtual ~IServerSocket() { }


/**
 * Wyjątek rzucany gdy wystąpi błąd socketu
 */
	class SocketError : public std::exception {};
/**
 * Wyjątek rzucany gdy zablokowany jest port
 */
	class BindError : public std::exception {};
/**
 * Wyjątek rzucany gdy nie uda się rozpoczęcie nasłuchiwania
 */
	class ListenError : public std::exception {};
/**
 * Wyjątek rzucany gdy nie uda się wysłać danych do serwera
 */
	class WriteError : public std::exception {};
/**
 * Wyjątek rzucany gdy nie uda się odebrać danych od serwera
 */
	class ReadError : public std::exception {};
/**
 * Wyjątek rzucany gdy nie uda się połączyć z klientem
 */
	class AcceptError : public std::exception {};
/** 
 * Wyjątek rzucany gdy w czasie 1000ms nie uda się odebrać danych od serwera
 */
	class TimeoutError : public std::exception {};
/**
 * Wyjątek rzucany gdy nie uda się odebrać danych od serwera
 */
	class SendtoError : public std::exception {};
/**
 * Wyjątek rzucany gdy nie uda się odebrać danych od serwera
 */
	class RecvfromError : public std::exception {};
/**
 * Wyjątek
 */
	class SelectError : public std::exception {};

};

}

#endif // ISERVER_SOCKET_H
