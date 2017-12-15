/*
1001. A+B Format (20)
Calculate a + b and output the sum in standard format -- that is,
the digits must be separated into groups of three by commas (unless 
there are less than four digits).

Input

Each input file contains one test case. Each case contains a pair 
of integers a and b where -1000000 <= a, b <= 1000000. The numbers 
are separated by a space.

Output

For each test case, you should output the sum of a and b in one line. 
The sum must be written in the standard format.

Sample Input
-1000000 9
Sample Output
-999,991
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// rename this to main int PAT
int A1001Func(void)
{
	int a, b;
	cin >> a >> b;
	string s1;
	stringstream ss;
	ss << a + b;
	s1 = ss.str();
	bool neg = false;
	if (s1.front() == '-')
	{
		neg = true;
		s1.erase(0, 1);
	}
	string s2;
	int len = (int)s1.length();
	for (int i = 0; i < len; ++i)
	{
		s2.push_back(s1[len - 1 - i]);
		if (i % 3 == 2)
		{
			s2.push_back(',');
		}
	}
	if (s2.back() == ',')
	{
		s2.erase(s2.length() - 1, 1);
	}
	if (neg)
	{
		s2.push_back('-');
	}
	len = (int)s2.length();
	int half = len / 2;
	for (int i = 0; i < half; ++i)
	{
		swap(s2[i], s2[len-i-1]);
	}
	cout << s2 << endl;

	return 0;
}


void A1001(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1001Func();
	cout << endl;
}

void A1001(void)
{
	A1001("data\\A1001-1.txt"); // 
}

