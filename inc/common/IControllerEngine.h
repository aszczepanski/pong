#ifndef ICONTROLLER_ENGINE_H
#define ICONTROLLER_ENGINE_H

namespace common
{

class SharedMemory;
class ICommunicator;

class IControllerEngine
{

public:
	IControllerEngine(SharedMemory&, ICommunicator&);

	virtual void run() = 0;

	virtual ~IControllerEngine() { }

protected:
	SharedMemory& sharedMemory;
	ICommunicator& communicator;

};

}

#endif // ICONTROLLER_ENGINE_H
