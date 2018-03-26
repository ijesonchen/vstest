#include "FastLog.h"
#include <chrono>
#include <algorithm>
#include <thread>
#include <iostream>
#include <functional>
#include <csignal>

namespace nsFastLog
{
	using namespace std;

	bool gSigHandlerInstalled = false;
	Logger* gpLogger = nullptr;

	void SignalHandler(int signal_number)
	{
		if (gpLogger)
		{
			gpLogger->SigHandler(signal_number);
		}
	}


	void Logger::SigHandler(int signal_number)
	{
		bRuning = false;
		thFlush.join();
		FlushLog();
		fsLog << "SIGNAL RAISE " << signal_number << endl;
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
		if (fsLog) 
		{
			fsLog.close();
		}
		fsLog.open(logFile, ios::in | ios::app);
		if (!fsLog) 
		{ 
			return false; 
		}
		idxCntr = 0;
		nThread = std::min(threadCnt, MAXCNTR);

		bRuning = true;
		std::thread th(ThreadFlush, this);
		thFlush = std::move(th);
		return true;
	}

	void Logger::Stop(void)
	{
		bRuning = false;
		thFlush.join();
		fsLog.close();
	}

	void Logger::ThreadFlush(Logger* pLogger)
	{
		while (pLogger->bRuning)
		{
			pLogger->FlushLog();
		}
	}


	void Logger::FlushLog(void)
	{
		std::vector<SLogHeader> vLogTmp(nThread);

		for (unsigned i = 0; i < nThread; ++i)
		{
			lock_guard<mutex> lk(vMtx[i]);
			vLogTmp[i].FlushFrom(vLogContent[i]);
		}

		vector<int> vItemIdx(nThread);
		vector<LogTime> vLogTime;
		for (size_t i = 0; i < vLogTmp.size(); ++i)
		{
			if (!vLogTmp[i].vLogs.empty())
			{
				vLogTime.emplace_back(vLogTmp[i].vLogs.front().tp, i);
				vItemIdx[i] = 0;
			}
		}
		make_heap(vLogTime.begin(), vLogTime.end(), std::greater<LogTime>());
		while (!vLogTime.empty())
		{
			pop_heap(vLogTime.begin(), vLogTime.end(), std::greater<LogTime>());
			size_t hdrIdx = vLogTime.back().hdrIdx;
			vLogTime.pop_back();
			int& itemIdx = vItemIdx[hdrIdx];
			auto& logItem = vLogTmp[hdrIdx];
			fsLog << logItem.hdr << " " << logItem.vLogs[itemIdx].tp << " " << logItem.vLogs[itemIdx].log << endl;
			if (itemIdx < logItem.vLogs.size() - 1)
			{
				++itemIdx;
				vLogTime.emplace_back(vLogTmp[hdrIdx].vLogs[itemIdx].tp, hdrIdx);
				push_heap(vLogTime.begin(), vLogTime.end(), std::greater<LogTime>());
			}
		}
	}

	ThreadLogger Logger::GetThreadLogger(const string& hdr, Logger* pFastLogger)
	{
		auto idx = ++idxCntr % nThread;
		vLogContent[idx].hdr = hdr;
		ThreadLogger thLogger(idx, pFastLogger, hdr);
		return thLogger;
	}
}