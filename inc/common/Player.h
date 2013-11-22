#ifndef PLAYER_H
#define PLAYER_H

#include <common/Transferable.h>
#include <common/Mutex.h>

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

	virtual void send(ISocket&);
	virtual void receive(ISocket&);
private:
	int x;
	int score;

	mutable Mutex mutex;

};

}

#endif // PLAYER_H
