/*
1004. To Buy or Not to Buy - Hard Version (35)

Eva would like to make a string of beads with her favorite colors 
so she went to a small shop to buy some beads. 
There were many colorful strings of beads. 
However the owner of the shop would only sell the strings in whole pieces. 
Hence in some cases Eva might have to buy several strings to get all the beads she needs. 
With a hundred strings in the shop, Eva needs your help to tell her 
whether or not she can get all the beads she needs with the least number of extra beads she has to pay for.

For the sake of simplicity, let's use the characters in the ranges [0-9], [a-z], and [A-Z] to represent the colors. 
In sample 1, buying the 2nd and the last two strings is the best way since there are only 3 extra beads. 
In sample 2, buying all the three strings won't help since there are three "R" beads missing.

Input Specification:

Each input file contains one test case. 
Each case first gives in a line the string that Eva wants. 
Then a positive integer N (<=100) is given in the next line, 
followed by N lines of strings that belong to the shop. All the strings contain no more than 1000 beads.

Output Specification:

For each test case, print your answer in one line. 
If the answer is "Yes", then also output the least number of extra beads Eva has to buy; 
or if the answer is "No", then also output the number of beads missing from all the strings. 
There must be exactly 1 space between the answer and the number.

Sample Input 1:
RYg5
8
gY5Ybf
8R5
12346789
gRg8h
5Y37
pRgYgbR52
8Y
8g
Sample Output 1:
Yes 3

Sample Input 2:
YrRR8RRrY
3
ppRGrrYB225
8ppGrrB25
Zd6KrY
Sample Output 1:
No 3

*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
14:20
全排列搜索
o(n!)

15:20 放弃。全排列算法不熟悉

*/
namespace nsT1004A
{
	const int TOTALBEADS = 52;
	const int MAXRESULT = 10000000;
	char Index(char ch)
	{
		// 0-9,a-z,A-Z
		if (ch >= '0' && ch <= '9')
		{
			return ch - '0';
		}
		if (ch >= 'a' && ch <= 'z')
		{
			return ch - 'a' + 10;
		}
		if (ch >= 'A' && ch <= 'Z')
		{
			return ch - 'A' + 36;
		}
		throw 0;
	}

	struct String
	{
		char data[TOTALBEADS] = {0};
		
		String(const string& str)
		{
			for (auto ch : str)
			{
				++data[Index(ch)];
			}
		}

		String(const String& s)
		{
			memcpy(data, s.data, TOTALBEADS * sizeof(char));
		}

		bool Remove(const String& s)
		{
			bool done = true;
			for (int i = 0; i < TOTALBEADS; ++i)
			{
				if (data[i] && data[i] <= s.data[i])
				{
					data[i] = 0;
				}
				else
				{
					data[i] -= s.data[i];
					done = false;
				}
			}
			return done;
		}

		int Count(void)
		{
			int cnt = 0;
			for (int i = 0; i < TOTALBEADS; ++i)
				{ cnt += data[i]; }
			return cnt;
		}
	};

	vector<String*> vResult;
	int nResult = MAXRESULT;
	int nRest = MAXRESULT;

	// input data
	vector<String*> vpData;
	int nTotal = 0;

	void Search(String strRest, const int start)
	{
		if (start >= MAXRESULT - 1)
		{
			// 减枝
			return;
		}
		if (start == nTotal - 1)
		{
			// no result
			int cnt = strRest.Count();
			if (cnt < nRest)
			{
				nRest = cnt;
			}
			return;
		}
		if (strRest.Remove(*vpData[start]))
		{
			// found
			if (start < nResult)
			{
				nResult = start;
			}
			return;
		}

		for (int i = start + 1; i < nTotal; ++i)
		{
			std::swap(vpData[start], vpData[i]);
			Search(strRest, i);
			std::swap(vpData[start], vpData[i]);
		}
	}

	void main(void)
	{
		string str;
		cin >> str;
		String target(str);
		vector<String> vData;
		cin >> nTotal;
		for (int i = 0; i < nTotal; ++i)
		{
			cin >> str;
			vData.push_back(str);
		}
		for (auto& s : vData)
		{
			vpData.push_back(&s);
		}
	}
}

namespace nsPermut
{
	string s("asdf");
	int nTotal = 4;

	void Search(int start)
	{
		if (start == nTotal - 1)
		{
			cout << endl;
			return;
		}


		cout << s[start];

		for (int i = start + 1; i < nTotal; ++i)
		{
			Search(i);
			swap(s[start], s[i]);
		}
	}

	void main(void)
	{
		Search(0);
	}

}

// rename this to main int PAT
int T1004Func(void)
{
	nsPermut::main();
	return 0;
}


void T1004(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1004Func();
	cout << endl;
}

void T1004(void)
{
	T1004("data\\T1004-1.txt"); // 
}

