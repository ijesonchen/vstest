/*
1118. Birds in Forest (25)
150 ms
65536 kB

Some scientists took pictures of thousands of birds in a forest. 
Assume that all the birds appear in the same picture belong to the same tree. 
You are supposed to help the scientists to count the maximum number of trees in the forest, and 
for any pair of birds, tell if they are on the same tree.

Input Specification:

Each input file contains one test case. For each case, the first line contains 
a positive number N (<= 10^4) which is the number of pictures. 
Then N lines follow, each describes a picture in the format:
K B1 B2 ... BK
where K is the number of birds in this picture, and Bi's are the indices of birds. 
It is guaranteed that the birds in all the pictures are numbered continuously from 1 to some number that is no more than 10^4.

After the pictures there is a 
positive number Q (<= 10^4) which is the number of queries. 
Then Q lines follow, each contains the indices of two birds.

Output Specification:

For each test case, first output in a line the maximum possible number of trees and the number of birds. 
Then for each query, print in a line "Yes" if the two birds belong to the same tree, or "No" if not.

Sample Input:
4
3 10 1 2
2 3 4
4 1 5 7 8
3 9 6 4
2
10 5
3 7
Sample Output:
2 10
Yes
No

*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
15:50
union-find
1. cluster，max bird
2. test union-find

16：20 22/25 tle3

优化：union find时带路径长度
union时用新的group id
printf代替cout
16：25 PASS
*/

namespace nsA1118A
{
	const int MAXBIRD = 10001;

	int FindIndex(const vector<int>& v, int i)
	{
		while (v[i])
		{
			i = v[i];
		}
		return i;
	}

	void main(void)
	{
		vector<int> vBirdIndex(MAXBIRD);
		int maxBird = 0;

		int n, k, bird, q;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &k);
			if (!k) { continue; }
			scanf("%d", &bird);
			if (maxBird < bird) { maxBird = bird; }
			int bird0 = bird;
			int id0 = FindIndex(vBirdIndex, bird);
			for (int j = 1; j < k; ++j)
			{
				scanf("%d", &bird);
				if (maxBird < bird) { maxBird = bird; }
				int idj = FindIndex(vBirdIndex, bird);
				if (idj == bird)
				{
					// new bird
					vBirdIndex[bird] = id0;
				}
				else if (idj != id0)
				{
					// union
//					vBirdIndex[idj] = id0;
					// improve-1
					vBirdIndex[id0] = idj;
					id0 = idj;
				}
			}
		}
		int tree = 0;
		for (int i = 1; i <= maxBird; ++i)
		{
			if (!vBirdIndex[i])
			{
				++tree;
			}
		}
		printf("%d %d\n", tree, maxBird);

		scanf("%d", &q);
		int b1, b2;
		for (int i = 0; i < q; ++i)
		{
			scanf("%d %d", &b1, &b2);
			int id1 = FindIndex(vBirdIndex, b1);
			int id2 = FindIndex(vBirdIndex, b2);
			if (id1==id2)
			{
				printf("Yes\n");
			}
			else
			{
				printf("No\n");
			}
		}
	}
}

// rename this to main int PAT
int A1118Func(void)
{
	nsA1118A::main();
	return 0;
}


void A1118(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1118Func();
	cout << endl;
}

void A1118(void)
{
	A1118("data\\A1118-1.txt"); // 
}

