//////////////////////////////////////////////////////////////////////////
/*
The file contains the edges of a directed graph. Vertices are labeled as positive integers 
from 1 to 875714. Every row indicates an edge, the vertex label in first column is the tail 
and the vertex label in second column is the head (recall the graph is directed, and the 
edges are directed from the first column vertex to the second column vertex).

So for example, the 11th row looks liks : "2 47646". This just means that the vertex with 
label 2 has an outgoing edge to the vertex with label 47646

Your task is to code up the algorithm from the video lectures for computing strongly connected 
components (SCCs), and to run this algorithm on the given graph.

Output Format: You should output the sizes of the 5 largest SCCs in the given graph, in 
decreasing order of sizes, separated by commas (avoid any spaces).

So if your algorithm computes the sizes of the five largest SCCs to be 500, 400, 300, 200 and 
100, then your answer should be "500,400,300,200,100" (without the quotes). If your algorithm 
finds less than 5 SCCs, then write 0 for the remaining terms. Thus, if your algorithm computes 
only 3 SCCs whose sizes are 400, 300, and 100, then your answer should be "400,300,100,0,0" 
(without the quotes). (Note also that your answer should not have any spaces in it.)

WARNING: This is the most challenging programming assignment of the course. Because of the size 
of the graph you may have to manage memory carefully. The best way to do this depends on your 
programming language and environment, and we strongly suggest that you exchange tips for doing 
this on the discussion forums.
*/

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <stack>
#include "common.h"

using namespace std;
#pragma warning(disable: 4018)
// vertext index is 1-based


class AdjGraph
{
public:
	AdjGraph(int nVertices)
		: adj(nVertices + 1)
	{
	}

	void AddEdge(int from, int to) { adj[from].push_front(to); ++nEdge; }
	int V(void) const { return adj.size() - 1; }
	int E(void) const { return nEdge; }
	list<int> Adj(int v) const { return adj[v]; };

	AdjGraph Reverse(void)
	{
		AdjGraph g(V());
		for (int from = 1; from < adj.size(); ++from)
		{
			for (auto to : adj[from])
			{
				g.AddEdge(to, from);
			}
		}
		return g;
	}

	void Print(void)
	{
		cout << V() << " " << E() << endl;
		for (int i = 1; i < adj.size(); ++i)
		{
			cout << i << ": ";
			for (auto n : adj[i]) { cout << n << " "; }
			cout << endl;
		}
	}

	void Print0Base(void)
	{
		cout << V() << " " << E() << endl;
		for (int i = 1; i < adj.size(); ++i)
		{
			cout << i-1 << ": ";
			for (auto n : adj[i]) { cout << n-1 << " "; }
			cout << endl;
		}
	}
private:
	vector<list<int>> adj;
	int nEdge = 0;
};


bool operator==(const AdjGraph& lhs, const AdjGraph& rhs)
{
	if (lhs.E() != rhs.E() ||
		lhs.V() != rhs.V())
	{
		return false;
	}
	auto n = lhs.V();
	for (int i = 1; i < n; ++i)
	{
		auto lList = lhs.Adj(i);
		auto rList = rhs.Adj(i);
		lList.sort();
		rList.sort();
		if (lList != rList)
		{
			return false;
		}
	}
	return true;
}

bool operator!=(const AdjGraph& lhs, const AdjGraph& rhs)
{
	return !(lhs == rhs);
}
class DirectedDFS
{
public:
	DirectedDFS(AdjGraph g)
	{
		marked.assign(g.V() + 1, false);
		stacked.assign(g.V() + 1, false);
	}

	DirectedDFS& Search(AdjGraph g, int s)
	{
		if (!marked[s]) dfs(g, s);
		return *this;
	}

	DirectedDFS& SearchAll(AdjGraph g)
	{
		for (int ii = 1; ii < marked.size(); ++ii)
		{
			if (!marked[ii]) dfs(g, ii);
		}
		return *this;
	}

	bool Marked(int v) { return marked[v]; };
	bool Cycled() const { return cycled; }

	vector<int> Pre(void) 
	{
		vector<int> v;
		auto p = pre;
		while (p.size())
		{
			v.push_back(p.front());
			p.pop();
		}
		return v;
	};
	vector<int> Post(void) 
	{
		vector<int> v;
		auto p = post;
		while (p.size())
		{
			v.push_back(p.front());
			p.pop();
		}
		return v;
	};
	vector<int> RevPost(void) 
	{
		vector<int> v;
		auto p = revPost;
		while (p.size())
		{
			v.push_back(p.top());
			p.pop();
		}
		return v;
	};

	void Print0Base(void)
	{
		for (int i = 1; i < marked.size(); ++i)
		{
			if (marked[i])
			{
				cout << i - 1 << " ";
			}
		}
		cout << endl;
	}
private:
	void dfs(const AdjGraph& g, int s)
	{
		pre.push(s);

		marked[s] = true;
		stacked[s] = true;
		for (const auto i : g.Adj(s))
		{
			if (!marked[i])
			{
				dfs(g, i);
			}
			if (stacked[i])
			{
				cycled = true;
			}
		}
		stacked[s] = false;

		post.push(s);
		revPost.push(s);
	}
	vector<bool> marked;
	vector<bool> stacked;
	bool cycled = false;
	// dfs order
	queue<int> pre;
	queue<int> post;
	stack<int> revPost;
};

// class KosarajuSCC
// {
// public:
// 	KosarajuSCC(AdjGraph g)
// private:
// };

AdjGraph ReadGraph0Base(const string& fileName, int nVertices)
{
	AdjGraph g(nVertices);

	fstream f(fileName, ios::in);
	if (!f) { abort(); }
	int x = 0;
	int u = 0;
	bool second = true;
	while (f >> x)
	{
		++x;
		second = !second;
		if (second)
		{
			g.AddEdge(u, x);
			continue;
		}
		u = x;
	}
	return g;
}

AdjGraph ReadRGraph0Base(const string& fileName, int nVertices)
{
	AdjGraph g(nVertices);

	fstream f(fileName, ios::in);
	if (!f) { abort(); }
	int x = 0;
	int u = 0;
	bool second = true;
	while (f >> x)
	{
		++x;
		second = !second;
		if (second)
		{
			g.AddEdge(x, u);
			continue;
		}
		u = x;
	}
	return g;
}

void GraphRev0Base(void)
{
	auto g1 = ReadGraph0Base("data\\wk5-Test-TinyDAG-13-15-0base.txt", 13);
	auto g2 = g1.Reverse();
	auto g3 = ReadRGraph0Base("data\\wk5-Test-TinyDAG-13-15-0base.txt", 13);
	if (g2 != g3)
	{
		g2.Print0Base();
		g3.Print0Base();
		abort();
	}
	cout << "reverse passed." << endl;
}

void GraphDFS0Base(void)
{
	auto fnTinyDG = "data\\wk5-Test-TinyDG-13-22-0base.txt";
	auto g = ReadGraph0Base(fnTinyDG, 13);
	g.Print0Base();

	DirectedDFS(g).Search(g, 1 + 1).Print0Base();
	DirectedDFS(g).Search(g, 2 + 1).Print0Base();
	DirectedDFS(g).Search(g, 1 + 1).Search(g, 2 + 1).Search(g, 6 + 1).Print0Base();

	cout << "cycled: " << DirectedDFS(g).SearchAll(g).Cycled() << endl;
}

void GraphDfsOrder0Base(void)
{
	auto g = ReadGraph0Base("data\\wk5-Test-TinyDAG-13-15-0base.txt", 13);
	g.Print0Base();

	DirectedDFS dfs(g);
	dfs.SearchAll(g);
	cout << "cycled: " << dfs.Cycled() << endl;

	cout << "pre  : ";
	for (auto i : dfs.Pre())
	{
		cout << i - 1 << " ";
	}
	cout << endl;

	cout << "post : ";
	for (auto i : dfs.Post())
	{
		cout << i - 1 << " ";
	}
	cout << endl;

	cout << "rPost: ";
	for (auto i : dfs.RevPost())
	{
		cout << i - 1 << " ";
	}
	cout << endl;
}


void GraphTest0Base(void)
{
	// input / output 0based, proc 1-based
	GraphDFS0Base();
	GraphDfsOrder0Base();
	GraphRev0Base();
}

void SCC(void)
{
	GraphTest0Base();
	return;


	class InputFile
	{
	public:
		InputFile(const string& str, vector<int> res) :
			filename(str), result(res)
		{}
		string filename;
		vector<int> result;
	};

	vector<InputFile> vtFileNames = {
		{ "wk5-SCC.txt", { 0, 0, 0, 0, 0 } },
		{ "wk5-Test-3,3,1,1,0.txt", { 3, 3, 1, 1, 0 } },
		{ "wk5-Test-3,3,2,0,0.txt", { 3, 3, 2, 0, 0 } },
		{ "wk5-Test-3,3,3,0,0.txt", { 3, 3, 3, 0, 0 } },
		{ "wk5-Test-6,3,2,1,0.txt", { 6, 3, 2, 1, 0 } },
		{ "wk5-Test-7,1,0,0,0.txt", { 7, 1, 0, 0, 0 } },
	};
}