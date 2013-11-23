#ifndef CLIENT_APPLICATION_H
#define CLIENT_APPLICATION_H

namespace common
{
	class SharedMemory;
}

namespace client
{

class Drawer;
class ClientTCP;
class ClientUDP;
class Communicator;

class ClientApplication
{
public:
	//ClientApplication(common::SharedMemory&, Drawer&, ClientTCP&, Communicator&);
	ClientApplication(common::SharedMemory&, Drawer&, ClientUDP&, Communicator&);
	void start();

private:
	common::SharedMemory& sharedMemory;
	Drawer& drawer;
	//ClientTCP& clientTCP;
	ClientUDP& clientUDP;
	Communicator& communicator;
};

}

#endif // CLIENT_APPLICATION_H
