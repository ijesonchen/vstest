#include <iostream>
#include <sstream>
#include <memory>

#pragma warning(disable: 4800 4291)
#include "RouteGuide.grpc.pb.h"
#include <grpc++/grpc++.h>
#include <grpc++/server.h>

using namespace std;
using namespace grpc;
using namespace routeguide;

class RouteGuideClient
{
private:
	std::unique_ptr<RouteGuide::Stub> stub;
	std::string clientName;
public:
	RouteGuideClient(const std::string& addr, const std::string _clientName)
		: stub(RouteGuide::NewStub(CreateChannel(addr, InsecureChannelCredentials()))), clientName(_clientName)
	{
		// _clientName not used currently.
	};

	bool GetFeature(const Point& pt, Feature& feature)
	{
		ClientContext context;
		auto status = stub->GetFeature(&context, pt, &feature);
		if (!status.ok())
		{
			cout << "GetFeature failed: " << status.error_message() << endl;
		}
		return status.ok();
	}

	bool ListFeatures(const routeguide::Rectangle& rect, std::vector<routeguide::Feature>& vtFeature)
	{
		ClientContext context;
		// unique_ptr<ClientReader<Feature>> reader
		auto reader = stub->ListFeatures(&context, rect);
		Feature fea;
		while (reader->Read(&fea))
		{
			vtFeature.push_back(fea);
		}
		// Status status = reader->Finish(); 
		auto status = reader->Finish();
		if (!status.ok())
		{
			cout << "ListFeatures failed: " << status.error_message() << endl;
		}
		return status.ok();
	}

	bool RecordRoute(std::vector<routeguide::Point>& vtPoint, routeguide::RouteSummary& sum)
	{
		ClientContext context;
		// unique_ptr<ClientWriter<Point>> writer;
		auto writer = stub->RecordRoute(&context, &sum);
		for (auto& pt : vtPoint)
		{
			if (!writer->Write(pt))
			{
				cout << "writer->Write failed." << endl;
				break;
			}
		}
		writer->WritesDone();
		auto status = writer->Finish();
		if (!status.ok())
		{
			cout << "RecordRoute failed: " << status.error_message() << endl;
		}
		return status.ok();
	}

	bool RouteChatInterweave(const vector<RouteNote>& in, vector<RouteNote>& out)
	{
		ClientContext cc;
		// unique_ptr<ClientReaderWriter<RouteNote, RouteNote>> rw
		auto rw = stub->RouteChat(&cc);
		RouteNote noteRead;
		for (auto& noteWrite : in)
		{
			if (!rw->Write(noteWrite))
			{
				cout << "RouteChatInterweave Write failed" << endl;
				break;
			}
			if (!rw->Read(&noteRead))
			{
				cout << "RouteChatInterweave Read failed" << endl;
				break;
			}
			out.push_back(noteRead);
		}
		rw->WritesDone();
		while (rw->Read(&noteRead))
		{
			out.push_back(noteRead);
		}
		auto status = rw->Finish();
		if (!status.ok())
		{
			cout << "RouteChatInterweave failed: " << status.error_message() << endl;
		}
		return status.ok();	
	}

	bool RouteChatSeq(const vector<RouteNote>& in, vector<RouteNote>& out)
	{
		ClientContext cc;
		auto rw = stub->RouteChat(&cc);
		for (auto& n: in)
		{
			if (!rw->Write(n))
			{
				cout << "RouteChatSeq Write failed" << endl;
			}
		}
		rw->WritesDone();

		RouteNote nr;
		while (rw->Read(&nr))
		{
			out.push_back(nr);
		}

		auto status = rw->Finish();
		if (!status.ok())
		{
			cout << "RouteChatSeq failed: " << status.error_message() << endl;
		}
		return status.ok();
	}
};

void RunClient(const std::string& ip, const int port)
{
	stringstream ss;
	ss << ip << ":" << port;
	auto addr = ss.str();
	RouteGuideClient client(addr, "Client230");
	Point pt;
	pt.set_latitude(100);
	pt.set_longitude(200);
	Feature fea;
	if (!client.GetFeature(pt, fea))
	{
		cout << "GetFeature failed." << endl;
	}
	cout << "GetFeature:" << endl << fea.Utf8DebugString() << endl;

	routeguide::Rectangle rect;
	auto& ptlo = *rect.mutable_lo();
	ptlo.set_latitude(300);
	ptlo.set_longitude(400);
	auto& pthi = *rect.mutable_hi();
	pthi.set_latitude(500);
	pthi.set_longitude(600);
	vector<Feature> vtFea;
	if (!client.ListFeatures(rect, vtFea))
	{
		cout << "ListFeatures failed." << endl;
	}
	cout << "ListFeatures: " << endl;
	for (auto& f : vtFea)
	{
		cout << f.Utf8DebugString() << endl;
	}

	vector<Point> vtPoint;
	vtPoint.push_back(pt);
	vtPoint.push_back(ptlo);
	vtPoint.push_back(pthi);
	RouteSummary sum;
	if (!client.RecordRoute(vtPoint, sum))
	{
		cout << "RecordRoute failed." << endl;
	}
	cout << "RecordRoute:" << endl << sum.Utf8DebugString() << endl;

	vector<RouteNote> vtNoteSend;
	for (auto p : vtPoint)
	{
		RouteNote n;
		*n.mutable_location() = p;
		n.set_message(p.Utf8DebugString());
		vtNoteSend.push_back(n);
	}
	vector<RouteNote> vtNoteRecv1;
	if (!client.RouteChatInterweave(vtNoteSend, vtNoteRecv1))
	{
		cout << "RouteChatInterweave failed." << endl;
	}
	cout << "RouteChatInterweave:" << endl;
	for (auto& n : vtNoteRecv1)
	{
		cout << n.Utf8DebugString() << endl;
	}

	vector<RouteNote> vtNoteRecv2;
	if (!client.RouteChatSeq(vtNoteSend, vtNoteRecv2))
	{
		cout << "RouteChatSeq failed." << endl;
	}
	cout << "RouteChatSeq:" << endl;
	for (auto& n : vtNoteRecv2)
	{
		cout << n.Utf8DebugString() << endl;
	}

	cout << "RunClient finished." << endl;
}

