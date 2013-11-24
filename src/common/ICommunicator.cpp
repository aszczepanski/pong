#include <common/ICommunicator.h>
#include <common/SharedMemory.h>

using namespace common;

ICommunicator::ICommunicator(SharedMemory& sharedMemory)
	: sharedMemory(sharedMemory)
{
}
