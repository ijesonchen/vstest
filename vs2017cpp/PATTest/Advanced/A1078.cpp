/*
1078. Hashing (25)
100 ms
65536 kB



The task of this problem is simple: insert a sequence of distinct positive integers into a hash table,
and output the positions of the input numbers. 
The hash function is defined to be "H(key) = key % TSize" 
where TSize is the maximum size of the hash table. 
Quadratic probing (with positive increments only) is used to solve the collisions.

Note that the table size is better to be prime. 
If the maximum size given by the user is not prime, 
you must re-define the table size to be the smallest prime number which is larger than the size given by the user.

Input Specification:

Each input file contains one test case. 
For each case, the first line contains two positive numbers: 
MSize (<=10^4) and N (<=MSize) which are the user-defined table size and the number of input numbers, respectively. 
Then N distinct positive integers are given in the next line. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print the corresponding positions (index starts from 0) of the input numbers in one line. 
All the numbers in a line are separated by a space, and there must be no extra space at the end of the line. 
In case it is impossible to insert the number, print "-" instead.

Sample Input:
4 4
10 6 4 15
Sample Output:
0 1 4 -
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

/*
19:15
哈希表 k非负，不重复
H=K%size，size取最近的素数(10^4)
冲突：平方搜索
19:45 20/25 wa3
PT3 22ms，数据量较大
调式：取最近素数应该没问题
19:50 放弃
*/

namespace nsA1078A
{
	bool IsPrime(int n)
	{
		if (n<=1)
		{
			return false;
		}
		if (n==2)
		{
			return true;
		}
		if ((n&1)==0)
		{
			return false;
		}
		int k = (int)sqrt(n) + 1;
		for (int i = 2; i <= k; ++i)
		{
			if (n/i*i==n)
			{
				return false;
			}
		}
		return true;
	}
	int NextPrim(int n)
	{
		while (!IsPrime(n))
		{
			++n;
		}
		return n;
	}

	vector<int> vHash;
	int nSize;
	bool bFirst;
	
	void Hash(int n)
	{
		int h = n % nSize;
		if (h<2)
		{
			if (vHash[h])
			{
				cout << "-";
			}
			else
			{
				cout << h;
				vHash[h] = n;
			}
			return;
		}
		for (int i = h; i < nSize; i*=i)
		{
			if (!vHash[i])
			{
				cout << i;
				vHash[i] = n;
				return;
			}
		}
		cout << "-";
	}

	void main(void)
	{
		int m, n, k;
		cin >> m >> n;
		nSize = NextPrim(m);
		vHash.assign(nSize, 0);
		bFirst = true;
		for (int i = 0; i < n; ++i)
		{
			cin >> k;
			if (bFirst)
			{
				bFirst = false;
			}
			else
			{
				cout << " ";
			}
			Hash(k);
		}
		cout << endl;
	}
}

// rename this to main int PAT
int A1078Func(void)
{
	nsA1078A::main();
	return 0;
}


void A1078(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1078Func();
	cout << endl;
}

void A1078(void)
{
//	A1078("data\\A1078-1.txt"); // 
//	A1078("data\\A1078-2.txt"); // 
	A1078("data\\A1078-3.txt"); // 
}

