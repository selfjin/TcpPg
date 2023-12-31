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

	if (ListenSocket == INVALID_SOCKET)std::cout << "Listen Socket 생성 실패";

	std::cout << "서버 실행" << std::endl;

	SOCKADDR_IN addr = {};
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(25000);
	addr.sin_family = AF_INET;
	


	if (SOCKET_ERROR == bind(ListenSocket, (sockaddr*)&addr, sizeof(addr))) {  std::cout << "bind error"; }
	if (SOCKET_ERROR == listen(ListenSocket, SOMAXCONN)) {  std::cout << "listen error"; }


	SOCKADDR_IN ClientAddr;
	int len = sizeof(ClientAddr);

	while ((SOCKET Client = accept(ListenSocket, (sockaddr*)&ClientAddr, &len)) != -1)
	{
		
		std::cout << " 클라이언트 연결 " << std::endl;
		
		// Accpet를 통해 통신을 위한 Client 소켓을 반환받으면 
		// 별도의 쓰레드로 recv를 갱신한다.
		std::thread t1([&]()
			{
				char buffer[512] = {};
				int check = 1;

				while (check)
				{
					
					if ((recv(Client, buffer, 512, 0)) == -1)
					{ 
						std::cout << " Recv 실패,연결이 되어있지 않습니다. " << std::endl;
						check = 0;
						break;
					}
					std::cout << "Recv Message : " << buffer << std::endl;


					
					if (buffer == eos) { closesocket(Client); check = 0; break; }
				}
				
				
			}
		);
		//계속해서 채팅을 주고 받는다.
		while (1)
		{
			
			char ServerMessage[512] = {};
			
			std::cin >> ServerMessage;
			if (send(Client, ServerMessage, sizeof(ServerMessage), 0) == -1)
			{
				std::cout << " Send 실패, 연결이 되어있지 않습니다. " << std::endl;
				break;
			}
			
		}
	}

	
	WSACleanup();
	return 0;
}


