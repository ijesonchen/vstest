/*
1021. Deepest Root (25)

cost: 21:10 40min
sln1: bfs
	注意流程细节

A graph which is connected and acyclic can be considered a tree. 
The height of the tree depends on the selected root. 
Now you are supposed to find the root that results in a highest tree. 
Such a root is called the deepest root.

Input Specification:

Each input file contains one test case. 
For each case, the first line contains a positive integer 
N (<=10000) which is the number of nodes, and hence the nodes are numbered from 1 to N. 
Then N-1 lines follow, each describes an edge by given the two adjacent nodes' numbers.

Output Specification:

For each test case, print each of the deepest roots in a line. 
If such a root is not unique, print them in increasing order of their numbers. 
In case that the given graph is not a tree, 
print "Error: K components" where K is the number of connected components in the graph.

Sample Input 1:
5
1 2
1 3
1 4
2 5
Sample Output 1:
3
4
5
Sample Input 2:
5
1 3
1 4
2 5
3 4
Sample Output 2:
Error: 2 components

*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

class A1021Graph
{
public:
	void Read(void);
	void Search(void);
	int Bfs(int start);
	// ignore below
	void SearchRoot(void);
	int BfsLayer(int start);
private:
	vector<vector<int>> adjs;
	vector<int> nodeLayer;
	vector<bool> visit;
	int node;
};

void A1021Graph::Read(void)
{
	cin >> node;
	adjs.assign(node, vector<int>());
	for (int i = 0; i < node - 1; ++i)
	{
		int u, v;
		cin >> u >> v;
		if (u == v)
		{
			continue;
		}
		--u, --v;
		adjs[u].push_back(v);
		adjs[v].push_back(u);
	}
}


void A1021Graph::Search(void)
{
	visit.assign(node, false);
	nodeLayer.assign(node, 0);
	int maxlayer = 0;
	int component = 0;
	for (int i = 0; i < node; ++i)
	{
		if (visit[i])
		{
			continue;
		}
		++component;
		maxlayer = Bfs(i);
	}
	if (component > 1)
	{
		// Error: 2 components
		cout << "Error: " << component << " components" << endl;
		return;
	}
	if (component != 1)
	{
		throw 0;
	}

	vector<int> roots;
	roots.push_back(0);
	for (int i = 1; i < node; ++i)
	{
		visit.assign(node, false);
		nodeLayer.assign(node, 0);
		int layer = Bfs(i);
		if (layer > maxlayer)
		{
			maxlayer = layer;
			roots.clear();
			roots.push_back(i);
		}
		else if (layer == maxlayer)
		{
			roots.push_back(i);
		}
	}

	for (auto n : roots)
	{
		cout << n + 1 << endl;
	}
}

int A1021Graph::Bfs(int start)
{
	deque<int> dq;
	dq.push_back(start);
	visit[start] = true;
	nodeLayer[start] = 1;
	int maxlayer = 0;
	while (!dq.empty())
	{
		int u = dq.front();
		int hight = nodeLayer[u];
		dq.pop_front();
		auto& ue = adjs[u];
		for (auto v : ue)
		{
			if (visit[v])
			{
				continue;
			}
			dq.push_back(v);
			visit[v] = true;
			maxlayer = hight + 1;
			nodeLayer[v] = maxlayer;
		}
	}
	return maxlayer;
}

void A1021Graph::SearchRoot(void)
{
	for (int i = 0; i < node; ++i)
	{
		cout << i + 1 << " " << BfsLayer(i) << endl;
	}
}

int A1021Graph::BfsLayer(int start)
{
	visit.assign(node, false);
	nodeLayer.assign(node, 0);
	deque<int> dq;
	dq.push_back(start);
	visit[start] = true;
	nodeLayer[start] = 1;
	int maxlayer = 0;
	while (!dq.empty())
	{
		int u = dq.front();
		int hight = nodeLayer[u];
		dq.pop_front();
		auto& ue = adjs[u];
		for (auto v : ue)
		{
			if (visit[v])
			{
				continue;
			}
			dq.push_back(v);
			visit[v] = true;
			maxlayer = hight + 1;
			nodeLayer[v] = maxlayer;			
		}
	}
	return maxlayer;
}

// rename this to main int PAT
int A1021Func(void)
{
	A1021Graph g;
	g.Read();
	g.Search();
	return 0;
}


void A1021(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1021Func();
	cout << endl;
}

void A1021(void)
{
	A1021("data\\A1021-1.txt"); // 
	A1021("data\\A1021-2.txt"); // 
}

