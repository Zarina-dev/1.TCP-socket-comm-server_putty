#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define PORT 5400
void main()
{
	// initialize winsock
	WSADATA wsData;
	int wsOk = WSAStartup(MAKEWORD(2, 2), &wsData);   //MAKEWORD(2, 2) : socket version
	if (wsOk != 0)      //wsOk == 0이여야 초기화가 됨 
	{
		cerr << "Can not initialize winsock! Quitting.." << endl;
		return;
	}




	// create a xsocket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0); // AF_INET : IPv4, SOCK_STREAM : TCP comm
	if (listening == INVALID_SOCKET)
	{
		cerr << "Con not create a socket! Quitting.." << endl;
		return;
	}



	   
	// bind the ip add and port to a socket
	sockaddr_in hint;			 // hint = contains socket address, port, address 종류
	hint.sin_family = AF_INET;   // IPv4
	hint.sin_port = htons(PORT); // port
	hint.sin_addr.s_addr = INADDR_ANY;  // my computer's IP [I'm using "my comp" as a server] can be used   -> inet_pton 


	//    listening 소켓을    hint에 있는 정보와 binding 하고 싶다
	bind(  listening,     (sockaddr*)&hint,    sizeof(hint));



	//tell winsock the socket is for listening 
	listen(listening, SOMAXCONN);  // SOMAXCONN : maximum connection num [ 한꺼번에 요청 가능한 최대 접송승인 수 ]
	


	/*------------------------ server setted up! client 대기 중 ------------------------*/
	

	//wait for a connection
	sockaddr_in client;
	int clientSIze = sizeof(client);
	cout << "client size = " << clientSIze << endl;

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSIze);
	
	cout << "client accepting... \n client Socket random port: " << clientSocket << endl;
	if (clientSocket == INVALID_SOCKET)
	{
		cerr << "client Socket is invalid. " << endl;
		return;
	}




	char host[NI_MAXHOST];  	// client's remote name  // NI_MAXHOST 1025 - max size of fully qualified domain name
	char service[NI_MAXHOST];   // service (i.e port) the client is connect on

	ZeroMemory(host, NI_MAXHOST);  // same as  memset(host, 0, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);
	
	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout <<"80 - " << host << " connected on port " << service << endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << "84 - " << host << " connected on port " << ntohs(client.sin_port) << endl;
	}





	//cloase listening socket
	closesocket(listening);

	//while loop: accept and exho msg back to client
	char buf[4096];
	while (true)
	{
		ZeroMemory(buf, 4096);    // buf를 4096개 0로 채워 
	
		// wait for client to 
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		cout << "92 - byteReceived : " << bytesReceived << endl;  // 입력된 데이터 크기 EX: buf is char, 입력: zarina => 6letters x 1byte = 6 ==> returns 6

		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}
		if (bytesReceived == 0)
		{
			cout << "recv() == 0 . Quit";
			break;
		}

		// echo message back to client
		send(clientSocket, buf, bytesReceived + 1, 0);

		
	}

	//close the sock
	closesocket(clientSocket);

	//cleanup winsock
	WSACleanup();


}