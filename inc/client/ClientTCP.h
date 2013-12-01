#ifndef CLIENT_TCP_H
#define CLIENT_TCP_H

#include <client/IClientSocket.h>
#include <cstdlib>
#include <common/Mutex.h>
#include <string>

namespace client
{

/**
 * Klasa klienta TCP oparta na socketach
 */
class ClientTCP
	: public IClientSocket
{
public:
/**
 * Konstruktor nawiązuje połączenie z serwerem
 * @param hostname adres ip serwera
 * @param port port na którym nasłuchuje serwer
 */
	ClientTCP(const std::string& hostname, const std::string& port);
/**
 * Destruktor zamyka połączenie z serwerem jeśli jest otwarte
 */
	~ClientTCP();

	virtual void send(const void*, size_t) const;
	virtual void receive(void*, size_t) const;
	virtual void receiveNoBlock(void*, size_t) const;

/**
 * Zamyka połączenie z serwerem
 */
	void closeSocket();
private:
	ClientTCP(const ClientTCP&);
	ClientTCP& operator=(const ClientTCP&);
	const std::string hostname;
	const std::string port;
	int sockfd;
	bool connectionOpened;

	mutable common::Mutex mutex;
};

}

#endif // CLIENT_TCP_H
