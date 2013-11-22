#ifndef CLIENT_APPLICATION_H
#define CLIENT_APPLICATION_H

namespace client
{

class SharedMemory;
class Drawer;
class ClientTCP;
class Communicator;

class ClientApplication
{
public:
	ClientApplication(SharedMemory&, Drawer&, ClientTCP&, Communicator&);
	void start();

private:
	SharedMemory& sharedMemory;
	Drawer& drawer;
	ClientTCP& clientTCP;
	Communicator& communicator;
};

}

#endif // CLIENT_APPLICATION_H
