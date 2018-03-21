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

10:00 继续全排列搜索算法
注意理解题意
应该用动态规划减少复杂度
11:00 29/35 PT2,6 TLE

bug-fix-1: 30/35 pt2 TLE


ref改进：
1. 读取时确定是否有需要的beed	
	剔除无用信息（不需要的bead只记数量，需要的bead记录每个color的数量）
2. 不要在62维数组上搜索，只要记录所需要的几个字母即可（用map或者数组映射）
3. 使用DFS搜索（如何实现？）
http://blog.csdn.net/zorelemn/article/details/50152597
http://blog.csdn.net/jtjy568805874/article/details/50759483
https://mephis.me/2017/10/21/to_buy_not_not_buy/


*/
namespace nsT1004A
{
	const int TOTALBEADS = 62;
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
		return 0;
	}

	struct Beads
	{
		vector<int> data;
		int total = 0;
		string s;
		
		Beads(const string& str): data(TOTALBEADS), s(str)
		{
			for (auto ch : str)
			{
				auto i = Index(ch);
				++data[i];
			}
			total = (int)str.length();
		}

		int Remove(const Beads& b)
		{
			int rest = b.total - total;
			for (int i = 0; i < TOTALBEADS; ++i)
			{
				if (data[i])
				{
					if (data[i] <= b.data[i])
					{
						total -= data[i];
						data[i] = 0;
					}
					else
					{
						total -= b.data[i];
						data[i] -= b.data[i];
					}
				}
			}

			if (total < 0)
			{
				throw 0;
			}

			for (auto ch : b.s)
			{
				auto it = s.find(ch);
				if (it != s.npos)
				{
					s.erase(it, 1);
				}
			}
			
			return rest + total;
		}

		int Count(void)
		{
			return total;
		}
	};

	// input data
	vector<Beads*> vpData;
	int nBeads = 0;

	int nResult = MAXRESULT;
	int nRest = 0;


	void Search(Beads& beads, const int start, int rest)
	{
		// bug-fix-1 start >= nResult ->  
		if (nRest || rest >= nResult)
		{
			// 减枝: 全搜完有剩余 或者 已经有更少的选择
			return;
		}
		if (start == nBeads)
		{
			// no result
			nRest = beads.Count();
			return;
		}

		for (int i = start; i < nBeads; ++i)
		{
			std::swap(vpData[start], vpData[i]);
			Beads nextBead(beads);
			auto pNext = vpData[start];
			int nextRest = nextBead.Remove(*pNext) + rest;
			if (!nextBead.total)
			{
				// found
				if (nextRest < nResult)
				{
					nResult = nextRest;
				}
			}
			Search(nextBead, start + 1, nextRest);
			std::swap(vpData[start], vpData[i]);
		}
	}

	void main(void)
	{
		vpData.clear();
		nResult = MAXRESULT;
		nRest = 0;
		
		string str;
		cin >> str;
		Beads target(str);
		vector<Beads> vData;
		cin >> nBeads;
		for (int i = 0; i < nBeads; ++i)
		{
			cin >> str;
			vData.push_back(str);
		}
		for (auto& s : vData)
		{
			vpData.push_back(&s);
		}
		Search(target, 0, 0);
		if (nRest)
		{
			cout << "No " << nRest << endl;
		}
		else
		{
			cout << "Yes " << nResult << endl;
		}
	}
}

// see perm2, permStl
namespace nsPermutation
{
	string str("123");
	int nTotal = (int)str.length();
	// wrong, to perm1
	void Perm(string s, int start)
	{
		if (start >= nTotal - 1) // X stop too early
		{
			cout << s << endl;
			return;
		}

		// X i from start
		for (int i = start + 1; i < nTotal; ++i)
		{
			swap(s[start], s[i]);
			Perm(s, i+1); // X: next is start + 1
			swap(s[start], s[i]);
		}
	}
	// wrong, to perm11
	void Perm1(int start)
	{
		if (start == nTotal)
		{
			cout << str << endl;
			return;
		}

		for (int i = start; i < nTotal; ++i)
		{
			swap(str[start], str[i]);
			Perm1(i + 1); // X: next from start + 1
			swap(str[start], str[i]);
		}
	}
	// pass
	void Perm11(int start)
	{
		if (start == nTotal)
		{
			cout << str << endl;
			return;
		}
		for (int i = start; i < nTotal; ++i)
		{
			swap(str[start], str[i]);
			Perm11(start + 1);
			swap(str[start], str[i]);
		}
	}

	// pass. ref to PermRef
	void Perm2(int start)
	{
		if (start == nTotal)
		{
			cout << str << endl;
			return;
		}
		for (int i = start; i < nTotal; ++i)
		{
			swap(str[start], str[i]);
			Perm2(start + 1);
			swap(str[start], str[i]);
		}
	}

	void PermStl(string s)
	{
		sort(s.begin(), s.end());
		do
		{
			cout << s << endl;
		} while (next_permutation(s.begin(), s.end()));
	}


	void main(void)
	{
		
//		Perm(str, 0);
//		Perm1(0);
//		Perm2(0);
//		Perm11(0);
		PermStl(str);
	}

}

namespace nsPermRef
{
	int nCount = 0;
	int nTotal = 0;

	void Permutation(char* pStr, char* pBegin)
	{
		if (*pBegin == '\0')
		{
			++nCount;
			printf("%s\n", pStr);
			return;
		}

		for (char* pCh = pBegin; *pCh != '\0'; ++pCh)
		{
			swap(*pCh, *pBegin);
			Permutation(pStr, pBegin + 1);
			swap(*pCh, *pBegin);
		}
	}

	void Permutation2(char* p, int start)
	{
		if (*(p+start) == '\0')
		{
			++nCount;
			printf("%s\n", p);
			return;
		}

		for (char* pCh = p + start; *pCh != '\0'; ++pCh)
		{
			swap(*pCh, *(p + start));
			Permutation2(p, start + 1);
			swap(*pCh, *(p + start));
		}
	}

	void Permutation3(char* p, int start)
	{
		if (start == nTotal)
//		if (p[start] == 0)
		{
			++nCount;
			printf("%s\n", p);
			return;
		}
		for (int i = start; i < nTotal; ++i)
		{
			swap(p[start], p[i]);
			Permutation3(p, start + 1);
			swap(p[start], p[i]);
		}
	}

	int factor(int n)
	{
		int sum = 1;
		for (int i = 1; i <= n; ++i)
		{
			sum *= i;
		}
		return sum;
	}

	void main(void)
	{
		nCount = 0;
		string s("123");
		nTotal = (int)s.length();
		char* p = (char*)s.c_str();
//		Permutation(p, p);
//		Permutation2(p, 0);
		Permutation3(p, 0);
		auto cnt = factor((int)s.length());
		if (nCount != cnt)
		{
			throw 0;
		}

	}
}

// rename this to main int PAT
int T1004Func(void)
{
	nsT1004A::main();
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
	T1004("data\\T1004-2.txt"); // 
}

