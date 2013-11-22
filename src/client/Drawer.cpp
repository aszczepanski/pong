#include <client/Drawer.h>
#include <client/SharedMemory.h>
#include <client/Communicator.h>
#include <iostream>
#include <SDL2/SDL.h>

using namespace client;

Drawer::Drawer(SharedMemory& sharedMemory, Communicator& communicator)
	: sharedMemory(sharedMemory), communicator(communicator)
{
}

void* Drawer::start_routine()
{
	std::cout << "Drawer thread" << std::endl;


	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
//		return 1;
	}

	SDL_Window *win;
	win = SDL_CreateWindow("Hello World!", 100, 100, 600, 600, SDL_WINDOW_SHOWN);
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

	bool quit = false;
	float lastX, lastY;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				quit = true;
			}
			if (e.type == SDL_MOUSEMOTION)
			{
				lastX = e.motion.x / 100.0f;
				lastY = e.motion.y / 100.0f;
				//printf("\t\t%d %d\n", e.motion.x, e.motion.y);
			}
		}

//		b2Vec2 pos = tmpbody->GetPosition();
//		b2Vec2 tmpVel(30.0f*(lastX - pos.x), 0.0f/*100.0f*(lastY - pos.y)*/);
//		tmpbody->SetLinearVelocity(tmpVel);
		//tmpbody->SetTransform(b2Vec2(lastX/10.0f, lastY/10.0f), 0.0f);

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);

//		world.Step(timeStep, velocityIterations, positionIterations);
//		b2Vec2 position = body->GetPosition();
		//float32 angle = body->GetAngle();
		//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
//		b2Vec2 cxz = tmpbody->GetLinearVelocity();
//		printf("%4.2f %4.2f\n", tmpVel.x, cxz.x);
//		b2Vec2 vcx = body->GetLinearVelocity();
		//printf("%4.2f %4.2f\n", vcx.x, vcx.y);
//		if (vcx.y < 8.0f && vcx.y > -8.0f)
//		{
//			if (vcx.y >= 0.0f)
//				vcx.y = 8.0f;
//			else
//				vcx.y = -8.0f;
//			body->SetLinearVelocity(vcx);
//		}

		int positionX, positionY;

		// draw ball
		sharedMemory.ball.getPosition(positionX, positionY);
		rectangle.x = positionX * 100.0 - 16;
		rectangle.y = positionY * 100.0 - 16;
		rectangle.w = 32;
		rectangle.h = 32;
		SDL_RenderCopy(ren, greenTex, NULL, &rectangle);

		// draw platform
		sharedMemory.player[0].getPosition(positionX, positionY);
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		rectangle.x = positionX * 100.00 - 40;
		rectangle.y = positionY * 100.00 - 7;
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
		SDL_Delay((int)(1000.0/60.0));
	}

	SDL_DestroyTexture(greenTex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDL_Quit();

	return NULL;
}
