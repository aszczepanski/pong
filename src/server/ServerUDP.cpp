#include <server/ServerUDP.h>
#include <server/IServerSocket.h>
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace server;
using namespace common;

ServerUDP::ServerUDP(const std::string& port)
	: IServerSocket(), port(port)
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
	{
		perror("socket error");
		exit(1);
	}

	length = sizeof(server);

	bzero(&server,length);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(port.c_str()));

	if (bind(sock, (struct sockaddr*)&server, length) == -1)
	{
		perror("bind error");
		exit(1);
	}

	fromlen = sizeof(struct sockaddr_in);
}

ServerUDP::ServerUDP(const ServerUDP& server)
	: sock(server.sock), length(server.length), fromlen(server.fromlen), from(server.from), port(server.port)
{
}

ServerUDP::~ServerUDP()
{
}

void ServerUDP::send(const void* msg, size_t size) const
{
	if (sendto(sock, msg, size, 0, (struct sockaddr*)&from, fromlen) == -1)
	{
		perror("sendto error");
		exit(1);
	}
}

void ServerUDP::receive(void* buf, size_t size) const
{
	if (recvfrom(sock, buf, size, 0, (struct sockaddr*)&from, &fromlen) == -1)
	{
		perror("recvfrom error");
		buf = NULL;
//		exit(1);
	}
}

void ServerUDP::closeConnection()
{
	printf("closing connection inside UDP\n");
//	close(from);
}

void ServerUDP::closeMainConnection()
{
	close(sock);
}

IServerSocket* ServerUDP::waitForSocket()
{
	unsigned char buf;
	size_t size = 1;
	if (recvfrom(sock, &buf, size, 0, (struct sockaddr*)&from, &fromlen) == -1)
	{
		perror("recvfrom");
		exit(1);
	}
	ServerUDP* result = new ServerUDP(*this);
	return result;
}
