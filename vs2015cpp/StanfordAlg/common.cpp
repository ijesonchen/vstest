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
using namespace std::tr2;

std::chrono::steady_clock::time_point g_tp;

void EXPECT_TRUE(bool b)
{
	if (!b)
	{
		abort();
	}
}


template <typename TA, typename TB>
void EXPECT_TRUE(const TA& a, const TB& b)
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

std::vector<int64_t> ReadIntWithCount(const std::string& filename)
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

	EXPECT_TRUE(n == v.size());

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


void TimeCost(const std::chrono::high_resolution_clock::time_point& tp)
{
	using namespace chrono;

	auto tpNow = high_resolution_clock::now();
	auto dur = tpNow - tp;
	auto cost = duration_cast<duration<double>>(dur);
	auto costsec = cost.count();
	cout << endl << "time cost: ";
	if (costsec > 1)
	{
		cout << costsec << " seconds.";
	}
	else
	{
		cout << costsec * 1000 << " milliseconds.";
	}
	cout << endl;
}


// load test case file: beaunus/stanford-algs@github
std::vector<TestCaseInfo> BeaunusTestCase(const std::string tcPath, const std::string& root /*= "."*/)
{
	vector<TestCaseInfo> vtc;
	string is("input");
	auto ilen = is.length();
	string os("output");
	for (auto it = sys::directory_iterator(root + "\\" + tcPath), end = sys::directory_iterator();
		it != end; ++it)
	{
		auto ifn = it->path().string();
		auto stem = it->path().stem().string();
		auto pos = ifn.find(is);
		if (pos == string::npos)
		{
			continue;
		}
		// result file name
		auto rfn(ifn);
		rfn.replace(pos, ilen, os);
		if (!sys::exists(rfn))
		{
			cout << "output file not exist: " << rfn << endl;
			continue;
		}
		auto rlen = sys::file_size(rfn);
		if (rlen == uintmax_t(-1))
		{
			cout << "output file size error: " << rfn << endl;
			continue;
		}
		ifstream rf(rfn);
		if (!rf)
		{
			cout << "output file open error: " << rfn << endl;
			continue;
		}
		vtc.emplace_back(std::move(ifn));
		vtc.back().stem = stem;
		rf >> vtc.back().result;
	}
	return std::move(vtc);
}

void FinalTestResult(int n)
{
	if (n)
	{
		cout << " * failed: " << n << endl;
	}
	else
	{
		cout << " * All Passed." << endl;
	}
}