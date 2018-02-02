/*
1023. Have Fun with Numbers (20)

cost: 16:30 20min

Notice that the number 123456789 is a 9-digit number consisting exactly 
the numbers from 1 to 9, with no duplication.
Double it we will obtain 246913578, which happens to be another 9-digit number 
consisting exactly the numbers from 1 to 9,
only in a different permutation. 
Check to see the result if we double it again!

Now you are suppose to check if there are more numbers with this property. 
That is, double a given number with k digits, 
you are to tell if the resulting number consists 
of only a permutation of the digits in the original number.

Input Specification:

Each input file contains one test case. 
Each case contains one positive integer with no more than 20 digits.

Output Specification:

For each test case, first print in a line "Yes" if 
doubling the input number gives a number that consists of 
only a permutation of the digits in the original number,
or "No" if not. Then in the next line, print the doubled number.

Sample Input:
1234567899
Sample Output:
Yes
2469135798
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string A1023Double(const string& s)
{
	int len = (int)s.length();
	char carry = 0;
	string res(s.length(), '0');
	for (int i = len - 1; i >= 0; --i)
	{
		char ch = (s[i] - '0') * 2 + carry;
		carry = ch / 10;
		res[i] += (ch % 10);
	}
	if (carry)
	{
		res.insert(res.begin(), '0' + carry);
	}
	return res;
}

// rename this to main int PAT
int A1023Func(void)
{
	string s1;
	cin >> s1;
	string s2 = A1023Double(s1);
	string s3 = s2;
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());
	if (s1 == s2)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}
	cout << s3 << endl;

	return 0;
}


void A1023(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1023Func();
	cout << endl;
}

void A1023(void)
{
	A1023("data\\A1023-1.txt"); // 
	A1023("data\\A1023-2.txt"); // 
	A1023("data\\A1023-3.txt"); // 
}

