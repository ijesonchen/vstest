/*
1018. Subnumbers (35)
300 ms
65536 kB

Given a positive integer N, let us define a "subnumber" of N as a consecutive number of digits NOT starting with 0. 
For example if N = 1021, it has 7 subnumbers, namely, 1, 10, 102, 1021, 2, 21 and 1 (again). 
Here is your task: please calculate the sum of all the subnumbers of N. 
For 1021, the sum is 1+10+102+1021+2+21+1 = 1158. 
Since the result may be very large, output the answer modulo 1000000007 (10^9 + 7) please.

Input Specification:

Each input file contains one test case, which gives the integer N (0 < N < 10^100000) in a line.

Output Specification:

Print in a line the sum of all N's subnumbers (modulo 1000000007).

Sample Input:
1234567890123456789
Sample Output:
332876913

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

/*
sln1:
	1. 穷举（TLE）
	2. vector<int64_t> 存储整形，每单元10^18（单独实现余数算法）
ref：
	http://blog.csdn.net/baidu_37550206/article/details/79448325
	找规律
*/

namespace T1018A
{

}

// rename this to main int PAT
int T1018Func(void)
{
	return 0;
}


void T1018(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1018Func();
	cout << endl;
}

void T1018(void)
{
	T1018("data\\T1018-1.txt"); // 
}

