/*
1146. Topological Order (25)
200 ms
65536 kB

This is a problem given in the Graduate Entrance Exam in 2018: 
Which of the following is NOT a topological order obtained from the given directed graph? 
Now you are supposed to write a program to test each of the options.

Input Specification:

Each input file contains one test case. 
For each case, the first line gives two positive integers 
N (<= 1,000), the number of vertices in the graph, and 
M (<= 10,000), the number of directed edges.
Then M lines follow, each gives the start and the end vertices of an edge. 
The vertices are numbered from 1 to N. 
After the graph, there is another positive integer K (<= 100). 
Then K lines of query follow, each gives a permutation of all the vertices. 
All the numbers in a line are separated by a space.

Output Specification:

Print in a line all the indices of queries which correspond to "NOT a topological order".
The indices start from zero. 
All the numbers are separated by a space, 
and there must no extra space at the beginning or the end of the line. 
It is graranteed that there is at least one answer.

Sample Input:
6 8
1 2
1 3
5 2
5 4
2 3
2 6
3 4
6 4
5
1 5 2 3 6 4
5 1 2 6 3 4
5 1 2 3 6 4
5 2 1 6 3 4
1 2 3 4 5 6
Sample Output:
3 4
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


/*
00:00
for (auto v : uAdj) : id[u] <= id[v]
20m pass
*/

namespace nsA1146A
{
	void main(void)
	{
		int n, m, u, v;
		scanf("%d %d", &n, &m);
		vector<vector<int>> vvAdj(n + 1);
		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			if (u == v) { throw 0; }
			vvAdj[u].push_back(v);
		}
		int k, d;
		scanf("%d", &k);
		vector<int> vResult;
		vector<int> vIndex(n + 1);
		for (int i = 0; i < k; ++i)
		{
			vector<int> vData(n);
			for (int j = 0; j < n; ++j)
			{
				scanf("%d", &d);
				vData[j] = d;
				vIndex[d] = j;
			}
			bool done = false;
			for (int j = 0; j < n; ++j)
			{
				if (done) { break; }
				int u = vData[j];
				for (auto v : vvAdj[u])
				{
					if (vIndex[v] < vIndex[u])
					{
						vResult.push_back(i);
						done = true;
						break;
					}
				}
			}
		}
		cout << vResult.front();
		for (size_t i = 1; i < vResult.size(); ++i)
		{
			cout << " " << vResult[i];
		}
		cout << endl;
	}
}

// rename this to main int PAT
int A1146Func(void)
{
	nsA1146A::main();
	return 0;
}


void A1146(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1146Func();
	cout << endl;
}

void A1146(void)
{
	A1146("data\\A1146-1.txt"); // 
}

