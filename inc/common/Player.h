#ifndef PLAYER_H
#define PLAYER_H

#include <common/Transferable.h>

namespace common
{

class Player
	: public Transferable
{
public:
	Player();

	void getPosition(int& x, int& y);
	void setPosition(int x, int y);

	void getScore(int& score);
	void setScore(int score);

	virtual void send(ISocket&);
	virtual void receive(ISocket&);
private:
	int x;
	int score;

};

}

#endif // PLAYER_H
