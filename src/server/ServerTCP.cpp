#include <server/ServerTCP.h>
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
#include <algorithm>
#include <string>
#include <iostream>

using namespace server;

ServerTCP::ServerTCP(const std::string& port)
	: IServerSocket(), in_sockfd(-1), port(port)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("server socket error");
		throw SocketError();
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port.c_str()));
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("server bind error");
		throw BindError();
	}

	if (listen(sockfd, MAX_WAITING_SERVERS) == -1)
	{
		perror("server listen error");
		throw ListenError();
	}

}

ServerTCP::ServerTCP(const ServerTCP& server)
	: IServerSocket(), sockfd(server.sockfd),
	in_sockfd(server.in_sockfd), port(server.port)
{
}

namespace server
{
void swap(ServerTCP& a, ServerTCP& b)
{
	std::swap(a.sockfd, b.sockfd);
	std::swap(a.in_sockfd, b.in_sockfd);
	std::swap(a.port, b.port);
}
}

ServerTCP& ServerTCP::operator=(const ServerTCP& server)
{
	ServerTCP temp = ServerTCP(server);
	swap(*this, temp);
	return *this;
}

ServerTCP::~ServerTCP()
{
}

void ServerTCP::send(const void* msg, size_t size) const
{
	int st = write(in_sockfd, msg, size);
	if (-1 == st)
	{
		perror("server write error");
		throw WriteError();
	}
}

void ServerTCP::receive(void* buf, size_t size) const
{
	int st = read(in_sockfd, buf, size);
	if (-1 == st)
	{
		perror("server read error");
		throw ReadError();
	}
}

void ServerTCP::receiveNoBlock(void* buf, size_t size) const
{
	fd_set masterfds, readfds;
	FD_ZERO(&masterfds);
	FD_SET(in_sockfd, &masterfds);
	memcpy(&readfds,&masterfds,sizeof(fd_set));
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 100000;
	if (select(in_sockfd+1, &readfds, NULL, NULL, &timeout) < 0)
	{
		printf("select error");
		throw SelectError();
	}

	if (FD_ISSET(in_sockfd, &readfds))
	{
//		printf("Read from socket\n");
		int st = read(in_sockfd, buf, size);
		if (-1 == st)
		{
			perror("server read error");
			throw ReadError();
		}
	}
	else
	{
		printf("read tcp timedout\n");
		throw TimeoutError();
	}
}

void ServerTCP::closeSocket()
{
	std::cout << "server sockfd = " << sockfd << std::endl;
	if (close(sockfd) < 0)
	{
		perror("server close sockfd");
	}
}

void ServerTCP::closeConnection()
{
	std::cout << "server in_sockfd = " << in_sockfd << std::endl;
	if (close(in_sockfd) < 0)
	{
		perror("server close in_sockfd");
	}
}

ServerTCP ServerTCP::waitForSocket()
{
	socklen_t socklen;
	sockaddr_in in_addr;
	socklen = sizeof(in_addr);
	
	int new_sockfd = accept(sockfd, (sockaddr*)&in_addr, &socklen);
	std::cout << "server new_sockfd = " << new_sockfd << std::endl;
	if (new_sockfd == -1)
	{
		perror("server accept");
		throw AcceptError();
	}
	ServerTCP result = ServerTCP(*this);
	result.in_sockfd = new_sockfd;
	return result;
}

// it is possibly wrong
namespace server
{
bool operator>(const ServerTCP& a, const ServerTCP& b)
{
	return a.in_sockfd > b.in_sockfd;
}

bool operator<(const ServerTCP& a, const ServerTCP& b)
{
	return a.in_sockfd < b.in_sockfd;
}

bool operator==(const ServerTCP& a, const ServerTCP& b)
{
	return a.sockfd == b.sockfd;
}
}
