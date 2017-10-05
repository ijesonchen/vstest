/*
The goal of this problem is to implement a variant of the 2-SUM algorithm 
covered in this week's lectures.
The file contains 1 million integers, both positive and negative (there 
might be some repetitions!).This is your array of integers, with the ith 
row of the file specifying the ith entry of the array.
Your task is to compute the number of target values t in the interval 
[-10000,10000] (inclusive) such that there are distinct numbers x,y in 
the input file that satisfy x+y=t. (NOTE: ensuring distinctness requires 
a one-line addition to the algorithm from lecture.)
Write your numeric answer (an integer between 0 and 20001) in the space 
provided.
OPTIONAL CHALLENGE: If this problem is too easy for you, try implementing 
your own hash table for it. For example, you could compare performance 
under the chaining and open addressing approaches to resolving collisions.
*/

// n: input size 1000000  m: 20001

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <ctime>
#include "common.h"

using namespace std;

// all sum: n^2 = 1T


// m * n  : 10k * 1m  = 10g
// release: 1600 sec
// bad hash?
int NumberOfTargetsHash(const std::string& fn, const int low, const int high)
{
	auto v = ReadInt(fn);

	unordered_set<int64_t> uset;
	uset.insert(v.begin(), v.end());

	cout << v.size() << " read, " << uset.size() << " in set" << endl;

	int num = 0;
	for (int t = low; t <= high; ++t)
	{
		if (t % 100 == 0)
			cout << "\t\t" << num << " - " << t << endl;
		auto length = uset.size() - 1;
		for (auto a : uset)
		{
			auto b = t - a;
			if (a == b)
			{
				continue;
			}
			if (uset.find(b) != uset.end())
			{
				++num;
				break;
			}
		}
	}
	return num;
}

// m * n * logn : 10k * 1m * 20 = 200g
// RELASE: 500 sec
int NumberOfTargets(const std::string& fn, const int low, const int high)
{
	auto v = ReadInt(fn);

	cout << v.size() << " read." << endl;
	sort(v.begin(), v.end());

	int num = 0;
	for (int t = low; t <= high; ++t)
	{
		if (t % 100 == 0)
			cout << "\t\t" << num << " - " << t << endl;
		auto length = v.size() - 1;
		for (size_t i = 0; i < length; i++)
		{
			auto a = v[i];
			auto b = t - a;
			if (b < a)
			{
				continue;
			}
			if (binary_search(v.begin() + i + 1, v.end(), b))
			{
				++num;
				break;
			}
		}
	}
	return num;
}

void TwoSum(void)
{
	// ?? hash is slower than binSearch
	if (NumberOfTargets("data\\wk8-test1-3-10-8.txt", 3, 10) != 8)
	{
		abort();
	}
	auto fn = "data\\wk8-2sum.txt"; // result: 427
	auto tm1 = time(nullptr);
	if (NumberOfTargets(fn, -10000, 10000) != 427)
	{
		abort();
	}
	tm1 = time(nullptr) - tm1;
	cout << "cost: " << tm1 << endl;
}