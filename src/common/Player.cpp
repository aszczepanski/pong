#include <common/Player.h>

using namespace common;

Player::Player()
{
}

void Player::send(unsigned char* buf, int startPos) const
{
	buf[startPos + 0] = ((unsigned char*)&x)[0];
	buf[startPos + 1] = ((unsigned char*)&x)[1];
	buf[startPos + 2] = ((unsigned char*)&x)[2];
	buf[startPos + 3] = ((unsigned char*)&x)[3];
	buf[startPos + 4] = ((unsigned char*)&y)[0];
	buf[startPos + 5] = ((unsigned char*)&y)[1];
	buf[startPos + 6] = ((unsigned char*)&y)[2];
	buf[startPos + 7] = ((unsigned char*)&y)[3];
	buf[startPos + 8] = ((unsigned char*)&score)[0];
	buf[startPos + 9] = ((unsigned char*)&score)[1];
	buf[startPos + 10] = ((unsigned char*)&score)[2];
	buf[startPos + 11] = ((unsigned char*)&score)[3];

//	socket.send(&x, sizeof(int));
//	socket.send(&y, sizeof(int));
//	socket.send(&score, sizeof(int));
}

void Player::receive(unsigned char* buf, int startPos)
{
	((unsigned char*)&x)[0] = buf[startPos + 0];
	((unsigned char*)&x)[1] = buf[startPos + 1];
	((unsigned char*)&x)[2] = buf[startPos + 2];
	((unsigned char*)&x)[3] = buf[startPos + 3];
	((unsigned char*)&y)[0] = buf[startPos + 4];
	((unsigned char*)&y)[1] = buf[startPos + 5];
	((unsigned char*)&y)[2] = buf[startPos + 6];
	((unsigned char*)&y)[3] = buf[startPos + 7];
	((unsigned char*)&score)[0] = buf[startPos + 8];
	((unsigned char*)&score)[1] = buf[startPos + 9];
	((unsigned char*)&score)[2] = buf[startPos + 10];
	((unsigned char*)&score)[3] = buf[startPos + 11];
//	socket.receiveNoBlock(&x, sizeof(int));
//	socket.receiveNoBlock(&y, sizeof(int));
//	socket.receiveNoBlock(&score, sizeof(int));
}

void Player::getPosition(int& x, int& y) const
{
	x = this->x;
	y = this->y;
}

void Player::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
