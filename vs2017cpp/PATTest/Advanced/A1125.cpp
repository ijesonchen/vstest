/*
1125. Chain the Ropes (25)
200 ms
65536 kB

Given some segments of rope, you are supposed to chain them into one rope. 
Each time you may only fold two segments into loops and chain them into one piece, as shown by the figure. 
The resulting chain will be treated as another segment of rope and can be folded again. 
After each chaining, the lengths of the original two segments will be halved.

Your job is to make the longest possible rope out of N given segments.

Input Specification:

Each input file contains one test case. For each case, 
the first line gives a positive integer N (2 <= N <= 10^4). 
Then N positive integer lengths of the segments are given in the next line, separated by spaces. 
All the integers are no more than 10^4.

Output Specification:

For each case, print in a line the length of the longest possible rope that can be made by the given segments. 
The result must be rounded to the nearest integer that is no greater than the maximum length.

Sample Input:
8
10 15 12 3 4 13 1 15
Sample Output:
14
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
15:30
贪心的选择最短两根合并
输出round to最近整形

问题：10000根，合并9999次
按大小排序
每次合并后，(m1+m2)/2 <= m3
从前往后合并
由于round to最近整形
可考虑整形合并

15:50 pass

疑问：round to: 数据只有1 3 4 10时，为6.5 输出应为？
*/

namespace nsA1125A
{

	void main(void)
	{
		int n;
		cin >> n;
		vector<int> vData(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> vData[i];
		}
		sort(vData.begin(), vData.end());
		int last = vData.front();
		for (int i = 1; i < n; ++i)
		{
			last = (last + vData[i]) / 2;
		}
		// 注意取整问题
		cout << last << endl;
	}
}

// rename this to main int PAT
int A1125Func(void)
{
	nsA1125A::main();
	return 0;
}


void A1125(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1125Func();
	cout << endl;
}

void A1125(void)
{
	A1125("data\\A1125-1.txt"); // 
}

