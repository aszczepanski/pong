#ifndef BALL_H
#define BALL_H

#include <common/Transferable.h>

namespace common
{

class Ball
	: public Transferable
{
public:
	Ball();
	void getPosition(int& x, int& y);
	void setPosition(int x, int y);

	virtual void send(ISocket&);
	virtual void receive(ISocket&);
private:
	int x, y;
};

}

#endif // BALL_H
