void ApproxTravelingSalesmanProblem(void);
//////////////////////////////////////////////////////////////////////////
/*
ANS: 1203406
In this assignment we will revisit an old friend, the traveling salesman problem 
(TSP). This week you will implement a heuristic for the TSP, rather than an exact 
algorithm, and as a result will be able to handle much larger problem sizes. Here 
is a data file describing a TSP instance (original source: 
http://www.math.uwaterloo.ca/tsp/world/bm33708.tsp).
nn.txt
The first line indicates the number of cities. Each city is a point in the plane, 
and each subsequent line indicates the x- and y-coordinates of a single city.
The distance between two cities is defined as the Euclidean distance --- that is, 
two cities at locations (x,y) and (z,w) have distance sqrt( (x-z)^2+(y-w)^2 )between 
them.
You should implement the nearest neighbor heuristic:
1. Start the tour at the first city.
2. Repeatedly visit the closest city that the tour hasn't visited yet. In case of 
a tie, go to the closest city with the lowest index. For example, if both the third 
and fifth cities have the same distance from the first city (and are closer than 
any other city), then the tour should begin by going from the first city to the third city.
3. Once every city has been visited exactly once, return to the first city to 
complete the tour.
In the box below, enter the cost of the traveling salesman tour computed by the 
nearest neighbor heuristic for this instance, rounded down to the nearest integer.
[Hint: when constructing the tour, you might find it simpler to work with squared 
Euclidean distances (i.e., the formula above but without the square root) than 
Euclidean distances. But don't forget to report the length of the tour in terms of 
standard Euclidean distance.]
*/

#include "common.h"
using namespace std;

struct Point
{
	double x = 0;
	double y = 0;

	Point(double _x, double _y) : x(_x), y(_y) {};
};


vector<Point> LoadMap14(const std::string& fn)
{
	vector<Point> coords;
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
	EXPECT_TRUE(coords.size() == n);
	return coords;
}

vector<Point> LoadMap15(const std::string& fn)
{
	vector<Point> coords;
	fstream f(fn, ios::in);
	EXPECT_TRUE(f.good());
	uint64_t n = 0;
	f >> n;
	uint64_t i = 0;
	double x = 0;
	double y = 0;
	while (f >> i >> x >> y)
	{
		coords.push_back(Point(x, y));
	}
	EXPECT_TRUE(coords.size() == n);
	return coords;
}

double Dist(const Point& x, const Point& y)
{
	auto d1 = pow(x.x - y.x, 2);
	auto d2 = pow(x.y - y.y, 2);
	auto d = sqrt(d1 + d2);
	return d;
}

template<typename Iter>
tuple<Iter, double>
FindMinDist(const bool* const mask, Iter first, Iter last, bool forward = true)
{
	double minDis = numeric_limits<double>::max();
	auto itDis = first;
	for (auto i = first; i != last; ++i)
	{
		if (!mask[i - first])
		{
			auto d = Dist(*first, *i);
			if ((forward && d < minDis) ||
				(!forward && d <= minDis))
			{
				minDis = d;
				itDis = i;
			}
			if (abs(i->x - first->x) > minDis)
			{
				break;
			}
		}
	}
	return make_tuple(itDis, minDis);
}

double ApproxTSP(const std::string& fn)
{
	auto coords = LoadMap15(fn);
	const auto length = coords.size();
	double tsp = 0;
	double doubleMax = numeric_limits<double>::max();
	auto maskForward = new bool[length];
	auto maskBackward = new bool[length];
	memset(maskForward, 0, sizeof(bool) * length);
	memset(maskBackward, 0, sizeof(bool) * length);

	int counter = (int)length;
	auto itLast = coords.begin();
	maskForward[0] = true;
	maskBackward[length - 1] = true;
	while (--counter > 0)
	{
		// left side:
		vector<Point>::reverse_iterator itLeft(itLast);
		double disLeft = doubleMax;
		if (itLast != coords.end())
		{
			--itLeft;
			auto offLeft = itLeft - coords.rbegin();
			std::tie(itLeft, disLeft) = FindMinDist(maskBackward + offLeft, itLeft, coords.rend(), false);
		}
		// right side
		vector<Point>::iterator itRight;
		double disRight = doubleMax;
		if (itLast != coords.end())
		{
			auto offRight = itLast - coords.begin();
			std::tie(itRight, disRight) = FindMinDist(maskForward + offRight, itLast, coords.end());
		}

		if ((disLeft == doubleMax) && 
			(disRight == doubleMax))
		{
			abort();
		}

		if (disLeft <= disRight)
		{
			tsp += disLeft;
			itLast = --(itLeft.base());
		}
		else
		{
			tsp += disRight;
			itLast = itRight;
		}
		auto idx = itLast - coords.begin();

		// output path.
//		cout << idx + 1 << " ";
		maskForward[idx] = true;
		maskBackward[length - idx - 1] = true;
	}
	
	tsp += Dist(*itLast, coords.front());

	return tsp;
}

void ApproxTravelingSalesmanProblem(void)
{
	vector<string> fns = {
// 		"data\\zwk14-3-10.24.txt",
// 		"data\\zwk14-4-14.txt",
// 		"data\\zwk14-8-12.36.txt",
// 		"data\\zwk14-16-73.99.txt",
// 		"data\\zwk14_tsp.txt",      
		// file above should use LoadMap14, due to different data format.

		"data\\zwk15-6-15.2361.txt", // may not work with FindMinDist, data not sorted by x-coord
		"data\\zwk15-nn.txt",
	};
	/*	
	data\zwk14-3-10.24.txt: 10.2426
	data\zwk14-4-14.txt: 14
	data\zwk14-8-12.36.txt: 12.3648
	data\zwk14-16-73.99.txt: 89.078
	data\zwk14_tsp.txt: 32982

	data\zwk15-4-14.txt: 15.2361 15, path 0 2 1 4 5 3 

	data\zwk15-nn.txt: 1.20341e+06 1203406
	3.84567 seconds to 120.449 milliseconds. (with x coord short-cut)
	*/

	for (auto& i : fns)
	{
		auto d = ApproxTSP(i);
		int64_t id = (int64_t)(d * 1/*00000000*/);
		cout << i << ": " << d << " " << id << endl;
	}

}