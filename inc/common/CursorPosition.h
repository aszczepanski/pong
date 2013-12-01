#ifndef CURSOR_POSITION_H
#define CURSOR_POSITION_H

#include <common/Transferable.h>

namespace common
{

/**
 * Klasa reprezentująca pozycję kursora - myszki lub ręki
 */
class CursorPosition
	: public Transferable
{
public:
/**
 * Konstruktor
 */
	CursorPosition();
/**
 * Konstruktor ustawia pozycję startową x i y
 * @param x pozycja x
 * @param y pozycja y
 */
	CursorPosition(int x, int y);
/**
 * Zawiera aktualną pozycję x kursora
 */
	int x;
/**
 * Zawiera aktualną pozycję y kursora
 */
	int y;

	virtual void send(unsigned char*, int startPos) const;
	virtual void receive(unsigned char*, int startPos);
};

}

#endif // CURSOR_POSITION_H
