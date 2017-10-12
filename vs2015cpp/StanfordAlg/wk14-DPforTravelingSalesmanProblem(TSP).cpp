//////////////////////////////////////////////////////////////////////////
/*
ANS: file: data\zwk14_tsp.txt, tsp: 26442.7, cost: 39.3084 sec, 3.8G 
(I7 4790)
In this assignment you will implement one or more algorithms for the 
traveling salesman problem, such as the dynamic programming algorithm 
covered in the video lectures. Here is a data file describing a TSP instance.
tsp.txt
The first line indicates the number of cities. Each city is a point in the 
plane, and each subsequent line indicates the x- and y-coordinates of a 
single city.
The distance between two cities is defined as the Euclidean distance --- that 
is, two cities at locations (x,y) and (z,w) have distance sqrt((x-z)^2+(y-w)^2) 
between them.
In the box below, type in the minimum cost of a traveling salesman tour for 
this instance, rounded down to the nearest integer.
OPTIONAL: If you want bigger data sets to play with, check out the TSP instances 
from around the world here. The smallest data set (Western Sahara) has 29 cities, 
and most of the data sets are much bigger than that. What's the largest of these 
data sets that you're able to solve --- using dynamic programming or, if you like, 
a completely different method?
HINT: You might experiment with ways to reduce the data set size. For example, 
trying plotting the points. Can you infer any structure of the optimal solution?
Can you use that structure to speed up your algorithm?
*/

#include "common.h"

using namespace std;

struct Point
{
	double x = 0;
	double y = 0;

	Point(double _x, double _y) : x(_x), y(_y) {};
};

class CityMap
{
public:
	bool Load(const std::string& fn)
	{
		fstream f(fn, ios::in);
		EXPECT_TRUE(f.good());
		uint64_t n = 0;
		f >> n;
		double x = 0;
		double y = 0;
		while (f >> x >> y)
		{
			coords.push_back(Point(x, y));
		}
		if (coords.size() != n)
		{
			return false;
		}
		dis.assign(n, vector<double>(n, -1));
		return true;
	}

	// 0-based
	double Dis(int a, int b)
	{
		auto& d = dis[a][b];
		if (d >= 0)
		{
			return d;
		}
		if (a < 0 || b < 0 || a >= coords.size() || b >= coords.size() || a == b)
		{
			abort();
		}
		const auto& x = coords[a];
		const auto& y = coords[b];
		auto d1 = pow(x.x - y.x, 2);
		auto d2 = pow(x.y - y.y, 2);
		d = sqrt(d1 + d2);
		dis[b][a] = d;
		return d;
	}

	unsigned Size(void) { return coords.size(); };
private:
	vector<Point> coords;
	vector<vector<double>> dis;
};

vector<unsigned> GetBitIdx(unsigned n)
{
	vector<unsigned> v;
	auto i = 0;
	while (n >>= 1)
	{
		++i;
		if (n & 1)
		{
			v.push_back(i);
		}
	}
	return v;
}

uint32_t ResetBit(uint32_t n, uint32_t b)
{
	return n & ~((uint32_t)(-1) & (1 << b));
}

double TravelingSalesmanProblem(const std::string& fn)
{
	auto dmax = std::numeric_limits<double>::max();
	CityMap cm;
	EXPECT_TRUE(cm.Load(fn));
	vector<vector<double>> dis;
	auto n = cm.Size();
	EXPECT_TRUE(n <= 32);
	auto ns = (unsigned)pow(2, n - 1);
	dis.assign(ns + 1, vector<double>(n, std::numeric_limits<double>::max()));
	// dis[s][0] always MAX, useless. can be optimized.
	auto& ad = dis[0];
	for (size_t i = 0; i < n; i++)
	{
		ad[i] = 0;// cm.Dis(0, i);
	}
	for (size_t ii = 1; ii < ns; ii++)
	{
		auto si = ii * 2;
		auto v = GetBitIdx(si);
		if (v.size() == 1)
		{
			auto j = v.front();
			dis[ii][j] = cm.Dis(0, j);
			continue;
		}
		for (auto j : v)
		{
			auto vv = v;
			auto sj = ResetBit(si, j);
			auto ij = sj >> 1;
			auto minDist = dmax;
			vv.erase(find(vv.begin(), vv.end(), j));
			for (auto k : vv)
			{
				minDist = std::min(dis[ij][k] + cm.Dis(k, j), minDist);
			}
			dis[ii][j] = minDist;
		}
	}
	auto& vd = dis.back();
	vd = dis[ns - 1];
	auto length = vd.size();
	for (size_t i = 1; i < length; i++)
	{
		vd[i] += cm.Dis(0, i);
	}
	auto tsp = *min_element(vd.begin(), vd.end());
	cout << "min: " << tsp << endl;
// 	for (auto& d : dis)
// 	{
// 		for (auto i : d)
// 		{
// 			cout << (i == dmax ? -1 : i) << " ";
// 		}
// 		cout << endl;
// 	}

	return tsp;
}

void TravelingSalesmanProblem(void)
{
	vector<string> vfn = {
		"data\\zwk14-3-10.24.txt",
		"data\\zwk14-4-14.txt",
		"data\\zwk14-8-12.36.txt",
		"data\\zwk14-16-73.99.txt",
		"data\\zwk14_tsp.txt",
// 		"",
// 		"",
// 		"",
// 		"",
// 		"",
	};
	for (auto& f : vfn)
	{
		Tick();
		auto res = TravelingSalesmanProblem(f);
		cout << "file: " << f << ", tsp: " << res << ", cost: " << Tock() << endl;
	}
}