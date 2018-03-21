/*
1126. Eulerian Path (25)
300 ms
65536 kB

In graph theory, an Eulerian path is a path in a graph which visits every edge exactly once. 
Similarly, an Eulerian circuit is an Eulerian path which starts and ends on the same vertex. 
They were first discussed by Leonhard Euler while solving the famous Seven Bridges of Konigsberg problem in 1736. 
It has been proven that connected graphs with all vertices of even degree have an Eulerian circuit, 
and such graphs are called Eulerian.
If there are exactly two vertices of odd degree, all Eulerian paths start at one of them and end at the other. 
A graph that has an Eulerian path but not an Eulerian circuit is called semi-Eulerian. 
(Cited from https://en.wikipedia.org/wiki/Eulerian_path)

Given an undirected graph, you are supposed to tell if it is Eulerian, semi-Eulerian, or non-Eulerian.

Input Specification:

Each input file contains one test case. 
Each case starts with a line containing 2 numbers N (<= 500), and M, 
which are the total number of vertices, and the number of edges, respectively. 
Then M lines follow, each describes an edge by giving the two ends of the edge 
(the vertices are numbered from 1 to N).

Output Specification:

For each test case, first print in a line the degrees of the vertices in ascending order of their indices. 
Then in the next line print your conclusion about the graph -- either "Eulerian", "Semi-Eulerian", or "Non-Eulerian". 
Note that all the numbers in the first line must be separated by exactly 1 space, 
and there must be no extra space at the beginning or the end of the line.

Sample Input 1:
7 12
5 7
1 2
1 3
2 3
2 4
3 4
5 2
7 6
6 3
4 5
6 4
5 6
Sample Output 1:
2 4 4 4 4 4 2
Eulerian

Sample Input 2:
6 10
1 2
1 3
2 3
2 4
3 4
5 2
6 3
4 5
6 4
5 6
Sample Output 2:
2 4 4 4 3 3
Semi-Eulerian

Sample Input 3:
5 8
1 2
2 5
5 4
4 1
1 3
3 2
3 4
5 3
Sample Output 3:
3 3 4 3 3
Non-Eulerian
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

/*
15:50
degree of vertex
根据顶点的度判断图形
1-based

判定（proven）
connected, all even: Eulerian
only 2 odd: semi_Eulerian

先不考虑自环，重边
未判定连通
16:20 20/25 wa3

连通判定
16:30 pass
*/
namespace nsA1126A
{

	void main(void)
	{
		int n, m;
		cin >> n >> m;
		++n; // to 1-based
		vector<vector<int>> vvAdjs(n);
		vector<size_t> vDegree(n);
		int u, v;
		for (int i = 0; i < m; ++i)
		{
			cin >> u >> v;
			if (u==v) // 自环
			{
				throw 0;
			}
			// 重边
			auto& uAdj = vvAdjs[u];
			auto& vAdj = vvAdjs[v];
			if (find(uAdj.begin(), uAdj.end(), v) != uAdj.end() ||
				find(vAdj.begin(), vAdj.end(), u) != vAdj.end())
			{
				throw 0;
			}

			vvAdjs[u].push_back(v);
			vvAdjs[v].push_back(u);
		}
		int nOdd = 0;
		for (int i = 1; i < n; ++i)
		{
			vDegree[i] = vvAdjs[i].size();
			if (vDegree[i] & 1)
			{
				++nOdd;
			}
		}
		cout << vDegree[1]; 
		for (int i = 2; i < n; ++i)
		{
			cout << " " << vDegree[i];
		}
		cout << endl;

		// connected?
		vector<bool> vVisit(n);

		deque<int> dqNode;
		dqNode.push_back(1);
		vVisit[1] = true;
		int nVisit = 1;
		while (!dqNode.empty())
		{
			int u = dqNode.front();
			dqNode.pop_front();
			auto& uAdj = vvAdjs[u];
			for (auto v : uAdj)
			{
				if (!vVisit[v])
				{
					++nVisit;
					vVisit[v] = true;
					dqNode.push_back(v);
				}
			}
		}

		if (nVisit != n-1)
		{
			nOdd = -1;
		}

		
		if (nOdd == 0)
		{
			cout << "Eulerian" << endl;
		}
		else if (nOdd == 2)
		{
			cout << "Semi-Eulerian" << endl;
		}
		else
		{
			cout << "Non-Eulerian" << endl;
		}
	}
}
// rename this to main int PAT
int A1126Func(void)
{
	nsA1126A::main();
	return 0;
}


void A1126(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1126Func();
	cout << endl;
}

void A1126(void)
{
	A1126("data\\A1126-1.txt"); // 
	A1126("data\\A1126-2.txt"); // 
	A1126("data\\A1126-3.txt"); // 
}

