#ifndef TRANSFERABLE_H
#define TRANSFERABLE_H

namespace common
{

class ISocket;

class Transferable
{
public:
	virtual void send(ISocket&) = 0;
	virtual void receive(ISocket&) = 0;

	virtual ~Transferable() { }
};

}

#endif // TRANSFERABLE_H
