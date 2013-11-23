#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <common/IThread.h>

namespace common
{
	class SharedMemory;
}

namespace server
{

class GameEngine
	: public common::IThread
{
public:
	GameEngine(common::SharedMemory&);

private:
	virtual void* start_routine();

	common::SharedMemory& sharedMemory;
};

}

#endif // GAME_ENGINE_H
