/*
1010. Radix (25)
cost: 15:10
sln1:
	n1, r
	n2, ?
	n2, [rmin, rmax] -> n3,r  n3?n1  binsearch

	void div(x,y,&a,&b): x/y=a...b
	dst RedixConv(src, r1, r2): src,r1 -> dst, r2
sln2:
	使用一个vector<int>作为中间结果进行比较

Given a pair of positive integers, for example, 6 
and 110, can this equation 6 = 110 be true? The answer 
is "yes", if 6 is a decimal number and 110 is a 
binary number.

Now for any pair of positive integers N1 and N2, your 
task is to find the radix of one number while that of 
the other is given.

Input Specification:

Each input file contains one test case. Each case 
occupies a line which contains 4 positive integers:
N1 N2 tag radix
Here N1 and N2 each has no more than 10 digits. A digit
is less than its radix and is chosen from the set 
{0-9, a-z} where 0-9 represent the decimal numbers 0-9,
and a-z represent the decimal numbers 10-35. The last
number "radix" is the radix of N1 if "tag" is 1, or of 
N2 if "tag" is 2.

Output Specification:

For each test case, print in one line the radix of the 
other number so that the equation N1 = N2 is true. If 
the equation is impossible, print "Impossible". If the
solution is not unique, output the smallest possible radix.

Sample Input 1:
6 110 1 10
Sample Output 1:
2
Sample Input 2:
1 ab 1 2
Sample Output 2:
Impossible
*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1010Func(void)
{
	return 0;
}


void A1010(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1010Func();
	cout << endl;
}

void A1010(void)
{
	// '0' 0x30
	// '1' 0x31
	// 'A' 0x41
	// 'a' 0x61
	string s = "123";
	char* p = nullptr;
	int x = strtol(s.c_str(), &p, 8);
//	A1010("data\\A1010-1.txt"); // 
}

