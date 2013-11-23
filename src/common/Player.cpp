#include <common/Player.h>
#include <common/ISocket.h>

using namespace common;

Player::Player()
{
}

void Player::send(ISocket& socket) const
{
	socket.send(&x, sizeof(int));
	socket.send(&y, sizeof(int));
	socket.send(&score, sizeof(int));
}

void Player::receive(ISocket& socket)
{
	socket.receive(&x, sizeof(int));
	socket.receive(&y, sizeof(int));
	socket.receive(&score, sizeof(int));
}

void Player::getPosition(int& x, int& y) const
{
//	mutex.lock();

	x = this->x;
	y = this->y;

//	mutex.unlock();
}

void Player::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
