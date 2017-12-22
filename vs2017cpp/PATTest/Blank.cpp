#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <deque>


using namespace std;

struct T1001E
{
	int u = 0;
	int v = 0;
	int64_t c = 0;
	T1001E(int _u, int _v, int64_t _c)
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
	int64_t CityCost(int iCity);
	int64_t BuildCost(vector<int>& v1, vector<int>& v2);
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

	int64_t Prim(void);
	int64_t KruskalWithUnionfind(void);
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
	int64_t c;
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
	int64_t maxCost = 0;
	int64_t cost = 0;
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

int64_t T1001G::CityCost(int iCity)
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
	int64_t buildcost = 0;
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
			groupEdges.push_back(T1001E(i, j, buildcost));
		}
	}

	T1001Mst mst(groupEdges, nCC);
	return mst.Prim();

	// MST for groupCC
	vector<T1001E*> pgEdges;
	for (auto& e : groupEdges)
	{
		pgEdges.push_back(&e);
	}
	sort(pgEdges.begin(), pgEdges.end(), T1001ELess);
	int totalCost = 0;

	unordered_set<int> setGroup;
	bool hasU, hasV;
	int geSize = (int)pgEdges.size();
	for (int i = 0; i < geSize; ++i)
	{
		T1001E& e = *pgEdges[i];
		hasU = setGroup.find(e.u) != setGroup.end();
		hasV = setGroup.find(e.v) != setGroup.end();
		if (hasU && hasV) { continue; }
		totalCost += e.c;
		if (!hasU) { setGroup.insert(e.u); }
		if (!hasV) { setGroup.insert(e.v); }
	}
	return totalCost;
}

int64_t T1001G::BuildCost(vector<int>& v1, vector<int>& v2)
{
	int64_t cost = 0x7FFFFFFFFFFFFFFF;
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
	if (cost == 0x7FFFFFFF)
	{
		abort();
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


int64_t T1001Mst::Prim(void)
{
	const int64_t MAXDIST = 0x7fffffffffffffff;
	vector<bool> visited(nNodes, false);
	vector<int64_t>  dist(nNodes, MAXDIST);
	vector<vector<const T1001E*>> adjs(nNodes);
	for (auto& pe : *pvtEdges)
	{
		adjs[pe.u].push_back(&pe);
		adjs[pe.v].push_back(&pe);
	}

	int left = nNodes;
	dist[0] = 0;
	int u;
	int64_t total = 0;
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
// rename this to main int PAT
int main(void)
{
	T1001G g;
	g.Read();
	g.SearchCity();
	return 0;
}
