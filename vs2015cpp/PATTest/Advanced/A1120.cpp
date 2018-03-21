/*
1120. Friend Numbers (20)

cost: 14:35 10min pass

Two integers are called "friend numbers" if they share the same sum of their digits,
and the sum is their "friend ID". 
For example, 123 and 51 are friend numbers since 1+2+3 = 5+1 = 6, and 6 is their friend ID. 
Given some numbers, you are supposed to count the number of different friend ID's among them. 
Note: a number is considered a friend of itself.

Input Specification:

Each input file contains one test case. 
For each case, the first line gives a positive integer N. 
Then N positive integers are given in the next line, separated by spaces. 
All the numbers are less than 10^4.

Output Specification:

For each case, print in the first line the number of different friend ID's among the given integers. 
Then in the second line, output the friend ID's in increasing order. 
The numbers must be separated by exactly one space and there must be no extra space at the end of the line.

Sample Input:
8
123 899 51 998 27 33 36 12
Sample Output:
4
3 6 9 26
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

namespace nsA1120A
{
	int Friend(const string& s)
	{
		int f = 0;
		for (size_t i = 0; i < s.length(); ++i)
		{
			f += s[i] - '0';
		}
		return f;
	}
	int main(void)
	{
		int n;
		cin >> n;
		set<int> sf;
		for (int i = 0; i < n; ++i)
		{
			string s;
			cin >> s;
			int f = Friend(s);
			sf.insert(f);
		}
		cout << sf.size() << endl;
		set<int>::iterator it = sf.begin();
		cout << *it;
		for (++it; it != sf.end(); ++it)
		{
			cout << " " << *it;
		}
		cout << endl;
		return 0;
	}
}

// rename this to main int PAT
int A1120Func(void)
{
	return nsA1120A::main();
}


void A1120(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1120Func();
	cout << endl;
}

void A1120(void)
{
	A1120("data\\A1120-1.txt"); // 
}

