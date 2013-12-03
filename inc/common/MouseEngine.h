#ifndef MOUSE_ENGINE_H
#define MOUSE_ENGINE_H

#include <common/IControllerEngine.h>

namespace common
{

class SharedMemory;
class ICommunicator;
class GameBoardDrawer;

class MouseEngine
	: public IControllerEngine
{

public:
	MouseEngine(SharedMemory&, ICommunicator&, GameBoardDrawer&);

	virtual void run();

private:
	GameBoardDrawer& drawer;

};

}

#endif // MOUSE_ENGINE_H
