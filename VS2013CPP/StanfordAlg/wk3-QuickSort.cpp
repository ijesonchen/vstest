#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "common.h"
using namespace std;

vector<int32_t> ReadNumber(const string& filename)
{
	vector<int32_t> v;
	fstream f(filename, ios::in);
	if (!f.is_open())
	{
		abort();
	}
	int32_t i;
	while (f >> i)
	{
		v.push_back(i);
	}

	return std::move(v);
}

// l & r are included.

int32_t PartitionL(vector<int32_t>& v, int32_t l, int32_t r)
{
	auto p = v[l];
	auto i = l + 1;
	for (auto j = l + 1; j <= r; ++j)
	{
		if (v[j] < p)
		{
			swap(v[i], v[j]);
			++i;
		}
	}
	swap(v[l], v[i - 1]);

	return i - 1;
}

int32_t PartitionR(vector<int32_t>& v, int32_t l, int32_t r)
{
	swap(v[l], v[r]);
	auto p = v[l];
	auto i = l + 1;
	for (auto j = l + 1; j <= r; ++j)
	{
		if (v[j] < p)
		{
			swap(v[i], v[j]);
			++i;
		}
	}
	swap(v[l], v[i - 1]);

	return i - 1;
}

int32_t FindM3(vector<int32_t>& v, int32_t l, int32_t r)
{
	auto m = (r + l) / 2;
	if (v[l] < v[r])
	{
		if (v[l] < v[m])
		{
			if (v[m] < v[r])
			{
				// l m r
				return m;
			}
			else
			{
				// l r m
				return r;
			}
		}
		else
		{
			// m l r
			return l;
		}
	}
	else
	{
		// v[l] > v[r]
		if (v[l] < v[m])
		{
			//  r l m 
			return l;
		}
		else
		{
			// l max
			if (v[m] < v[r])
			{
				// m r l 
				return r;
			}
			else
			{
				// r m l
				return m;
			}
		}
	}
	abort();
}

int PartitionM3(vector<int32_t>& v, int32_t l, int32_t r)
{
	if (r - l + 1 < 3)
	{
		abort();
	}

	int32_t t = FindM3(v, l, r);

	swap(v[l], v[t]);
	auto p = v[l];
	auto i = l + 1;
	for (auto j = l + 1; j <= r; ++j)
	{
		if (v[j] < p)
		{
			swap(v[i], v[j]);
			++i;
		}
	}
	swap(v[l], v[i - 1]);

	return i - 1;
}

// return comp count
int32_t QuickSort(vector<int32_t>& v, int32_t l, int32_t r, decltype(PartitionL) Func)
{
	auto len = r - l + 1;
	if (len < 0)
	{
		abort();
	}
	else if (len <= 1)
	{
		return 0; // len - 1
	}
	else if (len == 2)
	{
		if (v[l] > v[r])
		{
			swap(v[l], v[r]);
		}
		return 1; // len - 1 
	}
	auto a = len - 1;

	auto idx = Func(v, l, r);
	auto b = QuickSort(v, l, idx - 1, Func);
	auto c = QuickSort(v, idx + 1, r, Func);

	return a + b + c;
}

void CheckSorted(const vector<int32_t>& v, int32_t ni)
{
	for (int32_t ii = 1; ii < ni; ++ii)
	{
		if (v[ii - 1] > v[ii])
		{
			abort();
		}
	}
}

void QuickSortPartition(void)
{
	/*
	first: 162085
	last: 164123
	m3: 138382
	*/
	auto fileName = "QuickSort.txt";
	auto v = ReadNumber(fileName);
	if (v.size() != 10000)
	{
		abort();
	}
	auto vL = v;
	auto vR = v;
	auto vM3 = v;
	auto s = v.size() - 1;
	//	auto s = 2;
	cout << "first: " << QuickSort(vL, 0, s, PartitionL) << endl;
	cout << "last: " << QuickSort(vR, 0, s, PartitionR) << endl;
	cout << "m3: " << QuickSort(vM3, 0, s, PartitionM3) << endl;

	CheckSorted(vL, s);
	CheckSorted(vR, s);
	CheckSorted(vM3, s);
}
