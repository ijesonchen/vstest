/*
1108. Finding Average (20)

cost: 14:25

The basic task is simple: given N real numbers, you are supposed to calculate their average. 
But what makes it complicated is that some of the input numbers might not be legal. 
A "legal" input is a real number in [-1000, 1000] and 
is accurate up to no more than 2 decimal places. 
When you calculate the average, those illegal numbers must not be counted in.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (<=100). 
Then N numbers are given in the next line, separated by one space.

Output Specification:

For each illegal input number, print in a line
"ERROR: X is not a legal number" where X is the input. 
Then finally print in a line the result: 
"The average of K numbers is Y" where K is the number of legal inputs and Y is their average, 
accurate to 2 decimal places. 
In case the average cannot be calculated, output "Undefined" instead of Y. 
In case K is only 1, output "The average of 1 number is Y" instead.

Sample Input 1:
7
5 -3.2 aaa 9999 2.3.4 7.123 2.35
Sample Output 1:
ERROR: aaa is not a legal number
ERROR: 9999 is not a legal number
ERROR: 2.3.4 is not a legal number
ERROR: 7.123 is not a legal number
The average of 3 numbers is 1.38

Sample Input 2:
2
aaa -9999
Sample Output 2:
ERROR: aaa is not a legal number
ERROR: -9999 is not a legal number
The average of 0 numbers is Undefined

*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
14:25 14:45 18/20 PT2 WA
可能错误：误差累计 
改进：整数小数分开累加计算
*/
namespace nsA1108A
{
	bool ValidChar(const string& s)
	{
		for (auto ch : s)
		{
			if (!isdigit(ch))
			{
				return false;
			}
		}
		return true;
	}

	bool IsValid(string s)
	{
		if (s[0] == '-')
		{
			s.erase(s.begin());
		}
		size_t dot = s.find('.');
		string s1(s);
		string s2;
		if (dot != string::npos)
		{
			s1 = s.substr(0, dot);
			s2 = s.substr(dot + 1);
			if (s2.length() > 2)
			{
				return false;
			}
		}
		if (!ValidChar(s1) || !ValidChar(s2))
		{
			return false;
		}
		float f = stof(s);
		if (f > 1000)
		{
			return false;
		}
		return true;
	}

	void main(void)
	{
		int n;
		cin >> n;
		vector<float> vNumbers;
		for (int i = 0; i < n; ++i)
		{
			string s;
			cin >> s;
			if (!IsValid(s))
			{
				printf("ERROR: %s is not a legal number\n", s.c_str());
				continue;
			}
			float f = stof(s);
			vNumbers.push_back(f);
		}
		if (vNumbers.empty())
		{
			cout << "The average of 0 numbers is Undefined" << endl;
			return;
		}
		float sum = 0;
		for (auto f : vNumbers)
		{
			sum += f;
		}
		int nLen = (int)vNumbers.size();
		sum /= nLen;
		printf("The average of %d numbers is %.2f\n", nLen, sum);
	}
}

// rename this to main int PAT
int A1108Func(void)
{
	nsA1108A::main();
	return 0;
}


void A1108(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1108Func();
	cout << endl;
}

void A1108(void)
{
	A1108("data\\A1108-1.txt"); // 
	A1108("data\\A1108-2.txt"); // 
}

