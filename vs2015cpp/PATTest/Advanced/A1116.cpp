/*
1116. Come on! Let's C (20)
200 ms
65536 kB

"Let's C" is a popular and fun programming contest hosted by the College of Computer Science and Technology, Zhejiang University.
Since the idea of the contest is for fun, the award rules are funny as the following:

0. The Champion will receive a "Mystery Award" (such as a BIG collection of students' research papers...).
1. Those who ranked as a prime number will receive the best award -- the Minions (小黄人)!
2. Everyone else will receive chocolates.

Given the final ranklist and a sequence of contestant ID's, you are supposed to tell the corresponding awards.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (<=10000), 
the total number of contestants. 
Then N lines of the ranklist follow, each in order gives a contestant's ID (a 4-digit number). 
After the ranklist, there is a positive integer K followed by K query ID's.

Output Specification:

For each query, print in a line "ID: award" where the award is "Mystery Award", or "Minion", or "Chocolate". 
If the ID is not in the ranklist, print "Are you kidding?" instead. 
If the ID has been checked before, print "ID: Checked".

Sample Input:
6
1111
6666
8888
1234
5555
0001
6
8888
0001
1111
2222
8888
2222
Sample Output:
8888: Minion
0001: Chocolate
1111: Mystery Award
2222: Are you kidding?
8888: Checked
2222: Are you kidding?
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

/*
14:20 
n: [1,10000]
4-digi id
k: >0
query id

按照排序指定奖品：0，素数，其他
根据示例，rank 1-based

14:45 pass
*/

namespace nsA1116A
{
	bool IsPrim(int n)
	{
		if (n <= 1) { return false; }
		if (n == 2) { return true; }
		if ((n & 1) == 0) { return false; }
		int k = (int)sqrt(n) + 1;
		for (int i = 2; i <=k; ++i)
		{
			if (n / i * i == n) { return false; }
		}
		return true;
	}

	enum EAward
	{
		EAKID = 0,
		EAMYS = 1,
		EAMIN = 2,
		EACHO = 3,
	};



	void main(void)
	{
		const int MAXID = 10000;
		vector<int> vAward(MAXID);
		vector<bool> vVisit(MAXID);

		int n, id, k;
		cin >> n;
		cin >> id;
		vAward[id] = EAMYS;
		for (int i = 1; i < n; ++i)
		{
			cin >> id;
			// 0-based
			if (IsPrim(i+1))
			{
				vAward[id] = EAMIN;
			}
			else
			{
				vAward[id] = EACHO;
			}
		}
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> id;
			switch (vAward[id])
			{
			case EAKID:
				printf("%04d: Are you kidding?\n", id);
				break;
			case EAMYS:
				if (!vVisit[id])
				{
					vVisit[id] = true;
					printf("%04d: Mystery Award\n", id);
				}
				else
				{
					printf("%04d: Checked\n", id);
				}
				break;
			case EAMIN:
				if (!vVisit[id])
				{
					vVisit[id] = true;
					printf("%04d: Minion\n", id);
				}
				else
				{
					printf("%04d: Checked\n", id);
				}
				break;
			case EACHO:
				if (!vVisit[id])
				{
					vVisit[id] = true;
					printf("%04d: Chocolate\n", id);
				}
				else
				{
					printf("%04d: Checked\n", id);
				}
				break;
			default:
				throw 0;
				break;
			}
		}
	}
}

// rename this to main int PAT
int A1116Func(void)
{
	nsA1116A::main();
	return 0;
}


void A1116(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1116Func();
	cout << endl;
}

void A1116(void)
{
	A1116("data\\A1116-1.txt"); // 
}

