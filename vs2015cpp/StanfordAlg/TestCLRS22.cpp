#include "common.h"

/*
test for graph present in CLRS 22
all nodes index is 0-based.
DFS: u.d 节点发现时间 u.f 节点完成时间。如果无环，u.f倒序为拓扑排序
SCC算法：
	1. DFS计算G.u.f
	2. 计算G的转置T
	3. 按照G.u.f倒序计算DFS(T)
	4. T的深度优先森林即SCC
*/

void TestBfs(void);
void TestDfs(void);
void TestScc(void);

void TestClrs22(void)
{
// 	TestBfs();
// 	TestDfs();
	TestScc();
}


using namespace std;
// graph with adjacent array
// baseOffset: node index offset in file present
class GraphAdjClrs22
{
private:
	struct Node
	{
		int i = -1; // node name (index)
		int p = -1; // parent
		int d = -1; // search start time
		int f = -1; // search end time

		Node(int _i) : i(_i) {};
	};

	vector<bool> visited; // search mark
	vector<Node> nodes; // node info
	vector<vector<int>> adjacents; // node adjacent array
	vector<int> visitSeq; // discover seq
	vector<int> finishSeq; // seq when finish (dfs)
	vector<int> loadSeq; // seq when read file
	bool hasCycle = false;
	int time = 0; // visit time
	int nodeCount = 0;
	void ClearAllNodes(int nNode);
	void ResetAssistData(void);
public:
	bool LoadFile(const std::string& fn, int nNode, int baseOffset = 0);
	void Bfs(int startIdx);
	void PrintNodes(int baseOffset = 0);
	void Dfs(void);
	void DfsByLoadSeq(void);
	void DfsVisit(GraphAdjClrs22::Node& u);
	void PrintFinishSeq(int baseOffset = 0);
	bool HasCycle(void);

	

	vector<int> Adj(int x) { return adjacents[x]; }
};

//////////////////////////////////////////////////////////////////////////
// GraphAdjClrs22 functions
bool GraphAdjClrs22::LoadFile(const std::string& fn, int nNode, int baseOffset /*= 0*/)
{
	ClearAllNodes(nNode);
	ifstream f(fn);
	if (!f)
	{
		cout << "open file error: " << fn;
		return false;
	}
	int idx = 0;
	int u, v;
	int x, y;
	vector<bool> loaded(nNode);
	while (f >> u >> v)
	{
		++idx;
		if (u == v)
		{
			cout << "\t**node cycle found: " << u << " at line: " << idx << endl;
			continue;
		}
		x = u - baseOffset; y = v - baseOffset;
		if (!loaded[x])
		{
			loadSeq.push_back(x);
			loaded[x] = true;
		}
		auto& adj = adjacents[x];
		if (find(adj.begin(), adj.end(), y) != adj.end())
		{
			cout << "\t**node dup found: " << u << ", " << v << " at line: " << idx << endl;
			continue;
		}
		adj.push_back(y);
	}

	return true;
}

void GraphAdjClrs22::Bfs(int startIdx)
{
	ResetAssistData();
	queue<int> q;

	auto& nodeStart = nodes[startIdx];
	visited[nodeStart.i] = true;
	nodeStart.d = 0;
	visitSeq.push_back(nodeStart.i);
	q.push(nodeStart.i);
	while (!q.empty())
	{
		auto i = q.front();
		auto& u = nodes[i];
		q.pop();
		auto& adj = adjacents[i];
		for (auto a : adj)
		{
			if (!visited[a])
			{
				auto& v = nodes[a];
				v.p = u.i;
				v.d = u.d + 1;
				visited[v.i] = true;
				visitSeq.push_back(v.i);
				q.push(v.i);
			}
		}
	}
}
void GraphAdjClrs22::PrintNodes(int baseOffset /*= 0*/)
{
	cout << "Nodes: i/p/d";
	if (nodes.front().f != -1)
	{
		cout << "/f";
	}
	cout << endl;
	for (auto& n : nodes)
	{
		cout << n.i + baseOffset << "/" << n.p + baseOffset << "/" << n.d;
		if (n.f != -1)
		{
			cout << "/" << n.f;
		}
		cout << ", ";
	}
	cout << endl << "SEQ:" << endl;
	for (auto i : visitSeq)
	{
		cout << i + baseOffset << " ";
	}
	cout << endl;
}


void GraphAdjClrs22::PrintFinishSeq(int baseOffset /*= 0*/)
{
	cout << "Topological:" << endl;
	for (auto it = finishSeq.rbegin(); it != finishSeq.rend(); ++it)
	{
		cout << *it + baseOffset << " ";
	}
	cout << endl;
}


void GraphAdjClrs22::Dfs()
{
	ResetAssistData();	
	for (auto& u : nodes)
	{
		if (!visited[u.i])
		{
			DfsVisit(u);
		}
	}
}

void GraphAdjClrs22::DfsByLoadSeq()
{
	ResetAssistData();
	for (auto ui: loadSeq)
	{
		auto& u = nodes[ui];
		if (!visited[u.i])
		{
			DfsVisit(u);
		}
	}
}

void GraphAdjClrs22::DfsVisit(GraphAdjClrs22::Node& u)
{
	u.d = ++time;
	visited[u.i] = true;
	visitSeq.push_back(u.i);
	for (auto& vi : adjacents[u.i])
	{
		if (!hasCycle && visited[vi] && nodes[vi].f == -1)
		{
			hasCycle = true;
		}
		if (!visited[vi])
		{
			auto& v = nodes[vi];
			v.p = u.i;
			DfsVisit(v);
		}
	}
	u.f = ++time;
	finishSeq.push_back(u.i);
}

bool GraphAdjClrs22::HasCycle(void)
{
	if (hasCycle)
	{
		cout << "has cycle." << endl;
	}
	return hasCycle;
}

void GraphAdjClrs22::ClearAllNodes(int nNode)
{
	loadSeq.clear();
	adjacents.assign(nNode, vector<int>());
	for (size_t i = 0; i < nNode; i++)
	{
		nodes.push_back(i);
	}
	nodeCount = nNode; 
	ResetAssistData();
}
void GraphAdjClrs22::ResetAssistData(void)
{
	visited.assign(nodeCount, false);
	finishSeq.clear();
	for (size_t i = 0; i < nodeCount; i++)
	{
		nodes[i] = i;
	}
	time = 0;
	hasCycle = false;
}

//////////////////////////////////////////////////////////////////////////
// functions

void TestBfs(string fn, int n)
{
	cout << "file: " << fn << endl;
	GraphAdjClrs22 g;
	g.LoadFile(fn, n, 1);
	g.Bfs(1);
	g.PrintNodes(1);
	cout << endl;
}
void TestBfs(void)
{
	TestBfs("data\\clrs22-b1-8.txt", 8);
// 	1/2/1, 2/0/0, 3/6/2, 4/3/3, 5/1/2, 6/2/1, 7/6/2, 8/7/3,
// 	2 1 6 5 3 7 4 8
}

void TestDfs(string fn, int n)
{
	cout << "file: " << fn << endl;
	GraphAdjClrs22 g;
	g.LoadFile(fn, n, 1);
	g.DfsByLoadSeq();
	g.PrintNodes(1);
	g.PrintFinishSeq(1);
	g.HasCycle();
	cout << endl;
}

void TestDfs(void)
{
	TestDfs("data\\clrs22-d1-6.txt", 6);
// 	**node cycle found: 6 at line: 8
// 	1/0/1/8, 2/1/2/7, 3/0/9/12, 4/5/4/5, 5/2/3/6, 6/3/10/11,
// 	1 2 5 4 3 6
//	3 6 1 2 5 4
	// D2 D3 D4为同一副图。D2 D4输入顺序不同。D2 D3顶点名和输入顺序都不同
	TestDfs("data\\clrs22-d2-8.txt", 8);
// 	1/0/1/10, 2/0/11/16, 3/2/12/13, 4/2/14/15, 5/6/4/5, 6/7/3/6, 7/1/2/9, 8/7/7/8,
// 	1 7 6 5 8 2 3 4
//	2 4 3 1 7 8 6 5
	TestDfs("data\\clrs22-d3-8.txt", 8);
// 	1/0/1/8, 2/5/3/6, 3/0/9/10, 4/0/11/16, 5/1/2/7, 6/2/4/5, 7/4/12/13, 8/4/14/15,
// 	1 5 2 6 3 4 7 8
//	4 8 7 3 1 5 2 6
	TestDfs("data\\clrs22-d4-8.txt", 8);
// 	1/0/9/10, 2/0/11/16, 3/2/12/13, 4/2/14/15, 5/6/2/7, 6/0/1/8, 7/5/3/6, 8/7/4/5,
// 	6 5 7 8 1 2 3 4
//	2 4 3 1 6 5 7 8
	TestDfs("data\\clrs22-d5-8.txt", 8);
//	1/0/1/10, 2/0/11/16, 3/2/12/13, 4/2/14/15, 5/6/4/5, 6/7/3/6, 7/1/2/9, 8/7/7/8,
//	1 7 6 5 8 2 3 4
//	2 4 3 1 7 8 6 5
	TestDfs("data\\clrs22-d6-8.txt", 8);
//	1/0/9/10, 2/0/11/16, 3/2/12/13, 4/2/14/15, 5/6/2/3, 6/0/1/4, 7/0/5/8, 8/7/6/7,
//	6 5 7 8 1 2 3 4
//	2 4 3 1 7 8 6 5
}


//////////////////////////////////////////////////////////////////////////
class GraphAdjScc
{
	struct Node
	{
		int i = -1; // node name (index)
		int p = -1; // parent
		int d = -1; // search start time
		int f = -1; // search end time

		Node(int _i) : i(_i) {};
	};

	vector<bool> visited;
	vector<int> loadSeq;
	vector<int> visitSeq;
	vector<int> finishSeq;
	vector<int> visitSeqPass1;
	vector<int> finishSeqPass1;
	vector<int> sccGroup;
	bool	satFail = false ;
	unordered_map<int, vector<int>> sccMap;
	vector<Node> nodes;
	vector<Node> nodesPass1;
	vector<vector<int>> adjacents;
	vector<vector<int>> adjacentsRev;
	int time = 0; // time for dfs
	
public:
private:
	void Clear(int nNode);
	void ResetAssist(void);
	void Dfs(vector<vector<int>>& adjs, const vector<int>& dfsSeq);
	void DfsVisit(vector<vector<int>>& adjs, Node& u);
	int  GetNodeGroup(int ui);
	int  Var2NodeIdx(int x, int baseOffset)
	{
		if (x >= 0)
		{
			return 2 * (x - baseOffset);
		}
		else
		{
			return -2 * (x + baseOffset) + 1;
		}
	};
public:
	// load file and generate reverse graph
	bool LoadFile(const string& fn, int nNode, int baseOffset);
	bool LoadFile2Sat(const string& fn, int baseOffset);

	void InsertEdge(vector<int> &loaded, int x, int y, int u, int v, int idx);

	void SearchScc(void);
	void PrintNodes(int baseOffset);
	void PrintSccs(int baseOffset);
	bool SatFail() const { return satFail; }
};



void GraphAdjScc::Clear(int nNode)
{
	nodes.clear();
	for (size_t i = 0; i < nNode; i++)
	{
		nodes.push_back(i);
	}
	adjacents.assign(nNode, vector<int>());
	adjacentsRev.assign(nNode, vector<int>());
	loadSeq.clear();
	ResetAssist();
}


void GraphAdjScc::ResetAssist(void)
{
	auto len = nodes.size();
	visited.assign(len, false);
	sccGroup.assign(len, -1);
	visitSeq.clear();
	finishSeq.clear();
	satFail = false;
	time = 0;
}

int GraphAdjScc::GetNodeGroup(int ui)
{
	while (nodes[ui].p != -1)
	{
		ui = nodes[ui].p;
	}
	return ui;
}


bool GraphAdjScc::LoadFile(const string& fn, int nNode, int baseOffset)
{
	ifstream f(fn);
	if (!f)
	{
		cout << "open file error: " << fn << endl;
		return false;
	}
	Clear(nNode);
	int u, v, x, y, idx = 0;
	vector<int> loaded(nNode, false);
	while (f >> u >> v)
	{
		++idx;
		if (u == v)
		{
			cout << "\t**node cycle found: " << u << " at line: " << idx << endl;
			continue;
		}
		x = u - baseOffset;
		y = v - baseOffset;
		if (!loaded[x])
		{
			loadSeq.push_back(x);
			loaded[x] = true;
		}
		auto& adjx = adjacents[x];
		if (find(adjx.begin(), adjx.end(), y) != adjx.end())
		{
			cout << "\t**node dup found: " << u << ", " << v << " at line: " << idx << endl;
		}
		else
		{
			adjx.push_back(y);
		}
		auto& adjy = adjacentsRev[y];
		if (find(adjy.begin(), adjy.end(), x) != adjy.end())
		{
			cout << "\t**rev node dup found: " << u << ", " << v << " at line: " << idx << endl;
		}
		else
		{
			adjy.push_back(x);
		}		
	}

	return true;
}


bool GraphAdjScc::LoadFile2Sat(const string& fn, int baseOffset)
{

	ifstream f(fn);
	if (!f)
	{
		cout << "open file error: " << fn << endl;
		return false;
	}
	int nNode = 0;
	if (!(f >> nNode))
	{
		cout << "read file error: " << fn << endl;
	}
	nNode *= 2;
	Clear(nNode);
	int u, v, x, y, idx = 0;
	vector<int> loaded(nNode, false);
	while (f >> u >> v)
	{
		++idx;
		// svt : -u -> v, -v -> u
		// k>0 -> 2k , k<0 > -2k+1
		x = Var2NodeIdx(-u, baseOffset);
		y = Var2NodeIdx(v, baseOffset);
		InsertEdge(loaded, x, y, u, v, idx);
		x = Var2NodeIdx(-v, baseOffset);
		y = Var2NodeIdx(u, baseOffset);
		InsertEdge(loaded, x, y, u, v, idx);
	}

	return true;
}


void GraphAdjScc::InsertEdge(vector<int> &loaded, int x, int y, int u, int v, int idx)
{
	if (!loaded[x])
	{
		loadSeq.push_back(x);
		loaded[x] = true;
	}
	auto& adjx = adjacents[x];
	if (find(adjx.begin(), adjx.end(), y) != adjx.end())
	{
//		cout << "\t**node dup found: " << u << ", " << v << " at line: " << idx << endl;
	}
	else
	{
		adjx.push_back(y);
	}
	auto& adjy = adjacentsRev[y];
	if (find(adjy.begin(), adjy.end(), x) != adjy.end())
	{
//		cout << "\t**rev node dup found: " << u << ", " << v << " at line: " << idx << endl;
	}
	else
	{
		adjy.push_back(x);
	}
}

void GraphAdjScc::Dfs(vector<vector<int>>& adjs, const vector<int>& dfsSeq)
{
	ResetAssist();
	for (auto i : dfsSeq)
	{
		auto& u = nodes[i];
		if (!visited[i])
		{
			DfsVisit(adjs, u);
		}
	}
}


void GraphAdjScc::DfsVisit(vector<vector<int>>& adjs, GraphAdjScc::Node& u)
{
	u.d = ++time;

	auto ui = u.i;
	visitSeq.push_back(ui);
	visited[ui] = true;

	for (auto vi : adjs[ui])
	{
		if (visited[vi])
		{
			continue;
		}
		auto& v = nodes[vi];
		v.p = ui;
		auto gi = sccGroup[vi] = GetNodeGroup(ui);
		
		// 2-sat check
		auto vj = (vi & 1) ? vi - 1 : vi + 1;
		auto gj = sccGroup[vj];
		if ((gj == -1) && (gi == vj))
		{
			satFail = true;			
		}
		if ((gj != -1) && (gi == gj))
		{
			satFail = true;
		}
		
		DfsVisit(adjs, v);
	}
	finishSeq.push_back(ui);
	u.f = ++time;
}


void GraphAdjScc::SearchScc(void)
{
	Dfs(adjacents, loadSeq);
	visitSeqPass1 = visitSeq;
	finishSeqPass1 = finishSeq;
	nodesPass1 = nodes;
	vector<int> revFinishSeq;
	for (auto it = finishSeq.crbegin(); it != finishSeq.crend(); ++it)
	{
		revFinishSeq.push_back(*it);
	}
	for (auto& n : nodes)
	{
		n = n.i;
	}
	Dfs(adjacentsRev, revFinishSeq);
	auto length = sccGroup.size();
	for (size_t i = 0; i < length; i++)
	{
		auto g = sccGroup[i];
		if (g == -1)
		{
			g = i;
		}
		sccMap[g].push_back(i);
	}
}

void GraphAdjScc::PrintNodes(int baseOffset)
{

	cout << "Nodes: i/p/d/f";
	cout << endl;
	for (auto& n : nodesPass1)
	{
		cout << n.i + baseOffset << "/" << n.p + baseOffset << "/" << n.d << "/" << n.f << ", ";
	}
	cout << endl << "SEQ:" << endl;
	for (auto i : visitSeqPass1)
	{
		cout << i + baseOffset << " ";
	}
	cout << endl;
	cout << "Topological:" << endl;
	for (auto it = finishSeqPass1.rbegin(); it != finishSeqPass1.rend(); ++it)
	{
		cout << *it + baseOffset << " ";
	}
	cout << endl;
}


void GraphAdjScc::PrintSccs(int baseOffset)
{
	cout << "SCC:" << endl;
	for (auto& p : sccMap)
	{
		cout << p.first + baseOffset << ": ";
		for (auto i : p.second)
		{
			cout << i + baseOffset << " ";
		}
		cout << endl;
	}
}

void TestScc(string fn, int n)
{
	cout << "file: " << fn << endl;
	GraphAdjScc g;
	g.LoadFile(fn, n, 1);
	g.SearchScc();
	g.PrintNodes(1);
	g.PrintSccs(1);
	cout << endl;
}

void TestScc(void)
{	
	TestScc("data\\clrs22-d1-6.txt", 6);
// 	**node cycle found: 6 at line: 8
// 	1/0/1/8, 2/1/2/7, 3/0/9/12, 4/5/4/5, 5/2/3/6, 6/3/10/11,
// 	1 2 5 4 3 6
//	3 6 1 2 5 4
	// D2 D3 D4为同一副图。D2 D4输入顺序不同。D2 D3顶点名和输入顺序都不同
	TestScc("data\\clrs22-d2-8.txt", 8);
// 	1/0/1/10, 2/0/11/16, 3/2/12/13, 4/2/14/15, 5/6/4/5, 6/7/3/6, 7/1/2/9, 8/7/7/8,
// 	1 7 6 5 8 2 3 4
//	2 4 3 1 7 8 6 5
	TestScc("data\\clrs22-d3-8.txt", 8);
// 	1/0/1/8, 2/5/3/6, 3/0/9/10, 4/0/11/16, 5/1/2/7, 6/2/4/5, 7/4/12/13, 8/4/14/15,
// 	1 5 2 6 3 4 7 8
//	4 8 7 3 1 5 2 6
	TestScc("data\\clrs22-d4-8.txt", 8);
// 	1/0/9/10, 2/0/11/16, 3/2/12/13, 4/2/14/15, 5/6/2/7, 6/0/1/8, 7/5/3/6, 8/7/4/5,
// 	6 5 7 8 1 2 3 4
//	2 4 3 1 6 5 7 8
	TestScc("data\\clrs22-d5-8.txt", 8);
//	1/0/1/10, 2/0/11/16, 3/2/12/13, 4/2/14/15, 5/6/4/5, 6/7/3/6, 7/1/2/9, 8/7/7/8,
//	1 7 6 5 8 2 3 4
//	2 4 3 1 7 8 6 5
	TestScc("data\\clrs22-d6-8.txt", 8);
//	1/0/9/10, 2/0/11/16, 3/2/12/13, 4/2/14/15, 5/6/2/3, 6/0/1/4, 7/0/5/8, 8/7/6/7,
//	6 5 7 8 1 2 3 4
//	2 4 3 1 7 8 6 5
}


bool Test2Sat(const string& fn)
{
	cout << "file: " << fn << " ";
	GraphAdjScc g;
	g.LoadFile2Sat(fn, 1);
	g.SearchScc();
	cout << !g.SatFail() << endl;
	return !g.SatFail();
}
