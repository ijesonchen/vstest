#include <atomic>
#include <chrono>
#include <iostream>
#include <sstream>
#include <ctime>
#include <thread>
#include <vector>

void AtomicTest(void);
using namespace std;
using namespace std::chrono;

/*
release: 10亿次 9sec
debug: 1亿次 12sec

GCounter/ U64toString  1G次 3.8G cpu
release: 
	GCounter + only 29sec
	GCounter + U64toString: 210 sec
debug: about 10 times of release

*/


atomic_ullong gCounter;

inline std::uint64_t GCounter(void)
{
	return (uint64_t)(std::time(nullptr) << 32) | (++gCounter & 0xFFFFFFFF);
}

inline char Byte2Char(const char b0)
{
	auto b = (b0 > 0xf || b0 < 0) ? 0 : b0;
	return b < 10 ? ('0' + b) : ('a' - 10 + b);
}

inline std::string U64toString(const std::uint64_t i)
{
	std::string s;
	char* p = (char*)&i;
	char c[3] = { 0 };
	int k = 8;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			unsigned char b = p[--k];
			c[0] = Byte2Char(b >> 4);
			c[1] = Byte2Char(b & 15);
			s.append(c);
		}
		if (k)
		{
			s.append("-");
		}
	}

	return s;
}

void AtomicPerf()
{
	auto n = high_resolution_clock::period::num;
	auto d = high_resolution_clock::period::den;

	atomic_ullong cnt;

	int length = 10000 * 10000;

	auto t1 = high_resolution_clock::now();
	for (size_t i = 0; i < length; i++)
	{
		++cnt;
	}

	auto t2 = high_resolution_clock::now();

	auto t3 = t2 - t1;
	cout << "time cost: " << t3.count() * high_resolution_clock::period::num / high_resolution_clock::period::den << endl;
}


atomic_int64_t idx = -1;

void ThreadIdxTest(int64_t total)
{
	int64_t i;

	stringstream s0;
	s0 << this_thread::get_id() << ": ";
	auto s = s0.str();
	for (i = ++idx; i < total; i = ++idx)
	{
		stringstream ss;
		ss << s << i << endl;
		cout << ss.str();
	}
	s += ": exit.\n";
	cout << s;
}


void MultiThreadIdxTest()
{
	int64_t total = 100;
	int nThread = 25;
	vector<thread> v;

	auto t1 = high_resolution_clock::now();
	for (int i = 0; i < nThread; ++i)
	{
		thread th(ThreadIdxTest, total);
		v.push_back(std::move(th));
	}
	for (auto& i : v)
	{
		i.join();
	}

	auto t2 = high_resolution_clock::now();
	auto t3 = t2 - t1;
	cout << "time cost: " << t3.count() * high_resolution_clock::period::num / high_resolution_clock::period::den << endl;
}

void AtomicTest(void)
{
	// atomic_int64_t idx with multithread i = ++idx, passed.
	MultiThreadIdxTest();
}
