#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <common/IThread.h>

namespace common
{
	class SharedMemory;
}

namespace server
{

/**
 * Wątek realizujący silnik gry. Przeprowadza wszystkie niezbędne obliczenia. Wykorzystuje bibliotekę Box2D.
 */
class GameEngine
	: public common::IThread
{
public:
/**
 * Konstruktor 
 */
	GameEngine(common::SharedMemory&);

private:
	virtual void* start_routine();

	common::SharedMemory& sharedMemory;
};

}

#endif // GAME_ENGINE_H
