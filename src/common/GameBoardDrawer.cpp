#include <common/GameBoardDrawer.h>
#include <common/SharedMemory.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <common/dimmensions.h>
#include <iostream>
#include <cstdio>
#include <unistd.h>

using namespace common;

GameBoardDrawer::GameBoardDrawer(SharedMemory& sharedMemory)
: sharedMemory(sharedMemory)
{
}

GameBoardDrawer::~GameBoardDrawer()
{
	delete window;
	window = NULL;
}

void GameBoardDrawer::init()
{
//	window->create(sf::VideoMode(windowWidth, windowHeight, 32), "Pong!");
	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight, 32), "Pong!");
	window->setActive(false);
}

void* GameBoardDrawer::start_routine()
{
	std::cout << "GameBoardDrawer thread" << std::endl;

	window->setActive(true);

 	bool quit = false;

 	while (!quit)
 	{

		drawBoard();

		usleep(25000);

 		sharedMemory.getEnded(quit);
 	}

	return NULL;
}

void GameBoardDrawer::getMousePosition(int& x, int& y)
{
	sf::Vector2i mpos = sf::Mouse::getPosition(*window);

	mpos.x = std::max(mpos.x, 0);
	mpos.x = std::min(mpos.x, windowWidth-1);

	x = mpos.x;
	y = mpos.y;
}

void GameBoardDrawer::drawBoard()
{
	int positionX, positionY;
	Ball ball;
	Player player[2];

	// draw ball
	sharedMemory.getCurrentState(ball, player[0], player[1]);

	ball.getPosition(positionX, positionY);
	window->clear(sf::Color::Black);

	sf::CircleShape circle(circleRadius);
	circle.setPosition(positionX - circleRadius, positionY - circleRadius);
	circle.setFillColor(sf::Color::Green);
	window->draw(circle);

	// draw bottom platform
	player[0].getPosition(positionX, positionY);

	sf::RectangleShape bottomPlayer(sf::Vector2f(platformWidth, platformHeight));
	bottomPlayer.setPosition(positionX - platformWidth/2, positionY - platformHeight/2);
	bottomPlayer.setFillColor(sf::Color::Red);
	window->draw(bottomPlayer);

	// draw top platform
	player[1].getPosition(positionX, positionY);

	sf::RectangleShape topPlayer(sf::Vector2f(platformWidth, platformHeight));
	topPlayer.setPosition(positionX - platformWidth/2, positionY - platformHeight/2);
	topPlayer.setFillColor(sf::Color::Yellow);
	window->draw(topPlayer);

	// draw borders
	sf::RectangleShape topBorder(sf::Vector2f(windowWidth, 2*borderSize));
	topBorder.setPosition(0, -borderSize);
	topBorder.setFillColor(sf::Color::Blue);
	window->draw(topBorder);

	sf::RectangleShape leftBorder(sf::Vector2f(2*borderSize, windowHeight));
	leftBorder.setPosition(-borderSize, 0);
	leftBorder.setFillColor(sf::Color::Blue);
	window->draw(leftBorder);

	sf::RectangleShape bottomBorder(sf::Vector2f(windowWidth, 2*borderSize));
	bottomBorder.setPosition(0, windowHeight-borderSize);
	bottomBorder.setFillColor(sf::Color::Blue);
	window->draw(bottomBorder);

	sf::RectangleShape rightBorder(sf::Vector2f(2*borderSize, windowHeight));
	rightBorder.setPosition(windowWidth-borderSize, 0);
	rightBorder.setFillColor(sf::Color::Blue);
	window->draw(rightBorder);

	static sf::Font font;
	static bool fontLoaded = false;
	if (!fontLoaded && font.loadFromFile("dreamorphans.ttf"))
	{
		std::cout << "font loaded" << std::endl;
		fontLoaded = true;
	}
	
	if (fontLoaded)
	{
		static int score = 0;
		player[0].getScore(score);

		char buffer[32];
		sprintf(buffer, "score: %d", score);

		static sf::Text text;
		text.setFont(font);
		text.setString(buffer);
		text.setCharacterSize(24);
		text.setColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);
		text.setPosition(20,20);
		window->draw(text);

		player[1].getScore(score);
		sprintf(buffer, "score: %d", score);
		text.setString(buffer);
		text.setPosition(20,windowHeight-54);
		window->draw(text);
	}

	window->display();
}
