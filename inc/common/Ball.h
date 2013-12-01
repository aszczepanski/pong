#ifndef BALL_H
#define BALL_H

#include <common/Transferable.h>
#include <common/Mutex.h>

namespace common
{

/**
 * Klasa przechowująca położenie piłki
 */
class Ball
	: public Transferable
{
public:
/**
 * Konstruktor
 */
	Ball();
/**
 * Pobiera pozycję piłki
 * @param x pozycja x
 * @param y pozycja y
 */
	void getPosition(int& x, int& y) const;
/**
 * Ustawia pozycję piłki
 * @param x pozycja x
 * @param y pozycja y
 */
	void setPosition(int x, int y);

	virtual void send(unsigned char*, int startPos) const;
	virtual void receive(unsigned char*, int startPos);
private:
	int x, y;

	mutable Mutex mutex;
};

}

#endif // BALL_H
