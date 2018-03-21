/*
1065. A+B and C (64bit) (20)
100 ms
65536 kB

Given three integers A, B and C in [-2^63, 2^63], you are supposed to tell whether A+B > C.

Input Specification:

The first line of the input gives the positive number of test cases, T (<=10). 
Then T test cases follow, each consists of a single line containing three integers A, B and C, separated by single spaces.

Output Specification:

For each test case, output in one line "Case #X: true" if A+B>C, 
or "Case #X: false" otherwise, where X is the case number (starting from 1).

Sample Input:
3
1 2 3
2 3 4
9223372036854775807 -9223372036854775808 0
Sample Output:
Case #1: false
Case #2: true
Case #3: false
*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

/*
16：00
大整数加法：
16：35放弃

直接根据溢出判断
16：45pass
思路要清晰！！！
*/

namespace nsA1065A
{
	bool Check(int64_t a, int64_t b, int64_t c)
	{
		if (a>=0 && b<=0 || a<=0 && b>=0)
		{
			return a + b > c;
		}
		if (a>=0&&b>=0)
		{
			int64_t d = a + b;
			if (d>=a&&d>=b)
			{
				return a + b > c;
			}
			else
			{
				return true;
			}
		}
		if (a<=0 && b<=0)
		{
			int64_t d = a + b;
			if (d<=a && d<=b)
			{
				return a + b > c;
			}
			else
			{
				return false;
			}
		}
	}

	void main(void)
	{
		int n;
		int64_t a, b, c;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> a >> b >> c;
			if (!Check(a,b,c))
			{
				printf("Case #%d: false\n", i + 1);
			}
			else
			{
				printf("Case #%d: true\n", i + 1);
			}
		}
	}
}


// rename this to main int PAT
int A1065Func(void)
{
	nsA1065A::main();
	return 0;
}


void A1065(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1065Func();
	cout << endl;
}

void A1065(void)
{
	A1065("data\\A1065-1.txt"); // 
}

