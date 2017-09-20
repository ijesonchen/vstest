#include <atomic>
#include <chrono>
#include <iostream>
#include <ctime>
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

void AtomicTest(void)
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