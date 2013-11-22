#ifndef ISOCKET_H
#define ISOCKET_H

#include <cstddef>

namespace common
{

class ISocket
{

public:
	virtual void send(void*, size_t) const = 0;
	virtual void receive(void*, size_t) const = 0;

	virtual ~ISocket() { }
};

}

#endif // ISOCKET_H
