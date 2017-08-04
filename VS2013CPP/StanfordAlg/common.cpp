#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>
#include <filesystem>
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


std::vector<int64_t> ReadInt(const std::string& filename)
{
	fstream f(filename, ios::in);
	if (!f) { abort(); }

	vector<int64_t> v;

	int64_t x = 0;
	while (f >> x)
	{
		v.push_back(x);
	}

	return std::move(v);
}

std::vector<int64_t> ReadIntSkipFirst(const std::string& filename)
{
	fstream f(filename, ios::in);
	if (!f) { abort(); }

	vector<int64_t> v;

	int64_t n = 0;
	f >> n;
	if (!f) { abort(); }

	int64_t x = 0;

	while (f >> x)
	{
		v.push_back(x);
	}

	CHECK(n == v.size());

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
