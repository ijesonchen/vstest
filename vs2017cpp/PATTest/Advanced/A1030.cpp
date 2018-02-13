/*
1030. Travel Plan (30)

cost 10:55

sln1: Dijkstra sp
	dfs遍历所有可能路径，利用SP减枝，找到最小cost
	60min 24/30 pt2 TLE


A traveler's map gives the distances between cities along the highways, 
together with the cost of each highway. 
Now you are supposed to write a program to help a traveler to
decide the shortest path between his/her starting city and the destination. 
If such a shortest path is not unique, you are supposed to output 
the one with the minimum cost, which is guaranteed to be unique.

Input Specification:

Each input file contains one test case. 
Each case starts with a line containing 4 positive integers N, M, S, and D, 
where N (<=500) is the number of cities (and hence the cities are numbered from 0 to N-1); 
M is the number of highways; 
S and D are the starting and the destination cities, respectively. 
Then M lines follow, each provides the information of a highway, in the format:
City1 City2 Distance Cost
where the numbers are all integers no more than 500, and are separated by a space.

Output Specification:
For each test case, print in one line the cities along the shortest path 
from the starting point to the destination, 
followed by the total distance and the total cost of the path.
The numbers must be separated by a space and there must be no extra space at the end of output.

Sample Input
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
Sample Output
0 2 3 3 40
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

namespace nsA1030
{
	class Graph
	{
	public:
		void ReadData(void);
		int Dijkstra(void);
		void SearchPath(void);
		void Dfs(int u);
	private:
		struct Edge
		{
			int u = 0;
			int v = 0;
			int d = 0;
			int c = 0;
			void Reverse(void) { swap(u, v); };
			bool Circle(void) { return u == v; };
		};
		const int MAXDIST = 1000000;
		// graph info
		vector<vector<Edge>> vAdj;
		int node = 0;
		int start = 0;
		int dst = 0;
		int sp = 0;
		
		// for search
		vector<bool> vVisit;
		vector<int> vDist;
		vector<int> path;
		int cost = 0;
		vector<int> dstPath;
		int dstCost = MAXDIST;
	};
	
	void Graph::ReadData(void)
	{
		int ne;
		cin >> node >> ne >> start >> dst;
		vAdj.assign(node, vector<Edge>());
		for (int i = 0; i < ne; ++i)
		{
			Edge e;
			cin >> e.u >> e.v >> e.d >> e.c;
			if (e.Circle()) { continue; }
			vAdj[e.u].push_back(e);
			e.Reverse();
			vAdj[e.u].push_back(e);			
		}
	}

	int Graph::Dijkstra(void)
	{
		vVisit.assign(node, false);
		vDist.assign(node, MAXDIST);
		vDist[start] = 0;
		for (int i = 0; i < node; ++i)
		{
			int u = 0;
			int minDist = MAXDIST;
			for (int i = 1; i < node; ++i)
			{
				if (!vVisit[i] && vDist[i] < minDist)
				{
					u = i;
					minDist = vDist[i];
				}
			}
			vVisit[u] = true;
			auto du = vDist[u];
			auto& uAdj = vAdj[u];
			for (auto& e : uAdj)
			{
				if (vVisit[e.v])
				{
					continue;
				}
				auto duv = du + e.d;
				if (duv < vDist[e.v])
				{
					vDist[e.v] = duv;
				}
			}
		}
		return vDist[dst];
	}
	
	void Graph::Dfs(int u)
	{
		if (u == dst && cost < dstCost)
		{
			dstPath = path;
			dstCost = cost;
			return;
		}
		for (int i = 0; i < node; ++i)
		{
			auto& uAdj = vAdj[u];
			auto ud = vDist[u];
			for (auto& e : uAdj)
			{
				if (vVisit[e.v] || ud + e.d > vDist[e.v])
				{
					continue;
				}
				vVisit[e.v] = true;
				path.push_back(e.v);
				cost += e.c;
				Dfs(e.v);
				vVisit[e.v] = false;
				path.pop_back();
				cost -= e.c;
			}
		}
	}

	void Graph::SearchPath(void)
	{
		vVisit.assign(node, false);
		vVisit[start] = true;
		path.push_back(start);
		cost = 0;
		Dfs(start);
		for (auto v : dstPath)
		{
			cout << v << " ";
		}
		cout << vDist[dst] << " " << dstCost << endl;
	}
}

// rename this to main int PAT
int A1030Func(void)
{
	using namespace nsA1030;
	Graph g;
	g.ReadData();
	g.Dijkstra();
	g.SearchPath();
	return 0;
}


void A1030(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1030Func();
	cout << endl;
}

void A1030(void)
{
	A1030("data\\A1030-1.txt"); // 
}

