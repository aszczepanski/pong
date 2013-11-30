#include <common/Drawer.h>
#include <common/SharedMemory.h>
#include <common/ICommunicator.h>
#include <common/CursorPosition.h>
#include <common/Camera.h>
#include <iostream>
#include <cstddef>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>

using namespace common;

Drawer::Drawer(SharedMemory& sharedMemory, ICommunicator& communicator, Camera* camera)
	: sharedMemory(sharedMemory), communicator(communicator), camera(camera)
{
}

void Drawer::setCamera(Camera* camera)
{
	this->camera = camera;
}

void Drawer::run()
{
	std::cout << "Drawer thread" << std::endl;

	sf::RenderWindow window(sf::VideoMode(600, 600, 32), "Pong!");

 	bool quit = false;
 	float tmp_position;

 	while (!quit)
 	{
		sf::Vector2i mpos = sf::Mouse::getPosition(window);
		if (camera)
		{
			camera->getPosition(tmp_position);
			mpos.x = int(tmp_position * 600);
		}

		mpos.x = std::max(mpos.x, 0);
		mpos.x = std::min(mpos.x, 599);

		communicator.sendCursorPosition(CursorPosition(mpos.x, mpos.y));

#ifndef __APPLE__
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			std::cout << "escape" << std::endl;
			communicator.sendEndRequest();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			std::cout << "space" << std::endl;
			communicator.sendStartRequest();
		}
#endif

 		int positionX, positionY;

 		// draw ball
 		Ball ball;
 		Player player[2];

 		sharedMemory.getCurrentState(ball, player[0], player[1]);

 		ball.getPosition(positionX, positionY);
		window.clear(sf::Color::Black);

		sf::CircleShape circle(16);
		circle.setPosition(positionX - 16, positionY - 16);
		circle.setFillColor(sf::Color::Green);
		window.draw(circle);


 		// draw bottom platform
 		player[0].getPosition(positionX, positionY);

		sf::RectangleShape bottomPlayer(sf::Vector2f(80, 14));
		bottomPlayer.setPosition(positionX - 40, positionY - 7);
		bottomPlayer.setFillColor(sf::Color::Red);
		window.draw(bottomPlayer);

 		// draw top platform
 		player[1].getPosition(positionX, positionY);

		sf::RectangleShape topPlayer(sf::Vector2f(80, 14));
		topPlayer.setPosition(positionX - 40, positionY - 7);
		topPlayer.setFillColor(sf::Color::Yellow);
		window.draw(topPlayer);

		sf::RectangleShape topBorder(sf::Vector2f(600, 60));
		topBorder.setPosition(0, -30);
		topBorder.setFillColor(sf::Color::Blue);
		window.draw(topBorder);

		sf::RectangleShape leftBorder(sf::Vector2f(60, 600));
		leftBorder.setPosition(-30, 0);
		leftBorder.setFillColor(sf::Color::Blue);
		window.draw(leftBorder);

		sf::RectangleShape bottomBorder(sf::Vector2f(600, 60));
		bottomBorder.setPosition(0, 570);
		bottomBorder.setFillColor(sf::Color::Blue);
		window.draw(bottomBorder);

		sf::RectangleShape rightBorder(sf::Vector2f(60, 600));
		rightBorder.setPosition(570, 0);
		rightBorder.setFillColor(sf::Color::Blue);
		window.draw(rightBorder);

		window.display();

		usleep(25000);

 		sharedMemory.getEnded(quit);
 	}
}
