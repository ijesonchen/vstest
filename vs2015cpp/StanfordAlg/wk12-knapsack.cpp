#include "common.h"

//////////////////////////////////////////////////////////////////////////
/*
Programming Assignment #4

1¡£
In this programming problem and the next you'll code up the knapsack 
algorithm from lecture.
Let's start with a warm-up. Download the text file below.
knapsack1.txt
This file describes a knapsack instance, and it has the following format:
[knapsack_size][number_of_items]
[value_1] [weight_1]
[value_2] [weight_2]
...

For example, the third line of the file is "50074 659", indicating that the 
second item has value 50074 and size 659, respectively.
You can assume that all numbers are positive. You should assume that item 
weights and the knapsack capacity are integers.
In the box below, type in the value of the optimal solution.

2¡£
This problem also asks you to solve a knapsack instance, but a much bigger one.
Download the text file below.
knapsack_big.txt
This file describes a knapsack instance, and it has the following format:
[knapsack_size][number_of_items]
[value_1] [weight_1]
[value_2] [weight_2]
...
For example, the third line of the file is "50074 834558", indicating that 
the second item has value 50074 and size 834558, respectively. As before, you 
should assume that item weights and the knapsack capacity are integers.
This instance is so big that the straightforward iterative implemetation uses 
an infeasible amount of time and space. So you will have to be creative to 
compute an optimal solution. One idea is to go back to a recursive implementation, 
solving subproblems --- and, of course, caching the results to avoid redundant 
work --- only on an "as needed" basis. Also, be sure to think about appropriate 
data structures for storing and looking up solutions to subproblems.
In the box below, type in the value of the optimal solution.


*/

using namespace std;
//////////////////////////////////////////////////////////////////////////
// 
struct KSItem
{
	int v = 0;
	int w = 0;
	KSItem(int vv, int ww) : v(vv), w(ww){};
};

tuple<vector<KSItem>,int> ReadKnapSack(const std::string& fn)
{
	fstream f(fn, ios::in);
	if (!f)
	{
		abort();
	}
	int size = 0;
	int item = 0;
	f >> size;
	f >> item;
	if (!f)
	{
		abort();
	}
	vector<KSItem> vtItem;
	int v = 0;
	int w = 0;
	while (f >> v && f >> w)
	{
		vtItem.push_back(KSItem(v, w));
	}
	if (vtItem.size() != item)
	{
		abort();
	}
	return make_tuple(std::move(vtItem), size);
}

// for large scale, calc sub-problem as need.
void KnapSackTopDown(void)
{

}

template<typename T>
vector<vector<T>> Make2DArray(const int x, const int y)
{
	vector<vector<T>> vv(x, vector<T>(y));
	return std::move(vv);
}

template<typename T>
T GetBagValue2DArray(const vector<vector<T>>& vv, const int x, const int y, const int v = 0)
{
	if (x < -1)
	{
		return 0;
	}
	if (y < -1)
	{
		return 0;
	}
	if (x == -1 || y == -1)
	{
		return v;
	}
	return vv[x][y] + v;
}


// for small scale, calc all sub-problem
void KnapSackBottomUp(const std::string& fn)
{
	vector<KSItem> items;
	int bagSize = 0;
	std::tie(items, bagSize) = ReadKnapSack(fn);
	auto vv = Make2DArray<int>(items.size(), bagSize);

	auto length = items.size();
	
	for (size_t i = 0; i < length; i++)
	{
		for (int j = 0; j < bagSize; ++j)
		{
			auto v = items[i].v;
			auto w = items[i].w;
			auto n1 = GetBagValue2DArray(vv, i - 1, j);
			auto n2 = GetBagValue2DArray(vv, i - 1, j - w, v);
			vv[i][j] = max(n1, n2);
		}
	}

// 	for (auto& v : vv)
// 	{
// 		for (auto i : v)
// 		{
// 			cout << i << " ";
// 		}
// 		cout << endl;
// 	}
// 	cout << endl;

	cout << fn << " ans: " << vv.back().back() << endl;
}

void KnapSack(void)
{
	KnapSackBottomUp("data\\zwk12-8_6-14.txt");
	KnapSackBottomUp("data\\zwk12-190_16-150.txt");
	KnapSackBottomUp("data\\zwk12-10_100_10-147.txt");
	KnapSackBottomUp("data\\zwk12-15_100_100-627.txt");
	KnapSackBottomUp("data\\zwk12-knapsack1.data"); // 2493893
	KnapSackBottomUp("data\\zwk12-knapsack_big.data"); // 4243395
	KnapSackTopDown();


}