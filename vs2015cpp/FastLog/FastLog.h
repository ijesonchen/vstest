#include <cstdint>
#include <string>
#include <mutex>
#include <fstream>
#include <vector>
#include <atomic>
#include <thread>
#include <cstring>
#include <array>

/*
实现一个低延迟的日志系统，这个系统单次允许写入长度为128-256字节的字符串, 字符串顺序包含写入线程的名
字(８字节ASCII)，精确到纳秒的写入时间(六十四位长整型距离epoch纳秒数)，以及从预先定义的长度为
112-240字节的1024个字符串中随机选取的一个

要求：
实现语言为modern c++, linux平台. x86处理器. 至少允许８个线程并发各写入一百万次，各线程不破坏
其他线程写入的字符串，写入顺序需要按时间顺序递增不发生乱序.在尽可能短的时间完成全部写入，单个写入
任务平均延迟低于5０纳秒.支持重启app不丢失已经写入的记录

不允许使用包括但不限于boost的第三方库，仅允许使用原生的语言特性和标准库,递交源代码请附带设计说明,并使用有意义的变量命名
编码风格是一个需要注意的要素
*/

namespace nsFastLog
{
	class ThreadLogger;

	struct LogTime
	{
		std::int64_t tp;
		size_t hdrIdx;

		LogTime(std::int64_t t, size_t i)
			: tp(t)
			, hdrIdx(i)
		{}

		bool operator>(const LogTime& other) const
		{
			return tp > other.tp;
		}
	};

	typedef std::int64_t SLogItem;

// 	struct SLogItem
// 	{
// 		std::int64_t tp;
//		std::string log;
//		char log[256];
		
// 		SLogItem(std::int64_t t, const std::string& l)
// 			: tp(t)
//			, log(l)
//		{
//			memcpy(log, l.c_str(), l.length() + 1);
//		}
//	};

	struct SLogHeader
	{
		const unsigned PRESIZE = 1000000;
		std::string hdr;
		std::vector<SLogItem> vLogs;

		SLogHeader(void)
		{
			vLogs.reserve(PRESIZE);
		}

		void FlushFrom(SLogHeader& other)
		{
			hdr = other.hdr;
			vLogs.swap(other.vLogs);
		}
	};

	class Logger
	{
		const unsigned MAXCNTR = 8;
		std::fstream fsLog;
		
		std::vector<std::mutex> vMtx;
		std::vector<SLogHeader> vLogContent;
		std::vector<std::vector<std::array<char, 256>>> vLogContent2;
		std::atomic_uint idxCntr;
		unsigned nThread;

		std::thread thFlush;
		bool bRuning = false;
		static void ThreadFlush(Logger* pLogger);

		void FlushLog(void);
		void FlushLog2(void);
	public: 
		Logger() :vMtx(MAXCNTR), vLogContent(MAXCNTR), vLogContent2(MAXCNTR)
		{
		};
		bool Init(const std::string& logFile, unsigned threadCnt);
		void Stop(void);
		ThreadLogger GetThreadLogger(const std::string& hdr, Logger* pFastLogger);
		void GetCntr(std::vector<std::array<char, 256>>*& pv, std::mutex*& pMtx);
		inline void Log(const int idCntr, const std::string& logHdr, const std::string& log)
		{
			std::int64_t tp = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			std::lock_guard<std::mutex> lk(vMtx[idCntr]);
			vLogContent[idCntr].vLogs.emplace_back(tp);
//			vLogContent2[idCntr].emplace_back();
//			memcpy(vLogContent2[idCntr].back().data(), log.c_str(), log.size());
		}

		void SigHandler(int signal_number);
	};


	class ThreadLogger
	{
		int idxLogCntr;
		Logger* pFastLogger;
		std::string logHdr;
	public:
		ThreadLogger(int idx, Logger* pLogger, const std::string& hdr)
			: idxLogCntr(idx)
			, pFastLogger(pLogger)
			, logHdr(hdr)
		{
		}

		inline void Log(const std::string& log)
		{
			pFastLogger->Log(idxLogCntr, logHdr, log);
		}
	};
}