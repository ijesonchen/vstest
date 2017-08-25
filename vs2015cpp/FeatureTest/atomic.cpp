#include <atomic>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

/*
release: 10亿次 9sec
debug: 1亿次 12sec
*/

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