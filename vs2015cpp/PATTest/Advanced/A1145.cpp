/*
1145. Hashing - Average Search Time (25)
200 ms
65536 kB

The task of this problem is simple: insert a sequence of distinct positive integers into a hash table first.
Then try to find another sequence of integer keys from the table and output the average search time 
(the number of comparisons made to find whether or not the key is in the table). 
The hash function is defined to be "H(key) = key % TSize" where TSize is the maximum size of the hash table.
Quadratic probing (with positive increments only) is used to solve the collisions.

Note that the table size is better to be prime. 
If the maximum size given by the user is not prime, 
you must re-define the table size to be the smallest prime number 
which is larger than the size given by the user.

Input Specification:

Each input file contains one test case. 
For each case, the first line contains two positive numbers: MSize, N, and M, 
which are the user-defined table size, 
the number of input numbers, 
and the number of keys to be found, respectively. 
All the three numbers are no more than 10^4. 
Then N distinct positive integers are given in the next line. 
All the numbers in a line are separated by a space and are no more than 10^5.

Output Specification:

For each test case, in case it is impossible to insert some number, 
print in a line "X cannot be inserted." where X is the input number. 
Finally print in a line the average search time for all the M keys,
accurate up to 1 decimal place.

Sample Input:
4 5 4
10 6 4 15 11
11 4 15 2
Sample Output:
15 cannot be inserted.
2.8
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


/*
00:30
bug-fix-1 pass
30m pass

Quadratic probing:
i: [0, size] (取0是为了合并不冲突的情况）
h = (k + i*i) % size
*/

namespace nsA1145A
{
	bool IsPrime(int n)
	{
		if (n <= 1) { return false; }
		if (n == 2 || n == 3) { return true; }
		int k = (int)sqrt(n) + 1;
		for (int i = 2; i <= k; ++i)
		{
			if (n / i*i == n) { return false; }
		}
		return true;
	}

	int NextPrime(int i)
	{
		while (!IsPrime(i)) { ++i; }
		return i;
	}

	void main(void)
	{
		int msize, n, m, d;
		scanf("%d %d %d", &msize, &n, &m);
		msize = NextPrime(msize);
		vector<int> vHash(msize);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			bool found = false;
			// bug-fix-1 j < msize -> j <= msize
			for (int j = 0; j <= msize; ++j)
			{
				int h = (d + j*j) % msize;
				if (!vHash[h])
				{
					found = true;
					vHash[h] = d;
					break;
				}
			}
			if (!found)
			{
				printf("%d cannot be inserted.\n", d);
			}
		}
		int nCheck = 0;
		for (int i = 0; i < m; ++i)
		{
			scanf("%d", &d);
			// bug-fix-1 j < msize -> j <= msize
			for (int j = 0; j <= msize; ++j)
			{
				int h = (d + j*j) % msize;
				++nCheck;
				if (!vHash[h] || vHash[h] == d)
				{
					break;
				}
			}
		}
		printf("%.1lf\n", double(nCheck) / m);
	}
}

// rename this to main int PAT
int A1145Func(void)
{
	nsA1145A::main();
	return 0;
}


void A1145(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1145Func();
	cout << endl;
}

void A1145(void)
{
	A1145("data\\A1145-1.txt"); // 
}
