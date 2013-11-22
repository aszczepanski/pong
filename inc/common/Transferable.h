#ifndef TRANSFERABLE_H
#define TRANSFERABLE_H

class ISocket;

namespace common
{

class Transferable
{
public:
	virtual void send(ISocket&) = 0;
	virtual void receive(ISocket&) = 0;

	virtual ~Transferable() { }
};

}

#endif // TRANSFERABLE_H
