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
		cin >> n;
		numbers = n + 1;

		vector<int> vData(numbers);
		vData[0] = n;
		for (int i = 1; i < numbers; ++i)
		{
			cin >> vData[i];
		}
		vector<int> vSort(vData);
//		sort(vSort.begin(), vSort.end());
// 		if (vSort == vData)
// 		{
// 			cout << 0 << endl;
// 		}
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

// rename this to main int PAT
int A1067Func(void)
{
	nsA1067A::main();
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
//	A1067("data\\A1067-1.txt"); // 
	A1067("data\\A1067-2.txt"); // 
}

