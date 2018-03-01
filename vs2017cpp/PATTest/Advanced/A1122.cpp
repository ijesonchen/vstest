/*
1122. Hamiltonian Cycle (25)

cost: 15:15 20min pass

300ms
The "Hamilton cycle problem" is to find a simple cycle that contains every vertex in a graph. 
Such a cycle is called a "Hamiltonian cycle".

In this problem, you are supposed to tell if a given cycle is a Hamiltonian cycle.

Input Specification:

Each input file contains one test case. 
For each case, the first line contains 2 positive integers N (2< N <= 200), the number of vertices, 
and M, the number of edges in an undirected graph. 
Then M lines follow, each describes an edge in the format "Vertex1 Vertex2", 
where the vertices are numbered from 1 to N. 

The next line gives a positive integer K which is the number of queries, 
followed by K lines of queries, each in the format:
n V1 V2 ... Vn

where n is the number of vertices in the list, and Vi's are the vertices on a path.

Output Specification:

For each query, print in a line "YES" if the path does form a Hamiltonian cycle, or "NO" if not.

Sample Input:
6 10
6 2
3 4
1 5
2 5
3 1
4 1
1 6
6 3
1 2
4 5
6
7 5 1 4 3 6 2 5
6 5 1 4 3 6 2
9 6 2 1 6 3 4 5 2 6
4 1 2 5 1
7 6 1 3 4 5 2 6
7 6 1 2 5 4 3 1
Sample Output:
YES
NO
NO
NO
YES
NO
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace nsA1122A
{

	int main(void)
	{
		int n, m;
		cin >> n >> m;
		vector<vector<bool>> vMatrix(n + 1, vector<bool>(n + 1, false));
		for (int i = 0; i < m; ++i)
		{
			int u, v;
			cin >> u >> v;
			vMatrix[u][v] = true;
			vMatrix[v][u] = true;
		}
		int k;
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			int node;
			cin >> node;
			vector<int> vPath(node, 0);
			for (int j = 0; j < node; ++j)
			{
				cin >> vPath[j];
			}
			if (node != (n + 1))
			{
				cout << "NO" << endl;
				continue;
			}
			vector<bool> vVisit(n + 1, false);
			int u, v;
			u = vPath[0];
			bool bHam = true;
			for (size_t j = 1; j < node; ++j)
			{
				v = vPath[j];
				if (vVisit[v] || !vMatrix[u][v])
				{
					cout << "NO" << endl;
					bHam = false;
					break;
				}
				vVisit[v] = true;
				u = v;
			}
			if (bHam)
			{
				cout << "YES" << endl;
			}
		}
		return 0;
	}
}

// rename this to main int PAT
int A1122Func(void)
{
	nsA1122A::main();
	return 0;
}


void A1122(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1122Func();
	cout << endl;
}

void A1122(void)
{
	A1122("data\\A1122-1.txt"); // 
}

