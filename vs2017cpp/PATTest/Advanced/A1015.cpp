/*
1015. Reversible Primes (20)
cost: 20:55 15min 12/20

sln1: 穷举素数
	12/20
	测试 n <= 1000000
sln2：看题解 http://blog.csdn.net/realxuejin/article/details/10148713
	表述不清，没有理解题目意思
	示例2： 23 2
	23不可能是2进制，所以题目意思应该是，
	N在D进制表示下的倒序数字是不是也是素数。

A reversible prime in any number system is a prime whose "reverse" 
in that number system is also a prime. For example in the decimal 
system 73 is a reversible prime because its reverse 37 is also a prime.

Now given any two positive integers N (< 10^5) and D (1 < D <= 10), 
you are supposed to tell if N is a reversible prime with radix D.

Input Specification:

The input file consists of several test cases. Each case occupies a 
line which contains two integers N and D. The input is finished by a 
negative N.

Output Specification:

For each test case, print in one line "Yes" if N is a reversible prime 
with radix D, or "No" if not.

Sample Input:
73 10
23 2
23 10
-2
Sample Output:
Yes
Yes
No
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int64_t A1015Rev(int64_t n, int r)
{
	string s;
	while (n >= r)
	{
		s.push_back('0' + (char)(n%r));
		n /= r;
	}
	s.push_back('0' + (char)n);

	return strtoull(s.c_str(), nullptr, r);
}

bool IsPrime(int64_t n)
{
	if (n < 2)
	{
		return false;
	}
	auto sq = sqrt(n);
	for (int i = 2; i <= sq; ++i)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

// rename this to main int PAT
int A1015Func(void)
{
	int r;
	int64_t n1, n2;

	while (true)
	{
		cin >> n1;
		if (n1 < 0)
		{
			break;
		}
		cin >> r;
		if (IsPrime(n1))
		{
			n2 = A1015Rev(n1, r);
			if (IsPrime(n2))
			{
				cout << "Yes" << endl;
				continue;
			}
		}
		cout << "No" << endl;
	}

	return 0;
}


void A1015(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1015Func();
	cout << endl;
}

void A1015(void)
{
	A1015("data\\A1015-1.txt"); // 
}

