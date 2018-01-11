
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <deque>

using namespace std;


//////////////////////////////////////////////////////////////////////////
// common function
int A1010ConvCh2I(const char c)
{
	if (c >= '0' && c <= '9') { return c - '0'; }
	else if (c >= 'a' && c <= 'z') { return c - 'a' + 10; }
	else if (c >= 'A' && c <= 'Z') { return c - 'A' + 10; }
	else { throw 1; return -1; }
}

int MinBase(const string& s)
{
	int minBase = 0;
	for (auto c : s)
	{
		auto i = A1010ConvCh2I(c);
		if (i > minBase) { minBase = i; }
	}
	if (minBase > 35) { throw 1; }
	return minBase + 1;
}



//////////////////////////////////////////////////////////////////////////
// vector -> large int

class A1010LargeInt
{
public:
	bool LoadFrom(const string& s, int nBase);

	A1010LargeInt& operator*(const int n);
	A1010LargeInt& operator+(const int n);

	bool operator==(const A1010LargeInt& other);
	bool operator<(const A1010LargeInt& other);

private:
	int base;
	using ShortInt = uint32_t;
	using LongInt = uint64_t;
	const int Shift = sizeof(ShortInt) * 8;
	vector<ShortInt> result;
	vector<LongInt> assist;
};


bool A1010LargeInt::LoadFrom(const string& s, int nBase)
{
	base = nBase;

	int n = 0;
	n = A1010ConvCh2I(s.front());
	if (n < 0 || n >= base)
	{
		throw 1;
		return false;
	}
	result.clear();
	result.push_back(n);

	auto len = s.length();
	for (size_t i = 1; i < len; ++i)
	{
		n = A1010ConvCh2I(s[i]);
		if (n < 0 || n >= base)
		{
			throw 1;
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
	ShortInt carry = 0;
	LongInt  ass = 0;
	auto len = result.size();
	for (auto i = 0; i < len; ++i)
	{
		ass = assist[i] + carry;
		result[i] = (ShortInt)ass;
		carry = (ShortInt)(ass >> Shift);
	}
	if (carry)
	{
		result.push_back(carry);
	}
	return *this;
}


A1010LargeInt& A1010LargeInt::operator+(const int n)
{
	assist.assign(result.begin(), result.end());
	ShortInt carry = n;
	LongInt  ass = 0;
	auto len = result.size();
	for (auto i = 0; i < len; ++i)
	{
		ass = assist[i] + carry;
		result[i] = (ShortInt)ass;
		carry = (ShortInt)(ass >> Shift);
		if (!carry)
		{
			break;
		}
	}
	if (carry)
	{
		result.push_back(carry);
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
int main(void)
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

	int64_t b2low = MinBase(s2);
	int64_t b2high = 0x7fffffff;
	int64_t mid = 0;
	while (b2low <= b2high)
	{
		mid = (b2high - b2low) / 2 + b2low;
		if (mid <= 0)
		{
			throw 0;
		}
		l2.LoadFrom(s2, (int)mid);
		if (l2 == l1)
		{
			cout << mid << endl;
			return 0;
		}
		else if (l2 < l1)
		{
			b2low = mid + 1;
		}
		else
		{
			b2high = mid - 1;
		}
	}
	cout << "Impossible" << endl;
	return 0;
}
