#ifndef CLIENTUDP_H
#define CLIENTUDP_H

#include <client/IClientSocket.h>
#include <cstdlib>
#include <common/Mutex.h>
#include <netinet/in.h>

struct hostent;

namespace client
{

/**
 * Klient UDP oparty na socketach
 */
class ClientUDP
	: public IClientSocket
{
public:
/**
 * Konstruktor otwierający połączenie z serwerem
 * @param hostname adres ip serwera
 * @param port port na którym serwer nasłuchuje
 */
	ClientUDP(const char* hostname, const char* port);
/**
 * Destruktor zamyka połączenie z serwerem jeśli jest otwarte
 */
	~ClientUDP();

	void send(const void*, size_t) const;
	void receive(void*, size_t) const;
	virtual void receiveNoBlock(void*, size_t) const;

/**
 * Zamyka połączenie z serwerem
 */
	void closeConnection();
private:
	const char* hostname;
	const char* port;
	int sock;
	mutable unsigned int length;
	struct sockaddr_in server, from;
	struct hostent* hp;

	mutable common::Mutex mutex;
};

}

#endif // CLIENTTCP_H
