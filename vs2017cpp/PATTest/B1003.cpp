#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
1003. 我要通过！(20)

得分；题目；错误点
17/20;4/6;1,5

解析：题目给出问题的递归形式
c1+c2+c3：P、T分隔为前中后三部分
c2：中间至少一个A；前后A数量相等（初始）
c3:中间每增加一个A，后面增加和前面相同数量的A
abc为前中后A的个数
递归：b!=0, a*b=c

alg1: x 和题意不同 
	中间为PAT或PAAT，前后只有A或空格

“答案正确”是自动判题系统给出的最令人欢喜的回复。本题属于PAT的“答案正确”大派送 —— 只要读入的字符串满足下列条件，系统就输出“答案正确”，否则输出“答案错误”。

得到“答案正确”的条件是：

1. 字符串中必须仅有P, A, T这三种字符，不可以包含其它字符；
2. 任意形如 xPATx 的字符串都可以获得“答案正确”，其中 x 或者是空字符串，或者是仅由字母 A 组成的字符串；
3. 如果 aPbTc 是正确的，那么 aPbATca 也是正确的，其中 a, b, c 均或者是空字符串，或者是仅由字母 A 组成的字符串。

现在就请你为PAT写一个自动裁判程序，判定哪些字符串是可以获得“答案正确”的。
输入格式： 每个测试输入包含1个测试用例。第1行给出一个自然数n (<10)，是需要检测的字符串个数。
接下来每个字符串占一行，字符串长度不超过100，且不包含空格。

输出格式：每个字符串的检测结果占一行，如果该字符串可以获得“答案正确”，则输出YES，否则输出NO。

输入样例：
8
PAT
PAAT
AAPATAA
AAPAATAAAA
xPATx
PT
Whatever
APAAATAA
输出样例：
YES
YES
YES
YES
NO
NO
NO
NO

时间限制
400 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
*/

using namespace std;

bool IsPassAlg1(string& s)
{
	// this is wrong
	size_t p = s.find('P');
	for (size_t i = 0; i < p; ++i)
	{
		if (s[i] != 'A')
		{
			return false;
		}
	}
	if (p == string::npos)
	{
		return false;
	}
	size_t k = s.length() - p;
	if (k >= 3 && s.substr(p, 3) == "PAT")
	{
		p += 3;
		for (size_t i = p; i < s.length(); ++i)
		{
			if (s[i] != 'A')
			{
				return false;
			}
		}
		return true;
	}
	if (k >= 4 && s.substr(p, 4) == "PAAT")
	{
		p += 4;
		for (size_t i = p; i < s.length(); ++i)
		{
			if (s[i] != 'A')
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool IsA(const string& s)
{
	return all_of(s.begin(), s.end(), [](char ch) { return ch == 'A'; });
}

bool IsPass(const string& s)
{
	auto n1 = s.find("P");
	auto n2 = s.find("T");
	if (n1 == string::npos || n2 == string::npos || n1 >= n2)
	{
		return false;
	}
	string s1;
	if (n1)
	{
		s1 = s.substr(0, n1);
	}
	auto s2 = s.substr(n1 + 1, n2 - n1 - 1);
	auto s3 = s.substr(n2 + 1, string::npos);
	if (s2.empty())
	{
		return false;
	}
	if (!IsA(s1) ||
		!IsA(s2) ||
		!IsA(s3))
	{
		return false;
	}
	if (s3.length() != s1.length() * s2.length())
	{
		return false;
	}
	return true;
}

void B1003(void)
{
	vector<string> v = {
		"PAT", // yes
		"PAAT",
		"AAPATAA",
		"AAPAATAAAA",
		"AAPAAATAAAAAA",
		"xPATx", // no 
		"PT",
		"Whatever",
		"APAAATAA",
		"TAP", // no 
	};

	for (auto& i : v)
	{
		auto b = IsPass(i);
		if (b)
		{
			cout << "Yes";
		}
		else
		{
			cout << "No";
		}
		cout << endl;
	}
}