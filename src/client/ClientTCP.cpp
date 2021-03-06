#include <client/ClientTCP.h>
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <cstdio>
#include <cassert>
#include <string>

using namespace std;
using namespace client;

ClientTCP::ClientTCP(const string& hostname, const string& port)
	: IClientSocket(), hostname(hostname), port(port), connectionOpened(false)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("client socket error");
		throw SocketError();
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port.c_str()));

	if (inet_aton(hostname.c_str(), (in_addr*)&addr.sin_addr.s_addr) == 0)
	{
		perror("client aton error");
		throw AtonError();
	}

	cout << "TCP connecting" << endl;

	if (connect(sockfd, (sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("client connect error");
		throw ConnectError();
	}

	connectionOpened = true;
}

ClientTCP::~ClientTCP()
{
/*
	if (connectionOpened)
	{
		std::cout << "client sockfd = " << sockfd << endl;
		if (close(sockfd) < 0)
		{
			perror("client close sockfd");
		}
	}
*/
}

void ClientTCP::closeSocket()
{
	assert(connectionOpened);
	std::cout << "client sockfd = " << sockfd << endl;
	if (close(sockfd) < 0)
	{
		perror("client close sockfd");
	}
	connectionOpened = false;
}

void ClientTCP::send(const void* msg, size_t size) const
{
	assert(connectionOpened);
	int st = write(sockfd, msg, size);

	if (-1 == st)
	{
		perror("client write error");
		throw WriteError();
	}
}

void ClientTCP::receive(void* buf, size_t size) const
{
	assert(connectionOpened);
	int st = read(sockfd, buf, size);

	if (-1 == st)
	{
		perror("client read error");
		throw ReadError();
	}
}

void ClientTCP::receiveNoBlock(void* buf, size_t size) const
{
	assert(connectionOpened);
	int st = read(sockfd, buf, size);

	if (-1 == st)
	{
		perror("client read error");
		throw ReadError();
	}
}
