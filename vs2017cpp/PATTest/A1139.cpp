/*
1139. First Contact (30)

tip: id可能是0开头的字串，但不为0；（测试输入数据）

Unlike in nowadays, the way that boys and girls expressing
their feelings of love was quite subtle in the early years.
When a boy A had a crush on a girl B, he would usually not 
contact her directly in the first place. Instead, he might 
ask another boy C, one of his close friends, to ask another
girl D, who was a friend of both B and C, to send a message
to B -- quite a long shot, isn't it? Girls would do analogously.

Here given a network of friendship relations, you are supposed 
to help a boy or a girl to list all their friends who can 
possibly help them making the first contact.

Input Specification:

Each input file contains one test case. For each case, the
first line gives two positive integers N (1 < N <= 300) and M,
being the total number of people and the number of friendship 
relations, respectively. Then M lines follow, each gives a pair
of friends. Here a person is represented by a 4-digit ID. To 
tell their genders, we use a negative sign to represent girls.

After the relations, a positive integer K (<= 100) is given, 
which is the number of queries. Then K lines of queries follow, 
each gives a pair of lovers, separated by a space. It is assumed
that the first one is having a crush on the second one.

Output Specification:

For each query, first print in a line the number of different 
pairs of friends they can find to help them, then in each line 
print the IDs of a pair of friends.

If the lovers A and B are of opposite genders, you must first 
print the friend of A who is of the same gender of A, then the 
friend of B, who is of the same gender of B. If they are of the 
same gender, then both friends must be in the same gender as 
theirs. It is guaranteed that each person has only one gender.

The friends must be printed in non-decreasing order of the first 
IDs, and for the same first ones, in increasing order of the
seconds ones.

Sample Input:
10 18
-2001 1001
-2002 -2001
1004 1001
-2004 -2001
-2003 1005
1005 -2001
1001 -2003
1002 1001
1002 -2004
-2004 1001
1003 -2002
-2003 1003
1004 -2002
-2001 -2003
1001 1003
1003 -2001
1002 -2001
-2002 -2003
5
1001 -2001
-2003 1001
1005 -2001
-2002 -2004
1111 -2003

Sample Output:
4
1002 2004
1003 2002
1003 2003
1004 2002
4
2001 1002
2001 1003
2002 1003
2002 1004
0
1
2003 2001
0
*/

#include "patMain.h"
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;


class A1139Graph
{
public:
	void Read()
	{
		int n, m;
		cin >> n >> m;
		string sa, sb;
		for (int i = 0; i < m; ++i)
		{
			cin >> sa >> sb;
			int ia = Get(sa);
			int ib = Get(sb);
			v[ia].adjs.push_back(ib);
			v[ib].adjs.push_back(ia);
		}
		if (v.size() > n)
		{
			abort();
		}
	}

	void Search(const string& sa, const string& st)
	{
		map<string, set<string>> res;
		int ia = Get(sa);
		Node& na = v[ia];
		int it = Get(st);
		Node& nt = v[it];
		vector<int>& va = na.adjs;
		for (int ib = 0; ib < va.size(); ++ib)
		{
			Node& nb = v[va[ib]];
			if (nb.boy != na.boy)
			{
				continue;
			}
			vector<int>& vb = nb.adjs;
			for (int ic = 0; ic < vb.size(); ++ic)
			{
				Node& nc = v[vb[ic]];
				if (nc.boy != nt.boy)
				{
					continue;;
				}
				vector<int>& vc = nc.adjs;
				for (int id = 0; id < vc.size(); ++id)
				{
					Node& nd = v[vc[id]];
					if (nd.id == st)
					{
						res[nb.pid].insert(nc.pid);
					}
				}
			}
		}
		int total = 0;
		for (map<string, set<string>>::iterator it = res.begin();
			it != res.end();
			++it)
		{
			total += (int)it->second.size();
		}
		cout << total << endl;
		for (map<string, set<string>>::iterator it = res.begin();
			it != res.end();
			++it)
		{
			set<string>& s = it->second;
			for (set<string>::iterator its = s.begin();
				its != s.end();
				++its)
			{
				cout << it->first << " " << *its << endl;
			}
		}
	}

private:
	struct Node
	{
		string id;
		string pid;
		bool boy;
		// adjacent index in v
		vector<int> adjs;
		
		Node(string s)
			: id(s)
			, pid(s)
		{
			int i = atoi(s.c_str());
			boy = (i < 0) ? false : true;
			if (!boy)
			{
				pid.erase(0, 1);
			}
		}
	};

	int Get(const string& s)
	{
		int i = r[s];
		if (i == 0)
		{
			if (!v.empty() && v[i].id == s)
			{
				return 0;
			}
			v.push_back(s);
			i = (int)v.size() - 1;
			r[s] = i;
		}
		return i;
	}

	// nodes;
	vector<Node> v;
	// id to node
	map<string, int> r;
};


// 22/30 pt2,3,4,5
// 5应该是大数据 396ms 1408kb
int A1139Func(void)
{
	A1139Graph g;
	g.Read();
	int k = 0;
	string sa, st;
	cin >> k;
	for (int i = 0; i < k; ++i)
	{
		cin >> sa >> st;
		g.Search(sa, st);
	}
	return 0;
}


void A1139(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1139Func();
}

void A1139(void)
{
	A1139("data\\A1139-1.txt"); // 
}

