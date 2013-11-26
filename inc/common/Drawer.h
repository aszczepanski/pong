#ifndef DRAWER_H
#define DRAWER_H

namespace common
{

class ICommunicator;
class SharedMemory;
class Camera;

class Drawer
{

public:
	Drawer(common::SharedMemory&, ICommunicator&, Camera&);
	void run();

private:
	common::SharedMemory& sharedMemory;
	ICommunicator& communicator;
	Camera& camera;
};

}

#endif // DRAWER_h
