#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>
#include "common.h"

using namespace std;

void CHECK(bool b)
{
	if (!b)
	{
		abort();
	}
}


template <typename TA, typename TB>
void CHECK(const TA& a, const TB& b)
{
	if (a != b)
	{
		abort();
	}
}


std::vector<int> ReadInt(const std::string& filename)
{
	fstream f(filename, ios::in);
	if (!f) { abort(); }
	int x = 0;
	vector<int> v;
	while (f >> x){ v.push_back(x); }
	return std::move(v);
}

void SleepMs(int millisec)
{
	cout << "sleep for " << millisec << " milliseconds..." << endl;
	std::chrono::milliseconds ms(millisec);
	this_thread::sleep_for(ms);
}

void SleepSec(int sec)
{
	SleepMs(sec * 1000);
}
