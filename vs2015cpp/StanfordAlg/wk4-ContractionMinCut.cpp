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

/*
auto fileName = "data\\wk4-kargerMinCut.txt";
mincut : 17

random select 2 super vertices is wrong, usually stooped when a supper vertex with single vertex
should chose edged randomly. max loop record is about 2000, usually found min cut within 500 loop;
*/

using namespace std;

uint32_t VEC_COUNT = 200;
bool PRINT_CONTENT = false;

void TestVecListGraph(void);

class VSet
{
public:
	VSet(int32_t v) : head(v) { heads.insert(v); }

	VSet(VSet&& v)
	{
		head = v.head;
		edges = std::move(v.edges);
		heads = std::move(v.heads);
	}

	void Add(int32_t v)
	{
		edges.insert(v);
	}

	void Contract(VSet& v)
	{
		heads.insert(v.head);
		for (auto h : v.heads)
		{
			edges.erase(h);
		}
		for (auto h : v.heads)
		{
			v.edges.erase(h);
		}
		edges.insert(v.edges.begin(), v.edges.end());
	}

	uint32_t E() const { return edges.size(); };

private:
	int32_t head = -1;
	unordered_multiset<int32_t> edges;
	unordered_multiset<int32_t> heads;
};

class VVec
{
public:
	VVec(int32_t v) : edges(VEC_COUNT + 1, 0) { heads.push_back(v); };

	void Add(int32_t v)
	{
		if (v >= edges.size())
		{
			abort();
		}
		++edges[v];
	}

	void Contract(VVec& v)
	{
		heads.insert(heads.end(), v.heads.begin(), v.heads.end());
		for (uint32_t i = 1; i < edges.size(); ++i)
		{
			edges[i] += v.edges[i];
		}
		for (auto h : heads)
		{
			edges[h] = 0;
		}
	}

	uint32_t E() const 
	{ 
		uint32_t cnt = 0;
		for (auto e: edges)
		{
			cnt += e;
		}
		return cnt;
	};

	void Print(void)
	{
		if (!PRINT_CONTENT)
		{
			return;
		}
		for (auto h : heads)
		{
			cout << h << " ";
		}
		cout << "\t\t";
		for (auto e : edges)
		{
			cout << e << " ";
		}
		cout << endl;
	}
	void PrintHeads(void)
	{
		for (auto h : heads)
		{
			cout << h << " ";
		}
	}
	void PrintEdgeCnt(void)
	{
		int s = 0;
		for_each(edges.begin(), edges.end(), [&s](int32_t n) { s += n; });
		cout << " edge " << s << " ";
	}
public:
	vector<int32_t> heads;
	// 1-based
	vector<int32_t> edges; 
};


class Graph
{
public:
	Graph(const std::string filename)
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
			VVec v(i);
			while (ss >> i)
			{
				v.Add(i);
			}
			vList.push_back(std::move(v));
		}
	}

	uint32_t V(void) const { return vList.size(); };
	uint32_t E(void) const
	{
		uint32_t e = 0;
		for (auto l : vList)
		{
			e += l.E();
		}
		if (e & 1)
		{
			abort();
		}
		return e >> 1;
	}


	void Contraction(void)
	{
		ContractionE();
	}

	void ContractionV(void)
	{
		if (vList.size() < 3)
		{
			abort();
		}
		random_device gen;
		uniform_int_distribution<int> dist(0, vList.size() - 1);
		auto i = dist(gen);
		auto j = i;
		while (j == i)
		{
			j = dist(gen);
		}
		auto p = vList.begin();
		auto v1 = vList.begin();
		auto v2 = vList.begin();
		for (int ii = 0; ii < vList.size(); ii++)
		{
			if (i == ii)
			{
				v1 = p;
			}
			if (j == ii)
			{
				v2 = p;
			}
			++p;
		}
		v1->Contract(*v2);
		vList.erase(v2);
	}


	void ContractionE(void)
	{
		if (vList.size() < 3)
		{
			abort();
		}
		random_device gen;
		uniform_int_distribution<int> dist(0, vList.size() - 1);
		auto i = dist(gen);
		auto j = i;
		while (j == i)
		{
			j = dist(gen);
		}
		auto p = vList.begin();
		auto v1 = vList.begin();
		auto v2 = vList.begin();
		for (int ii = 0; ii < vList.size(); ii++)
		{
			if (i == ii)
			{
				v1 = p;
			}
			if (j == ii)
			{
				v2 = p;
			}
			++p;
		}
		v1->Contract(*v2);
		vList.erase(v2);
	}


	void Print(void)
	{
		if (!PRINT_CONTENT)
		{
			return;
		}
		for (auto v : vList)
		{
			v.Print();
		}
		cout << endl;
	}

	void PrintHeads(void)
	{
		for (auto v : vList)
		{
			v.PrintHeads();
			v.PrintEdgeCnt();
			cout << endl;
		}
		cout << endl;
	}
public:
	list<VVec> vList;
};

random_device gen;
int RAND_NUM = 20;
uniform_int_distribution<int> dist(0, RAND_NUM);
void Gen(int& i, int& j)
{
	i = dist(gen);
	j = dist(gen);
//	cout << i << " " << j << endl;
}

void TestMinCut(const std::string& fileName, uint32_t vecCount, uint32_t ans)
{
	int sleepSec = 1;
	VEC_COUNT = vecCount;
	auto vv = vecCount * vecCount;
	uint32_t loop = vv * vv;
	cout << "|||| " << fileName << " ** " << loop << endl;
	Graph g(fileName);
	g.Print();
	Graph gMin(g);
	uint32_t mincut = vv;
	vector<uint32_t> vtMinCut;
	int last = 0;
	int findcount = 0;
	for (int i = 0; i < loop; ++i)
	{
		Graph h(g);
		while (h.V() > 2)
		{
			h.Contraction();
			h.Print();
		}
		auto e = h.E();
		vtMinCut.push_back(e);
		if (e < mincut)
		{
			mincut = e;
			cout << "++++ " << e << endl;
			h.PrintHeads();
			gMin = h;
			this_thread::sleep_for(chrono::seconds(sleepSec));
		}
		if (e == ans)
		{
			++findcount;
			last = i;
			cout << "found" << endl;
			this_thread::sleep_for(chrono::seconds(sleepSec));
		}
		cout << "****" << i << " mincut " << mincut << endl;
	}

	cout << "mincut " << mincut << " found " << findcount << " last " << last << endl;
	this_thread::sleep_for(chrono::seconds(sleepSec));
	if (mincut != ans)
	{
		gMin.Print();
		gMin.PrintHeads();
		abort();
	}
}

void ProgAssign(void)
{
	auto fileName = "data\\wk4-kargerMinCut.txt";

	VEC_COUNT = 200;
	Graph g(fileName);
	g.PrintHeads();
	Graph gMin(g);
	uint32_t mincut = 100;
	vector<uint32_t> vtMinCut;
	uint64_t i = 0;
	uint64_t last = 0;
	while (true)
	{
		++i;
		Graph h(g);
		while (h.V() > 2)
		{
			h.Contraction();
		}
		auto e = h.E();
		if (e < mincut)
		{
			mincut = e;
			std::cout << "count " << i - last  << " mincut " << e << endl;
			h.PrintHeads();
			gMin = h;
			last = i;
			this_thread::sleep_for(chrono::seconds(3));
		}
		if (i % 0x400 == 0)
		{
			std::cout << "****" << i << " last " << last << " mincut " << mincut << endl;
		}
	}

	std::cout << "mincut " << mincut << endl;

}

void TestProgAssign()
{
	auto fileName = "data\\wk4-kargerMinCut.txt"; 

	VEC_COUNT = 200;
	Graph g(fileName);

	g.PrintHeads();
	auto e = g.E();
	auto v = g.V();
	Graph gMin(g);
	uint32_t mincut = 100;
	vector<uint32_t> vtMinCut;
	uint64_t i = 0;
	uint64_t last = 0;
}

void Contraction(void)
{
	TestVecListGraph();

	return;
	TestProgAssign();
	return;
// 	vector<int> vt(RAND_NUM + 1, 0);
// 	int k = (RAND_NUM + 1) * 2000;
// 	int i = -1;
// 	int j = -1;
// 	while (--k)
// 	{
// 		Gen(i ,j);
// 		++vt[i];
// 		++vt[j];
// 	}
// 	for (auto v : vt)
// 	{
// 		cout << v << " ";
// 	}
// 	return;
	auto fileName = "data\\wk4-kargerMinCut.txt";
	// 40000, 220000
	auto loop = 220000;

//	PRINT_CONTENT = true;
//	TestMinCut(fileName, 200, 10);
	//	TestMinCut("data\\wk4-Test-MinCut-4-2.txt", 4, 2);
	TestMinCut("data\\wk4-Test-MinCut-8-1.txt", 8, 1);
	TestMinCut("data\\wk4-Test-MinCut-8-2-2.txt", 8, 2);
	TestMinCut("data\\wk4-Test-MinCut-8-2.txt", 8, 2);
}
