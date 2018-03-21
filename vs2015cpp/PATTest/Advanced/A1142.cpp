/*
1142. Maximal Clique (25)
400 ms
65536 kB

A clique is a subset of vertices of an undirected graph such that every two distinct vertices in the clique are adjacent.
A maximal clique is a clique that cannot be extended by including one more adjacent vertex. 
(Quoted from https://en.wikipedia.org/wiki/Clique_(graph_theory))

Now it is your job to judge if a given subset of vertices can form a maximal clique.

Input Specification:

Each input file contains one test case. For each case, the first line gives two 
positive integers Nv (<= 200), the number of vertices in the graph, and 
Ne, the number of undirected edges.
Then Ne lines follow, each gives a pair of vertices of an edge. 
The vertices are numbered from 1 to Nv.

After the graph, there is another positive integer M (<= 100). 
Then M lines of query follow, each first gives a positive number K (<= Nv), 
then followed by a sequence of K distinct vertices.
All the numbers in a line are separated by a space.

Output Specification:

For each of the M queries, print in a line "Yes" if the given subset of vertices can form a maximal clique; 
or if it is a clique but not a maximal clique, print "Not Maximal"; or if it is not a clique at all, print "Not a Clique".

Sample Input:
8 10
5 6
7 8
6 4
3 6
4 5
2 3
8 2
2 7
5 3
3 4
6
4 5 4 3 6
3 2 8 7
2 2 3
1 1
3 4 3 6
3 3 2 1
Sample Output:
Yes
Yes
Yes
Yes
Not Maximal
Not a Clique
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace nsA1142A
{
	int nv, ne;
	vector<vector<int>>  vvAdj;
	vector<vector<bool>> vvMat;

	void Test(const vector<int>& vec)
	{
		// Clique
		vector<bool> vVisit(ne + 1);
		for (auto u : vec) {
			vVisit[u] = true;
			for (auto v : vec) {
				if (!vvMat[u][v]) {
					cout << "Not a Clique" << endl;
					return;
				}
			}
		}
		// Maximal
		for (auto u : vec)
		{
			for (auto v : vvAdj[u])
			{
				if (!vVisit[v])
				{
					// v connected all w in vec?
					bool bConnAll = true;
					for (auto w : vec)
					{
						if (!vvMat[v][w])
						{
							bConnAll = false;
							break;
						}
					}
					if (bConnAll)
					{
						cout << "Not Maximal" << endl;
						return;
					}
				}
			}
		}
		cout << "Yes" << endl;
	}

	void main(void)
	{
		cin >> nv >> ne;
		vvAdj.assign(nv + 1, vector<int>());
		vvMat.assign(nv + 1, vector<bool>(nv + 1));
		int u, v;
		for (int i = 0; i < ne; ++i)
		{
			cin >> u >> v;
			vvAdj[u].push_back(v);
			vvAdj[v].push_back(u);
			vvMat[u][v] = true;
			vvMat[v][u] = true;
		}

		// self connected
		for (int i = 1; i <= nv; ++i)
		{
			vvMat[i][i] = true;
		}

		int m;
		cin >> m;

		for (int i = 0; i < m; ++i)
		{
			int k;
			cin >> k;
			vector<int> v(k);
			for (int j = 0; j < k; ++j)
			{
				cin >> v[j];
			}
			Test(v);
		}
	}
}

// rename this to main int PAT
int A1142Func(void)
{
	nsA1142A::main();
	return 0;
}


void A1142(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1142Func();
	cout << endl;
}

void A1142(void)
{
	A1142("data\\A1142-1.txt"); // 
}

