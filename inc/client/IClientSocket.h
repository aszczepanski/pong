#ifndef ICLIENT_SOCKET_H
#define ICLIENT_SOCKET_H

#include <common/ISocket.h>

namespace client
{

class IClientSocket
	: public common::ISocket
{

public:
	virtual void send(const void*, size_t) const = 0;
	virtual void receive(void*, size_t) const = 0;

	virtual ~IClientSocket() { }

};

}

#endif // ICLIENT_SOCKET_H
