#ifndef PLAYER_H
#define PLAYER_H

#include <common/Transferable.h>
#include <common/Mutex.h>
#include <common/CursorPosition.h>

namespace common
{

/**
 * Klasa przechowująca pozycję oraz wynik gracza
 */
class Player
	: public Transferable
{
public:
/**
 * Konstruktor
 */
	Player();
/**
 * Zwraca pozycję
 * @param x pozycja x
 * @param y pozycja y
 */
	void getPosition(int& x, int& y) const;
/**
 * Ustawia pozycję
 * @param x pozycja x
 * @param y pozycja y
 */
	void setPosition(int x, int y);

/**
 * Pobiera wynik
 * @param score wynik
 */
	void getScore(int& score) const;
/**
 * Ustawia wynik
 * @param score wynik
 */
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
