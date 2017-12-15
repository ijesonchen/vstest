/*
1005. Spell It Right (20)

解析：数字求和+转换
难点：输入长度最长10^100,最大值9*10^100，i64会溢出。
方法：分段计算，手动加法器

Given a non-negative integer N, your task is to compute 
the sum of all the digits of N, and output every digit 
of the sum in English.

Input Specification:

Each input file contains one test case. Each case occupies 
one line which contains an N (<= 10^100).

Output Specification:

For each test case, output in one line the digits of the 
sum in English words. There must be one space between two 
consecutive words, but no extra space at the end of a line.

Sample Input:
12345
Sample Output:
one five
*/

#include "..\patMain.h"

#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

 int A1005PARTWIDTH = 9;
 int A1005PARTMAX = 1000000000;
vector<int> result;

string i2str(const int n)
{
	stringstream ss; 
	ss << n;
	return ss.str();
}

string i2num(char ch)
{
	switch (ch - '0')
	{
	case 0: return "zero";
	case 1: return "one";
	case 2: return "two";
	case 3: return "three";
	case 4: return "four";
	case 5: return "five";
	case 6: return "six";
	case 7: return "seven";
	case 8: return "eight";
	case 9: return "nine";
	default: throw "exception";
	}
	return "";
}

void A1005Print(void)
{
	auto s0 = i2str(result.back());
	cout << i2num(s0[0]);
	for (int i = 1; i < s0.length(); ++i)
	{
		cout << " " << i2num(s0[i]);
	}

	for (auto iter = result.rbegin() + 1;
		iter != result.rend(); ++iter)
	{
		auto si = i2str(*iter);
		auto z = A1005PARTWIDTH - si.length();
		for (int i = 0; i < z; ++i)
		{
			cout << " zero";
		}
		for (auto i : si)
		{
			cout << " " << i2num(i);
		}
	}
	cout << endl;
}

void Add(const char ch)
{
	result.front() += ch - '0';
	auto length = result.size();
	for (size_t i = 0; i < length - 1; ++i)
	{
		auto& n = result[i];
		if (n < A1005PARTMAX)
		{
			break;;
		}
		n -= A1005PARTMAX;
		++result[i + 1];
	}
	if (result.back() >= A1005PARTMAX)
	{
		result.back() -= A1005PARTMAX;
		result.push_back(1);
	}
}

void A1005(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);

	result.clear();
	result.push_back(0);
	char ch;
	while (cin >> ch)
	{
		Add(ch);
	}
	A1005Print();
}

void A1005(void)
{
 	A1005("data\\A1005-1.TXT"); // one five
	Tick();
	A1005("data\\A1005-2.TXT"); // one three seven six nine nine one
	Tock();
	A1005PARTWIDTH = 3;
	A1005PARTMAX = 1000;
	A1005("data\\A1005-2.TXT"); // 
	Tock();
	A1005PARTWIDTH = 5;
	A1005PARTMAX = 100000;
	A1005("data\\A1005-2.TXT"); // 
	Tock();
}