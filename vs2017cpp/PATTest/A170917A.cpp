void A170917A(void);
/*
A. Cut Integer (20)
Cutting an integer means to cut a K digits long integer Z into 
two integers of (K/2) digits long integers A and B. For example, 
after cutting Z = 167334, we have A = 167 and B = 334. It is 
interesting to see that Z can be devided by the product of A and B, 
as 167334 / (167 x 334) = 3. Given an integer Z, you are supposed to 
test if it is such an integer.

Input Specification:

Each input file contains one test case. For each case, the first 
line gives a positive integer N (<= 20). Then N lines follow, each 
gives an integer Z (10<=Z<=231). It is guaranteed that the number 
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

#include "patMain.h"
#include <iostream>
#include <sstream>

using namespace std;

string A170917An2s(int n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}

int A170917As2n(const string& s)
{
	int n;
	stringstream ss(s);
	ss >> n;
	return n;
}

void A170917AFunc(int n0)
{
	string s0 = A170917An2s(n0);
	int len = (int)s0.length() / 2;
	string s1 = s0.substr(0, len);
	string s2 = s0.substr(len, -1);
	int n1 = A170917As2n(s1);
	int n2 = A170917As2n(s2);
	if ((n0 % (n1 * n2)) == 0)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}

}

void A170917A(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);

	int cnt, n;
	cin >> cnt;
	while (cin >> n)
	{
		A170917AFunc(n);
	}
}

void A170917A(void)
{
	A170917A("data\\A170917A-1.TXT"); // Yes No No
}