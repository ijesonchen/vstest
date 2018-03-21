/*
1104. Sum of Number Segments (20)
200 ms

14:00


Given a sequence of positive numbers, a segment is defined to be a consecutive subsequence. 
For example, given the sequence {0.1, 0.2, 0.3, 0.4}, we have 10 segments: 
(0.1) (0.1, 0.2) (0.1, 0.2, 0.3) (0.1, 0.2, 0.3, 0.4) (0.2) (0.2, 0.3) (0.2, 0.3, 0.4) (0.3) (0.3, 0.4) (0.4).

Now given a sequence, you are supposed to find the sum of all the numbers in all the segments. 
For the previous example, the sum of all the 10 segments is 0.1 + 0.3 + 0.6 + 1.0 + 0.2 + 0.5 + 0.9 + 0.3 + 0.7 + 0.4 = 5.0.

Input Specification:

Each input file contains one test case. 
For each case, the first line gives a positive integer N, the size of the sequence which is no more than 10^5.
The next line contains N positive numbers in the sequence, each no more than 1.0, separated by a space.

Output Specification:

For each test case, print in one line the sum of all the numbers in all the segments, accurate up to 2 decimal places.

Sample Input:
4
0.1 0.2 0.3 0.4
Sample Output:
5.00
*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

/*
14:00 直接计算系数数组
14:20 pass
*/

namespace nsA1104A
{
	// i: 0-based
	int64_t Count(int64_t n, int64_t i)
	{
		return (n - i)*(i + 1);
	}

	void main(void)
	{
		int n;
		double d, sum = 0;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> d;
			d *= Count(n, i);
			sum += d;
		}
		printf("%.2lf\n", sum);
	}
}

// rename this to main int PAT
int A1104Func(void)
{
	nsA1104A::main();
	return 0;
}


void A1104(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1104Func();
	cout << endl;
}

void A1104(void)
{
	A1104("data\\A1104-1.txt"); // 
}

