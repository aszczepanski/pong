#ifndef CURSOR_POSITION_H
#define CURSOR_POSITION_H

#include <common/Transferable.h>

namespace common
{

class CursorPosition
	: public Transferable
{
public:
	CursorPosition();
	CursorPosition(int x, int y);

	int x, y;

	virtual void send(ISocket&) const;
	virtual void receive(ISocket&);
};

}

#endif // CURSOR_POSITION_H
