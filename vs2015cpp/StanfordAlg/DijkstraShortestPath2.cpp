#include "common.h"
#include <iostream>

/*
算法：
0. 选取源节点s，标记，更新s邻接点：最短路径
1. 选取最近节点v，标记，更新：最短路径
2. 遍历v的邻接点，更新：最短路径

改进：保证第一次选取s
0。 选取未标记的最近节点s，标记，更新s最短路径
1. 遍历s的邻接点v，更新：最短路径

*/

using namespace std;

// I/O 1-based, process 0-based.

int DSP2NodeCount = 200;
const int DSP2Src = 0;
const int DSP2MaxLen = 1000000;
vector<int> DSP2Targets = {
//	7,37,59,82,99,115,133,165,188,197
	7 - 1,37 - 1,59 - 1,82 - 1,99 - 1,115 - 1,133 - 1,165 - 1,188 - 1,197 - 1,
};

class DSP2G
{
private:
	struct Edge
	{
		int v = -1; // dst node
		int w = 0; // weight

		Edge(int _t, int _w) :v(_t), w(_w) {};
	};

	struct Node
	{
		int p = -1; // parent in SP
		int s = DSP2MaxLen; // shortest path
		bool v = false; // visited

		Node() {};
	};

	vector<Node> nodes;
	vector<vector<Edge>> adjs;
	int SelectNearest(void);
	void UpdateNearest(int n);
	void PrintDist(void)
	{
		for (auto& i : nodes)
		{
			if (i.s == DSP2MaxLen)
			{
				cout << "- ";
				continue;
			}
			cout << i.s << " ";
		}
		cout << endl;
		for (auto& i : nodes)
		{
			cout << i.v << " ";
		}
		cout << endl;
		for (auto& i : nodes)
		{
			if (i.p == -1)
			{
				cout << "- ";
				continue;
			}
			cout << i.p << " ";
		}
		cout << endl << endl;
	}
public:
	void LoadFile(const std::string& fn);
	void ShortestPath(void);
	string Result(void);
};

void DSP2G::LoadFile(const std::string& fn)
{
	fstream f(fn);
	EXPECT_TRUE((bool)f);
	adjs.assign(DSP2NodeCount, vector<Edge>());
	nodes.assign(DSP2NodeCount, Node());
	string s;
	char ch;
	int u, v, w;
	while (getline(f, s))
	{
		istringstream iss(s);
		iss >> u;
		auto& adju = adjs[u - 1];
		while (iss >> v >> ch >> w)
		{
			adju.emplace_back(v - 1, w);
		}
	}
}

void DSP2G::UpdateNearest(int n)
{
	// update adjs of u: 
	// smaller SP dist? -> SP dist, parent
	auto& u = nodes[n];
	for (auto& vEdge : adjs[n])
	{
		auto& vNode = nodes[vEdge.v];
		if (vNode.v)
		{
			continue;
		}
		if (vEdge.w + u.s < vNode.s)
		{
			vNode.s = vEdge.w + u.s;
			vNode.p = n;
		}
	}
}

int DSP2G::SelectNearest(void)
{
	// select unvisited, nearest node (min SP dist)
	int sel = -1;
	int len = DSP2MaxLen + 1;
	auto length = nodes.size();
	for (size_t i = 0; i < length; i++)
	{
		auto& node = nodes[i];
		if (node.v)
		{
			continue;
		}
		if (node.s < len)
		{
			len = node.s;
			sel = i;
		}
	}
	return sel;
}

void DSP2G::ShortestPath(void)
{
	auto& src = nodes[DSP2Src];
	src.p = -1;
	src.s = 0;
	int sel = -1;
	while ((sel = SelectNearest()) != -1)
	{
		auto& nSel = nodes[sel];
		nSel.v = true;
		UpdateNearest(sel);
//		PrintDist();
	}
}

string DSP2G::Result(void)
{
	stringstream ss;
	auto len = DSP2Targets.size();
	ss << nodes[DSP2Targets.front()].s;
	for (size_t i = 1; i < len; i++)
	{
		ss << "," << nodes[DSP2Targets[i]].s;
	}
	return ss.str();
}

string DijkstraShortestPath2(const string& fn)
{
	DSP2G g;
	g.LoadFile(fn);
	g.ShortestPath();
	return g.Result();
}

void DijkstraShortestPath2Test8Node(void)
{
	DSP2NodeCount = 8;
	// will exception when call g.Result();
	auto res = DijkstraShortestPath2("data\\wk6-test1-8.txt");
}

void DijkstraShortestPath2(void)
{
	int e = 0;
	auto v = BeaunusTestCase("course2\\assignment2Dijkstra", "C:\\Users\\user\\Documents\\GitHub\\stanford-algs-testcase\\testCases");
	for (auto i : v)
	{
		auto res = DijkstraShortestPath2(i.input);
		if (res != i.result)
		{
			cout << " * " << i.stem << " failed: " << res << " to " << i.result << endl;
			++e;
			continue;
		}
		cout << i.stem << " passed." << endl;
	}
	FinalTestResult(e);
}