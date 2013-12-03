#ifndef SERVER_APPLICATION_H
#define SERVER_APPLICATION_H

#include <server/ConnectionTCP.h>
#include <server/ConnectionUDP.h>

namespace common
{
	class SharedMemory;
	class GameBoardDrawer;
	class IControllerEngine;
}

namespace server
{

class GameEngine;
class ServerTCP;
class ServerUDP;

/**
 * Klasa aplikacji serwera
 */
class ServerApplication
{
public:
/**
 * Konstruktor
 */
	ServerApplication(common::SharedMemory&, common::GameBoardDrawer&, common::IControllerEngine*, GameEngine&, ServerTCP&, ServerUDP&);
/**
 * Metoda rozpoczynająca działanie aplikacji
 */
	void start();

/**
 * Destruktor
 */
	~ServerApplication();

private:
	common::SharedMemory& sharedMemory;
	common::GameBoardDrawer& drawer;
	common::IControllerEngine* controllerEngine;
	GameEngine& gameEngine;

	ServerTCP& serverTCP;
	ConnectionTCP connectionTCP;

	ServerUDP& serverUDP;
	ConnectionUDP connectionUDP;
};

}

#endif // SERVER_APPLICATION_H
