#ifndef CLIENTUDP_H
#define CLIENTUDP_H

#include <common/ISocket.h>
#include <cstdlib>
#include <common/Mutex.h>
#include <netinet/in.h>

struct hostent;

namespace client
{

class ClientUDP
	: public common::ISocket
{
public:
	ClientUDP(const char* hostname, const char* port);
	~ClientUDP();
	void send(const void*, size_t) const;
	void receive(void*, size_t) const;
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
