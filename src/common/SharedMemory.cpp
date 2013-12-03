#include <common/SharedMemory.h>
#include <common/Ball.h>
#include <common/Player.h>
#include <cassert>
#include <iostream>

using namespace common;

SharedMemory::SharedMemory()
	: started(false), ended(false)
{
}

void SharedMemory::addPoint(int nr)
{
	assert(nr == 0 || nr == 1);

	mutex.lock();

	int score;
	player[nr].getScore(score);
	score++;
	player[nr].setScore(score);

	mutex.unlock();

	std::cout << "player " << nr << " score: " << score << std::endl;
}

void SharedMemory::setPlayerCameraPosition(const int& x, int nr)
{
	assert(nr == 0 || nr == 1);

	mutex.lock();

	this->cameraPosition[nr] = x;

	mutex.unlock();
}

void SharedMemory::getPlayerCameraPosition(int& x, int nr) const
{
	assert(nr == 0 || nr == 1);

	mutex.lock();

	x = this->cameraPosition[nr];

	mutex.unlock();
}

void SharedMemory::getPlayerCursorPosition(CursorPosition& cursorPosition, int nr) const
{
	assert(nr == 0 || nr == 1);

	mutex.lock();

	cursorPosition = this->cursorPosition[nr];

	mutex.unlock();
}

void SharedMemory::setPlayerCursorPosition(const CursorPosition& cursorPosition, int nr)
{
	assert(nr == 0 || nr == 1);

	mutex.lock();

	this->cursorPosition[nr] = cursorPosition;

	mutex.unlock();
}

void SharedMemory::getCurrentState(Ball& b, Player& p0, Player& p1) const
{
	mutex.lock();

	b = ball;
	p0 = player[0];
	p1 = player[1];

	mutex.unlock();
}

void SharedMemory::setCurrentState(const Ball& b, const Player& p0, const Player& p1)
{
	int x,y;

	mutex.lock();

	ball = b;
	p0.getPosition(x,y);
	player[0].setPosition(x,y);
	p1.getPosition(x,y);
	player[1].setPosition(x,y);
//	player[0] = p0;
//	player[1] = p1;

	mutex.unlock();
}

void SharedMemory::getBall(Ball& ball) const
{
	mutex.lock();

	ball = this->ball;

	mutex.unlock();
}

void SharedMemory::setBall(const common::Ball& ball)
{
	mutex.lock();

	this->ball = ball;

	mutex.unlock();
}

void SharedMemory::getPlayer(Player& player, int nr) const
{
	assert(nr == 0 || nr == 1);
	mutex.lock();

	player = this->player[nr];

	mutex.unlock();
}

void SharedMemory::setPlayer(const common::Player& player, int nr)
{
	assert(nr == 0 || nr == 1);
	mutex.lock();

	this->player[nr] = player;

	mutex.unlock();
}

void SharedMemory::getStarted(bool& started) const
{
	mutex.lock();

	started = this->started;

	mutex.unlock();
}

void SharedMemory::setStarted(bool started)
{
	mutex.lock();

	this->started = started;

	mutex.unlock();
}

void SharedMemory::getEnded(bool& ended) const
{
	mutex.lock();

	ended = this->ended;

	mutex.unlock();
}

void SharedMemory::setEnded(bool ended)
{
	mutex.lock();

	this->ended = ended;

	mutex.unlock();
}
