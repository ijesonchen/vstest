/*
1005. Programming Pattern (35)

Programmers often have a preference among program constructs. 
For example, some may prefer "if(0==a)", while others may prefer "if(!a)". 
Analyzing such patterns can help to narrow down a programmer's identity, 
which is useful for detecting plagiarism.

Now given some text sampled from someone's program, 
can you find the person's most commonly used pattern of a specific length?

Input Specification:

Each input file contains one test case.
For each case, there is one line consisting of the pattern length N (1<=N<=1048576), 
followed by one line no less than N and no more than 1048576 characters in length, terminated by a carriage return '\n'. 
The entire input is case sensitive.

Output Specification:

For each test case, print in one line the length-N substring that occurs most frequently in the input, 
followed by a space and the number of times it has occurred in the input. 
If there are multiple such substrings, print the lexicographically smallest one.

Whitespace characters in the input should be printed as they are. 
Also note that there may be multiple occurrences of the same substring overlapping each other.

Sample Input 1:
4
//A can can can a can.
Sample Output 1:
can 4
Sample Input 2:
3
int a=~~~~~~~~~~~~~~~~~~~~~0;
Sample Output 2:
~~~ 19
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
15:20
找到下一行中长度为N的、重复最多的模式
暴力循环搜索

15:45 24/35 PT3,4 TLE PT5 WA

bug-fix: N和字串长度相等
15:50 28/35 pt3,4 TLE 
*/

namespace nsT1005A
{
	const int MAXCHAR = 1048576;

	int CountPattern(const string& data, const string& sub)
	{
		int cnt = 0;
		int sublen = (int)sub.length();
		for (int i = 0; i <= data.length() - sublen; ++i)
		{
			int n = data.find(sub, i);
			if (n < 0)
			{
				break;
			}
			i = n;
			++cnt;
		}
		return cnt;
	}

	void main(void)
	{
		int nSub = 0;
		cin >> nSub;
		string data;
		getline(cin, data);
		getline(cin, data);

		int maxPattern = 0;
		vector<string> vPattern;
		string strPattern;

		int nData = data.length();

		for (int iStart = 0; iStart <= nData - nSub; ++iStart)
		{
			string sub = data.substr(iStart, nSub);
			if (find(vPattern.begin(), vPattern.end(), sub) != vPattern.end())
			{
				continue;
			}
			int n = CountPattern(data, sub);
			if (n < maxPattern)
			{
				continue;
			}
			if (n > maxPattern)
			{
				maxPattern = n;
				vPattern.clear();
				vPattern.push_back(sub);
			}
			else
			{
				vPattern.push_back(sub);
			}
		}
		if (vPattern.empty())
		{
			throw 0;
		}
		cout << *min_element(vPattern.begin(), vPattern.end()) << " " << maxPattern << endl;
	}
}

// rename this to main int PAT
int T1005Func(void)
{
	nsT1005A::main();
	return 0;
}


void T1005(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1005Func();
	cout << endl;
}

void T1005(void)
{
	T1005("data\\T1005-1.txt"); // 
	T1005("data\\T1005-2.txt"); // 
	T1005("data\\T1005-3.txt"); // 
}

