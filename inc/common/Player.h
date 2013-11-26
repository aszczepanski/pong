#ifndef PLAYER_H
#define PLAYER_H

#include <common/Transferable.h>
#include <common/Mutex.h>
#include <common/CursorPosition.h>

namespace common
{

class Player
	: public Transferable
{
public:
	Player();

	void getPosition(int& x, int& y) const;
	void setPosition(int x, int y);

	void getScore(int& score) const;
	void setScore(int score);

	virtual void send(unsigned char*, int startPos) const;
	virtual void receive(unsigned char*, int startPos);
private:
	int x, y;
	int score;

	mutable Mutex mutex;

};

}

#endif // PLAYER_H
