#pragma comment(lib, "ws2_32.lib")

#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>



int n;

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
		

	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (ListenSocket == INVALID_SOCKET)std::cout << "Listen Socket 생성 실패";

	std::cout << "서버 실행" << std::endl;

	SOCKADDR_IN addr = {};
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(25000);
	addr.sin_family = AF_INET;
	


	if (SOCKET_ERROR == bind(ListenSocket, (sockaddr*)&addr, sizeof(addr))) {  std::cout << "bind error"; }
	if (SOCKET_ERROR == listen(ListenSocket, SOMAXCONN)) {  std::cout << "listen error"; }

	std::cout << "서버 리슨 상태 전환" << std::endl;

	SOCKADDR_IN ClientAddr;
	int len = sizeof(ClientAddr);

	SOCKET Client = accept(ListenSocket, (sockaddr*)&ClientAddr, &len);


		char buffer[1024] = {};
		recv(Client, buffer, 1024, 0);
		std::cout << "Recv Message : " << buffer << std::endl;

		char ServerMessage[] = "Server Send";
		send(Client, ServerMessage, sizeof(ServerMessage), 0);

		closesocket(Client);
		closesocket(ListenSocket);

		WSACleanup();
	
		while (1)
		{
			std::cin >> n;
			if (n == 4)break;
		}

	return 0;
}