#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <common/Ball.h>
#include <common/Player.h>

namespace client
{

class SharedMemory
{
public:
	SharedMemory();

	common::Ball ball;
	common::Player player[2];
};

}

#endif // SHARED_MEMORY_H
