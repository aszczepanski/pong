#include <common/Drawer.h>
#include <common/SharedMemory.h>
#include <common/ICommunicator.h>
#include <common/CursorPosition.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace common;

#define USE_SDL

Drawer::Drawer(SharedMemory& sharedMemory, ICommunicator& communicator)
	: sharedMemory(sharedMemory), communicator(communicator)
{
}

void* Drawer::start_routine()
{
	std::cout << "Drawer thread" << std::endl;

#ifndef USE_SDL
  int x;
  bool playing = true;
  while(playing)
  {
    sharedMemory.getPlayerCameraPosition(x, 0);
    std::cout << x << "\n";
  }
#endif

#ifdef USE_SDL

	sf::RenderWindow window(sf::VideoMode(600, 600, 32), "Pong!");

/*
 	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
 	{
 		std::cout << SDL_GetError() << std::endl;
 //		return 1;
 	}

 	SDL_Window *win;
 	win = SDL_CreateWindow("Pong!", 100, 100, 600, 600, SDL_WINDOW_SHOWN);
 	if (!win)
 	{
 		std::cout << SDL_GetError() << std::endl;
 //		return 1;
 	}

 	SDL_Renderer *ren;
 	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
 	if (!ren)
 	{
 		std::cout << SDL_GetError() << std::endl;
 //		return 1;
 	}

 	SDL_Surface *bmp;
 	bmp = SDL_LoadBMP("green.bmp");
 	if (!bmp)
 	{
 		std::cout << SDL_GetError() << std::endl;
 //		return 1;
 	}

 	SDL_Texture *greenTex;
 	greenTex = SDL_CreateTextureFromSurface(ren, bmp);
 	SDL_FreeSurface(bmp);

 	SDL_Rect rectangle;
 	SDL_Event e;
*/
	

 	bool quit = false;
 	int lastX, lastY;
 	while (!quit)
 	{
/*
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				communicator.sendEndRequest();
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_SPACE:
						std::cout << "space" << std::endl;
						communicator.sendStartRequest();
						break;
					case SDLK_ESCAPE:
						std::cout << "escape" << std::endl;
						communicator.sendEndRequest();
						break;
				}
			}
			if (e.type == SDL_MOUSEMOTION)
			{
				lastX = e.motion.x;
				lastY = e.motion.y;
				communicator.sendCursorPosition(CursorPosition(lastX, lastY));
				//printf("\t\t%d %d\n", e.motion.x, e.motion.y);
			}
		}
    

 		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
 		SDL_RenderClear(ren);
*/
		sf::Vector2i mpos = sf::Mouse::getPosition(window);

		if (mpos.x >= 0 && mpos.y >= 0 && mpos.x < 600 && mpos.y < 600)
		{
			communicator.sendCursorPosition(CursorPosition(mpos.x, mpos.y));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			std::cout << "escape" << std::endl;
			communicator.sendEndRequest();
		}

 		int positionX, positionY;

 		// draw ball
 		Ball ball;
 		Player player[2];

 		sharedMemory.getCurrentState(ball, player[0], player[1]);

 		ball.getPosition(positionX, positionY);
 		//std::cout << positionX << " " << positionY << std::endl;
/* 		rectangle.x = positionX - 16;
 		rectangle.y = positionY - 16;
 		rectangle.w = 32;
 		rectangle.h = 32;
 		SDL_RenderCopy(ren, greenTex, NULL, &rectangle);
*/
		window.clear(sf::Color::Black);

		sf::CircleShape circle(16);
		circle.setPosition(positionX, positionY);
		circle.setFillColor(sf::Color::Green);
		window.draw(circle);



 		// draw bottom platform
 		player[0].getPosition(positionX, positionY);
 		//std::cout << positionX << " " << positionY << std::endl;
/* 		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
 		rectangle.x = positionX - 40;
 		rectangle.y = positionY - 7;
 		rectangle.w = 80;
 		rectangle.h = 14;
 		SDL_RenderFillRect(ren, &rectangle);
*/
		sf::RectangleShape bottomPlayer(sf::Vector2f(80, 14));
		bottomPlayer.setPosition(positionX - 40, positionY - 7);
		bottomPlayer.setFillColor(sf::Color::Red);
		window.draw(bottomPlayer);

 		// draw top platform
/* 		player[1].getPosition(positionX, positionY);
 		//std::cout << positionX << " " << positionY << std::endl;
 		SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
 		rectangle.x = positionX - 40;
 		rectangle.y = positionY - 7;
 		rectangle.w = 80;
 		rectangle.h = 14;
 		SDL_RenderFillRect(ren, &rectangle);

 		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
 		rectangle.x = 0;
 		rectangle.y = -30;
 		rectangle.w = 600;
 		rectangle.h = 60;
 		SDL_RenderFillRect(ren, &rectangle);

 		rectangle.x = -30;
 		rectangle.y = 0;
 		rectangle.w = 60;
 		rectangle.h = 600;
 		SDL_RenderFillRect(ren, &rectangle);

 		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
 		rectangle.x = 0;
 		rectangle.y = 570;
 		rectangle.w = 600;
 		rectangle.h = 60;
 		SDL_RenderFillRect(ren, &rectangle);

 		rectangle.x = 570;
 		rectangle.y = 0;
 		rectangle.w = 60;
 		rectangle.h = 600;
 		SDL_RenderFillRect(ren, &rectangle);
 		SDL_RenderPresent(ren);

*/

		window.display();

 		SDL_Delay((int)(1000.0/60.0));

 		sharedMemory.getEnded(quit);
 	}

// 	SDL_DestroyTexture(greenTex);
//	SDL_DestroyRenderer(ren);
// 	SDL_DestroyWindow(win);

// 	SDL_Quit();
#endif

	return NULL;
}
