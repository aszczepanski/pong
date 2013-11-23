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
	socket.receive(&x, sizeof(int));
	socket.receive(&y, sizeof(int));
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
