//////////////////////////////////////////////////////////////////////////
/*
1¡£
In this assignment you will implement one or more algorithms for the all-pairs 
shortest-path problem. Here are data files describing three graphs:
g1.txt	NULL
g2.txt	NULL
g3.txt	-19
The first line indicates the number of vertices and edges, respectively. Each 
subsequent line describes an edge (the first two numbers are its tail and head, 
respectively) and its length (the third number). NOTE: some of the edge lengths 
are negative. NOTE: These graphs may or may not have negative-cost cycles.

Your task is to compute the "shortest shortest path". Precisely, you must first 
identify which, if any, of the three graphs have no negative cycles. For each 
such graph, you should compute all-pairs shortest paths and remember the smallest 
one (i.e., compute min u,v¡ÊV d(u,v), where d(u,v) denotes the shortest-path 
distance from u to v).

If each of the three graphs has a negative-cost cycle, then enter "NULL" in the 
box below. If exactly one graph has no negative-cost cycles, then enter the length 
of its shortest shortest path in the box below. If two or more of the graphs have 
no negative-cost cycles, then enter the smallest of the lengths of their shortest 
shortest paths in the box below.

OPTIONAL: You can use whatever algorithm you like to solve this question. If you 
have extra time, try comparing the performance of different all-pairs shortest-path 
algorithms!

OPTIONAL: Here is a bigger data set to play with.

large.txt -6
i7-4790(3.6G-4G 4C8T), 32G ddr3. win7 sp1, vs2013 update4, SSD
cpu time: 8:22:35, max mem: 11,755,424K
relative: g1-g3: total cpu less than 5 sec, mem less than 100M

For fun, try computing the shortest shortest path of the graph in the file above.

//////////////////////////////////////////////////////////////////////////
// bugs:
zwk13_3_-14.txt: fix multi edge bug: with min
zwk13_1_null.txt: self negative cycle
*/

#include "common.h"
#include <windows.h>
#include <limits>
#include <filesystem>

#undef max

using namespace std;
using namespace std::tr2;

bool bPrintDetail = false;

// for shortest path, input 1-based, vp 1-based, vw 0-based
class GraphMatrixSP
{
public:
	GraphMatrixSP();
	~GraphMatrixSP();

	void Load(const std::string& fn)
	{
		fstream f(fn, ios::in);
		assert(f);
		f >> v >> e;
		assert(f);
		vw.assign(v, vector<int64_t>(v, maxValue));
		vp.assign(v, vector<int16_t>(v, INT16_MAX));
		int64_t u = 0;
		int64_t v = 0;
		int64_t w = 0;
		int64_t n = 0;
		while (f >> u >> v >> w)
		{
			--u; --v;
			// bug-fix: zwk13_3_ - 14.txt: u->v has multi weight.
			vw[u][v] = min(vw[u][v], w);
			vp[u][v] = u + 1;
			++n;
		}
		auto length = vw.size();
		for (size_t i = 0; i < length; i++)
		{
			// bug-fix: zwk13_1_null.txt: self negative cycle
			vw[i][i] = min(vw[i][i], 0);
		}
		assert(n == e);
	}

	void GenNegMap(int nV)
	{
		v = nV;
		e = v * v;
		vw.assign(v, vector<int64_t>(v, maxValue));
		vp.assign(v, vector<int16_t>(v, INT16_MAX));
		for (auto& v : vw)
		{
			for (auto& w : v)
			{
				w = -1;
			}
		}
	}

	void Print(void) { return Print(vw); }

	tuple<int64_t, bool> APSP_FloydWarshall(void)
	{
		auto length = vw.size();

		// bug-fix: zwk13_1_null.txt: self negative cycle
		for (size_t i = 0; i < length; i++)
		{
			if (vw[i][i] < 0)
			{
				return make_tuple(0, true);
			}
		}

		auto vvi = vw;
		auto vvj = vw;
		auto vpi = vp;
		auto vpj = vp;
		auto cycle = false;

		Print(vvi);
		Print(vpi);
		for (size_t k = 0; k < length; k++)
		{
			for (size_t i = 0; i < length; i++)
			{
				for (size_t j = 0; j < length; j++)
				{
					auto pi = vvi[i][j];
					auto p1 = vvi[i][k];
					auto p2 = vvi[k][j];
					decltype(p1) pk = maxValue;
					if (p1 != maxValue && p2 != maxValue)
					{
						pk = p1 + p2;
					}
					vvj[i][j] = min(pi, pk);
					if (vvj[i][j] != vvi[i][j])
					{
						// set prev-node
						vpj[i][j] = vpi[k][j];
						if (i == j && vvj[i][j] < 0)
						{
							// has cycle
							return make_tuple(0, true);
						}
					}
				}
			}
			Print(vvj, vvi);
//			Print(vpj, vpi);
			vvi = vvj;
			vpi = vpj;
		}

		auto minWeight = Min(vvj);

		return make_tuple(minWeight, cycle);
	}
private:

	template<typename T>
	static void Print(const vector<vector<T>>& vvi, const vector<vector<T>>& vv0)
	{
		if (!bPrintDetail)
		{
			return;
		}
		auto m = numeric_limits<T>::max();
		auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
		auto length = vvi.size();
		if (length > 10)
		{
			cout << "to big." << endl;
			return;
		}
		for (size_t i = 0; i < length; i++)
		{
			for (size_t j = 0; j < length; j++)
			{
				auto n = vvi[i][j];
				if (n == m)
				{
					SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
					printf("%8s", "*");
					SetConsoleTextAttribute(handle, 7);
					continue;
				}
				auto n0 = vv0[i][j];
				if (n0 == n)
				{
					printf("%8lld", (int64_t)n);
				}
				else
				{
					SetConsoleTextAttribute(handle, FOREGROUND_RED);
					printf("%8lld", (int64_t)n);
					SetConsoleTextAttribute(handle, 7);
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	template<typename T>
	static void Print(const vector<vector<T>>& vvi)
	{
		if (!bPrintDetail)
		{
			return;
		}
		auto m = numeric_limits<T>::max();
		auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
		auto length = vvi.size();
		if (length > 10)
		{
			cout << "to big." << endl;
			return;
		}
		for (auto& v : vvi)
		{
			for (auto n : v)
			{
				if (n == m)
				{
					SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
					printf("%8s", "*");
					SetConsoleTextAttribute(handle, 7);
					continue;
				}
				printf("%8lld", (int64_t)n);
			}
			cout << endl;
		}
		cout << endl;
	}
	
	int64_t Min(const vector<vector<int64_t>>& vvi)
	{
		auto value = INT64_MAX;
		auto length = vvi.size();
		for (size_t i = 0; i < length; i++)
		{
			auto v = vvi[i];
			v[i] = INT64_MAX;
			value = min(value, *min_element(v.begin(), v.end()));
		}
		
		return value;
	}

private:
	static const int64_t maxValue = INT64_MAX;


	int64_t v;
	int64_t e;
	vector<vector<int64_t>> vw;
	vector<vector<int16_t>> vp;
};

GraphMatrixSP::GraphMatrixSP()
{
}

GraphMatrixSP::~GraphMatrixSP()
{
}

tuple<int64_t, bool> MinAllPairShortestPath(const std::string& fn)
{
	GraphMatrixSP g;
	g.Load(fn);
	return g.APSP_FloydWarshall();
}

string TC_GetOutput(const std::string& ifn)
{
	string ofn(ifn);
	return ofn.replace(ofn.find("input_random"), sizeof("input_random") - 1, "output_random");
}

vector<string> TC_LoadFiles(void)
{
	vector<string> vt;
	string tcPath("TestCase\\assignment1AllPairsShortestPath");

	for (auto it = sys::directory_iterator(tcPath), end = sys::directory_iterator();
		it != end; ++it)
	{
		auto fn = it->path().string();
		sys::path p(fn);
		if (p.stem().string().find("input_random") != string::npos)
		{
			vt.push_back(fn);
			auto ofn = TC_GetOutput(fn);
			fstream f(ofn, ios::in);
			assert(f);
			cout << ofn << endl;
		}
	}
	return vt;
}

void TC_APSPTest(void)
{
	vector<string> vtWrong;
	auto vti = TC_LoadFiles();
	for (auto& ifn : vti)
	{
		bool hasCycle = false;
		int64_t minValue = 0;
		std::tie(minValue, hasCycle) = MinAllPairShortestPath(ifn);

		stringstream ss;

		if (hasCycle)
		{
			ss << "NULL";
		}
		else
		{
			ss << minValue;
		}
		auto res = ss.str();
		cout << ifn << " " << res;
		auto ofn = TC_GetOutput(ifn);
		fstream f(ofn, ios::in);
		assert(f);
		string ans;
		f >> ans;
		assert(f);
		cout << " " << ans;
		if (res != ans)
		{
			cout << "    ****    ";
			stringstream ss1;
			ss1 << ifn << " bad " << res << " right " << ans;
			vtWrong.push_back(ss1.str());
		}
		cout << endl;
	}

	if (vtWrong.empty())
	{
		cout << "**** ALL PASSED ****" << endl;
		return;
	}

	cout << "**** FAILED ****" << endl;

	for (auto& i : vtWrong)
	{
		cout << i << endl;
	}
}

void APSP_Stanford(void)
{
	vector<tuple<int64_t, bool>> v;
	vector<string> files = {
		"data\\zwk13-g1.txt",
		"data\\zwk13-g2.txt",
		"data\\zwk13-g3.txt",
		"data\\zwk13-large.txt",
	};

	for (auto f : files)
	{
		int64_t value = 0;
		bool cycle = false;
		auto res = MinAllPairShortestPath(f);
		std::tie(value, cycle) = res;
		v.push_back(res);
		cout << f << " ";
		if (cycle)
		{
			cout << "NULL";
		}
		else
		{
			cout << value;
		}
		cout << endl;
	}
}

void NoStopOnNegCycle(void)
{
	// DO NOT STOP ON NEG CYCLE
	// weight is -1 for each node.
	// result is -2^n
	bPrintDetail = true;

	GraphMatrixSP g;
	g.GenNegMap(4);
	g.APSP_FloydWarshall();
}

void AllPairShortestPath(void)
{
	// assignment1AllPairsShortestPath/input_random_1_2.txt bad 51 right NULL
// 	c = false;
// 	TC_APSPTest();
// 	return;
// 	bPrintDetail = true;
// 	auto t = MinAllPairShortestPath("data\\zwk13_1_null.txt");
// 	cout << get<0>(t) << " " << get<1>(t) << endl;
//	return;
//	APSP_Stanford();
}