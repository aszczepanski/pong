#ifndef SERVERUDP_H
#define SERVERUDP_H

#include <server/IServerSocket.h>
#include <cstdlib>
#include <common/Mutex.h>
#include <netinet/in.h>
#include <string>

namespace server
{

/**
 * Serwer UDP oparty na socketach
 */
class ServerUDP
	: public IServerSocket
{
public:
/**
 * Konstruktor otwierający połączenie z serwerem
 * @param port port na którym serwer nasłuchuje
 */
	ServerUDP(const std::string& port);
/**
 * Konstruktor kopiujący
 */
	ServerUDP(const ServerUDP&);
/**
 * operator=
 */
	ServerUDP& operator=(const ServerUDP&);
/**
 * Destruktor zamyka połączenie z serwerem jeśli jest otwarte
 */
	~ServerUDP();
/**
 * Wysyła dane do klienta
 */
	void send(const void*, size_t) const;
/**
 * Odbiera dane od klienta. Jeśli dane nie są dostępne blokuje.
 */
	void receive(void*, size_t) const;
/**
 * Odbiera dane od klienta. Jeśli dane nie są dostępne rzuca wyjątek
 * @see server::IServerSocket::TimeoutError
 */
	void receiveNoBlock(void*, size_t) const;
/**
 * Zamyka połączenie z klientem
 */
	void closeConnection();
/**
 * Zamyka socket servera
 */
	void closeMainConnection();
private:
	int sock, length;
	mutable socklen_t fromlen;
	struct sockaddr_in server;
	struct sockaddr_in from;
	std::string port;

	mutable common::Mutex mutex;
};

}

#endif // SERVERUDP_H
