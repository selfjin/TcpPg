#pragma comment(lib, "ws2_32.lib")

#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>
#include<thread>


int n;



int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
		

	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (ListenSocket == INVALID_SOCKET)std::cout << "Listen Socket ���� ����";

	std::cout << "���� ����" << std::endl;

	SOCKADDR_IN addr = {};
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(25000);
	addr.sin_family = AF_INET;
	


	if (SOCKET_ERROR == bind(ListenSocket, (sockaddr*)&addr, sizeof(addr))) {  std::cout << "bind error"; }
	if (SOCKET_ERROR == listen(ListenSocket, SOMAXCONN)) {  std::cout << "listen error"; }


	SOCKADDR_IN ClientAddr;
	int len = sizeof(ClientAddr);

	while (1)
	{
		SOCKET Client = accept(ListenSocket, (sockaddr*)&ClientAddr, &len);
		std::cout << " Ŭ���̾�Ʈ ���� " << std::endl;
		
		// Accpet�� ���� ����� ���� Client ������ ��ȯ������ 
		// ������ ������� recv�� �����Ѵ�.
		std::thread t1([&]()
			{
				while (1)
				{
					char buffer[512] = {};
					if (recv(Client, buffer, 512, 0) == -1)
					{ 
						closesocket(Client); 
						std::cout << " ������ ����Ǿ� �ֽ��ϴ� " << std::endl;
						break;
					}
					std::cout << "Recv Message : " << buffer << std::endl;
					if (buffer == "EXIT") { closesocket(Client); break; }
				}

			}
		);
		//����ؼ� ä���� �ְ� �޴´�.
		while (1)
		{
			
			char ServerMessage[512] = {};
			
			std::cin >> ServerMessage;
			if (send(Client, ServerMessage, sizeof(ServerMessage), 0) == -1)
			{
				std::cout << " Ŭ���̾�Ʈ�� ������ ���������ϴ� " << std::endl;
				break;
			}
		
		}
	}

	
	WSACleanup();
	return 0;
}


