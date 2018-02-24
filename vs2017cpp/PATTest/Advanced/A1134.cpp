/*
1134. Vertex Cover (25)
cost: 10:15

总结：注意结果输出的大小写。

sln1: 记录边，顶点所在的边集。遍历
	25min pass

A vertex cover of a graph is a set of vertices such that 
each edge of the graph is incident to at least one vertex of the set. 
Now given a graph with several vertex sets, 
you are supposed to tell if each of them is a vertex cover or not.

Input Specification:

Each input file contains one test case. 
For each case, the first line gives two positive integers N and M (both no more than 104), 
being the total numbers of vertices and the edges, respectively. 
Then M lines follow, 
each describes an edge by giving the indices (from 0 to N-1) of the two ends of the edge.

After the graph, a positive integer K (<= 100) is given, which is the number of queries. 
Then K lines of queries follow, each in the format:

Nv v[1] v[2] ... v[Nv]

where Nv is the number of vertices in the set, and v[i]'s are the indices of the vertices.

Output Specification:

For each query, print in a line "Yes" if the set is a vertex cover, or "No" if not.

Sample Input:
10 11
8 7
6 8
4 5
8 4
8 1
1 2
1 4
9 8
9 1
1 0
2 4
5
4 0 3 8 4
6 6 1 7 5 4 9
3 1 8 4
2 2 8
7 9 8 7 6 5 4 2
Sample Output:
No
Yes
Yes
No
No
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

namespace nsA1134
{
	typedef map<int, set<int>> MapIntSet;

	struct Edge
	{
		int u = 0;
		int v = 0;

		Edge(int a, int b) : u(a), v(b) {};
	};

	vector<Edge> vEdges;
	vector<bool> vCovered;
	MapIntSet mapNodeEdges;

	// read edges, node to Edges
	// read querys, set vCovered

	void Read(void)
	{
		int n, m, u, v;
		cin >> n >> m;
		for (int i = 0; i < m; ++i)
		{
			cin >> u >> v;
			vEdges.emplace_back(u, v);
			mapNodeEdges[u].insert(i);
			mapNodeEdges[v].insert(i);
		}
		int k, nv, ni;
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			vCovered.assign(m, false);
			cin >> nv;
			for (int i = 0; i < nv; ++i)
			{
				cin >> ni;
				set<int>& si = mapNodeEdges[ni];
				for (auto ei : si)
				{
					vCovered[ei] = true;
				}
			}
			if (find(vCovered.begin(), vCovered.end(), false) == vCovered.end())
			{
				cout << "Yes" << endl;
			}
			else
			{
				cout << "No" << endl;
			}
		}
	}
}

// rename this to main int PAT
int A1134Func(void)
{
	nsA1134::Read();
	return 0;
}


void A1134(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1134Func();
	cout << endl;
}

void A1134(void)
{
	A1134("data\\A1134-1.txt"); // 
}

