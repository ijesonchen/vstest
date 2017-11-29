/*
1004. Counting Leaves (30)

思路：有向图，广度搜索

A family hierarchy is usually presented by a pedigree tree. 
Your job is to count those family members who have no child.
Input

Each input file contains one test case. Each case starts with 
a line containing 0 < N < 100, the number of nodes in a tree, 
and M (< N), the number of non-leaf nodes. Then M lines follow, 
each in the format:

ID K ID[1] ID[2] ... ID[K]
where ID is a two-digit number representing a given non-leaf 
node, K is the number of its children, followed by a sequence 
of two-digit ID's of its children. For the sake of simplicity, 
let us fix the root ID to be 01.
Output

For each test case, you are supposed to count those family members 
who have no child for every seniority level starting from the root. 
The numbers must be printed in a line, separated by a space, and 
there must be no extra space at the end of each line.

The sample case represents a tree with only 2 nodes, where 01 is the 
root and 02 is its only child. Hence on the root 01 level, there 
is 0 leaf node; and on the next level, there is 1 leaf node. Then 
we should output "0 1" in a line.

Sample Input
2 1
01 1 02
Sample Output
0 1

*/

#include "patMain.h"

#include <vector>
#include <deque>
#include <set>
#include <iostream>

using namespace std;

const int A1004_STARTNODE = 1;

class A1004DG
{
public:
	void Read(void);
	void Bfs(void);
private:
	// node level in bfs
	vector<int> levels;
	// node adjancents
	vector<set<int>> adjs;
	// leaf count of level
	vector<int> cnts;
	int n;
	int m;
};

void A1004DG::Read(void)
{
	cin >> n >> m;
	// input is 1 based.
	adjs.assign(n + 1, set<int>());
	levels.assign(n + 1, 0);
	// level is 0 based;
	cnts.assign(n, 0);
	int id, k, c;
	for (size_t i = 0; i < m; i++)
	{
		cin >> id >> k;
		auto& aid = adjs[id];
		for (int j = 0; j < k; ++j)
		{
			cin >> c;
			aid.insert(c);
		}
	}
}

void A1004DG::Bfs(void)
{
	int k = 0;
	int maxLv = 0;
	deque<int> v;
	if (adjs[A1004_STARTNODE].empty())
	{
		++cnts[0];
	}
	else
	{
		v.push_back(A1004_STARTNODE);
	}
	while (!v.empty())
	{
		auto i = v.front();
		auto l = levels[i] + 1;
		maxLv = l;
		v.pop_front();
		auto& ai = adjs[i];
		for (auto& p : ai)
		{
			levels[p] = l;
			if (adjs[p].empty())
			{
				++cnts[l];
				continue;
			}
			v.push_back(p);
		}
	}
	cout << cnts[0];
	for (int i = 1; i <= maxLv; ++i)
	{
		cout << " " << cnts[i];
	}
	cout << endl;
}

void A1004(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1004DG g;
	g.Read();
	g.Bfs();
}

void A1004(void)
{
	A1004("data\\A1004-1.TXT"); // 0 1
//	A1004("data\\A1004-2.TXT"); // 
}