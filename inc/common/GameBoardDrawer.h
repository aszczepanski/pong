#ifndef GAME_BOARD_DRAWER_H
#define GAME_BOARD_DRAWER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace common
{

class SharedMemory;

class GameBoardDrawer
{

public:
	GameBoardDrawer(SharedMemory&);

	void init();
	void drawBoard();
	void getMousePosition(int& x, int& y);
	
private:
	SharedMemory& sharedMemory;
	sf::RenderWindow window;
};

}

#endif // GAME_BOARD_DRAWER_H
