#ifndef CLIENT_TCP_H
#define CLIENT_TCP_H

#include <client/IClientSocket.h>
#include <cstdlib>
#include <common/Mutex.h>
#include <string>

namespace client
{

class ClientTCP
	: public IClientSocket
{
public:
	ClientTCP(const std::string& hostname, const std::string& port);
	~ClientTCP();
	virtual void send(const void*, size_t) const;
	virtual void receive(void*, size_t) const;
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
