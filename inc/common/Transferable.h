#ifndef TRANSFERABLE_H
#define TRANSFERABLE_H

namespace common
{

class Transferable
{
public:
	virtual void send(unsigned char*, int startPos) const = 0;
	virtual void receive(unsigned char*, int startPos) = 0;

	virtual ~Transferable() { }
};

}

#endif // TRANSFERABLE_H
