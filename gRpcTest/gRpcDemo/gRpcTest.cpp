#include <iostream>
#include <string>
#include <memory>
#include <grpc++/server.h>

#include "Common.h"

#pragma comment(lib, "Ws2_32.lib")
#ifdef _DEBUG
	#pragma comment(lib, "..\\lib\\libdebug\\crypto.lib")
	#pragma comment(lib, "..\\lib\\libdebug\\gpr.lib")
	#pragma comment(lib, "..\\lib\\libdebug\\grpc++.lib")
	#pragma comment(lib, "..\\lib\\libdebug\\grpc.lib")
	#pragma comment(lib, "..\\lib\\libdebug\\libprotobufd.lib")
	#pragma comment(lib, "..\\lib\\libdebug\\ssl.lib")
	#pragma comment(lib, "..\\lib\\libdebug\\zlibd.lib")
#else
	#pragma comment(lib, "..\\lib\\libRelease\\crypto.lib")
	#pragma comment(lib, "..\\lib\\libRelease\\gpr.lib")
	#pragma comment(lib, "..\\lib\\libRelease\\grpc++.lib")
	#pragma comment(lib, "..\\lib\\libRelease\\grpc.lib")
	#pragma comment(lib, "..\\lib\\libRelease\\libprotobuf.lib")
	#pragma comment(lib, "..\\lib\\libRelease\\ssl.lib")
	#pragma comment(lib, "..\\lib\\libRelease\\zlib.lib")
#endif // _DEBUG

void StartServer(std::thread& th, const std::string& svrName, const int nPort, std::unique_ptr<::grpc::Server>& server);
void RunClient(const std::string& ip, const int port);

using namespace std;

void TestServerClient(const string& svcName, int port, const string& ip)
{
	std::unique_ptr<::grpc::Server> server;
	thread th;
	StartServer(th, svcName, port, server);

	if (!server)
	{
		th.join();
		cout << "StartServer failed." << endl;
		return;
	}

	RunClient(ip, port);
	server->Shutdown();
	th.join();
	cout << "Shutdown server." << endl;
}

void TestServer(const string& svcName, int port, const string& ip)
{
	std::unique_ptr<::grpc::Server> server;
	thread th;
	StartServer(th, svcName, port, server);

	if (!server)
	{
		th.join();
		cout << "StartServer failed." << endl;
		return;
	}

	th.join();
}


void TestClient(const string& svcName, int port, const string& ip)
{
	RunClient(ip, port);
}

void main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "testExec s|c|a" << endl;
		cout << "s: server, c: client, a: both" << endl;
		return;
	}
	int port = 7979;
	const string svcName = "Service230";
	const string ip = "192.168.13.230";
	string arg = argv[1];
	if (arg == "s")
	{
		TestServer(svcName, port, ip);
	}
	else if (arg == "c")
	{
		TestClient(svcName, port, ip);
	}
	else if (arg == "a")
	{
		TestServerClient(svcName, port, ip);
	}
	return;
}