#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int A1018MaxDist = 1000000;

class A1018AdjGraph
{
public:
	void ReadData(void);
	void Calc(void);
	int FindMinDist(void) const;
	void Update(const int u, const int v);
protected:
	struct Edge
	{
		int v = 0;
		int d = 0;

		Edge() : v(0), d(0) {};
		Edge(int _v, int _t) : v(_v), d(_t) {}
	};
	int nodes = 0;
	int edges = 0;
	int problemStation = 0;
	int capPerNode = 0;
	int capPerfect = 0;

	vector<vector<Edge>> adjs;
	vector<int> nodeBikes;

	vector<bool> visit;
	// 最短路径
	vector<int> dist;
	// 当前路径总数量
	vector<int> pathBikes;
	vector<int> sendBikes;
	vector<vector<int>> paths;
};


void A1018AdjGraph::ReadData(void)
{
	cin >> capPerNode >> nodes >> problemStation >> edges;
	capPerfect = capPerNode / 2;
	// count PBMC as 0
	++nodes;
	adjs.assign(nodes, vector<Edge>());
	nodeBikes.assign(nodes, 0);
	for (int i = 1; i < nodes; ++i)
	{
		cin >> nodeBikes[i];
	}
	for (int i = 0; i < edges; ++i)
	{
		int u, v, t;
		cin >> u >> v >> t;
		adjs[u].push_back(Edge(v, t));
		adjs[v].push_back(Edge(u, t));
	}
	dist.assign(nodes, A1018MaxDist);
	pathBikes.assign(nodes, A1018MaxDist);
	sendBikes.assign(nodes, A1018MaxDist);
	visit.assign(nodes, false);
	paths.assign(nodes, vector<int>());
}


void A1018AdjGraph::Calc(void)
{
	dist[0] = 0;
	int total = nodes;
	int last = 0;
	pathBikes[0] = 0;
	dist[0] = 0;
	do
	{
		int next = FindMinDist();
		visit[next] = true;
		Update(last, next);
		last = next;
	} while (--total > 0);

	auto totalBike = pathBikes[problemStation];
	auto& procPath = paths[problemStation];

	auto needBike = procPath.size() * capPerfect;

	if (needBike > totalBike)
	{
		if (needBike - totalBike != sendBikes[problemStation])
		{
			throw 0;
		}
		cout << needBike - totalBike << " 0";
		for (auto n : procPath)
		{
			cout << "->" << n;
		}
		cout << " 0" << endl;
	}
	else
	{
		cout << "0 0";
		for (auto n : procPath)
		{
			cout << "->" << n;
		}
		cout << " " << totalBike - needBike << endl;
	}
}

int A1018AdjGraph::FindMinDist(void) const
{
	int idx = -1;
	int minDist = A1018MaxDist + 1;
	int maxBile = 0;
	for (int i = 0; i < nodes; ++i)
	{
		if (visit[i])
		{
			continue;
		}
		if ((dist[i] < minDist) ||
			(dist[i] == minDist && pathBikes[i] > maxBile))
		{
			maxBile = pathBikes[i];
			minDist = dist[i];
			idx = i;
		}
	}
	if (idx == -1)
	{
		throw 0;
	}
	return idx;
}

void A1018AdjGraph::Update(const int last, const int next)
{
	auto edgeu = adjs[next];
	auto distu = dist[next];
	for (auto& e : edgeu)
	{
		auto v = e.v;
		auto distuv = distu + e.d;
		auto bikeuv = pathBikes[next] + nodeBikes[v];
		auto sendv = capPerfect * (int)(paths[next].size() + 1) - bikeuv;
		if (distuv < dist[v] ||
			(distuv == dist[v] && sendv < sendBikes[v]))
		{
			dist[v] = distuv;
			pathBikes[v] = bikeuv;
			sendBikes[v] = sendv;
			paths[v] = paths[next];
			paths[v].push_back(v);
		}
	}
}
// rename this to main int PAT
int main(void)
{
	A1018AdjGraph g;
	g.ReadData();
	g.Calc();

	return 0;
}