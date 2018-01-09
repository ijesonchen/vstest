/*
1010. Radix (25)
cost: 15:10
测试：没有  '+'
二分查找容易超时：代码不严谨
遍历18分，二分17分

sln1:
	n1, r
	n2, ?
	n2, [rmin, rmax] -> n3,r  n3?n1  binsearch

	void div(x,y,&a,&b): x/y=a...b
	dst RedixConv(src, r1, r2): src,r1 -> dst, r2
sln2:
	使用一个vector<int>作为中间结果进行比较

Given a pair of positive integers, for example, 6 
and 110, can this equation 6 = 110 be true? The answer 
is "yes", if 6 is a decimal number and 110 is a 
binary number.

Now for any pair of positive integers N1 and N2, your 
task is to find the radix of one number while that of 
the other is given.

Input Specification:

Each input file contains one test case. Each case 
occupies a line which contains 4 positive integers:
N1 N2 tag radix
Here N1 and N2 each has no more than 10 digits. A digit
is less than its radix and is chosen from the set 
{0-9, a-z} where 0-9 represent the decimal numbers 0-9,
and a-z represent the decimal numbers 10-35. The last
number "radix" is the radix of N1 if "tag" is 1, or of 
N2 if "tag" is 2.

Output Specification:

For each test case, print in one line the radix of the 
other number so that the equation N1 = N2 is true. If 
the equation is impossible, print "Impossible". If the
solution is not unique, output the smallest possible radix.

Sample Input 1:
6 110 1 10
Sample Output 1:
2
Sample Input 2:
1 ab 1 2
Sample Output 2:
Impossible
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

class A1010LargeInt
{
public:
	static int MinBase(const string& s);
	bool LoadFrom(const string& s, int nBase);
	A1010LargeInt& operator*(const int n);
	A1010LargeInt& operator+(const int n);

	bool operator==(const A1010LargeInt& other);
	bool operator<(const A1010LargeInt& other);
private:
	static int ConvS2I(const char c);
	int base;
	using ShortInt = uint8_t;
	using LongInt = uint64_t;
	const int Shift = sizeof(ShortInt) * 8;
	vector<ShortInt> result;
	vector<LongInt> assist;
};

int A1010LargeInt::MinBase(const string& s)
{
	int minBase = 0;
	for (auto c : s)
	{
		if (c == '+' || c == '-') { continue; }
		auto i = ConvS2I(c);
		if (i < 0) { return -1; }
		if (i > minBase) { minBase = i; }
	}
	return minBase + 1;
}

int A1010LargeInt::ConvS2I(const char c)
{
	if (c >= '0' && c <= '9') { return c - '0'; }
	else if (c >= 'a' && c <= 'z') { return c - 'a' + 10; }
	else if (c >= 'A' && c <= 'Z') { return c - 'A' + 10; }
	else { return -1; }
}

bool A1010LargeInt::LoadFrom(const string& s, int nBase)
{
	base = nBase;

	int n = 0;
	n = ConvS2I(s.front());
	if (n < 0 || n >= base)
	{
		return false;
	}
	result.clear();
	result.push_back(n);

	auto len = s.length();
	for (size_t i = 1; i < len; ++i)
	{
		n = ConvS2I(s[i]);
		if (n < 0 || n >= base)
		{
			return false;
		}
		operator*(base);
		operator+(n);
	}
	return true;
}

A1010LargeInt& A1010LargeInt::operator*(const int n)
{
	assist.assign(result.begin(), result.end());
	for (auto& i : assist)
	{
		i *= n;
	}
	auto len = result.size();
	ShortInt nLeft = 0;
	LongInt  nAss = 0;
	for (auto i = 0; i < len; ++i)
	{
		nAss = assist[i] + nLeft;
		result[i] = (ShortInt)nAss;
		nLeft = (ShortInt)(nAss >> Shift);
	}
	if (nLeft)
	{
		result.push_back(nLeft);
	}
	return *this;
}


A1010LargeInt& A1010LargeInt::operator+(const int n)
{
	assist.assign(result.begin(), result.end());
	assist.front() += n;
	auto len = result.size();
	ShortInt nLeft = 0;
	LongInt  nAss = 0;
	for (auto i = 0; i < len; ++i)
	{
		nAss = assist[i];
		result[i] = (ShortInt)nAss;
		nLeft = (ShortInt)(nAss >> Shift);
		if (!nLeft)
		{
			break;
		}
	}
	if (nLeft)
	{
		result.push_back(nLeft);
	}
	return *this;
}

bool A1010LargeInt::operator==(const A1010LargeInt& other)
{
	return result == other.result;
}

bool A1010LargeInt::operator<(const A1010LargeInt& other)
{
	if (operator==(other))
	{
		return false;
	}
	auto s1 = result.size();
	auto s2 = other.result.size();
	if (s1 != s2)
	{
		return s1 < s2;
	}
	vector<ShortInt> v1(result.rbegin(), result.rend());
	vector<ShortInt> v2(other.result.rbegin(), other.result.rend());
	return v1 < v2;
}

// rename this to main int PAT
int A1010Func(void)
{
	string s1, s2;
	int tag, b1;
	cin >> s1 >> s2 >> tag >> b1;
	if (tag == 2)
	{
		swap(s1, s2);
	}
	bool neg1 = (s1.front() == '-');
	bool neg2 = (s2.front() == '-');
	if (neg1 != neg2)
	{
		cout << "Impossible" << endl;
		return 0;		
	}
	if (neg1)
	{
		s1 = s1.substr(1, string::npos);
	}
	if (neg2)
	{
		s2 = s2.substr(1, string::npos);
	}
	A1010LargeInt l1;
	l1.LoadFrom(s1, b1);
	A1010LargeInt l2;
	int b2low = l2.MinBase(s2);
// 	for (int base = b2low; base <= 36; ++base)
// 	{
// 		l2.LoadFrom(s2, base);
// 		if (l1 == l2)
// 		{
// 			cout << base << endl;
// 			return 0;
// 		}
// 	}
// 	cout << "Impossible" << endl;
// 	return 0;

	int b2high = 36;
	int b2mid = (b2low + b2high ) / 2;
	while (b2low < b2high)
	{
		b2mid = (b2low + b2high) / 2;
		l2.LoadFrom(s2, b2mid);
		if (l2 == l1)
		{
			cout << b2mid << endl;
			return 0;
		}
		if (l2 < l1)
		{
			b2low = b2mid + 1;
		}
		else
		{
			b2high = b2mid - 1;
		}
	}
	if (b2low == b2high)
	{
		b2mid = b2low;
	}
	l2.LoadFrom(s2, b2mid);
	if (l1 == l2)
	{
		cout << b2mid << endl;
		return 0;
	}
	cout << "Impossible" << endl;
	return 0;
}


void A1010(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1010Func();
	cout << endl;
}

void A1010Comp(const string& s1, const string& s2)
{
	A1010LargeInt l1, l2;
	l1.LoadFrom(s1, 16);
	l2.LoadFrom(s2, 16);
	cout << s1 << " < " << s2 << " : " << (l1 < l2) << endl;
}

void A1010(void)
{
	A1010("data\\A1010-1.txt"); // 2
	A1010("data\\A1010-2.txt"); // Impossible
	A1010("data\\A1010-3.txt"); // 36
 	A1010("data\\A1010-4.txt"); // Impossible
	A1010("data\\A1010-5.txt"); // 2
	A1010("data\\A1010-6.txt"); // 3
	A1010("data\\A1010-7.txt"); // 35
	A1010("data\\A1010-8.txt"); // any
}

