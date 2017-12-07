/*
1007. Maximum Subsequence Sum (25)
解析：最大子列和
	一段连续序列，如果和非负，则计入子列和。

A1007Kadane
	20/25, 7/8, 3

Given a sequence of K integers { N1, N2, ..., NK }. 
A continuous subsequence is defined to be { Ni, Ni+1,
..., Nj } where 1 <= i <= j <= K. The Maximum Subsequence 
is the continuous subsequence which has the largest sum 
of its elements. For example, given sequence { -2, 11, 
-4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } 
with the largest sum being 20.

Now you are supposed to find the largest sum, together with 
the first and the last numbers of the maximum subsequence.

Input Specification:

Each input file contains one test case. Each case occupies 
two lines. The first line contains a positive integer K 
(<= 10000). The second line contains K numbers, separated 
by a space.

Output Specification:

For each test case, output in one line the largest sum, 
together with the first and the last numbers of the maximum 
subsequence. The numbers must be separated by one space, but 
there must be no extra space at the end of a line. In case 
that the maximum subsequence is not unique, output the one 
with the smallest indices i and j (as shown by the sample 
case). If all the K numbers are negative, then its maximum 
sum is defined to be 0, and you are supposed to output the 
first and the last numbers of the whole sequence.

Sample Input:
10
-10 1 2 3 4 -5 -23 3 7 -21
Sample Output:
10 1 4
*/

#include "patMain.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// passed
void A1007Scan(void)
{
	int cnt, n;
	cin >> cnt;

	int sum = 0;
	bool bFirst = false;
	bool bZero = false;
	int nLast, nFirst;
	int sumTemp = 0;
	int left = -1, leftTemp = -1, right = 0;

	while (cin >> n)
	{
		if (n == 0)
		{
			// if has zero
			bZero = true;
		}
		if (!bFirst)
		{
			// first for all neg
			bFirst = true;
			nFirst = n;
		}
		sumTemp += n;
		if (sumTemp == n)
		{
			leftTemp = n;
		}
		if (sumTemp > sum)
		{
			// max found, store
			left = leftTemp;
			right = n;
			sum = sumTemp;
		}
		if (sumTemp <= 0)
		{
			// reset
			sumTemp = 0;
		}
		nLast = n;
	}
	if (sum == 0)
	{
		if (bZero)
		{
			cout << "0 0 0" << endl;
		}
		else
		{
			cout << 0 << " " << nFirst << " " << nLast << endl;
		}
	}
	else
	{
		cout << sum << " " << left << " " << right << endl;
	}
}

// pt3 错误:enter判断，以及含0/全负时的判断可能有问题。
void A1007Kadane(void)
{
	int cnt = 0;
	int n = 0;
	cin >> cnt >> n;
	int first = n;

	int leftTemp = -1;
	int left = -1;
	int right = -1;
	int last = 0;
	bool enter = false;
	bool has0 = false;

	int maxCurrent = -1;
	int maxGlobal = 0;
	do
	{
		if (n == 0)
		{
			has0 = true;
		}
		if (maxCurrent > maxGlobal)
		{
			maxGlobal = maxCurrent;
			left = leftTemp;
			right = last;
		}
		maxCurrent += n;
		last = n;
		if (enter && maxCurrent > 0)
		{
			enter = false;
			leftTemp = n;
		}
		if (maxCurrent < 0)
		{
			enter = true;
			maxCurrent = 0;
		}
	} while (cin >> n);

	if (left == -1)
	{
		if (has0)
		{
			cout << "0 0 0" << endl;
		}
		else
		{
			cout << "0 " << first << " " << n << endl;
		}
	}
	else
	{
		cout << maxGlobal << " " << left << " " << right << endl;
	}
}

// pt7: 超时
void A1007BruteForce3(void)
{
	int cnt, n;
	cin >> cnt;
	vector<int> v;
	while (cin >> n)
	{
		v.push_back(n);
	}

	int sum = 0;
	int m = -1, l = -1, r;
	for (int i = 0; i < cnt; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			sum = 0;
			for (int k = j; k <= i; ++k)
			{
				sum += v[k];
			}
			if (sum > m)
			{
				m = sum;
				l = j;
				r = i;
			}
		}
	}
	if (m == -1)
	{
		cout << "0 " << v.front() << " " << v.back() << endl;
	}
	else
	{
		cout << m << " " << v[l] << " " << v[r] << endl;
	}
}

// pt7: 72ms all passed.
void A1007BruteForce2(void)
{
	int cnt, n;
	cin >> cnt;
	vector<int> v;
	while (cin >> n)
	{
		v.push_back(n);
	}

	int sum = 0;
	int m = -1, l = -1, r;
	for (int i = 0; i < cnt; ++i)
	{
		sum = 0;
		for (int j = i; j < cnt; ++j)
		{
			sum += v[j];
			if (sum > m)
			{
				m = sum;
				l = i;
				r = j;
			}
		}
	}
	if (m == -1)
	{
		cout << "0 " << v.front() << " " << v.back() << endl;
	}
	else
	{
		cout << m << " " << v[l] << " " << v[r] << endl;
	}
}



void A1007(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1007Kadane2();
}

void A1007(void)
{
	A1007("data\\A1007-1.TXT"); // 12 1 6
	A1007("data\\A1007-2.TXT"); // 0 -1 -5
	A1007("data\\A1007-3.TXT"); // 0 0 0
	A1007("data\\A1007-4.TXT"); // 20 11 13 
	A1007("data\\A1007-5.TXT"); // 4 4 4 
	A1007("data\\A1007-6.TXT"); // 4 4 4 or 4 0 4
}

