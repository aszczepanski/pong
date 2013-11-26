#include <client/ClientUDP.h>
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <cstdio>
#include <cstring>
#include <stdexcept>

using namespace std;
using namespace client;

ClientUDP::ClientUDP(const char* hostname, const char* port)
	: IClientSocket(), hostname(hostname), port(port)
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
	{
		perror("socket error");
		throw SocketError();
	}

	server.sin_family = AF_INET;
	hp = gethostbyname(hostname);
	if (hp == 0)
	{
		perror("Unknown host");
		throw HostError();
	}

	bcopy((char*)hp->h_addr, (char*)&server.sin_addr, hp->h_length);
	server.sin_port = htons(atoi(port));
	length = sizeof(struct sockaddr_in);
}

ClientUDP::~ClientUDP()
{
}

void ClientUDP::closeConnection()
{
}

void ClientUDP::send(const void* msg, size_t size) const
{
	int st = sendto(sock, msg, size, 0, (const struct sockaddr*)&server, length);
	if (-1 == st)
	{
		perror("sendto error");
		throw SendtoError();
	}
}

void ClientUDP::receive(void* buf, size_t size) const
{
	int st = recvfrom(sock, buf, size, 0, (struct sockaddr*)&from, &length);
	if (-1 == st)
	{
		perror("recvfrom error");
		throw RecvfromError();
	}
}

void ClientUDP::receiveNoBlock(void* buf, size_t size) const
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
		int st = recvfrom(sock, buf, size, 0, (struct sockaddr*)&from, &length);
		if (-1 == st)
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
