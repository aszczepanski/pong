#include <common/Player.h>

using namespace common;

Player::Player()
{
}

void Player::send(ISocket&)
{
}

void Player::receive(ISocket&)
{
}

void Player::getPosition(int& x, int& y) const
{
	mutex.lock();
	x = y = 3;
	mutex.unlock();
}

void Player::setPosition(int x, int y)
{
}
