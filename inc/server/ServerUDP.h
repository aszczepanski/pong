#ifndef SERVERUDP_H
#define SERVERUDP_H

#include <server/IServerSocket.h>
#include <cstdlib>
#include <common/Mutex.h>
#include <netinet/in.h>
#include <string>

namespace server
{

class ServerUDP
	: public IServerSocket
{
public:
	ServerUDP(const std::string& port);
	ServerUDP(const ServerUDP&);
	ServerUDP& operator=(const ServerUDP&);
	~ServerUDP();
	void send(const void*, size_t) const;
	void receive(void*, size_t) const;
	void closeConnection();
	void closeMainConnection();
	virtual IServerSocket* waitForSocket();
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
