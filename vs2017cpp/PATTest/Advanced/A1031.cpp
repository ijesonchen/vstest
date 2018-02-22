/*
1031. Hello World for U (20)

cost: 19:30

sln1: 15min 16/20 pt2,5 WA

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
	k = n2 - 2;
	for (int i  = 0; i < n1; ++i)
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
	A1031Func();
	cout << endl;
}

void A1031(void)
{
	A1031("data\\A1031-1.txt"); // 
}

