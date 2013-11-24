#ifndef CLIENT_APPLICATION_H
#define CLIENT_APPLICATION_H

namespace common
{
	class SharedMemory;
	class Drawer;
}

namespace client
{

class IClientSocket;
class Communicator;

class ClientApplication
{
public:
	ClientApplication(common::SharedMemory&, common::Drawer&, IClientSocket&, Communicator&);
	void start();

private:
	common::SharedMemory& sharedMemory;
	common::Drawer& drawer;
	IClientSocket& clientSocket;
	Communicator& communicator;
};

}

#endif // CLIENT_APPLICATION_H
