#include <common/CursorPosition.h>
#include <common/ISocket.h>

using namespace common;

CursorPosition::CursorPosition()
	: x(300), y(300)
{
}

CursorPosition::CursorPosition(int x, int y)
	: x(x), y(y)
{
}

void CursorPosition::send(ISocket& socket) const
{
	socket.send(&x, sizeof(int));
	socket.send(&y, sizeof(int));
}

void CursorPosition::receive(ISocket& socket)
{
	socket.receive(&x, sizeof(int));
	socket.receive(&y, sizeof(int));
}
