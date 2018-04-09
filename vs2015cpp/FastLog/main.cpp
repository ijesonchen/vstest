#include "FastLog.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <sstream>
#include <thread>
#include <chrono>
#include <cstring>
#include <array>
#include <atomic>

using namespace std;

std::atomic_uint_fast32_t g_totalCost;

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
		for (int i = 1; i < len-1; ++i)
		{
			s[i] = char('a' + rand() % 26);
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


void LogThread2(string id, int nLogCount, vector<string>* pvPreLog, nsFastLog::Logger* pLogger)
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
//		auto logger = pLogger->GetThreadLogger(id, pLogger);
		std::vector<std::array<char, 256>>* pv = nullptr;
		std::mutex* pMtx = nullptr;

		pLogger->GetCntr(pv, pMtx);
		auto& v = *pv;
		auto& mtx = *pMtx;
		for (int i = 0; i < nLogCount; ++i)
		{
			idxPreLog++;
			if (idxPreLog >= nPreSize)
			{
				idxPreLog = 0;
			}
			lock_guard<mutex> lk(mtx);
			v.emplace_back();
			memcpy(v.back().data(), vPreLog[idxPreLog].c_str(), vPreLog[idxPreLog].length() + 1);
		}
	}
	auto tCost = Tock(tp);

	ss.str("");
	ss << "Thread " << id << " LEAVE, cost" << tCost << " ms" << endl;
	cout << ss.str();
}


void LogThreadMem(string id, int nLogCount, vector<string>* pvPreLog, nsFastLog::Logger* pLogger)
{
	using namespace chrono;
	srand((int)time(nullptr));

	stringstream ss;
	ss << "Thread " << id << " ENTER" << endl;
	cout << ss.str();
	auto tp = Tick();
	int idxPreLog = 0;
	int idxTarget = -1;
	const int nMaxCntrSize = 10000;
	vector<array<char,256>> v(nMaxCntrSize);
	if (pLogger && pvPreLog)
	{
		const auto& vPreLog = *pvPreLog;
		const auto nPreSize = (int)vPreLog.size();
		auto logger = pLogger->GetThreadLogger(id, pLogger);
		for (int i = 0; i < nLogCount; ++i)
		{
			++idxPreLog;
			if (idxPreLog >= nPreSize)
			{
				idxPreLog = 0;
			}
			++idxTarget;
			if (idxTarget >= nMaxCntrSize)
			{
				idxTarget = 0;
			}
			memcpy(v[idxTarget].data(), vPreLog[idxPreLog].c_str(), vPreLog[idxPreLog].length() + 1);
		}
	}
	auto tCost = Tock(tp);

	ss.str("");
	ss << "Thread " << id << " LEAVE, cost" << tCost << " ms" << endl;
	cout << ss.str();
}

void LogThreadMem2(string id, int nLogCount, vector<string>* pvPreLog, nsFastLog::Logger* pLogger, mutex* pMtx)
{
	using namespace chrono;
	srand((int)time(nullptr));

	stringstream ss;
	ss << "Thread " << id << " ENTER" << endl;
	cout << ss.str();
	auto tp = Tick();
	int idxPreLog = 0;
//	vector<array<char, 256>> v;
	int idx = 0;
	mutex& mtx = *pMtx;
	if (pLogger && pvPreLog)
	{
		const auto& vPreLog = *pvPreLog;
		const auto nPreSize = (int)vPreLog.size();
		auto logger = pLogger->GetThreadLogger(id, pLogger);
		for (int i = 0; i < nLogCount; ++i)
		{
			++idxPreLog;
			if (idxPreLog >= nPreSize)
			{
				idxPreLog = 0;
			}
			lock_guard<mutex> lk(mtx);
			idx += i;
// 			v.emplace_back();
// 			memcpy(v.back().data(), vPreLog[idxPreLog].c_str(), vPreLog[idxPreLog].length() + 1);
		}
	}
	auto tCost = Tock(tp);

	ss.str("");
	ss << "Thread " << id << " LEAVE, cost" << tCost << " ms" << endl;
	g_totalCost += tCost;
	cout << ss.str();
}

int main(void)
{
	g_totalCost = 0;
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
	vector<mutex> vMutex(nThread);
	mutex mtx;
	for (int i = 0; i < nThread; ++i)
	{
		++sThreadId.back();
		thread th(LogThreadMem2, sThreadId, nLogPerThread, &vPreLog, &fastLogger, &mtx);
//		thread th(LogThread, sThreadId, nLogPerThread, &vPreLog, &fastLogger);
		vThread.push_back(std::move(th));
	}

	auto tp0 = Tick();

	// test for crash
// 	nsFastLog::Logger* p = nullptr;
// 	p->GetThreadLogger("", nullptr);

	for (auto& th : vThread)
	{
		if (th.joinable())
		{
			th.join();
		}
	}


	auto cost = Tock(tp0);

	cout << "log cost " << cost << " ms" << endl;
	cout << "total cost " << g_totalCost << " ms" << ", avg " << g_totalCost / nThread << endl;

	
	fastLogger.Stop();

	cout << "log stoped." << endl;

	return 0;
}