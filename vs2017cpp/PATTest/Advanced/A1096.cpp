/*
1096. Consecutive Factors (20)
400 ms
65536 kB

Among all the factors of a positive integer N, there may exist several consecutive numbers. 
For example, 630 can be factored as 3*5*6*7, where 5, 6, and 7 are the three consecutive numbers. 
Now given any positive N, you are supposed to find the maximum number of consecutive factors, 
and list the smallest sequence of the consecutive factors.

Input Specification:

Each input file contains one test case, which gives the integer N (1<N<2^31).

Output Specification:

For each test case, print in the first line the maximum number of consecutive factors. 
Then in the second line, print the smallest sequence of the consecutive factors in the format "factor[1]*factor[2]*...*factor[k]", 
where the factors are listed in increasing order, and 1 is NOT included.

Sample Input:
630
Sample Output:
3
5*6*7

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

/*
14:35
int32_t 最大12!
1. 穷举
a,b,c,d
其中[a,b]最大2-11不连续, [c,d]最大2-12连续
consecutive factor matrix[c,d]:最多11*12/2=66个
NonConFac(a,b)：枚举[a,b]所有不连续序列，递归获取
求乘积
ConcFac(c,d):可以预处理得到[c,d]连续序列的积

2. 分解质因数
如何转换为代码？

15:15 放弃
*/
namespace nsA1096A
{
	
}

// rename this to main int PAT
int A1096Func(void)
{
	return 0;
}


void A1096(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1096Func();
	cout << endl;
}

void A1096(void)
{
	A1096("data\\A1096-1.txt"); // 
}

