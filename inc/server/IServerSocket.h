#ifndef ISERVER_SOCKET_H
#define ISERVER_SOCKET_H

#include <common/ISocket.h>
#include <stdexcept>

namespace server
{

class IServerSocket
	: public common::ISocket
{

public:
	virtual void send(const void*, size_t) const = 0;
	virtual void receive(void*, size_t) const = 0;

	virtual ~IServerSocket() { }


	class SocketError : public std::exception {};
	class BindError : public std::exception {};
	class ListenError : public std::exception {};
	class WriteError : public std::exception {};
	class ReadError : public std::exception {};
	class AcceptError : public std::exception {};
	class TimeoutError : public std::exception {};
	class SendtoError : public std::exception {};
	class RecvfromError : public std::exception {};
	class SelectError : public std::exception {};

};

}

#endif // ISERVER_SOCKET_H
