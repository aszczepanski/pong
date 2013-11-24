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
		exit(0);
	}

	server.sin_family = AF_INET;
	hp = gethostbyname(hostname);
	if (hp == 0)
	{
		perror("Unknown host");
		exit(0);
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
//	mutex.lock();
	int st = sendto(sock, msg, size, 0, (const struct sockaddr*)&server, length);
//	mutex.unlock();
	if (-1 == st)
	{
		perror("sendto error");
		exit(0);
	}
}

void ClientUDP::receive(void* buf, size_t size) const
{
//	mutex.lock();
	//int st = recvfrom(sock, buf, size, 0, (struct sockaddr*)&from, &length);
	int st = recvfrom(sock, buf, size, 0, (struct sockaddr*)&from, &length);
//	mutex.unlock();
	if (-1 == st)
	{
		buf = NULL;
		perror("recvfrom error");
		//exit(0);
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
	timeout.tv_usec = 1000;
	if (select(sock+1, &readfds, NULL, NULL, &timeout) < 0)
	{
		printf("select error");
		exit(1);
	}

	if (FD_ISSET(sock, &readfds))
	{
//		printf("Read from socket\n");
//		mutex.lock();
		int st = recvfrom(sock, buf, size, 0, (struct sockaddr*)&from, &length);
//		mutex.unlock();
		if (-1 == st)
		{
			buf = NULL;
			perror("recvfrom error");
			//exit(0);
		}
	}
	else
	{
		printf("socket timedout\n");
		//printf("Socket timeout started=%d\n",packets_started);
		throw std::exception();
	}

}
