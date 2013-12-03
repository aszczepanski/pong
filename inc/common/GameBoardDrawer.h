#ifndef GAME_BOARD_DRAWER_H
#define GAME_BOARD_DRAWER_H

#include <common/IThread.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace common
{

class SharedMemory;

class GameBoardDrawer
	: public IThread
{

public:
	GameBoardDrawer(SharedMemory&);
	~GameBoardDrawer();

	void init();
	void drawBoard();
	void getMousePosition(int& x, int& y);

	sf::RenderWindow* getWindow() {
		return window;
	}
	
private:
	virtual void* start_routine();

	SharedMemory& sharedMemory;
	sf::RenderWindow* window;
};

}

#endif // GAME_BOARD_DRAWER_H
