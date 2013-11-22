#include <iostream>
#include <common/Mutex.h>

int main(int argc, char* argv[])
{
	std::cout << "Hello pong!" << std::endl;

	common::Mutex mutex;

	return 0;
}
