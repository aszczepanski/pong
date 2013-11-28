#ifndef DRAWER_H
#define DRAWER_H

#include <cstddef>

namespace common
{

class ICommunicator;
class SharedMemory;
class Camera;

class Drawer
{

public:
	Drawer(common::SharedMemory&, ICommunicator&, Camera* = NULL);
	void run();

private:
	common::SharedMemory& sharedMemory;
	ICommunicator& communicator;
	Camera* camera;
};

}

#endif // DRAWER_h
