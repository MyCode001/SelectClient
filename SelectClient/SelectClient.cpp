// SelectClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"   
#include <WINSOCK2.H>   
#include <stdio.h>   
#pragma comment(lib, "ws2_32.lib")   
#define SERVER_ADDRESS  "127.0.0.1"   
#define PORT  5150   
#define MSGSIZE  1024*4 


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;   
	SOCKET sClient;   
	SOCKADDR_IN server;   
	char szMessage[MSGSIZE];   
	memset(szMessage, 0, MSGSIZE);
	int ret;   
	// Initialize windows socket library   
	WSAStartup(0x0202, &wsaData);   
	// Create client socket   
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);   
	// Connect to server   
	memset(&server, 0, sizeof(SOCKADDR_IN));   
	server.sin_family = AF_INET;   
	server.sin_addr.S_un.S_addr = inet_addr(SERVER_ADDRESS);   
	server.sin_port = htons(PORT);   
	connect(sClient, (sockaddr*)&server, sizeof(SOCKADDR_IN));   
	while (TRUE)    
	{   
		printf("Send:");   
		gets(szMessage);   
		// Send message   
		send(sClient, szMessage, strlen(szMessage), 0);   
		// Receive message   
		ret = recv(sClient, szMessage, MSGSIZE, 0);   
		if (ret==0)
		{
			printf("Received nothing!");
			continue;
		}
	szMessage[ret] = '\0';   
		printf("Received [%d bytes]: %s\n", ret, szMessage);   
	}   
	// Clean up   
	closesocket(sClient);   
	WSACleanup();   
	return 0;   
}

