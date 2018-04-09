#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <vector>
#include <WinSock2.h>
#include <windows.h>


using namespace std;
using namespace std::chrono;
extern const int RECVCHECKTV;
extern unsigned short Port;

#pragma comment(lib, "Ws2_32.lib")

void Send(std::string ip, int bufLen, int count)
{
	int nRet;


	const int maxBufLen = 10 * 1024;
	char sendBuf[maxBufLen] = { 0 };

	char idx = -1;
	for (auto& ch : sendBuf)
	{
		ch = ++idx;
	}

	if (bufLen >= maxBufLen)
	{
		cout << "size too big" << endl;
		return;
	}

	//----------------------
	// Initialize Winsock
	WSADATA wsaData;
	nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nRet != NO_ERROR) {
		cout << "WSAStartup error." << endl;
		return;
	}

	//---------------------------------------------
	// Create a socket for sending data
	auto sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sendSocket == INVALID_SOCKET) {
		cout << "create socket error:" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	//---------------------------------------------
	// Set up the RecvAddr structure with the IP address of
	// the receiver (in this example case "192.168.1.1")
	// and the specified port number.
	sockaddr_in sendAddr;
	sendAddr.sin_family = AF_INET;
	sendAddr.sin_port = htons(Port);
	sendAddr.sin_addr.s_addr = inet_addr(ip.c_str());

	// max buf for udp
	int optVal;
	int optLen = sizeof(int);
	if (getsockopt(sendSocket, SOL_SOCKET, SO_SNDBUF, (char*)&optVal, &optLen) != SOCKET_ERROR)
	{
		cout << "SO_SNDBUF " << optVal << endl;
	}
	if (getsockopt(sendSocket, SOL_SOCKET, SO_RCVBUF, (char*)&optVal, &optLen) != SOCKET_ERROR)
	{
		cout << "SO_RCVBUF " << optVal << endl;
	}

	//---------------------------------------------
	// Send a datagram to the receiver
	cout << "Sending a datagram to the receiver...\n" << endl;
//	for (int i = 0; i < count; ++i)
	while (true)
	{
		nRet = sendto(sendSocket, sendBuf, bufLen, 0, (SOCKADDR *)& sendAddr, sizeof(sendAddr));
		if (nRet == SOCKET_ERROR) {
			cout << "sendto error: " << WSAGetLastError() << endl;
			closesocket(sendSocket);
			WSACleanup();
			return;
		}
	}
	//---------------------------------------------
	// When the application is finished sending, close the socket.
	wprintf(L"Finished sending. Closing socket.\n");
	nRet = closesocket(sendSocket);
	if (nRet == SOCKET_ERROR) {
		cout << "closesocket error: " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	//---------------------------------------------
	// Clean up and quit.
	cout << "Exiting.\n" << endl;
	WSACleanup();
}

atomic_uint nRecved = 0;
high_resolution_clock::time_point tpStart;
void RecvThread(void)
{
	int recvCount = 0;

	auto tpNext = tpStart;
	while (true)
	{
		tpNext += seconds(1);
		this_thread::sleep_until(tpNext);
		auto nano = (high_resolution_clock::now() - tpStart).count() / 1000000;
		recvCount = nRecved;
		cout << recvCount << " " << nano << endl;
	}
}

void Recv(void)
{
	tpStart = high_resolution_clock::now();
	thread th(RecvThread);


	SOCKET recvSock;
	sockaddr_in RecvAddr;


	const int bufLen = 10 * 1024;
	char recvBuf[bufLen];

	sockaddr_in addrSend;
	int addrSize = sizeof(addrSend);

	int nRet = 0;
	//-----------------------------------------------
	// Initialize Winsock
	WSADATA wsaData;
	nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nRet != NO_ERROR) {
		cout << "WSAStartup error" << endl;
		return;
	}
	//-----------------------------------------------
	// Create a receiver socket to receive datagrams
	recvSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (recvSock == INVALID_SOCKET) {
		cout << "create socket error:" << WSAGetLastError() << endl;
		return;
	}

	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(Port);
	RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	nRet = ::bind(recvSock, (SOCKADDR *)& RecvAddr, sizeof(RecvAddr));
	if (nRet != 0) {
		cout << "bind failed." << endl;
		return;
	}
	//-----------------------------------------------
	// Call the recvfrom function to receive datagrams
	// on the bound socket.
	cout << "recving..." << endl;


	// max buf for udp
	int optVal;
	int optLen = sizeof(int);
	if (getsockopt(recvSock, SOL_SOCKET, SO_SNDBUF, (char*)&optVal, &optLen) != SOCKET_ERROR)
	{
		cout << "SO_SNDBUF " << optVal << endl;
	}
	if (getsockopt(recvSock, SOL_SOCKET, SO_RCVBUF, (char*)&optVal, &optLen) != SOCKET_ERROR)
	{
		cout << "SO_RCVBUF " << optVal << endl;
	}


	bool setStart = true;
	while (true)
	{
		nRet = recvfrom(recvSock, recvBuf, bufLen, 0, (SOCKADDR *)& addrSend, &addrSize);
		if (nRet == SOCKET_ERROR) {
			cout << "recvfrom failed: " << WSAGetLastError() << endl;
			continue;
		}
		if (setStart)
		{
			setStart = false;
			tpStart = high_resolution_clock::now();
		}
		++nRecved;
	}

	//-----------------------------------------------
	// Close the socket when finished receiving datagrams
	wprintf(L"Finished receiving. Closing socket.\n");
	nRet = closesocket(recvSock);
	if (nRet == SOCKET_ERROR) {
		cout << "closesocket failed: " << WSAGetLastError() << endl;
		return;		
	}

	//-----------------------------------------------
	// Clean up and exit.
	cout << "Exiting..." << endl;
	WSACleanup();
}