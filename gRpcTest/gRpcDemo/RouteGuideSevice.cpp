#include <vector>
#include <sstream>
#include <thread>
#include <chrono>

#pragma warning(disable: 4800 4291)
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/security/server_credentials.h>
#include "RouteGuide.grpc.pb.h"

#include "..\Public\Common.h"


using namespace routeguide;
using namespace grpc;
using namespace std;

int32_t GetDist(const Point& pt1, const Point& pt2)
{
	return (int32_t)sqrt( pow(pt1.latitude() - pt2.latitude(), 2) + 
						pow(pt1.longitude() - pt2.longitude(), 2) );
}

class RouteGuideService final : public RouteGuide::Service
{
	std::string serviceName;
public:
	explicit RouteGuideService(const std::string _svcName)
				: serviceName(_svcName + " ")
			{}
	// A simple RPC.
	// Obtains the feature at a given position.
	Status GetFeature(ServerContext* context, const Point* request, Feature* response) override
	{
		auto s = serviceName + Timet2String(time(nullptr)) + ": ";
		s += request->Utf8DebugString();
		response->set_name(s);
		*response->mutable_location() = *request;
		return Status::OK;
	}
	// A server-to-client streaming RPC.
	// Obtains the Features available within the given Rectangle.  
	Status ListFeatures(ServerContext* context, const routeguide::Rectangle* request, ServerWriter< Feature>* writer) override
	{
		vector<Point> vp;
		vp.push_back(request->lo());
		vp.push_back(request->hi());
		auto s = serviceName + Timet2String(time(nullptr)) + ": ";
		for (auto& p : vp)
		{
			Feature f;
			f.set_name(s + p.Utf8DebugString());
			*f.mutable_location() = p;
			writer->Write(f);
		}
		return Status::OK;
	}
	// A client-to-server streaming RPC.
	// Accepts a stream of Points on a route being traversed, returning a
	// RouteSummary when traversal is completed.
	Status RecordRoute(ServerContext* context, ServerReader<Point>* reader, RouteSummary* response) override
	{
		/*
		int32 point_count = 1;
		int32 distance = 2;
		int32 elapsed_time = 3;
		string note = 4;
		*/
		Point ptCurrent;
		int32_t point_count = 0;
		int32_t distance = 0;
		int32_t elapsed_time = 0;
		std::string note;
		Point ptPrev;
		while (reader->Read(&ptCurrent))
		{
			if (point_count)
			{
				distance += GetDist(ptCurrent, ptPrev);
			}
			++point_count;
			ptPrev = ptCurrent;
		}
		elapsed_time = distance * 2;
		response->set_point_count(point_count);
		response->set_distance(distance);
		response->set_elapsed_time(elapsed_time);
		auto s = serviceName + Timet2String(time(nullptr)) + ": " + response->Utf8DebugString();
		response->set_note(s);

		return Status::OK;
	}
	// A Bidirectional streaming RPC.
	// Accepts a stream of RouteNotes sent while a route is being traversed,
	// while receiving other RouteNotes (e.g. from other users).
	Status RouteChat(ServerContext* context, ServerReaderWriter<RouteNote, RouteNote>* stream) override
	{
		RouteNote recvMsg;
		RouteNote sendMsg;
		while (stream->Read(&recvMsg))
		{
			*sendMsg.mutable_location() = recvMsg.location();
			sendMsg.set_message(serviceName + Timet2String(time(nullptr)));
			stream->Write(sendMsg);
		}

		return Status::OK;
	}
};


void ServerThread(const std::string& svrName, const int nPort, std::unique_ptr<Server>* pServer, bool* ready)
{
	ReturnGuard(rgServerThread2, *ready = true);
	cout << "**ServerThread sleep before start..." << endl;
	this_thread::sleep_for(chrono::seconds(1));
		
	stringstream ss; 
	ss << "0.0.0.0:" << nPort;
	auto addr = ss.str();
	RouteGuideService service(svrName);

	ServerBuilder builder;
	int nBindPort = 0;
	builder.AddListeningPort(addr, InsecureServerCredentials(), &nBindPort);
	builder.RegisterService(&service);
	*pServer = builder.BuildAndStart();
	if (nBindPort != nPort)
	{
		cout << "**ServerThread bind port failed: " << nBindPort << endl;
		return;
	}
	if (!*pServer)
	{
		cout << "**ServerThread BuildAndStart failed: " << nBindPort << endl;
	}
	auto& server = *pServer;
	cout << "**ServerThread Server started: " << addr << endl;

	*ready = true;
 	rgServerThread2.Release();

	server->Wait();
	cout << "**ServerThread Server shutdown: " << addr << endl;
}

void StartServer(std::thread& th, const std::string& svrName, const int nPort, std::unique_ptr<Server>& server)
{
	bool start = false;
	th = std::move(thread(ServerThread, svrName, nPort, &server, &start));

	// run server forever
//	cout << "sleep before shutdown" << endl;
//	auto b = true;
//	while (b)
// 	{
// 		this_thread::sleep_for(chrono::seconds(5));
// 	}
//	cout << "shutdown server" << endl;
// 	if (server)
// 	{
// 		server->Shutdown();
// 	}

	while (!start)
	{
		this_thread::sleep_for(chrono::microseconds(10));
	}

	cout << "StartServer done." << endl;
}