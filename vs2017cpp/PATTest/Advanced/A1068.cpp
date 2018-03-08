/*
1068. Find More Coins (30)
150 ms
65536 kB

17:20

Eva loves to collect coins from all over the universe, including some other planets like Mars. 
One day she visited a universal shopping mall which could accept all kinds of coins as payments.
However, there was a special requirement of the payment: for each bill, she must pay the exact amount. 
Since she has as many as 10^4 coins with her, she definitely needs your help. 
You are supposed to tell her, for any given amount of money, whether or not she can find some coins to pay for it.

Input Specification:

Each input file contains one test case. 
For each case, the first line contains 2 positive numbers: 
N (<=10^4, the total number of coins) and 
M(<=10^2, the amount of money Eva has to pay). 
The second line contains N face values of the coins, which are all positive numbers. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in one line the face values V1 <= V2 <= ... <= Vk such that V1 + V2 + ... + Vk = M. 
All the numbers must be separated by a space, and there must be no extra space at the end of the line. 
If such a solution is not unique, output the smallest sequence. 
If there is no solution, output "No Solution" instead.

Note: sequence {A[1], A[2], ...} is said to be "smaller" than sequence {B[1], B[2], ...} if there exists k >= 1 such that A[i]=B[i] for all i < k, and A[k] < B[k].

Sample Input 1:
8 9
5 9 8 7 2 3 4 1
Sample Output 1:
1 3 5
Sample Input 2:
4 8
7 2 4 3
Sample Output 2:
No Solution
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
17:20 
似乎是背包问题？
排序后，搜索所有可能排列，找到第一个后结束
18:10 29/30 PT6 TLE

PT6为no sln
尝试提前退出 
18:20 2/30
*/

namespace nsA1068A
{
	vector<int> vCoin(0);
	vector<int> vResult;
	int maxCoin = 0;
	int nCoin = 0;
	int dstCoin = 0;

	void PrintCoin(int n)
	{
		cout << vCoin[0];
		for (int j = 1; j < n; ++j)
		{
			cout << " " << vCoin[j];
		}
		cout << endl;
		return;
	}

	bool found = false;
	void Search(int start, int amount)
	{
		if (found || amount > dstCoin)
		{
			return;
		}
		if (amount == dstCoin)
		{
			if (!found)
			{
				vResult.assign(vCoin.begin(), vCoin.begin() + start);
				found = true;
			}

			return;
		}
		for (int i = start; i < nCoin; ++i)
		{
			swap(vCoin[i], vCoin[start]);
			Search(start + 1, amount + vCoin[start]);
			swap(vCoin[i], vCoin[start]);
		}
	}

	void main(void)
	{
		found = false;
		cin >> nCoin >> dstCoin;
		vCoin.resize(nCoin);
		vResult = vCoin;
		for (int i = 0; i < nCoin; ++i)
		{
			cin >> vCoin[i];
		}
		sort(vCoin.begin(), vCoin.end());
		maxCoin = 0;
		int total = 0;
		for (int i = 0; i < nCoin; ++i)
		{
			total += vCoin[i];
			if (total == dstCoin)
			{
				PrintCoin(i + 1);
				return;
			}
			if (total >= dstCoin)
			{
				maxCoin = i + 1;
				break;
			}
		}
		if (!maxCoin)
		{
			cout << "No Solution" << endl;
		}
		Search(0, 0);
		if (!found)
		{
			cout << "No Solution" << endl;
			return;
		}
		sort(vResult.begin(), vResult.end());

		cout << vResult[0];
		for (size_t j = 1; j < vResult.size(); ++j)
		{
			cout << " " << vResult[j];
		}
		cout << endl;
	}
}

// rename this to main int PAT
int A1068Func(void)
{
	nsA1068A::main();
	return 0;
}


void A1068(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1068Func();
	cout << endl;
}

void A1068(void)
{
//	A1068("data\\A1068-1.txt"); // 
	A1068("data\\A1068-2.txt"); // 
}

