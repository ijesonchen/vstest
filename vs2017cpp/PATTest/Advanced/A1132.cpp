void A1132(void);
/*

cost: 16:10

ÖØ×ö£º15min pass



tips:if A/B is zero? e.g. z=10

1132. Cut Integer (20)
Cutting an integer means to cut a K digits long integer Z into 
two integers of (K/2) digits long integers A and B. For example, 
after cutting Z = 167334, we have A = 167 and B = 334. It is 
interesting to see that Z can be devided by the product of A and B, 
as 167334 / (167 x 334) = 3. Given an integer Z, you are supposed to 
test if it is such an integer.

Input Specification:

Each input file contains one test case. For each case, the first 
line gives a positive integer N (<= 20). Then N lines follow, each 
gives an integer Z (10<=Z<=2^31). It is guaranteed that the number 
of digits of Z is an even number.

Output Specification:

For each case, print a single line "Yes" if it is such a number, 
or "No" if not.

Sample Input:
3
167334
2333
12345678
Sample Output:
Yes
No
No
*/

#include "..\patMain.h"
#include <iostream>
#include <sstream>

using namespace std;

namespace nsA1132A
{
	string A1132n2s(unsigned n)
	{
		stringstream ss;
		ss << n;
		return ss.str();
	}

	unsigned A1132s2n(const string& s)
	{
		unsigned n;
		stringstream ss(s);
		ss >> n;
		return n;
	}

	void A1132Func(unsigned n0)
	{
		string s0 = A1132n2s(n0);
		int len = (int)s0.length() / 2;
		string s1 = s0.substr(0, len);
		string s2 = s0.substr(len, -1);
		unsigned n1 = A1132s2n(s1);
		unsigned n2 = A1132s2n(s2);
		unsigned n3 = n1 * n2;
		if (!n3)
		{
			cout << "No" << endl;
			return;
		}
		if ((n0 % (n1 * n2)) == 0)
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
	}
}

namespace nsA1132B
{

	void A1132Func(unsigned long  n)
	{
		stringstream ss;
		ss << n;
		string s = ss.str();
		size_t len = s.length() / 2;
		string s1, s2;
		s1 = s.substr(0, len);
		s2 = s.substr(len, len);
		unsigned long  n1 = stoi(s1);
		unsigned long  n2 = stoi(s2);
		unsigned long  n3 = n1 * n2;
		if (n3 && n % n3 == 0)
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
	}
}

void A1132(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);

	unsigned long cnt, n;
	cin >> cnt;
	while (cin >> n)
	{
		nsA1132B::A1132Func(n);
	}
}

void A1132(void)
{
	A1132("data\\A1132-1.TXT"); // Yes No No
	A1132("data\\A1132-2.TXT"); // No No
}