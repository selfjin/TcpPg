#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)


int n;
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>


int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);


	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, 0);

	std::cout << " 클라이언트 실행" << std::endl;

	if (ClientSocket == INVALID_SOCKET)std::cout << "Client Socket 생성 실패";

	SOCKADDR_IN addr = {};
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(25000);
	addr.sin_family = AF_INET;

	connect(ClientSocket, (sockaddr*)&addr, sizeof(addr));

	char SendMessage[] = "Client Send Message";
	send(ClientSocket, SendMessage, strlen(SendMessage), 0);

	char Buffer[1024] = {};
	recv(ClientSocket, Buffer, 1024, 0);

	std::cout << Buffer;

	closesocket(ClientSocket);

	WSACleanup();
	

	while (1)
	{
		std::cin >> n;
		if (n == 4)break;
	}


	return 0;
}