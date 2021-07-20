/*************************************************************************
    > File Name: client.cpp
    > Created Time: 2019年08月12日 星期一 16时23分50秒
 ************************************************************************/
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include "WinSock2.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
// #include <strings.h>
// #include <unistd.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>

#pragma comment(lib, "ws2_32.lib")

#define MAXLINE 1024 
// #define SERV_PORT 8000

class IotUdp_Client
{
public:
	IotUdp_Client(const std::string& ip, int port);
	~IotUdp_Client();
	size_t Sendto(const void* ptr, size_t nbytes);
	size_t Recvfrom(void* ptr, size_t nbytes);

	size_t Read(void* ptr, size_t nbytes);
	size_t Write(const void* ptr, size_t nbytes);

private:
	// struct sockaddr_in servaddr;
  WSADATA wsaData;
  SOCKADDR_IN addrRec;
  SOCKET sockClient;
	int nLen;
};

