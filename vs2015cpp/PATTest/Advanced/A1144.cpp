/*
1144. The Missing Number (20)
150 ms
65536 kB

Given N integers, you are supposed to find the smallest positive integer that is NOT in the given list.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (<= 10^5).
Then N integers are given in the next line, separated by spaces. All the numbers are in the range of int.

Output Specification:

Print in a line the smallest positive integer that is missing from the input list.

Sample Input:
10
5 -25 9 6 1 3 4 2 5 17
Sample Output:
7
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;


/*
从0开始，下一个数的最大步长为1，则不跳过某一个数
pass
*/
namespace nsA1144D
{
	void main(void)
	{
		int n, t;
		vector<int> vData;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &t);
			if (t > 0)
			{
				vData.push_back(t);
			}
		}
		// seg fault
		if (vData.empty())
		{
			cout << 1 << endl;
			return;
		}
		sort(vData.begin(), vData.end());
		int d = 0;
		for (size_t i = 0; i < vData.size(); ++i)
		{
			// 下一个数最大步长为1
			if (vData[i] > d + 1)
			{
				cout << d + 1 << endl;
				return;
			}
			d = vData[i];
		}
		cout << vData.back() + 1 << endl;
	}
}

// rename this to main int PAT
int A1144Func(void)
{
	nsA1144D::main();
	return 0;
}


void A1144(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1144Func();
	cout << endl;
}

// from A
/*
vec<bool>记录每一个合法数
*/
namespace nsA1144C
{
	const int MAXINT = 100002;
	void main(void)
	{
		int n, t;
		vector<bool> vHas(MAXINT);
		scanf("%d", &n);

		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &t);
			if (t <= 0) { continue; }
			// 做多10^5个数，所以最大为10^5+1
			if (t >= MAXINT) { continue; }
			vHas[t] = true;
		}
		for (int i = 1; i <= MAXINT; ++i)
		{
			if (!vHas[i])
			{
				cout << i << endl;
				return;
			}
		}
	}
}

/*
pt1-5 wa
bug-fix-1: pass
uset去重，vec<int>排序
*/
namespace nsA1144B
{
	void main(void)
	{
		int n, t;
		vector<int> vData;
		unordered_set<int> usetData;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &t);
			if (t > 0 &&
				(usetData.find(t) == usetData.end()))
			{
				vData.push_back(t);
				usetData.insert(t);
			}
		}
		sort(vData.begin(), vData.end());
		for (size_t i = 0; i < vData.size(); ++i)
		{
			if (vData[i] != i + 1)
			{
				cout << i + 1 << endl;
				return;
			}
		}
		// bug-fix-1: 
		// cout << vData.size() << endl;
		cout << vData.size() + 1 << endl;
	}
}

/*
PT6 EXCEPTION
improve-1 pass
int[]记录每一个数是否存在
*/
namespace nsA1144A
{
	const int MAXINT = 1500000;
	int a[MAXINT + 1] = { false };
	void main(void)
	{
		int n, t;
		cin >> n;

		for (int i = 0; i < n; ++i)
		{
			cin >> t;
			if (t <= 0) { continue; }
			// improve-1: throw 0 -> continue
			if (t > MAXINT) { continue; }
			a[t] = true;
		}
		for (int i = 1; i <= MAXINT; ++i)
		{
			if (!a[i])
			{
				cout << i << endl;
				return;
			}
		}
	}
}

void A1144(void)
{
	A1144("data\\A1144-1.txt"); // 
	A1144("data\\A1144-2.txt"); // 
	A1144("data\\A1144-3.txt"); // 
}

