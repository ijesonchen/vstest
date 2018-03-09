/*
1067. Sort with Swap(0,*) (25)
150 ms
65536 kB

Given any permutation of the numbers {0, 1, 2,..., N-1}, 
it is easy to sort them in increasing order. 
But what if Swap(0, *) is the ONLY operation that is allowed to use? 
For example, to sort {4, 0, 2, 1, 3} we may apply the swap operations in the following way:

Swap(0, 1) => {4, 1, 2, 0, 3}
Swap(0, 3) => {4, 1, 2, 3, 0}
Swap(0, 4) => {0, 1, 2, 3, 4}

Now you are asked to find the minimum number of swaps need to sort the given permutation of the first N nonnegative integers.

Input Specification:

Each input file contains one test case, which gives a positive N (<=10^5) followed by a permutation sequence of {0, 1, ..., N-1}. 
All the numbers in a line are separated by a space.

Output Specification:

For each case, simply print in a line the minimum number of swaps need to sort the given permutation.

Sample Input:
10 3 5 7 2 6 4 9 0 8 1

Sample Output:
9
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
17:15
17:20 无思路。放弃。

18:20
排序后，交换的结果

*/

namespace nsA1067A
{

	void main(void)
	{
		int numbers, n;
		cin >> numbers;

		vector<int> vData;
		while (cin >> n)
		{
			vData.push_back(n);
		}
		numbers = vData.size();
		vector<int> vRef(numbers); // data to sort index
		for (int i = 0; i < numbers; ++i)
		{
			vRef[vData[i]] = i;
		}
		int cnt = 0;
		for (int i = 0; i < numbers; ++i)
		{
			int u = vData[i];
			if (u != i)
			{
				int ui = vRef[u];
				int ii = vRef[i];
				swap(vData[ui], vData[ii]);
				swap(vRef[u], vRef[i]);
				++cnt;
			}
		}
		cout << cnt << endl;
	}
}

/*
9:10
题意：只能和0调换
路径：0和当前位置的数字调换
0在对的位置时，找到第一个错的位置调换
9:40 29/25 pt1,2 tle
*/
namespace nsA1067B
{
	void main(void)
	{
		int n, t;
		scanf("%d", &n);

		vector<int> vData(n);
		int idx0 = 0;
		int left = 0;
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &t);
			if (!t) { idx0 = i; }
			if (t != i) { ++left; }
			vData[i] = t;
		}
		int cnt = 0;
		int idxi = 0;
		while (left)
		{
			if (!idx0)
			{
				// find next pos
				idxi = 1;
				while (idxi < n && vData[idxi] == idxi)
				{
					++idxi;
				}
				if (idxi == n)
				{
					break;
				}
				swap(vData[idx0], vData[idxi]);
				swap(idx0, idxi);
				++cnt;
				++left;
			}
			while (idx0)
			{
				idxi = 0;
				while (vData[idxi] != idx0)
				{
					++idxi;
				}
				swap(vData[idx0], vData[idxi]);
				swap(idx0, idxi);
				++cnt;
				--left;
			}
			--left;
		}
		cout << cnt << endl;
	}
}

// rename this to main int PAT
int A1067Func(void)
{
	nsA1067B::main();
	return 0;
}


void A1067(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1067Func();
	cout << endl;
}

void A1067(void)
{
	A1067("data\\A1067-1.txt"); // 
}

