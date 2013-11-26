#ifndef ICLIENT_SOCKET_H
#define ICLIENT_SOCKET_H

#include <common/ISocket.h>
#include <stdexcept>

namespace client
{

class IClientSocket
	: public common::ISocket
{

public:
	virtual void send(const void*, size_t) const = 0;
	virtual void receive(void*, size_t) const = 0;

	virtual ~IClientSocket() { }

	class SocketError : public std::exception {};
	class AtonError : public std::exception {};
	class ConnectError : public std::exception {};
	class WriteError : public std::exception {};
	class ReadError : public std::exception {};
	class HostError : public std::exception {};
	class SendtoError : public std::exception {};
	class RecvfromError : public std::exception {};
	class SelectError : public std::exception {};
	class TimeoutError : public std::exception {};

};

}

#endif // ICLIENT_SOCKET_H
