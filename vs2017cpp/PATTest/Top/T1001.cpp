/*
1001. Battle Over Cities - Hard Version (35)

sln1: 穷举+BFS, MST
	19/35 pt2,3 异常(buildCost未找到路径)， pt5 超时


It is vitally important to have all the cities connected by 
highways in a war. If a city is conquered by the enemy, all 
the highways from/toward that city will be closed. To keep
the rest of the cities connected, we must repair some highways
with the minimum cost. On the other hand, if losing a city
will cost us too much to rebuild the connection, we must pay
more attention to that city.

Given the map of cities which have all the destroyed and 
remaining highways marked, you are supposed to point out the 
city to which we must pay the most attention.

Input Specification:

Each input file contains one test case. Each case starts with
a line containing 2 numbers N (<=500), and M, which are the
total number of cities, and the number of highways, respectively. 
Then M lines follow, each describes a highway by 4 integers:

City1 City2 Cost Status
where City1 and City2 are the numbers of the cities the highway
connects (the cities are numbered from 1 to N), Cost is the effort
taken to repair that highway if necessary, and Status is either 0,
meaning that highway is destroyed, or 1, meaning that highway 
is in use.

Note: It is guaranteed that the whole country was connected 
before the war.

Output Specification:

For each test case, just print in a line the city we must protest 
the most, that is, it will take us the maximum effort to rebuild 
the connection if that city is conquered by the enemy.

In case there is more than one city to be printed, output them 
in increasing order of the city numbers, separated by one space,
but no extra space at the end of the line. In case there is no 
need to repair any highway at all, simply output 0.

Sample Input 1:
4 5
1 2 1 1
1 3 1 1
2 3 1 0
2 4 1 1
3 4 1 0
Sample Output 1:
1 2

Sample Input 2:
4 5
1 2 1 1
1 3 1 1
2 3 1 0
2 4 1 1
3 4 2 1
Sample Output 2:
0
*/
#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>

using namespace std;

class T1001G1
{
public:
	void Read(void)
	{
		int n, m;
		cin >> n >> m;
		cityCount = n;
		adjGood.assign(n, vector<Edge>());
		adjBad.assign(n, vector<Edge>());
		int u, v, c;
		bool ok;
		for (int i = 0; i < m; ++i)
		{
			cin >> u >> v >> c >> ok;
			if (u == v) { continue; }
			--u; --v;
			if (ok)
			{
				adjGood[u].emplace_back(Edge(u, v, c, ok));
				adjGood[v].emplace_back(Edge(v, u, c, ok));
			}
			else
			{
				adjBad[u].emplace_back(Edge(u, v, c, ok));
				adjBad[v].emplace_back(Edge(v, u, c, ok));
			}
		}
	}
	
	void SearchCity(void)
	{
		int maxCost = 0;
		int cost = 0;
		vector<int> cities;
		for (int i = 0; i < cityCount; ++i)
		{
			cost = CityCost(i);
			if (cost < maxCost)
			{
				continue;
			}
			if (cost == maxCost)
			{
				cities.push_back(i);
			}
			else
			{
				maxCost = cost;
				cities.clear();
				cities.push_back(i);
			}
		}

		if (cities.empty())
		{
			cout << "0" << endl;
		}
		else
		{
			sort(cities.begin(), cities.end());
			cout << cities.front() + 1;
			for (int i = 1; i < cities.size(); ++i)
			{
				cout << " " << cities[i] + 1;
			}
			cout << endl;
		}
	}

private:
	struct Edge
	{
		int u = 0;
		int v = 0;
		int c = 0;
		bool ok = false;
		Edge(int _u, int _v, int _c, bool _ok)
			:u(_u), v(_v), c(_c), ok(_ok) {};

		bool operator<(const Edge& e)
		{
			return c < e.c;
		}

		bool Relate(const Edge& e)
		{
			return (u == e.u) 
				|| (u == e.v) 
				|| (v = e.u) 
				|| (v = e.v);
		}
	};

	void Bfs(int start)
	{
		deque<int> dq;
		dq.push_back(start);
		while (!dq.empty())
		{
			int n = dq.front();
			dq.pop_back();
			vector<Edge>& adj = adjGood[n];
			int length = (int)adj.size();
			for (int i = 0; i < length; ++i)
			{
				Edge& e = adj[i];
				if (visited[e.v])
				{
					continue;
				}
				visited[e.v] = true;
				dq.push_back(e.v);
				m[start].push_back(e.v);
			}
		}
	}

	// do not return 0;
	int CityCost(int iCity)
	{
		ResetBfsAssist(iCity);
		for (int i = 0; i < cityCount; ++i)
		{
			if (i == badCity)
			{
				continue;
			}
			if (!visited[i])
			{
				visited[i] = true;
				m[i].push_back(i);
				Bfs(i);
			}
		}
		int msize = (int)m.size();
		if (msize == 1)
		{
			return -1;
		}
		// MST
		int buildcost = 0;
		vector<Edge> groupEdges;
		vector<vector<int>> costMatrix(msize);
		map<int, vector<int>>::iterator mbeg = m.begin();
		map<int, vector<int>>::iterator mend = m.end();
		map<int, vector<int>>::iterator mi;
		map<int, vector<int>>::iterator mj;
		int mii = 0;
		int mjj = 0;
		for (mi = m.begin(); mi != mend; ++mi, ++mii)
		{
			for (mj = mi, mjj = mii; mj != mend; ++mj, ++mjj)
			{
				if (mi == mj)
				{
					continue;
				}
				buildcost = BuildCost(mi->second, mj->second);
				groupEdges.push_back(Edge(mii, mjj, buildcost, true));
			}
		}
		sort(groupEdges.begin(), groupEdges.end());
		int totalCost = 0;
		int geSize = (int)groupEdges.size();
		for (int i = 0; i < geSize; ++i)
		{
			Edge& e = groupEdges[i];
			if (!e.ok)
			{
				continue;
			}
			totalCost += e.c;
			// mark all e
			for (int j = i; j < geSize; ++j)
			{
				Edge& e2 = groupEdges[j];
				if (e.Relate(e2))
				{
					e2.ok = false;
				}
			}
		}
		if (totalCost == 0)
		{
			abort();
		}
		return totalCost;
	}

	int BuildCost(vector<int>& v1, vector<int>& v2)
	{
		int cost = 0x7FFFFFFF;
		int v1size = (int)v1.size();
		int v2size = (int)v2.size();
		for (int i = 0; i < v1size; ++i)
		{
			const int u = v1[i];
			vector<Edge>& edges = adjBad[u];
			int edgesize = (int)edges.size();
			for (int j = 0; j < edgesize; ++j)
			{
				const Edge& e = edges[j];
				if (e.v == badCity)
				{
					continue;
				}
				for (int k = 0; k < v2size; ++k)
				{
					const int v = v2[k];
					if (e.v == v)
					{
						if (e.c < cost)
						{
							cost = e.c;
						}
					}
				}
			}
		}
		if (cost == 0x7FFFFFFF)
		{
			abort();
		}
		return cost;
	}

	// for BFS group
	void ResetBfsAssist(int i)
	{
		badCity = i;
		m.clear();
		visited.assign(cityCount, false);
		visited[badCity] = true;
	}
	int badCity = -1;
	map<int, vector<int>> m;
	vector<bool> visited;

	vector<vector<Edge>> adjGood;
	vector<vector<Edge>> adjBad;
	int cityCount = 0;
};

// rename this to main int PAT
int T1001Func(void)
{
	T1001G1 g;
	g.Read();
	g.SearchCity();
	return 0;
}


void T1001(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1001Func();
	cout << endl;
}

void T1001(void)
{
	T1001("data\\T1001-1.txt"); // 1 2
	T1001("data\\T1001-2.txt"); // 0
	T1001("data\\T1001-3.txt"); // 3
}
