#include "FastLog.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <sstream>
#include <thread>
#include <chrono>

using namespace std;

std::chrono::system_clock::time_point Tick(void)
{
	return std::chrono::system_clock::now();
}

int64_t Tock(const std::chrono::system_clock::time_point& tp)
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp).count();
}


void InitPreLog(vector<string>& vPreLog)
{
	int nPreLogCount = 1024;
	int nPreLogMinLen = 112;
	int nPreLogLenRange = 240 - 112 + 1;
	vPreLog.clear();
	vPreLog.resize(nPreLogCount);
	srand((int)time(nullptr));
	for (auto& s : vPreLog)
	{
		int len = nPreLogMinLen + rand() % nPreLogLenRange;
		s.resize(len);
		s.front() = '<';
		s.back() = '>';
		for (size_t i = 1; i < len-1; ++i)
		{
			s[i] = 'a' + rand() % 26;
		}
	}
}


void LogThread(string id, int nLogCount, vector<string>* pvPreLog, nsFastLog::Logger* pLogger)
{
	using namespace chrono;
	srand((int)time(nullptr));

	stringstream ss;
	ss << "Thread " << id << " ENTER" << endl;
	cout << ss.str();
	auto tp = Tick();
	int idxPreLog = 0;
	if (pLogger && pvPreLog)
	{
		const auto& vPreLog = *pvPreLog;
		const auto nPreSize = (int)vPreLog.size();
		auto logger = pLogger->GetThreadLogger(id, pLogger);
		for (int i = 0; i < nLogCount; ++i)
		{
			idxPreLog++;
			if (idxPreLog >= nPreSize)
			{
				idxPreLog = 0;
			}
			logger.Log(vPreLog[idxPreLog]);
		}
	}
	auto tCost = Tock(tp);

	ss.str("");
	ss << "Thread " << id << " LEAVE, cost" << tCost << " ms" << endl;
	cout << ss.str();
}

int main(void)
{
	int nThread = 8;
	int nLogPerThread = 1000000;
	vector<string> vPreLog;
	InitPreLog(vPreLog);


	nsFastLog::Logger fastLogger;
	if (!fastLogger.Init("tmp.log", nThread))
	{
		cout << "log init failed." << endl;
		return 0;
	}


	cout << "Starting log test thread" << endl;
	
	vector<thread> vThread;
	string sThreadId("THID0000");
	for (int i = 0; i < nThread; ++i)
	{
		++sThreadId.back();
		thread th(LogThread, sThreadId, nLogPerThread, &vPreLog, &fastLogger);
		vThread.push_back(std::move(th));
	}

	auto tp0 = Tick();


	for (auto& th : vThread)
	{
		th.join();
	}

	// test for crash
// 	nsFastLog::Logger* p = nullptr;
// 	p->GetThreadLogger("", nullptr);

	auto cost = Tock(tp0);

	cout << "log cost " << cost << " ms" << endl;

	fastLogger.Stop();

	return 0;
}