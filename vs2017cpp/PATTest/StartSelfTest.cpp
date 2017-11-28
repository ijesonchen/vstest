#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void PrintChar(int n, char ch)
{
	for (int i = 0; i < n; i++)
	{
		cout << ch;
	}
}

void PrintSandyClock(int n, char ch)
{
	int k = (int)sqrt((n + 1) / 2.0);
	int left = n - 2 * k*k + 1;
	if (n < (2*k*k+1))
	{
		left = 0;
	}
	int m = 2 * k - 1;
	int star = m;
	int space = 0;
	for (int i = 0; i < k; ++i)
	{
		PrintChar(space, ' ');
		PrintChar(star, ch);
		cout << endl;
		++space;
		star -= 2;
	}
	space = k - 2;
	star = 3;
	for (int i = 1; i < k; ++i)
	{
		PrintChar(space, ' ');
		PrintChar(star, ch);
		cout << endl;
		--space;
		star += 2;
	}
	cout << left << endl;
}

void SelfTest1(void)
{
	PrintSandyClock(999, '*');
}

bool IsPrime(int n)
{
	int k = (int)sqrt(n);
	for (int i = 2; i <= k; ++i)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

void SelfTest2(void)
{
	int n = 5;
	int cnt = 0;
	int last = 2;
	for (int i = 3; i <= n; ++i)
	{
		if (IsPrime(i))
		{
			if (i - last == 2)
			{
				++cnt;
			}
			last = i;
		}
	}
	cout << cnt << endl;
}

void ReverseArray(int* left, int len)
{
	int* right = left + len - 1;
	while (left < right)
	{
		swap(*left, *right);
		++left;
		--right;
	}
}

/*
0 ... n-m-1, n-m  ...  n
n ...   n-m, n-m-1 ... 0
n-m ...   n, 0 ... n-m-1
*/
void SelfTest3(int n, int m, int* p)
{
	if (m>=n)
	{
		m = m % n;
	}
	ReverseArray(p, n);
	ReverseArray(p, m);
	ReverseArray(p + m, n - m);
	for (int i = 0; i < n; ++i)
	{
		cout << p[i];
		if (i != n-1)
		{
			cout << " ";
		}
	}
	cout << endl;
}

void SelfTest3(void)
{
	int p[7] = { 1,2,3,4,5,6,7 };
	SelfTest3(7, 3, p);
}

#include <iostream>
#include <algorithm>
#include <sstream>

unsigned long long s2i(const string& s)
{
	unsigned long long a = 0;
	stringstream ss(s);
	ss >> a;
	return a;
}

string i2s(unsigned long long a)
{
	stringstream ss;
	ss << a;
	return ss.str();
}

string DoubleString(const string& s1)
{
	unsigned long long a = s2i(s1);
	a *= 2;
	return i2s(a);
}

bool IsPerm(const string& s1, const string& s2)
{
	vector<char> v1(s1.begin(), s1.end());
	sort(v1.begin(), v1.end());
	vector<char> v2(s2.begin(), s2.end());
	sort(v2.begin(), v2.end());
	return v1 == v2;
}

void SelfTest4(const string& s1)
{
	string s2;
	int len = (int)s1.length();

	if (len <= 18)
	{
		s2 = DoubleString(s1);
	}
	else
	{
		int part = len / 2;
		string p1 = s1.substr(0, part);
		string p2 = s1.substr(part);
		string d1 = DoubleString(p1);
		string d2 = DoubleString(p2);
		if (d2.length() > p2.length())
		{
			d2 = d2.substr(1);
			unsigned long long a1 = s2i(d1);
			++a1;
			d1 = i2s(a1);
		}
		s2 = d1 + d2;
	}
	if (IsPerm(s1, s2))
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}
	cout << s2 << endl;
}

void SelfTest4(void)
{
	SelfTest4("123456789");
	SelfTest4("1234567899");
	SelfTest4("123");
	SelfTest4("1");
}

#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

const int cardLen = 54;

string Card2String(int n)
{
	if (n < 13)
	{
		return "S" + i2s(n + 1);
	}
	else if (n < 26)
	{
		return "H" + i2s(n - 12);
	}
	else if (n < 39)
	{
		return "C" + i2s(n - 25);
	}
	else if (n < 52)
	{
		return "D" + i2s(n - 38);
	}
	else
	{
		return "J" + i2s(n - 51);
	}
}

void SelfTest5(int n, int* p)
{
	for (int i = 0; i < cardLen; ++i)
	{
		--p[i];
	}
	int c[cardLen] = { 0 };
	int d[cardLen] = { 0 };
	for (int i = 0; i < cardLen; ++i)
	{
		c[i] = i;
	}
	int* p1 = c;
	int* p2 = d;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < cardLen; ++j)
		{
			p2[p[j]] = p1[j];
		}
		swap(p1, p2);
	}
	cout << Card2String(p1[0]);
	for (int i = 1; i < cardLen; ++i)
	{
		cout << " " << Card2String(p1[i]);
	}
}

void SelfTest5(void)
{
	int n = 2;
	int p[cardLen] = { 36, 52, 37, 38, 3, 39, 40, 53, 54, 41, 11, 12, 13, 42, 43, 44, 2, 4, 23, 24, 25, 26, 27, 6, 7, 8, 48, 49, 50, 51, 9, 10, 14, 15, 16, 5, 17, 18, 19, 1, 20, 21, 22, 28, 29, 30, 31, 32, 33, 34, 35, 45, 46, 47 };

	SelfTest5(2, p);
}

void StartSelfTest(void)
{
	SelfTest5();
}
