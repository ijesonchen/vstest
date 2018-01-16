/*
1013. Battle Over Cities (25)
cost：21：30 

sln1: BFS求连通分量个数cc，需cc-1条
	3/25 pt0,1,3 错误 pt4超时


It is vitally important to have all the cities connected 
by highways in a war. If a city is occupied by the enemy, 
all the highways from/toward that city are closed. We must 
know immediately if we need to repair any other highways to
keep the rest of the cities connected. Given the map of 
cities which have all the remaining highways marked, you 
are supposed to tell the number of highways need to be 
repaired, quickly.

For example, if we have 3 cities and 2 highways connecting 
city1-city2 and city1-city3. Then if city1 is occupied by 
the enemy, we must have 1 highway repaired, that is the 
highway city2-city3.

Input

Each input file contains one test case. Each case starts 
with a line containing 3 numbers N (<1000), M and K, which 
are the total number of cities, the number of remaining 
highways, and the number of cities to be checked, respectively. 
Then M lines follow, each describes a highway by 2 integers,
which are the numbers of the cities the highway connects. 
The cities are numbered from 1 to N. Finally there is a line
containing K numbers, which represent the cities we concern.

Output

For each of the K cities, output in a line the number of 
highways need to be repaired if that city is lost.

Sample Input
3 2 3
1 2
1 3
1 2 3
Sample Output
1
0
0
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>

using namespace std;

class A1013G
{
public:
	void Load(void);
	size_t CC(int bad) const;
private:
	vector<vector<int>> adjs;
	int nNode;
	int nEdge;
};


void A1013G::Load(void)
{
	cin >> nNode >> nEdge;
	adjs.assign(nNode, vector<int>());
	int u, v;
	for (int i = 0; i < nEdge; ++i)
	{
		cin >> u >> v;
		if (u == v)
		{
			continue;
		}
		--u, --v;
		adjs[u].push_back(v);
		adjs[v].push_back(u);
	}
}

size_t A1013G::CC(int bad) const
{
	--bad;
	vector<bool> visited(nNode, false);
	visited[bad] = true;
	map<int, vector<int>> mcc;
	int idx = 0;
	for (int i = 0; i < nNode; ++i)
	{
		if (visited[i])
		{
			continue;
		}
		visited[i] = true;
		idx = i;
		deque<int> dq;
		dq.push_back(i);
		mcc[idx].push_back(i);
		while (!dq.empty())
		{
			auto u = dq.front();
			dq.pop_front();
			auto& a = adjs[u];
			for (auto v : a)
			{
				if (visited[v])
				{
					continue;
				}
				visited[v] = true;
				dq.push_back(v);
				mcc[idx].push_back(v);
			}
		}
	}
	auto n = mcc.size() - 1;
	cout << n << endl;
	return n;
}

// rename this to main int PAT
int A1013Func(void)
{
	A1013G g;
	g.Load();
	int k, n;
	cin >> k;
	for (int i = 0; i < k; ++i)
	{
		cin >> n;
		g.CC(n);
	}
	return 0;
}


void A1013(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1013Func();
	cout << endl;
}

void A1013(void)
{
	A1013("data\\A1013-1.txt"); // 1 0 0
	A1013("data\\A1013-2.txt"); // 0 0 3
}

