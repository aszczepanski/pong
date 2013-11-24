#ifndef SERVER_TCP_H
#define SERVER_TCP_H

#include <server/IServerSocket.h>
#include <cstdlib>
#include <common/Mutex.h>
#include <string>
#include <stdexcept>

namespace server
{

class ServerTCP
	: public IServerSocket
{
public:
	ServerTCP(const std::string& port);
	ServerTCP(const ServerTCP&);
	ServerTCP& operator=(const ServerTCP&);
	friend void swap(ServerTCP&, ServerTCP&);
	~ServerTCP();
	void send(const void*, size_t) const;
	void receive(void*, size_t) const;
	void closeSocket();
	void closeConnection();
	IServerSocket* waitForSocket();

	friend bool operator>(const ServerTCP&, const ServerTCP&);
	friend bool operator<(const ServerTCP&, const ServerTCP&);
	friend bool operator==(const ServerTCP&, const ServerTCP&);
private:
	int sockfd;
	int in_sockfd;
	std::string port;
	static const unsigned short MAX_WAITING_SERVERS = 2;

	mutable common::Mutex mutex;
};

}

#endif // SERVER_TCP_H
