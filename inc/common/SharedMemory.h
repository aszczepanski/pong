#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <common/Mutex.h>
#include <common/Ball.h>
#include <common/Player.h>
#include <common/CursorPosition.h>

namespace common
{

/**
 * Klasa ułatwia przechowywanie danych i wykorzystywanie ich w różnych wątkach. Umożliwia współbieżny dostęp do danych.
 */
class SharedMemory
{
public:
/**
 * Konstruktor
 */
	SharedMemory();

/**
 * Zwraca piłkę
 */
	void getBall(Ball&) const;
/**
 * Ustawia piłkę
 */
	void setBall(const Ball&);

/**
 * Zwraca gracza
 * @param nr numer gracza
 */
	void getPlayer(Player&, int nr) const;
/**
 * Ustawia gracza
 * @param nr numer gracza
 */
	void setPlayer(const Player&, int nr);

/**
 * Zwraca pozycję kursora
 * @param nr numer gracza
 */
	void getPlayerCursorPosition(CursorPosition&, int nr) const;
/**
 * Ustawia pozycję kursora
 * @param nr numer gracza
 */
	void setPlayerCursorPosition(const CursorPosition&, int nr);

/**
 * Zwraca pozycję kamery
 * @param nr numer gracza
 */
	void getPlayerCameraPosition(int&, int nr) const;
/**
 * Ustawia pozycję kamery
 * @param nr numer gracza
 */
	void setPlayerCameraPosition(const int&, int nr);

/**
 * Zwraca aktualny stan gry
 */
	void getCurrentState(Ball&, Player&, Player&) const;
/**
 * Ustawia aktualny stan gry
 */
	void setCurrentState(const Ball&, const Player&, const Player&);

/**
 * Zwraca informację czy gra wystartowała
 */
	void getStarted(bool&) const;
/**
 * Ustawia informację o starcie gry
 */
	void setStarted(bool);

/**
 * Zwraca informację czy gra się zakończyła
 */
	void getEnded(bool&) const;
/**
 * Ustawia informację o zakończeniu gry
 */
	void setEnded(bool);

private:
	Ball ball;
	Player player[2];
	CursorPosition cursorPosition[2];
	int cameraPosition[2];

	bool started, ended;

	mutable Mutex mutex;
};

}

#endif // SHARED_MEMORY_H
