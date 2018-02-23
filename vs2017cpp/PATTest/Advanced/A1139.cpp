/*
1139. First Contact (30)

test: 无自环 s1!=s2
	有 0000 PT1
	有 -0000 PT2

cost: 第二次：15:20
	
tip: id可能是0开头的字串，但不为0；（测试输入数据）
- 22/30 pt2,3,4,5
	可能存在自环，或中间环路
- 24/30 pt2，5（超时）
	pt5 应该是大数据 396ms 1408kb
	map -> unordered_map 291/384ms(快慢服务器）
- 28/30 pt2
	同性别是否需要去重？
	不需要，去重后pt5错误

nsA1139仍然未通过。推测原因应该是0000和-0000导致的。

nsA1139B:

sln4:题解： http://blog.csdn.net/gl486546/article/details/78816363
	重写 24/30 pt3-5 WA
	结果去重 24/30 pt3-5 WA
	推测：应该没有环？
	cost 2h

sln5: A-C-A-B? A-B-D-B?
	cost 10min PASS

ANS2:
1
1002 2002
2
1002 1003
1003 1002

Unlike in nowadays, the way that boys and girls expressing their feelings of love was quite subtle in the early years. 
When a boy A had a crush on a girl B, he would usually not contact her directly in the first place. 
Instead, he might ask another boy C, one of his close friends, 
to ask another girl D, who was a friend of both B and C, 
to send a message to B -- quite a long shot, isn't it? Girls would do analogously.

Here given a network of friendship relations, 
you are supposed to help a boy or a girl to list all their friends 
who can possibly help them making the first contact.

Input Specification:

Each input file contains one test case. 
For each case, the first line gives two positive integers N (1 < N <= 300) and M, 
being the total number of people and the number of friendship relations, respectively. 
Then M lines follow, each gives a pair of friends. 
Here a person is represented by a 4-digit ID. 
To tell their genders, we use a negative sign to represent girls.

After the relations, a positive integer K (<= 100) is given, which is the number of queries. 
Then K lines of queries follow, each gives a pair of lovers, separated by a space. 
It is assumed that the first one is having a crush on the second one.

Output Specification:

For each query, first print in a line the number of different pairs of friends they can find to help them, 
then in each line print the IDs of a pair of friends.

If the lovers A and B are of opposite genders, 
you must first print the friend of A who is of the same gender of A, 
then the friend of B, who is of the same gender of B. 
If they are of the same gender, then both friends must be in the same gender as theirs. 
It is guaranteed that each person has only one gender.

The friends must be printed in non-decreasing order of the first IDs, 
and for the same first ones, in increasing order of the seconds ones.

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

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

namespace nsA1139
{
	bool HasData(const vector<int>& v, int k)
	{
		int n = (int)v.size();
		for (int i = 0; i < n; ++i)
		{
			if (v[i] == k)
			{
				return true;
			}
		}
		return false;
	}

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
				if (sa == sb) // self loop
				{
					continue;
				}
				int ia = Get(sa);
				int ib = Get(sb);
				if (!HasData(v[ia].adjs, ib))
				{
					v[ia].adjs.push_back(ib);
				}
				if (!HasData(v[ib].adjs, ia))
				{
					v[ib].adjs.push_back(ia);
				}
			}
			if (v.size() > n)
			{
				abort();
			}
		}

		void Search(const string& sa, const string& st)
		{
			// a(sa) - c - d - b(st)
			map<string, set<string>> res;
			int ia = Get(sa);
			Node& na = v[ia];
			int it = Get(st);
			Node& nt = v[it];
			vector<int>& va = na.adjs;
			for (int i = 0; i < va.size(); ++i)
			{
				Node& nc = v[va[i]];
				if (nc.boy != na.boy ||
					nc.id == st) // a-b
				{
					continue;
				}
				vector<int>& vb = nc.adjs;
				for (int j = 0; j < vb.size(); ++j)
				{
					Node& nd = v[vb[j]];
					if (nd.boy != nt.boy ||
						nd.id == sa || // a-c-a
						nd.id == st) // a-c-b
					{
						continue;;
					}
					vector<int>& vc = nd.adjs;
					for (int k = 0; k < vc.size(); ++k)
					{
						Node& ndd = v[vc[k]];
						if (ndd.id == st)
						{
							res[nc.pid].insert(nd.pid);
						}
					}
				}
			}

			// dedup will not pass pt5
			// 		bool dedup = (na.boy == nt.boy);
			// 		DedupOutput(res, dedup);

			Output(res);
		}

		void Output(map<string, set<string>> &res)
		{
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

		void DedupOutput(map<string, set<string>> &res, bool dedup)
		{
			// dedup will not pass pt5
			// c ids
			vector<string> v1;
			// d ids
			vector<string> v2;
			// d id to v1 index
			unordered_map<string, set<int>> m2;
			for (map<string, set<string>>::iterator it = res.begin();
				it != res.end();
				++it)
			{
				set<string>& s = it->second;
				for (set<string>::iterator its = s.begin();
					its != s.end();
					++its)
				{
					const string& s1 = it->first;
					const string& s2 = *its;
					bool pass = false;
					if (dedup)
					{
						set<int>& setv1 = m2[s1];
						for (set<int>::iterator itsv1 = setv1.begin();
							itsv1 != setv1.end();
							++itsv1)
						{
							if (v1[*itsv1] == s2)
							{
								pass = true;
								continue;
							}
						}
					}
					if (pass)
					{
						continue;
					}
					v1.push_back(s1);
					v2.push_back(s2);
					if (dedup)
					{
						m2[s2].insert((int)v1.size() - 1);
					}
				}
			}
			int length = (int)v1.size();
			cout << length << endl;
			for (int i = 0; i < length; ++i)
			{
				cout << v1[i] << " " << v2[i] << endl;
			}
		}

	private:
		struct Node
		{
			string id;
			string pid; // id for print
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
		unordered_map<string, int> r;
	};

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
}

namespace nsA1139B {
	typedef map<string, int> MapStrInt;

	struct Node
	{
		// name = gender + id
		string name;
		bool girl = false;

		Node(const string& s)
			: name(s)
		{
			girl = s[0] == '-';
		}
	};

	struct Edge
	{
		vector<int> boys;
		vector<int> girls;
	};

	string RemoveGender(string s)
	{
		if (s[0] == '-')
		{
			s.erase(s.begin());
		}
		return s;
	}

	struct Result
	{
		string namec;
		string named;

		bool operator<(const Result& a) const
		{
			if (namec < a.namec)
			{
				return true;
			}
			else if (namec == a.namec)
			{
				return named < a.named;
			}
			return false;
		}

		void Print(void) const
		{
			string c = RemoveGender(namec), d = RemoveGender(named);
			cout << c << " " << d << endl;
		}
	};

	// 1 based. 0 for null
	vector<Node> vNodes;
	// string name to index in vNodes, 1based
	MapStrInt mapNodes;
	// relations, 1-based
	vector<Edge> vAdjs;

	void Reset(void)
	{
		vNodes.clear();
		mapNodes.clear();
		vAdjs.clear();
	}

	vector<int>& RelationVec(const string& name, bool girl)
	{
		Edge& e = vAdjs[mapNodes[name]];
		return girl ? e.girls : e.boys;
	}

	int NodeInd(const string& name)
	{
		int& ind = mapNodes[name];
		if (!ind)
		{
			vNodes.push_back(name);
			ind = (int)vNodes.size() - 1;
		}
		return ind;
	}

	void AddEdge(const int src, const int dst)
	{
		Edge& e = vAdjs[src];
		Node& nodeDst = vNodes[dst];
		vector<int>& v = nodeDst.girl ? e.girls : e.boys;
		v.push_back(dst);
	}

	void Search(const string& a, const string& b)
	{
		int indA = NodeInd(a);
		int indB = NodeInd(b);
		int indC, indD;
		Node& nodeA = vNodes[indA], nodeB = vNodes[indB];
		// A-C-D-B
		set<Result> vRes;
		vector<int>& vc = RelationVec(nodeA.name, nodeA.girl);
		size_t lenc = vc.size();
		
		for (size_t i = 0; i < lenc; ++i)
		{
			indC = vc[i];
			// A-B-D-B?
			if (indC == indB)
			{
				continue;
			}
			Node& nodeC = vNodes[indC];
			vector<int>& vd = RelationVec(nodeC.name, nodeB.girl);
			size_t lend = vd.size();
			for (size_t j = 0; j < lend; ++j)
			{
				indD = vd[j];
				// A-C-A-B? 
				if (indD == indA)
				{
					continue;
				}
				Node& nodeD = vNodes[indD];
				vector<int>& vb = RelationVec(nodeD.name, nodeD.girl);
				if (vb.end() != find(vb.begin(), vb.end(), indB))
				{
					Result res;
					res.namec = nodeC.name;
					res.named = nodeD.name;
					vRes.insert(res);
				}
			}
		}
//		sort(vRes.begin(), vRes.end());

		size_t lenRes = vRes.size();
		cout << lenRes << endl;
		for (auto& it : vRes)
		{
			it.Print();
		}
// 		for (size_t i = 0; i < lenRes; ++i)
// 		{
// 			vRes[i].Print();
// 		}
	}


	void A1139Func(void)
	{
		int n, m, k, ind1, ind2;
		set<string> nameAll;
		string s1, s2;
		cin >> n >> m;
		vNodes.push_back(string("NULL"));
		vAdjs.assign(n + 1, Edge());
		for (int i = 0; i < m; ++i)
		{
			cin >> s1 >> s2;
			nameAll.insert(s1);
			nameAll.insert(s2);
			ind1 = NodeInd(s1);
			ind2 = NodeInd(s2);
			AddEdge(ind1, ind2);
			AddEdge(ind2, ind1);
		}
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> s1 >> s2;
			Search(s1, s2);
		}
	}

}


void A1139(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	nsA1139B::Reset();
	nsA1139B::A1139Func();
}

void A1139(void)
{
	A1139("data\\A1139-1.txt"); // 
	A1139("data\\A1139-2.txt"); // 
}

