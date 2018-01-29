/*
1019. General Palindromic Number (20)

cost: 20:50 20min

sln1: 任意进制转换，结果使用v<i>保存
	最大值10^9，故而可以用int
	15min 17/20 pt5段错误
sln2: 3min 0特殊处理

A number that will be the same when it is written forwards or backwards is known as a Palindromic Number. 
For example, 1234321 is a palindromic number. 
All single digit numbers are palindromic numbers.

Although palindromic numbers are most often considered in the decimal system, 
the concept of palindromicity can be applied to the natural numbers in any numeral system. 
Consider a number N > 0 in base b >= 2, 
where it is written in standard notation with k+1 digits ai as the sum of (ai*b^i) for i from 0 to k. 
Here, as usual, 0 <= ai < b for all i and ak is non-zero. Then N is palindromic if and only if ai = ak-i for all i. 
Zero is written 0 in any base and is also palindromic by definition.

Given any non-negative decimal integer N and a base b, you are supposed to tell if N is a palindromic number in base b.

Input Specification:

Each input file contains one test case. 
Each case consists of two non-negative numbers N and b,
where 0 <= N <= 10^9 is the decimal number and 2 <= b <= 10^9 is the base. 
The numbers are separated by a space.

Output Specification:

For each test case, first print in one line "Yes" if N is a palindromic number in base b, or "No" if not. 
Then in the next line, print N as the number in base b in the form "ak ak-1 ... a0". 
Notice that there must be no extra space at the end of output.

Sample Input 1:
27 2
Sample Output 1:
Yes
1 1 0 1 1
Sample Input 2:
121 5
Sample Output 2:
No
4 4 1
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// rename this to main int PAT
int A1019Func(void)
{
	int n, b;
	cin >> n >> b;
	vector<int> vi;

	while (n >= b)
	{
		auto k = n % b;
		vi.push_back(k);
		n /= b;
	}
	if (n)
	{
		vi.push_back(n);
	}

	auto palin = true;
	auto len = (int)vi.size();
	for (int i = 0; i < len/2; ++i)
	{
		if (vi[i] != vi[len-1-i])
		{
			palin = false;
			break;
		}
	}

	if (palin)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}
	cout << vi.back();
	for (int i = len - 2; i >= 0; --i)
	{
		cout << " " << vi[i];
	}
	cout << endl;

	return 0;
}


void A1019(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1019Func();
	cout << endl;
}

void A1019(void)
{
	A1019("data\\A1019-1.txt"); // 
	A1019("data\\A1019-2.txt"); // 
}

