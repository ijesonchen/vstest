#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <unordered_set>
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <sstream>
#include <random>
#include <cmath>
#include <thread>
#include <chrono>
#include <tuple>
#include "common.h"

using namespace std;

extern uint32_t VEC_COUNT;
extern bool PRINT_CONTENT;

//////////////////////////////////////////////////////////////////////////
// vec list graph

class HeadEdges
{
public:
	HeadEdges(int32_t h) : head(h), edges(VEC_COUNT + 1, 0) {};

	void Add(int32_t v)
	{
		if (v >= edges.size())
		{
			abort();
		}
		++edges[0];
		++edges[v];
	}

	uint32_t E() const
	{
		return edges[0];
	}
public:
	int32_t head;
	vector <int32_t> edges; // 1-based. [0] stores edge count
};


class VVecList
{
public:
	VVecList(HeadEdges v)
	{
		nodes.push_back(v);
	}

	void Contract(VVecList& v)
	{
		nodes.insert(nodes.end(), v.nodes.begin(), v.nodes.end());

		RemoveSelfLoop();
	}

	void RemoveSelfLoop(void)
	{
		for (auto& h : nodes)
		{
			for (auto& n : nodes)
			{
				auto& e = n.edges[h.head];
				if (e)
				{
					n.edges[0] -= e;
					e = 0;
				}
			}
		}
	}

	uint32_t V() const
	{
		return nodes.size();
	};

	uint32_t E() const
	{
		int s = 0;
		for_each(nodes.begin(), nodes.end(), [&s](const HeadEdges& he) { s += he.edges[0]; });
		return s;
	};

	void Print(void)
	{
		if (!PRINT_CONTENT)
		{
			return;
		}
		cout << ">>>>" << endl;
		for (auto& he : nodes)
		{
			cout << he.head << " : ";
			for (auto& e: he.edges)
			{
				cout << e << " ";
			}
			cout << endl;
		}
	}
	void PrintHeads(void)
	{
		for (auto h : nodes)
		{
			cout << h.head << " ";
		}
	}

	void PrintEdgeCnt(void)
	{
		cout << " edge " << E() << " ";
	}

	bool HasV(int32_t v)
	{
		for (auto& n : nodes)
		{
			if (n.head == v)
			{
				return true;
			}
		}
		return false;
	}

	bool IsSingleNode(void) const
	{
		return nodes.size() == 1;
	}

public:
	vector <HeadEdges> nodes;
};

class VecListGraph
{
public:
	VecListGraph(const std::string filename)
	{
		fstream f(filename, ios::in);
		if (!f)
		{
			abort();
		}
		string s;
		uint32_t i = 0;
		while (getline(f, s))
		{
			stringstream ss(s);
			ss >> i;
			if (!i)
			{
				abort();
			}
			HeadEdges h(i);
			while (ss >> i)
			{
				h.Add(i);
			}
			VVecList v(h);
			vList.push_back(std::move(v));
		}
	}

	uint32_t V() const { return vList.size(); }
	uint32_t E() const
	{
		uint32_t cntE = 0;
		for_each(vList.begin(), vList.end(), [&cntE](const VVecList& v){ cntE += v.E(); });
		if (cntE & 1)
		{
			abort();
		}
		return cntE >> 1;
	}

	tuple<int32_t, int32_t> Contraction(void)
	{
		int32_t u = -1;
		int32_t v = -1;
		tie(u, v) = RSelEdge();
		
		auto pu = vList.end();
		auto pv = vList.end();
		int idx = 2;
		for (auto beg = vList.begin(); beg != vList.end(); ++beg)
		{
			if (!idx)
			{
				break;
			}
			if (beg->HasV(u))
			{
				pu = beg;
				--idx;
			}
			if (beg->HasV(v))
			{
				pv = beg;
				--idx;
			}
		}
		if (pu == vList.end() || pv == vList.end())
		{
			abort();
		}
		pu->Contract(*pv);
		vList.erase(pv);
		return make_tuple(u, v);
	}

	void Print(void)
	{
		if (!PRINT_CONTENT)
		{
			return;
		}
		for (auto& v : vList)
		{
			v.Print();
		}
	}

	bool HasSingleNode() const
	{
		for (auto& v : vList)
		{
			if (v.IsSingleNode())
			{
				return true;
			}
		}
		return false;
	}

	tuple<int32_t, int32_t> RSelEdge();

public:
	list<VVecList> vList;
};

tuple<int32_t, int32_t> VecListGraph::RSelEdge()
{
	random_device gen;
	uniform_int_distribution<int> dist(0, E() - 1);
	auto i = dist(gen);
	int32_t v1 = -1;
	int32_t v2 = -1;
	for (auto& v : vList)
	{
		if (i > v.E())
		{
			i -= v.E();
		}
		else
		{
			for (auto& n : v.nodes)
			{
				if (i > n.E())
				{
					i -= n.E();
				}
				else
				{
					auto& edges = n.edges;
					for (int32_t idx = 1; idx < edges.size(); ++idx)
					{
						if (edges[idx])
						{
							if (!i)
							{
								// found
								v1 = n.head;
								v2 = idx;

								return make_tuple(v1, v2);
								break;
							}
							else
							{
								--i;
							}
						}
					}
				}
			}
		}
	}

	if (v1 == -1)
	{
		abort();
	}
	return make_tuple(-1, -1);
}

//////////////////////////////////////////////////////////////////////////
// functions

void VecListSingleTest(void)
{
	PRINT_CONTENT = true;
	auto fileName = "data\\wk4-Test-MinCut-40-3.txt";

	int sleepSec = 1;
	int32_t vecCount = 40;
	VEC_COUNT = vecCount;
	auto vv = vecCount * vecCount;
	uint32_t loop = vv * vv;
	cout << "|||| " << fileName << " ** " << loop << endl;
	VecListGraph g(fileName);

	g.Print();

	while (g.V() > 2)
	{
		int32_t u = -1;
		int32_t v = -1;
		tie(u, v) = g.Contraction();
		cout << "selected " << u << " " << v << endl;
		g.Print();
	}

	cout << "cut " << g.E() << endl;

}

int32_t RunContract(VecListGraph g)
{
	g.Print();

	while (g.V() > 2)
	{
		int32_t u = -1;
		int32_t v = -1;
		tie(u, v) = g.Contraction();
		if (PRINT_CONTENT)
		{
			cout << "selected " << u << " " << v << endl;
		}
		g.Print();
	}

	auto vertics = g.V();
	auto edges = g.E();

	return edges;


	if (edges == 3)
	{
		cout << " found " << edges << endl;
		PRINT_CONTENT = true;
//		g.Print();
		PRINT_CONTENT = false;

		this_thread::sleep_for(chrono::seconds(3));
	}
}

void VecListMultiTest(void)
{
	PRINT_CONTENT = false;
	auto fileName = "data\\wk4-Test-MinCut-40-3.txt";

	int sleepSec = 1;
	int32_t vecCount = 40;
	VEC_COUNT = vecCount;
	auto vv = vecCount * vecCount;
	uint32_t loop = vv * vv;
	cout << "|||| " << fileName << " ** " << loop << endl;
	VecListGraph g(fileName);

	auto idx = 0;
	while (true)
	{
		cout << " loop " << ++idx << endl;
		RunContract(g);
		if (idx % 1024 == 0)
		{
			cout << " loop " << idx << endl;
		}
	}
}

void RunProgAssign(void)
{
	PRINT_CONTENT = false;
	auto fileName = "data\\wk4-kargerMinCut.txt";

	int sleepSec = 1;
	int32_t vecCount = 200;
	VEC_COUNT = vecCount;
	auto vv = vecCount * vecCount;
	uint32_t loop = vv * vv;
	cout << "|||| " << fileName << " ** " << loop << endl;
	VecListGraph g(fileName);

	int64_t idx = 0;
	int32_t mincut = 200 * 200;
	int64_t last = 0;
	while (true)
	{
		++idx;
		auto cut = RunContract(g);
		if (mincut > cut)
		{
			last = idx;
			cout << " loop " << idx << " min " << cut << " last " << mincut << " idx " << last << endl;
			mincut = cut;
			continue;
		}
		if (idx % 1024 == 0)
		{
			cout << " loop " << idx << " min " << mincut << " last " << last << endl;
		}
	}
}

void ProgAssignTestLoopCountWhenMincut(void)
{
	PRINT_CONTENT = false;
	auto fileName = "data\\wk4-kargerMinCut.txt";
	auto outputMax = 1000;

	int sleepSec = 1;
	int32_t vecCount = 200;
	VEC_COUNT = vecCount;
	cout << "|||| " << fileName << " ** " << endl;
	VecListGraph g(fileName);

	int32_t output = outputMax;
	int32_t mincut = 200 * 200;
	int32_t last = 0;
	int32_t idx = 0;
	vector<int32_t> vtFound;
	int32_t minLoop = ((uint32_t)-1) / 2;;
	int32_t maxLoop = 0;
	int64_t total = 0;
	while (true)
	{
		if (!--output)
		{
			output = outputMax;
			cout << "total " << total << " founds " << vtFound.size() << " min loop " << minLoop << " max loop " << maxLoop << endl;
			for (auto e : vtFound)
			{
				cout << e << " ";
			}
			cout << endl;
		}
		++idx;
		++total;
		auto cut = RunContract(g);
		if (cut ==17)
		{
			vtFound.push_back(idx);
			if (idx < minLoop) minLoop = idx;
			if (idx > maxLoop) maxLoop = idx;
			cout << "total " << total << " min loop " << minLoop << " max loop " << maxLoop << endl;
			idx = 0;
		}
	}
}

void TestVecListGraph(void)
{
	ProgAssignTestLoopCountWhenMincut();
}