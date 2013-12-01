#ifndef SERVER_TCP_H
#define SERVER_TCP_H

#include <server/IServerSocket.h>
#include <cstdlib>
#include <common/Mutex.h>
#include <string>
#include <stdexcept>

namespace server
{

/**
 * Serwer TCP oparty na socketach
 */
class ServerTCP
	: public IServerSocket
{
public:
/**
 * Konstruktor otwierający połączenie z serwerem
 * @param port port na którym serwer nasłuchuje
 */
	ServerTCP(const std::string& port);
/**
 * Konstruktor kopiujący
 */
	ServerTCP(const ServerTCP&);
/**
 * operator=
 */
	ServerTCP& operator=(const ServerTCP&);
/**
 * Destruktor zamyka połączenie z serwerem jeśli jest otwarte
 */
	~ServerTCP();

	void send(const void*, size_t) const;
	void receive(void*, size_t) const;
	void receiveNoBlock(void*, size_t) const;

/**
 * Zamyka socket
 */
	void closeSocket();
/**
 * Zamyka połączenie z klientem
 */
	void closeConnection();

/**
 * Oczekuje na nawiązanie połączenia przez klienta
 */
	ServerTCP waitForSocket();

/**
 * Operator >
 * NIE DZIAŁA !!!
 */
	friend bool operator>(const ServerTCP&, const ServerTCP&);
/**
 * Operator <
 * NIE DZIAŁA !!!
 */
	friend bool operator<(const ServerTCP&, const ServerTCP&);
/**
 * Operator ==
 * NIE DZIAŁA !!!
 */
	friend bool operator==(const ServerTCP&, const ServerTCP&);
private:
	friend void swap(ServerTCP&, ServerTCP&);

	int sockfd;
	int in_sockfd;
	std::string port;
	static const unsigned short MAX_WAITING_SERVERS = 1;

	mutable common::Mutex mutex;
};

}

#endif // SERVER_TCP_H
