/*
1108. Finding Average (20)

cost: 14:25

总结：
	1. 仔细读题，题目基本不会有废话，一定要注意结果输出要求。（ref-fix-1）
	2. 考虑简单的数据处理方式。例如sscanf获取输入
	3. 注意printf格式化字串（nsA1108RefRewrite）

nsA1108A：
	14:25 14:45 18/20 PT2 WA
	可能错误：误差累计
	改进：整数小数分开累加计算

	题解：ref-fix-1
	仔细读题：只有一个时用number，多个时numbers
	pass

nsA1108B
	17:25
	改进：不用小数
	17:40 15/20 pt2 异常 pt3 WA

	30min ref
	PT2异常：代码二分返回定位：stoi超出范围
	PT3WA: printf： n number/numbers

nsA1108RefRewrite:
	char[50] a,b
	cin >> a；sscanf: a %f -> f；sprintf: f %.2f -> b
	比较 a,b是否相同(strlen(a))
	可以正确处理: a: 8.5/8.50 , b:8.50
	注意：采用char[]而非string，可以方便后续读取，比较操作
	8.5: %f 8.500000 %.2f 8.50 %g 8.5

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
#include <cstring>

using namespace std;

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
		// ref-fix-1
		string s = (nLen == 1) ? "number" : "numbers";
		printf("The average of %d %s is %.2f\n", nLen, s.c_str(), sum);
	}
}


namespace nsA1108B
{
	vector<int> v1;
	vector<int> v2;
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
		bool neg = false;
		if (s[0] == '-')
		{
			neg = true;
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
		int n1 = 0;
		// bug-fix: stoi out of range
		if (s1.length() > 4)
		{
			return false;
		}
		if (s1.length())
		{
			n1 = stoi(s1);
		}
		int n2 = 0;
		if (s2.length() == 1)
		{
			n2 = 10 * stoi(s2);
		}
		else if (s2.length() == 2)
		{
			n2 = stoi(s2);
		}
		if (n1 > 1000 ||
			(n1 == 1000 && n2))
		{
			return false;
		}
		if (neg)
		{
			n1 = -n1;
			n2 = -n2;
		}
		v1.push_back(n1);
		v2.push_back(n2);
		return true;
	}

	void main(void)
	{
		v1.clear();
		v2.clear();
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			string s;
			cin >> s;
			if (!IsValid(s))
			{
				printf("ERROR: %s is not a legal number\n", s.c_str());
				continue;
			}
		}
		if (v1.empty())
		{
			cout << "The average of 0 numbers is Undefined" << endl;
			return;
		}
		int sum1 = 0;
		int sum2 = 0;
		for (size_t i = 0; i < v1.size(); ++i)
		{
			sum1 += v1[i];
		}
		for (size_t i = 0; i < v2.size(); ++i)
		{
			sum2 += v2[i];
		}
		sum1 += sum2 / 100;
		sum2 %= 100;
		float f = sum1 + float(sum2) / 100;
		int nLen = v1.size();
		f /= nLen;
		string s = (nLen == 1) ? "number" : "numbers";
		printf("The average of %d %s is %.2f\n", nLen, s.c_str(), f);
	}
}

// ref: https://www.liuchuo.net/archives/2955
namespace nsA1108RefRewrite
{
	
	void main(void)
	{
		int n;
		char a[50], b[50];
		vector<float> vNumbers;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> a;
			float f;
			sscanf(a, "%f", &f);
			sprintf(b, "%.2f", f);
			bool bad = false;
			for (int i = 0; i < strlen(a); ++i)
			{
				if (a[i] != b[i])
				{
					bad = true;
					break;
				}
			}
			if (bad || f > 1000 || f < -1000)
			{
				printf("ERROR: %s is not a legal number\n", a);
				continue;
			}
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
		// ref-fix-1
		string s = (nLen == 1) ? "number" : "numbers";
		printf("The average of %d %s is %.2f\n", nLen, s.c_str(), sum);
	}
}

// rename this to main int PAT
int A1108Func(void)
{
	nsA1108RefRewrite::main();
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

