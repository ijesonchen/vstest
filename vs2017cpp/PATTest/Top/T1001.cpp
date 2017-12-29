/*
1001. Battle Over Cities - Hard Version (35)

sln1: 穷举+BFS, MST
	19/35 pt2,3 异常(buildCost未找到路径)， pt5 超时
	1. 图正常路径、毁坏路径分别保存
		vector<vector<int>> adjGood
		vector<vector<Edge>> adjBad
	2. 对任意城市i：
		a) 标记该城市后，BFS对剩余城市求连通分量
			map<int, vector<int>> mapCC
		b) 连通个数为1：无需重建
		c) 对任意两个强连通分量，从毁坏路径中选取
		最短的连接路径，记录cost，生成连通分量图。
		d) 求连通分量图的最小生成树，作为i城市对应的花费
	3. 记录最高花费及对应城市(同一花费可能多个）
sln1-1:
	修正MST错误
	cityCost可能返回0x7FFFFFFF，(不是任意两个CC都有通路）取消检查abort
	25/35 pt3：错误 pt5:超时
sln1-2:
	改用int64记录cost未改善
sln1-test:
	最大cost不超过100W
sln1-3:修复星型bug tc-4。未见改进
	
	MST Prime/Kruskal算法已测试通过。


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
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <deque>
#include "..\..\..\vs2015cpp\StanfordAlg\common.h"


using namespace std;

const int T1001MAXDIST = 0x7fffffff;

struct T1001E
{
	int u = 0;
	int v = 0;
	int c = 0;
	T1001E(int _u, int _v, int _c)
		:u(_u), v(_v), c(_c) {};

	int t(int s) const { return s == u ? v : u; }

	bool operator<(const T1001E& e) const
	{
		return c < e.c;
	}
};

bool T1001ELess(const T1001E* const p1, const T1001E* const p2)
{
	return *p1 < *p2;
}

class T1001G
{
public:
	void Read(void);
	void SearchCity();
private:
	// do not return 0;
	int CityCost(int iCity);
	int BuildCost(vector<int>& v1, vector<int>& v2);
	void Bfs(int start);

	// for BFS group
	void ResetBfsAssist(int ibad);
	int badCity = -1;
	unordered_map<int, vector<int>> mapCC;
	vector<bool> visited;

	vector<vector<int>> adjGood;
	vector<vector<T1001E>> adjBad;
	int cityCount = 0;
};

class T1001Mst
{
public:
	T1001Mst(const vector<T1001E>& v, int n)
		: pvtEdges(&v), nNodes(n) {};

	int Prim(void);
	int KruskalWithUnionfind(void);
private:
	const vector<T1001E>* const pvtEdges;
	int nNodes;
};


void T1001G::Read(void)
{
	int n, m;
	cin >> n >> m;
	cityCount = n;
	adjGood.assign(n, vector<int>());
	adjBad.assign(n, vector<T1001E>());
	int u, v;
	int c;
	bool ok;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> c >> ok;
		if (u == v) { continue; }
		--u; --v;
		if (ok)
		{
			adjGood[u].emplace_back(v);
			adjGood[v].emplace_back(u);
		}
		else
		{
			adjBad[u].emplace_back(T1001E(u, v, c));
			adjBad[v].emplace_back(T1001E(v, u, c));
		}
	}
}

void T1001G::SearchCity(void)
{
	int maxCost = 0;
	int cost = 0;
	vector<int> cities;
	for (int i = 0; i < cityCount; ++i)
	{
		cost = CityCost(i);
		if (cost > maxCost)
		{
			maxCost = cost;
			cities.clear();
			cities.push_back(i);
		}
		else if (cost == maxCost)
		{
			cities.push_back(i);
		}
	}

	// output result
	if (cities.empty())
	{
		cout << "0" << endl;
		return;
	}
	set<int> s;
	for (auto i : cities)
	{
		s.insert(i);
	}
	auto its = s.begin();
	cout << *its + 1;
	for (++its; its != s.end(); ++its)
	{
		cout << " " << *its + 1;
	}
	cout << endl;
}

void T1001G::Bfs(int start)
{
	vector<int> vleft;
	vleft.push_back(start);
	while (!vleft.empty())
	{
		int next = vleft.back();
		vleft.pop_back();
		auto& subs = adjGood[next];
		for (auto v : subs)
		{
			if (visited[v])
			{
				continue;
			}
			visited[v] = true;
			vleft.push_back(v);
			mapCC[start].push_back(v);
		}
	}
}

int T1001G::CityCost(int iCity)
{
	ResetBfsAssist(iCity);
	for (int i = 0; i < cityCount; ++i)
	{
		if (i == badCity) { continue; }
		if (!visited[i])
		{
			visited[i] = true;
			mapCC[i].push_back(i);
			Bfs(i);
		}
	}

	int msize = (int)mapCC.size();
	if (msize == 1)
	{
		return -1;
	}
	// mapCC -> graphCC
	int buildcost = 0;
	vector<T1001E> groupEdges;
	vector<vector<int>*> vCC;
	for (auto& it : mapCC)
	{
		vCC.push_back(&(it.second));
	}
	int nCC = (int)vCC.size();
	for (int i = 0; i < nCC; ++i)
	{
		for (int j = i + 1; j < nCC; ++j)
		{
			buildcost = BuildCost(*vCC[i], *vCC[j]);
			if (buildcost != T1001MAXDIST)
			{
				groupEdges.push_back(T1001E(i, j, buildcost));
			}
		}
	}

	if (groupEdges.empty())
	{
		return T1001MAXDIST;
	}

	T1001Mst mst(groupEdges, nCC);
	return mst.KruskalWithUnionfind();
	return mst.Prim();
}

int T1001G::BuildCost(vector<int>& v1, vector<int>& v2)
{
	int cost = T1001MAXDIST;
	for (auto const u : v1)
	{
		vector<T1001E>& edges = adjBad[u];
		for (const auto e : edges)
		{
			if (e.v == badCity)
			{
				continue;
			}
			for (const auto v : v2)
			{
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
	return cost;
}


void T1001G::ResetBfsAssist(int ibad)
{
	mapCC.clear();
	visited.assign(cityCount, false);
	badCity = ibad;
	visited[badCity] = true;
}


int T1001Mst::Prim(void)
{
	const int MAXDIST = T1001MAXDIST;
	vector<bool> visited(nNodes, false);
	vector<int>  dist(nNodes, MAXDIST);
	vector<vector<const T1001E*>> adjs(nNodes);
	for (auto& pe : *pvtEdges)
	{
		adjs[pe.u].push_back(&pe);
		adjs[pe.v].push_back(&pe);
	}

	int left = nNodes;
	dist[0] = 0;
	int u;
	int total = 0;
	while (--left >= 0)
	{
		u = (int)(min_element(dist.begin(), dist.end()) - dist.begin());
		visited[u] = true;
		total += dist[u];
		// reset dist[u] as remove u
		dist[u] = MAXDIST;
		// update dist
		auto vEdge = adjs[u];
		for (auto pe : vEdge)
		{
			auto t = pe->t(u);
			if (visited[t]) { continue; }
			if (pe->c < dist[t]) { dist[t] = pe->c; }
		}
	}

	return total;
}

tuple<int,int>
	GetGroupId(const vector<int>& group, int u)
{
	int iter = 0;
	while (group[u] != -1)
	{
		++iter;
		u = group[u];
	}
	return make_tuple(u,iter);
}

// 查询较少，路径压缩效果不明显
tuple<int, int>
GetGroupIdCompressed(vector<int>& group, int u)
{
	int iter = 0;
	int v = u;
	while (group[u] != -1)
	{
		++iter;
		u = group[u];
	}

	int temp;
	while ((temp = group[v]) != -1)
	{
		group[v] = u;
		v = temp;
	}
	return make_tuple(u, iter);
}
int T1001Mst::KruskalWithUnionfind(void)
{
	vector<int> group(nNodes, -1);
	vector<const T1001E*> vpEdge;
	for (auto& e : *pvtEdges)
	{
		vpEdge.push_back(&e);
	}
	sort(vpEdge.begin(), vpEdge.end(), T1001ELess);

	int total = 0;
	int left = nNodes - 1;
	for (auto pe : vpEdge)
	{
		auto u = pe->u;
		auto v = pe->v;
		int gu, iu, gv, iv;
		std::tie(gu, iu) = GetGroupId(group, u);
		std::tie(gv, iv) = GetGroupId(group, v);
		if (gu == gv) { continue; }
		if (iu < iv) { group[gu] = gv; }
				else { group[gv] = gu; }
		total += pe->c;
		if (--left <= 0) { break; }
	}

	return total;
}

string PrimMst(const string& fn)
{
	RedirCin(fn);
	int n, m;
	cin >> n >> m;
	int u, v, w;
	vector<T1001E> vEdge;
	while (cin >> u >> v >> w)
	{
		vEdge.push_back(T1001E(u - 1, v - 1, w));
	}
	T1001Mst g(vEdge, n);
	auto mst = g.Prim();
	return ToStr(mst);
}

string KruskalMst(const string& fn)
{
	RedirCin(fn);
	int n, m;
	cin >> n >> m;
	int u, v, w;
	vector<T1001E> vEdge;
	while (cin >> u >> v >> w)
	{
		if (u==v) continue;
		vEdge.push_back(T1001E(u - 1, v - 1, w));
	}
	T1001Mst g(vEdge, n);
	auto mst = g.KruskalWithUnionfind();
	return ToStr(mst);
}

// rename this to main int PAT
int T1001Func(void)
{
	T1001G g;
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

void MstTest1(void)
{
	Tick2();
// 	cout << "RunPrimMst" << endl;
// 	RunBeaunusTest(PrimMst, "course3\\assignment1SchedulingAndMST\\question3");
// 	Tock2();
// 	Tick();
	cout << endl << endl << "RunBeauKruskalMstnusTest" << endl;
	RunBeaunusTest(KruskalMst, "course3\\assignment1SchedulingAndMST\\question3");
	Tock2();
}

void MstTest2(void)
{
	string root = "..\\..\\vs2015cpp\\StanfordAlg\\data\\";
	auto s1 = KruskalMst(root + "zwk9-edges-test1.txt");
	auto s2 = KruskalMst(root + "zwk9-edges-test2.txt");
	auto s3 = KruskalMst(root + "zwk9-edges.txt");
}

void MstTest3(void)
{
	auto root = BeaunusTestRootDir + "\\course3\\assignment1SchedulingAndMST\\question3\\";
	auto s1 = KruskalMst(root + "input_random_7_20.txt");
}

void T1001(void)
{
	MstTest1();
	return;
	T1001("data\\T1001-1.txt"); // 1 2
	T1001("data\\T1001-2.txt"); // 0
	T1001("data\\T1001-3.txt"); // 3
	T1001("data\\T1001-4.txt"); // 4   星型
	T1001("data\\T1001-5.txt"); // 4 5 杠铃型
}
