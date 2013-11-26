#include <common/CursorPosition.h>

using namespace common;

CursorPosition::CursorPosition()
	: x(300), y(300)
{
}

CursorPosition::CursorPosition(int x, int y)
	: x(x), y(y)
{
}

void CursorPosition::send(unsigned char* buf, int startPos) const
{
	buf[startPos + 0] = ((unsigned char*)&x)[0];
	buf[startPos + 1] = ((unsigned char*)&x)[1];
	buf[startPos + 2] = ((unsigned char*)&x)[2];
	buf[startPos + 3] = ((unsigned char*)&x)[3];
	buf[startPos + 4] = ((unsigned char*)&y)[0];
	buf[startPos + 5] = ((unsigned char*)&y)[1];
	buf[startPos + 6] = ((unsigned char*)&y)[2];
	buf[startPos + 7] = ((unsigned char*)&y)[3];

//	socket.send(&x, sizeof(int));
//	socket.send(&y, sizeof(int));
}

void CursorPosition::receive(unsigned char* buf, int startPos)
{
	((unsigned char*)&x)[0] = buf[startPos + 0];
	((unsigned char*)&x)[1] = buf[startPos + 1];
	((unsigned char*)&x)[2] = buf[startPos + 2];
	((unsigned char*)&x)[3] = buf[startPos + 3];
	((unsigned char*)&y)[0] = buf[startPos + 4];
	((unsigned char*)&y)[1] = buf[startPos + 5];
	((unsigned char*)&y)[2] = buf[startPos + 6];
	((unsigned char*)&y)[3] = buf[startPos + 7];
	
//	socket.receiveNoBlock(&x, sizeof(int));
//	socket.receiveNoBlock(&y, sizeof(int));
}
