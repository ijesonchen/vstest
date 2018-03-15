/*
1117. Eddington Number(25)
250 ms
65536 kB



British astronomer Eddington liked to ride a bike. It is said that in order to show off his skill,
he has even defined an "Eddington number", E -- 
that is, the maximum integer E such that it is for E days that one rides more than E miles.
Eddington's own E was 87.

Now given everyday's distances that one rides for N days, you are supposed to find the corresponding E (<=N).

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N(<=10^5), 
the days of continuous riding. 
Then N non-negative integers are given in the next line, being the riding distances of everyday.

Output Specification:

For each case, print in a line the Eddington number for these N days.

Sample Input:
10
6 7 6 9 3 10 8 2 7 8
Sample Output:
6
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

/*
14:45
区间和 >= 区间长度
动态规划？区间和？贪心？

最大10^5 scanf读取
15:10 推测E的计算方法
	每连续E天公里数都大于E*E
	E*E可能非常大，使用int64_t

判断E是否可能
E取值[1,n]

线性查找
15:30 1/25 wa0,1,2,4 lte3

bug-fix-1
15:40 1/25 wa0,1,2,4 lte3

判定：total < e*e?
15:42 1/25
15:50  bug-fix-2 bug-fix-3 4/25 wa0,1,4 tle3
*/

namespace nsA1117A
{
	bool MoreEdd(const vector<int>& v, const int k)
	{
		int len = (int)v.size();
		if (len < k){ return false; }
		long long total = 0;
		long long mindist = k * k;
		total = accumulate(v.begin(), v.begin() + k, total);
		// more than E miles
		if (total <= mindist) { return false; }
		for (int i = k; i < len; ++i)
		{
			// bug-fix-1 total = total + v[i - k] + v[i];
			total = total - v[i - k] + v[i];
			if (total <= mindist) { return false; }
		}
		return true;
	}

	void main(void)
	{
		int n;
		scanf("%d", &n);
		vector<int> vDist(n);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &vDist[i]);
		}
		// bug-fix-2 e=n
		int e = n;
		// bug-fix-3 e=n-1 (i<n) -> (i<=n)
		for (int i = 2; i <= n; ++i)
		{
			if (!MoreEdd(vDist, i))
			{
				e = i - 1;
				break;
			}
		}
		cout << e << endl;
	}
}

// rename this to main int PAT
int A1117Func(void)
{
	nsA1117A::main();
	return 0;
}


void A1117(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1117Func();
	cout << endl;
}

void A1117(void)
{
//	A1117("data\\A1117-1.txt"); // 
//	A1117("data\\A1117-2.txt"); // 
//	A1117("data\\A1117-3.txt"); //
//	A1117("data\\A1117-4.txt"); //
	A1117("data\\A1117-5.txt"); //
}

