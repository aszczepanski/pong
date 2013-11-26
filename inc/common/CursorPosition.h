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

	virtual void send(unsigned char*, int startPos) const;
	virtual void receive(unsigned char*, int startPos);
};

}

#endif // CURSOR_POSITION_H
