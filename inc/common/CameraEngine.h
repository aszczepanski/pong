#ifndef CAMERA_ENGINE_H
#define CAMERA_ENGINE_H

#include <common/IControllerEngine.h>

namespace common
{

class SharedMemory;
class ICommunicator;

class CameraEngine
	: public IControllerEngine
{

public:
	CameraEngine(SharedMemory&, ICommunicator&);

	virtual void run();


};

}

#endif // CAMERA_ENGINE_H
