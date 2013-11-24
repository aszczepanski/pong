#include <common/Ball.h>
#include <common/ISocket.h>

using namespace common;

Ball::Ball()
{
}

void Ball::send(ISocket& socket) const
{
	socket.send(&x, sizeof(int));
	socket.send(&y, sizeof(int));
}

void Ball::receive(ISocket& socket)
{
	socket.receiveNoBlock(&x, sizeof(int));
	socket.receiveNoBlock(&y, sizeof(int));
}

void Ball::getPosition(int& x, int& y) const
{
//	mutex.lock();

	x = this->x;
	y = this->y;

//	mutex.unlock();
}

void Ball::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
