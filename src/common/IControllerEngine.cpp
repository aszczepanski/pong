#include <common/IControllerEngine.h>
#include <common/SharedMemory.h>
#include <common/ICommunicator.h>

using namespace common;

IControllerEngine::IControllerEngine(SharedMemory& sharedMemory, ICommunicator& communicator)
	: sharedMemory(sharedMemory), communicator(communicator)
{
}
