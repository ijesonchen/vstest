/*
1031. Hello World for U (20)

cost: 19:30

sln1: 15min 16/20 pt2,5 WA
sln2: n2 >= 3
	5min  18/20 pt5 WA
sln3: n1 + n2 + n3 - 2 = N.
	5min pass

sln3: 根据n1 + n2 + n3 - 2 = N.重新计算n1,n2
	5min 0/20

sln4: bug-fix
	10min 18/20 pt3 WA

sln5: 题解 n1 = (len+2)/3-1 
	10min pass

Given any string of N (>=5) characters,
you are asked to form the characters into the shape of U.
For example, "helloworld" can be printed as:

h  d
e  l
l  r
lowo

That is, the characters must be printed in the original order, 
starting top-down from the left vertical line with n1 characters, 
then left to right along the bottom line with n2 characters,
and finally bottom-up along the vertical line with n3 characters. 
And more, we would like U to be as squared as possible -- that is,
it must be satisfied that n1 = n3 = max { k| k <= n2 for all 3 <= n2 <= N } 
with n1 + n2 + n3 - 2 = N.

Input Specification:

Each input file contains one test case. 
Each case contains one string with no less than 5 and no more than 80 characters in a line. 
The string contains no white space.

Output Specification:

For each test case, print the input string in the shape of U as specified in the description.

Sample Input:
helloworld!
Sample Output:
h   !
e   d
l   l
lowor
*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1031Func(void)
{
	string s;
	cin >> s;
	int n1, n2, k, len;
	len = (int)s.length();

	n1 = len / 3;
	n2 = len - n1 * 2;
	if (n2 < 3)
	{
		n2 = 3;
		n1 = (len - n2) / 2;
		n2 = len - n1 * 2;
	}
	if (n2 <= n1)
	{
		++n2;
		n1 = (len - n2) / 2;
		n2 = len - n1 * 2;
	}
	k = n2 - 2;
	for (int i = 0; i < n1; ++i)
	{
		cout << s[i];
		for (int j = 0; j < k; ++j)
		{
			cout << " ";
		}
		cout << s[len - 1 - i] << endl;
	}
	cout << s.substr(n1, n2) << endl;
	return 0;
}

int A1031Func2(void)
{
	string s;
	cin >> s;
	int n1, n2, k, len, len2;
	len = (int)s.length();
	len2 = len + 2;
	n1 = len2 / 3 - 1;
	n2 = len - n1 * 2;
	k = n2 - 2;
	for (int i = 0; i < n1; ++i)
	{
		cout << s[i];
		for (int j = 0; j < k; ++j)
		{
			cout << " ";
		}
		cout << s[len - 1 - i] << endl;
	}
	cout << s.substr(n1, n2) << endl;
	return 0;
}

void A1031(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1031Func2();
	cout << endl;
}

void A1031(void)
{
	A1031("data\\A1031-1.txt"); // 
	A1031("data\\A1031-2.txt"); // 
	A1031("data\\A1031-3.txt"); // 
	A1031("data\\A1031-4.txt"); // 
	A1031("data\\A1031-5.txt"); // 
	A1031("data\\A1031-6.txt"); // 
}

