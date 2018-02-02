/*
1024. Palindromic Number (25)

cost: 17:10
sln: int64_tÑ­»·¼ÆËã
	20min 18/25 pt6,8 ´íÎó

A number that will be the same when it is written forwards or backwards is known as a Palindromic Number. 
For example, 1234321 is a palindromic number. 
All single digit numbers are palindromic numbers.

Non-palindromic numbers can be paired with palindromic ones via a series of operations. 
First, the non-palindromic number is reversed and the result is added to the original number. 
If the result is not a palindromic number, this is repeated until it gives a palindromic number. 
For example, if we start from 67, we can obtain a palindromic number in 2 steps: 
67 + 76 = 143, and 143 + 341 = 484.

Given any positive integer N, you are supposed to find its paired palindromic number and 
the number of steps taken to find it.

Input Specification:

Each input file contains one test case. 
Each case consists of two positive numbers N and K, where 
N (<= 10^10) is the initial numer and 
K (<= 100) is the maximum number of steps. 
The numbers are separated by a space.

Output Specification:

For each test case, output two numbers, one in each line. 
The first number is the paired palindromic number of N, 
and the second number is the number of steps taken to find the palindromic number. 
If the palindromic number is not found after K steps, 
just output the number obtained at the Kth step and K instead.

Sample Input 1:
67 3
Sample Output 1:
484
2
Sample Input 2:
69 3
Sample Output 2:
1353
3
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

string A1024I2A(int64_t n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}

int64_t A1024RevInt(int64_t n)
{
	string s1 = A1024I2A(n);
	int len = (int)s1.length();
	for (int i = 0; i < len / 2; ++i)
	{
		swap(s1[i], s1[len - 1 - i]);
	}
	return atoll(s1.c_str());
}


// rename this to main int PAT
int A1024Func(void)
{
	int64_t n, m, k;
	cin >> n >> m;
	int64_t n2 = A1024RevInt(n);
	if (n == n2)
	{
		cout << n << endl << "0" << endl;
		return 0;
	}
	for (int i = 0; i < m; ++i)
	{
		k = A1024RevInt(n);
		if (n == k)
		{
			cout << k << endl << i << endl;
			return 0;
		}
		n = n + k;
	}
	cout << n << endl << m << endl;
	return 0;
}


void A1024(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1024Func();
	cout << endl;
}

void A1024(void)
{
	A1024("data\\A1024-1.txt"); // 
	A1024("data\\A1024-2.txt"); // 
	A1024("data\\A1024-3.txt"); // 
}

