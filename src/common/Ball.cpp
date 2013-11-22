#include <common/Ball.h>

using namespace common;

Ball::Ball()
{
}

void Ball::send(ISocket&)
{
}

void Ball::receive(ISocket&)
{
}

void Ball::getPosition(int& x, int& y) const
{
	mutex.lock();
	x = y = 2;
	mutex.unlock();
}

void Ball::setPosition(int x, int y)
{
}
