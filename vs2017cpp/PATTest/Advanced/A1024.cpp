/*
1024. Palindromic Number (25)

cost: 17:10
sln: int64_t循环计算
	20min 18/25 pt6,8 错误
snl2: 循环最多100次。每次循环*10，int64_t可能会溢出
	20min pass

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


string A1024RevString(string s1)
{
	int len = (int)s1.length();
	for (int i = 0; i < len / 2; ++i)
	{
		swap(s1[i], s1[len - 1 - i]);
	}
	return s1;
}

string A1024AddString(string s1, const string& s2)
{
	int len = (int)s1.length();
	if (len != (int)s2.length())
	{
		throw 2;
	}
	char carry = 0;
	for (int i = len - 1; i >= 0; --i)
	{
		char ch = s1[i] - '0' + s2[i] - '0' + carry;
		carry = ch / 10;
		s1[i] = '0' + (ch % 10);
	}
	if (carry)
	{
		s1.insert(s1.begin(), '0' + carry);
	}
	return s1;
}

int A1024Func2(void)
{
	string s1, s2;
	int m;
	cin >> s1 >> m;
	s2 = A1024RevString(s1);
	if (s1 == s2)
	{
		cout << s1 << endl << "0" << endl;
		return 0;
	}
	for (int i = 0; i < m; ++i)
	{
		s2 = A1024RevString(s1);
		if (s1 == s2)
		{
			cout << s2 << endl << i << endl;
			return 0;
		}
		s1 = A1024AddString(s1, s2);
	}
	cout << s1 << endl << m << endl;
	return 0;
}

void A1024(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1024Func2();
	cout << endl;
}

void A1024(void)
{
	A1024("data\\A1024-1.txt"); // 
	A1024("data\\A1024-2.txt"); // 
	A1024("data\\A1024-3.txt"); // 
	A1024("data\\A1024-4.txt"); // 
}

