/*
TIP:
shortest path, non-neg weight
alg1: x 可能会漏掉（中间某些等长路径）
	1. 计算最短路径sp
	2. Dijkstra，每次u-v长度为sp时，记录路径数量及team
alg2: x 同上
	Dijkstra，每次碰到U-V路径时，判断当前SP是否最小，并记录路径数量及team数
alg3: dp+Dijkstra
	节点u-v
	每个节点保存l：最短路径长度，n：最短路径数量，t：最大team数
	if edge(u,v) selected:
		calc new v(l,n,t) from u
		if new v.l > old v.l: ignore
		if new v.l = old v.l: dup path, add n, replace t if bigger
		if new v.l < old v.l: shorter path, relpace l,n,t
	point 5/6 score 22/25;bad 2
	错误原因：dup path分支代码错误：n+1，应为+=


1003. Emergency (25)
As an emergency rescue team leader of a city, you are given a special 
map of your country. The map shows several scattered cities connected 
by some roads. Amount of rescue teams in each city and the length of each 
road between any pair of cities are marked on the map. When there is an 
emergency call to you from some other city, your job is to lead your men 
to the place as quickly as possible, and at the mean time, call up as many 
hands on the way as possible.

Input

Each input file contains one test case. For each test case, the first line 
contains 4 positive integers: N (<= 500) - the number of cities (and the 
cities are numbered from 0 to N-1), M - the number of roads, C1 and C2 - the 
cities that you are currently in and that you must save, respectively. 
The next line contains N integers, where the i-th integer is the number of 
rescue teams in the i-th city. Then M lines follow, each describes a road 
with three integers c1, c2 and L, which are the pair of cities connected by 
a road and the length of that road, respectively. It is guaranteed that there 
exists at least one path from C1 to C2.

Output

For each test case, print in one line two numbers: the number of different 
shortest paths between C1 and C2, and the maximum amount of rescue teams you 
can possibly gather.
All the numbers in a line must be separated by exactly one space, and there 
is no extra space allowed at the end of a line.

Sample Input
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1
Sample Output
2 4
*/

#include <vector>
#include <iostream>
#include "patMain.h"

using namespace std;

const long long A1003MaxLength = 0x7fffffffffffffff;

class A1003Graph
{
private:
	struct Edge
	{
		int v = -1; // dst node
		int w = -1; // weight

		Edge(int _v, int _w) : v(_v), w(_w) {};
	};

	struct Node
	{
		int team = 0; // team count
		long long spDist = A1003MaxLength; // length of SP
		int spCnt = 0; // count of SP
		int totalRescue = 0; // total rescue team
		bool visited = false; // visited in BFS
		Node() {};
	};

	vector<Node> nodes;
	vector<vector<Edge>> adjs;
	int src = -1;
	int dst = -1;
public:
	void Read(void);
	void Calc(void);
	int SelectNearest(void);
	void UpdateNearest(int ui);
};

void A1003Graph::Read(void)
{
	int n, m, a;
	cin >> n >> m >> src >> dst;
	nodes.assign(n, Node());
	adjs.assign(n, vector<Edge>());
	for (int i = 0; i < n; ++i)
	{
		cin >> a;
		nodes[i].team = a;
	}
	int u, v, w;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> w;
		adjs[u].emplace_back(v, w);
		adjs[v].emplace_back(u, w);
	}
}

void A1003Graph::Calc(void)
{
	auto& u = nodes[src];
	u.spDist = 0;
	u.spCnt = 1;
	u.totalRescue = u.team;
	int sel = -1;
	while ((sel = SelectNearest()) != -1)
	{
		nodes[sel].visited = true;
		UpdateNearest(sel);
	}
	auto& v = nodes[dst];
	cout << v.spCnt << " " << v.totalRescue << endl;
}


int A1003Graph::SelectNearest(void)
{
	auto length = nodes.size();
	auto minLen = A1003MaxLength;
	auto sel = -1;
	for (size_t i = 0; i < length; i++)
	{
		auto& u = nodes[i];
		if (u.visited)
		{
			continue;
		}
		if (u.spDist < minLen)
		{
			minLen = u.spDist;
			sel = (int)i;
		}
	}
	return sel;
}


void A1003Graph::UpdateNearest(int ui)
{
	auto& u = nodes[ui];
	for (auto& e : adjs[ui])
	{
		auto& v = nodes[e.v];
		if (v.visited)
		{
			continue;
		}
		auto spdist = u.spDist + e.w;
		if (spdist < v.spDist)
		{
			v.spDist = spdist;
			v.spCnt = u.spCnt;
			v.totalRescue = u.totalRescue + v.team;
		}
		else if (spdist == v.spDist)
		{
			v.spCnt += u.spCnt;
			auto totalRescue = u.totalRescue + v.team;
			if (v.totalRescue < totalRescue)
			{
				v.totalRescue = totalRescue;
			}
		}
	}
}

void A1003(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1003Graph g;
	g.Read();
	g.Calc();
}


void A1003(void)
{
	A1003("data\\A1003-1.TXT"); // 2 4
	A1003("data\\A1003-2.TXT"); // 3 23
	A1003("data\\A1003-3.TXT"); // 3 34
	A1003("data\\A1003-4.TXT"); // 3 8
}