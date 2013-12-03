#ifndef CLIENT_APPLICATION_H
#define CLIENT_APPLICATION_H

namespace common
{
	class SharedMemory;
	class GameBoardDrawer;
	class IControllerEngine;
}

namespace client
{

class IClientSocket;
class Communicator;

/**
 * Klasa odpowiedzialna za działanie aplikacji klienta
 */
class ClientApplication
{
public:
/**
 * Konstruktor referencje do zainicjowanych obiektów z których będzie korzystać ClientApplication
 */
	ClientApplication(common::SharedMemory&, common::GameBoardDrawer&, common::IControllerEngine*, IClientSocket&, Communicator&);
/**
 * Motoda uruchamiająca aplikację.
 */
	void start();

private:
	common::SharedMemory& sharedMemory;
	common::GameBoardDrawer& drawer;
	common::IControllerEngine* controllerEngine;
	IClientSocket& clientSocket;
	Communicator& communicator;
};

}

#endif // CLIENT_APPLICATION_H
