#include "FastLog.h"
#include <chrono>
#include <algorithm>
#include <thread>
#include <iostream>
#include <functional>
#include <csignal>
#include <sstream>

namespace nsFastLog
{
	using namespace std;

	bool gSigHandlerInstalled = false;
	Logger* gpLogger = nullptr;

	void SignalHandler(int signal_number)
	{
		stringstream ss;
		ss << "call SignalHandler " << signal_number << endl;
		cout << ss.str();
		if (gpLogger)
		{
			gpLogger->SigHandler(signal_number);
		}
		signal(signal_number, SIG_DFL);
		exit(1);
	}


	void Logger::SigHandler(int signal_number)
	{
		bRuning = false;
		if (thFlush.joinable())
		{
			thFlush.join();
		}
		FlushLog();
		fsLog << "SIGNAL RAISE " << signal_number << endl;
		Stop();
	}

	bool Logger::Init(const std::string& logFile, unsigned threadCnt)
	{
		gpLogger = this;
		if (!gSigHandlerInstalled)
		{
			gSigHandlerInstalled = true;
			if (SIG_ERR == signal(SIGTERM, SignalHandler))
			{
				cout << "SignalHandler failed - SIGTERM" << endl;
				return false;
			}
			if (SIG_ERR == signal(SIGABRT, SignalHandler))
			{
				cout << "SignalHandler failed - SIGABRT" << endl;
				return false;
			}
			if (SIG_ERR == signal(SIGFPE, SignalHandler))
			{
				cout << "SignalHandler failed - SIGFPE" << endl;
				return false;
			}
			if (SIG_ERR == signal(SIGSEGV, SignalHandler))
			{
				cout << "SignalHandler failed - SIGSEGV" << endl;
				return false;
			}
			if (SIG_ERR == signal(SIGILL, SignalHandler))
			{
				cout << "SignalHandler failed - SIGILL" << endl;
				return false;
			}
		}
		if (thFlush.joinable())
		{
			// thread still running
			return false;
		}
		if (fsLog.is_open()) 
		{
			fsLog.close();
		}
		fsLog.open(logFile, ios::out | ios::app);
		if (!fsLog.is_open()) 
		{ 
			return false; 
		}
		idxCntr = -1;
		nThread = std::min(threadCnt, MAXCNTR);

		bRuning = true;
		std::thread th(ThreadFlush, this);
		thFlush = std::move(th);
		return true;
	}

	void Logger::Stop(void)
	{
		bRuning = false;
		if (thFlush.joinable())
		{
			thFlush.join();
		}
		fsLog.close();
	}

	void Logger::ThreadFlush(Logger* pLogger)
	{
		while (pLogger->bRuning)
		{
			pLogger->FlushLog();
		}
		pLogger->FlushLog();
	}


	void Logger::FlushLog(void)
	{
		FlushLog2();
		return;
		std::vector<SLogHeader> vLogTmp(nThread);

		for (unsigned i = 0; i < nThread; ++i)
		{
			lock_guard<mutex> lk(vMtx[i]);
			vLogTmp[i].FlushFrom(vLogContent[i]);
		}

		vector<int> vItemIdx(nThread);
		vector<LogTime> vLogTime;
		size_t maxLen = 0;
// 		for (size_t i = 0; i < vLogTmp.size(); ++i)
// 		{
// 			if (!vLogTmp[i].vLogs.empty())
// 			{
// 				vLogTime.emplace_back(vLogTmp[i].vLogs.front().tp, i);
// 				vItemIdx[i] = 0;
// 
// 				maxLen = std::max(maxLen, vLogTmp[i].vLogs.size());
// 			}
// 		}
// 		cout << "max len " << maxLen << endl;
// 		
// 		make_heap(vLogTime.begin(), vLogTime.end(), std::greater<LogTime>());
// 		while (!vLogTime.empty())
// 		{
// 			pop_heap(vLogTime.begin(), vLogTime.end(), std::greater<LogTime>());
// 			size_t hdrIdx = vLogTime.back().hdrIdx;
// 			vLogTime.pop_back();
// 			int& itemIdx = vItemIdx[hdrIdx];
// 			auto& logItem = vLogTmp[hdrIdx];
// 			fsLog << logItem.hdr << " " << logItem.vLogs[itemIdx].tp << " " << logItem.vLogs[itemIdx].log << endl;
// 			if (itemIdx < logItem.vLogs.size() - 1)
// 			{
// 				++itemIdx;
// 				vLogTime.emplace_back(vLogTmp[hdrIdx].vLogs[itemIdx].tp, hdrIdx);
// 				push_heap(vLogTime.begin(), vLogTime.end(), std::greater<LogTime>());
// 			}
// 		}
	}


	void Logger::FlushLog2(void)
	{
		cout << "FlushLog2 sleep" << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
		return;


		std::vector<vector<array<char, 256>>> vLogTmp(nThread);

		for (unsigned i = 0; i < nThread; ++i)
		{
			lock_guard<mutex> lk(vMtx[i]);
			vLogTmp[i].swap(vLogContent2[i]);
		}

		vector<int> vItemIdx(nThread);
		vector<LogTime> vLogTime;
		size_t maxLen = 0;
		for (size_t i = 0; i < vLogTmp.size(); ++i)
		{
			if (!vLogTmp[i].empty())
			{
				
				maxLen = std::max(maxLen, vLogTmp[i].size());
			}
		}
		cout << "max len " << maxLen << endl;

		this_thread::sleep_for(chrono::milliseconds(10));
		return;

// 		make_heap(vLogTime.begin(), vLogTime.end(), std::greater<LogTime>());
// 		while (!vLogTime.empty())
// 		{
// 			pop_heap(vLogTime.begin(), vLogTime.end(), std::greater<LogTime>());
// 			size_t hdrIdx = vLogTime.back().hdrIdx;
// 			vLogTime.pop_back();
// 			int& itemIdx = vItemIdx[hdrIdx];
// 			auto& logItem = vLogTmp[hdrIdx];
// 			fsLog << logItem.hdr << " " << logItem.vLogs[itemIdx].tp << " " << logItem.vLogs[itemIdx].log << endl;
// 			if (itemIdx < logItem.vLogs.size() - 1)
// 			{
// 				++itemIdx;
// 				vLogTime.emplace_back(vLogTmp[hdrIdx].vLogs[itemIdx].tp, hdrIdx);
// 				push_heap(vLogTime.begin(), vLogTime.end(), std::greater<LogTime>());
// 			}
// 		}
	}

	ThreadLogger Logger::GetThreadLogger(const string& hdr, Logger* pFastLogger)
	{
		auto idx = ++idxCntr % nThread;
		cout << "CNTR IDX " << idx << endl;
		vLogContent[idx].hdr = hdr;
		ThreadLogger thLogger(idx, pFastLogger, hdr);
		return thLogger;
	}

	void Logger::GetCntr(std::vector<std::array<char, 256>>*& pv, std::mutex*& pMtx)
	{
		auto idx = ++idxCntr % nThread;
		 pv = &vLogContent2[idx];
		 pMtx = &vMtx[idx];
		stringstream ss;
		ss << "CNTR IDX " << idx << ", ptr " << pv << ", mtx " << pMtx << endl;
		cout << ss.str();
		return;
	}
}