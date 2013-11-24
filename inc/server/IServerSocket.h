#ifndef ISERVER_SOCKET_H
#define ISERVER_SOCKET_H

#include <common/ISocket.h>

namespace server
{

class IServerSocket
	: public common::ISocket
{

public:
	virtual void send(const void*, size_t) const = 0;
	virtual void receive(void*, size_t) const = 0;

	virtual IServerSocket* waitForSocket() = 0;

	virtual ~IServerSocket() { }

};

}

#endif // ISERVER_SOCKET_H
