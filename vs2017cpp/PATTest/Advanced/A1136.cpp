/*
1136. A Delayed Palindrome (20)
tip：
大整数加减法
	1. 不考虑效率，可以对齐后逐位加减（带进位/借位）
	2. 考虑效率，分段转换为整数加减（方法1的扩展）
回文：
	1. 直接反转判断相等（效率低）
	2. 折半比对
这个题目有思路后，大约半小时AC（思考10分钟，代码20分钟）

Consider a positive integer N written in standard notation 
with k+1 digits ai as ak...a1a0 with 0 <= ai < 10 for all i 
and ak > 0. Then N is palindromic if and only if ai = ak-i 
for all i. Zero is written 0 and is also palindromic by definition.

Non-palindromic numbers can be paired with palindromic ones 
via a series of operations. First, the non-palindromic number 
is reversed and the result is added to the original number. 
If the result is not a palindromic number, this is repeated 
until it gives a palindromic number. Such number is called a 
delayed palindrome. (Quoted from 
https://en.wikipedia.org/wiki/Palindromic_number)

Given any positive integer, you are supposed to find its paired 
palindromic number.

Input Specification:

Each input file contains one test case which gives a positive 
integer no more than 1000 digits.

Output Specification:

For each test case, print line by line the process of finding 
the palindromic number. The format of each line is the following:

A + B = C
where A is the original number, B is the reversed A, and C is 
their sum. A starts being the input number, and this process 
ends until C becomes a palindromic number -- in this case we 
print in the last line "C is a palindromic number."; or if a 
palindromic number cannot be found in 10 iterations, print 
"Not found in 10 iterations." instead.

Sample Input 1:
97152
Sample Output 1:
97152 + 25179 = 122331
122331 + 133221 = 255552
255552 is a palindromic number.

Sample Input 2:
196
Sample Output 2:
196 + 691 = 887
887 + 788 = 1675
1675 + 5761 = 7436
7436 + 6347 = 13783
13783 + 38731 = 52514
52514 + 41525 = 94039
94039 + 93049 = 187088
187088 + 880781 = 1067869
1067869 + 9687601 = 10755470
10755470 + 07455701 = 18211171
Not found in 10 iterations.
*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

string A1136Sum(const string& s1, const string& s2)
{
	string sum(s1);
	bool carry = false;
	for (int i = (int)s1.length() - 1; i >= 0; --i)
	{
		int n = s1[i] + s2[i] - 2 * '0' + carry;
		if (n >= 10)
		{
			n -= 10;
			carry = true;
		}
		else
		{
			carry = false;
		}
		sum[i] = '0' + n;
	}
	if (carry)
	{
		sum.insert(0, "1");
	}
	return sum;
}

string A1136Reverse(const std::string s1)
{
	string s2(s1);
	int len = (int)s1.length();
	for (int i = 0; i < len; ++i)
	{
		s2[i] = s1[len - 1 - i];
	}
	return s2;
}

int A1136Func(void)
{
	int loop = 10;
	string s0;
	cin >> s0;
	if (A1136Reverse(s0) == s0)
	{
		cout << s0 << " is a palindromic number." << endl;
		return 0;
	}

	string s1 = s0;
	string s2;
	string sum;
	for (int i = 0; i < loop; ++i)
	{
		s2 = A1136Reverse(s1);
		sum = A1136Sum(s1, s2);
		cout << s1 << " + " << s2 << " = " << sum << endl;
		if (sum == A1136Reverse(sum))
		{
			cout << sum << " is a palindromic number." << endl;
			return 0;
		}
		s1 = sum;
	}
	cout << "Not found in 10 iterations." << endl;

	return 0;
}


void A1136(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1136Func();
	cout << endl;
}

void A1136(void)
{
	A1136("data\\A1136-1.TXT"); // 255552
	A1136("data\\A1136-2.TXT"); // Not found
	A1136("data\\A1136-3.TXT"); // Not found
	A1136("data\\A1136-4.TXT"); // Not found
}

