/*
1029. Median (25)

cost: 10:20
	5min 直接归并求值 12/25 pt2,5,10-13WA
	5min 排序后归并   12/25 pt2,5,10-13WA
	5min 问题出在长度为偶数上 m应取(size-1)/2 pass


Given an increasing sequence S of N integers, 
the median is the number at the middle position. 
For example, the median of S1={11, 12, 13, 14} is 12, 
and the median of S2={9, 10, 15, 16, 17} is 15. 
The median of two sequences is defined to be the median
of the nondecreasing sequence which contains all
the elements of both sequences.
For example, the median of S1 and S2 is 13.

Given two increasing sequences of integers, you are asked to find their median.

Input

Each input file contains one test case. 
Each case occupies 2 lines,
each gives the information of a sequence.
For each sequence, the first positive integer 
N (<=1000000) is the size of that sequence.
Then N integers follow, separated by a space. 
It is guaranteed that all the integers are in the range of long int.

Output

For each test case you should output the median of the two given sequences in a line.

Sample Input
4 11 12 13 14
5 9 10 15 16 17
Sample Output
13
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// rename this to main int PAT
int A1029Func(void)
{
	int n;
	cin >> n;
	vector<int64_t> v1(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> v1[i];
	}
	cin >> n;
	vector<int64_t> v2(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> v2[i];
	}
	vector<int64_t> v3(v1.size() + v2.size());
	std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	auto m = (v3.size() - 1) / 2;

	cout << v3[m] << endl;

	return 0;
}


void A1029(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1029Func();
	cout << endl;
}

void A1029(void)
{
	A1029("data\\A1029-1.txt"); // 13
	A1029("data\\A1029-2.txt"); // 12
	A1029("data\\A1029-3.txt"); // 15
}

