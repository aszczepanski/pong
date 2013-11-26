#include <server/ServerUDP.h>
#include <server/IServerSocket.h>
#include <cstdio>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdexcept>

using namespace server;
using namespace common;

ServerUDP::ServerUDP(const std::string& port)
	: IServerSocket(), port(port)
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
	{
		perror("socket error");
		throw SocketError();
	}

	length = sizeof(server);

	bzero(&server,length);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(port.c_str()));

	if (bind(sock, (struct sockaddr*)&server, length) == -1)
	{
		perror("bind error");
		throw BindError();
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
		throw SendtoError();
	}
}

void ServerUDP::receive(void* buf, size_t size) const
{
	if (recvfrom(sock, buf, size, 0, (struct sockaddr*)&from, &fromlen) == -1)
	{
		perror("recvfrom error");
		throw RecvfromError();
	}
}

void ServerUDP::receiveNoBlock(void* buf, size_t size) const
{
	fd_set masterfds, readfds;
	FD_ZERO(&masterfds);
	FD_SET(sock, &masterfds);
	memcpy(&readfds,&masterfds,sizeof(fd_set));
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 100000;
	if (select(sock+1, &readfds, NULL, NULL, &timeout) < 0)
	{
		printf("select error");
		throw SelectError();
	}

	if (FD_ISSET(sock, &readfds))
	{
//		printf("Read from socket\n");
		if (recvfrom(sock, buf, size, 0, (struct sockaddr*)&from, &fromlen) == -1)
		{
			perror("recvfrom error");
			throw RecvfromError();
		}
	}
	else
	{
		printf("socket timedout\n");
		throw TimeoutError();
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

