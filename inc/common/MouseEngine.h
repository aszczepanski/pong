#ifndef MOUSE_ENGINE_H
#define MOUSE_ENGINE_H

#include <common/IControllerEngine.h>

namespace common
{

class SharedMemory;
class ICommunicator;

class MouseEngine
	: public IControllerEngine
{

public:
	MouseEngine(SharedMemory&, ICommunicator&);

	virtual void run();


};

}

#endif // MOUSE_ENGINE_H
