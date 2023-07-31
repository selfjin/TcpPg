#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)


int n;
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>
#include<thread>

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

	int check = 1;

	while (1)
	{
		if (check == 0)break;
		std::thread t1([&]()
			{
				while (1)
				{
					char buffer[512] = {};
					if(recv(ClientSocket, buffer, 512, 0)==-1)break;
					std::cout << "Recv Message : " << buffer << std::endl;
					if (buffer == "EXIT") { closesocket(ClientSocket); break; }
				}

			}
		);

		while (1)
		{
			char SendMessage[512] = {};
			std::cin >> SendMessage;
			if (send(ClientSocket, SendMessage, strlen(SendMessage), 0) == -1)break;
		}
		

		
	}
	
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}