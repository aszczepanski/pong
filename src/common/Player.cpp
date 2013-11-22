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

void Player::getPosition(int& x, int& y)
{
	x = y = 3;
}

void Player::setPosition(int x, int y)
{
}
