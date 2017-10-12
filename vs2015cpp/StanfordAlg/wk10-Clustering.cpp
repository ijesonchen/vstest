/*
Programming Assignment #2
1¡£ ans: 106
In this programming problem and the next you'll code up the clustering algorithm from 
lecture for computing a max-spacing k-clustering.

clustering1.txt
This file describes a distance function (equivalently, a complete graph with edge costs). 
It has the following format:

[number_of_nodes]
[edge 1 node 1] [edge 1 node 2] [edge 1 cost]
[edge 2 node 1] [edge 2 node 2] [edge 2 cost]
...

There is one edge (i,j) for each choice of 1¡Üi<j¡Ün, where n is the number of nodes.

For example, the third line of the file is "1 3 5250", indicating that the distance 
between nodes 1 and 3 (equivalently, the cost of the edge (1,3)) is 5250. You can assume 
that distances are positive, but you should NOT assume that they are distinct.

Your task in this problem is to run the clustering algorithm from lecture on this data set, 
where the target number k of clusters is set to 4. What is the maximum spacing of a 
4-clustering?

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some 
small test cases. And then post them to the discussion forum!


2¡£ans: 7330 x  6118 v cost 10 min release
In this question your task is again to run the clustering algorithm from lecture, but on a 
MUCH bigger graph. So big, in fact, that the distances (i.e., edge costs) are only defined 
implicitly, rather than being provided as an explicit list.

clustering_big.txt

The format is:
[# of nodes] [# of bits for each node's label]
[first bit of node 1] ... [last bit of node 1]
[first bit of node 2] ... [last bit of node 2]
...

For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 1 1 0 1" 
denotes the 24 bits associated with node #2.

The distance between two nodes u and v in this problem is defined as the Hamming distance--- 
the number of differing bits --- between the two nodes' labels. For example, the Hamming 
distance between the 24-bit label of node #2 above and the label 
"0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3 (since they differ in the 3rd, 7th, 
and 21st bits).

The question is: what is the largest value of k such that there is a k-clustering with 
spacing at least 3? That is, how many clusters are needed to ensure that no pair of nodes 
with all but 2 bits in common get split into different clusters?

NOTE: The graph implicitly defined by the data file is so big that you probably can't write 
it out explicitly, let alone sort the edges by cost. So you will have to be a little creative 
to complete this part of the question. For example, is there some way you can identify the 
smallest distances without explicitly looking at every pair of nodes?

*/
#include "common.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
// cluster for small

struct SEdge
{
	SEdge(int ss, int tt, int ww) : a(ss), b(tt), w(ww) {};
	int a = 0;
	int b = 0;
	int w = 0;
};

bool operator < (const SEdge& lhs, const SEdge& rhs)
{
	return lhs.w < rhs.w;
}

class UFCluster
{
public:
	void Load(const string& fn)
	{
		fstream f(fn, ios::in);
		if (!f) { abort(); }

		f >> v;
		vtGroups.assign(v + 1, 0);
		vtCnt.assign(v + 1, 1);
		auto length = vtGroups.size();
		for (size_t i = 0; i < length; i++)
		{
			vtGroups[i] = i;
		}
		if (!f) abort();

		int a = 0;
		int b = 0;
		int w = 0;
		while (f >> a && f >> b && f >> w)
		{
			if (a > v || b > v) abort();
			vtEdges.push_back(SEdge(a, b, w));
		}
	};

	void Sort(void)
	{
		sort(vtEdges.begin(), vtEdges.end());
	}

	// return space after cluster
	int Cluster(int nTargetCluster)
	{
		auto nCluster = v;
		auto length = vtEdges.size();
		for (size_t i = 0; i < length; i++)
		{
			auto& e = vtEdges[i];
			if (nCluster <= nTargetCluster)
			{
				// skip clusters already unioned
				if (Find(e.a) == Find(e.b))
				{
					continue;
				}
				return vtEdges[i].w;
			}
			if (Union(e.a, e.b))
			{
				--nCluster;
			}
		}
		return -1;
	}

	int Find(int x)
	{
		vector<int> nodes;
		while (vtGroups[x] != x)
		{
			nodes.push_back(x);
			x = vtGroups[x];
		}
		// compress
		for (auto i : nodes)
		{
			vtGroups[i] = x;
		}
		return x;
	}

	bool Union(int u, int v)
	{
		auto x = Find(u);
		auto y = Find(v);
		if (x == y)
		{
			return false;
		}
		if (vtCnt[x] < vtCnt[y])
		{
			vtCnt[y] += vtCnt[x];
			vtGroups[x] = y;
		}
		else
		{
			vtCnt[x] += vtCnt[y];
			vtGroups[y] = x;
		}

		return true;
	}
private:
	// 1-based
	vector<int> vtCnt;
	vector<int> vtGroups;
	vector<SEdge> vtEdges;
	int v = 0;
};


int TestUnionFindCluster(const std::string& fn, int nCluster)
{
	UFCluster s;
	s.Load(fn);
	s.Sort();
	return s.Cluster(nCluster);
}

void ClusterSmall(void)
{
	EXPECT_TRUE(1 == TestUnionFindCluster("data\\zwk10-small-2-1.txt", 2));
	EXPECT_TRUE(5 == TestUnionFindCluster("data\\zwk10-small-2-5.txt", 2));
	EXPECT_TRUE(100 == TestUnionFindCluster("data\\zwk10-small-2-100.txt", 2));
	EXPECT_TRUE(3 == TestUnionFindCluster("data\\zwk10-small-4-3.txt", 4));
	auto n = TestUnionFindCluster("data\\zwk10-clustering1.txt", 4);
	cout << "space for clustering1 of 4 cluster is: " << n << endl;
}

//////////////////////////////////////////////////////////////////////////
// bit differ: 1-3, slow to fast. 3&4 is the same

int BitDiff1(int i, int j)
{
	auto count = 32;
	auto diff = 0;
	while (count--)
	{
		if ((i & 1) != (j & 1))
		{
			++diff;
		}
		i = i >> 1;
		j = j >> 1;
	}
	return diff;
}

void BitDiffMatrix1(int bit)
{
	vector<int> v;
	int n = pow(2, bit);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			auto b = BitDiff1(i, j);
			v.push_back(b);
//			cout << b << " ";
		}
		v.clear();
//		cout << i << endl;
	}
}

int BitDiff2(int i, int j)
{
	auto c = i ^ j;
	auto count = 32;
	auto diff = 0;
	while (count--)
	{
		if (c & 1)
		{
			++diff;
		}
		c = c >> 1;
	}
	return diff;
}

int BitDiff3(int i, int j)
{
	auto x = i ^ j;
	int count = 0;
	while (x)
	{
		count++;
		x = x  &   (x - 1);
	}
	return count;
}


void BitDiffMatrix2(int bit)
{
	vector<int> v;
	int n = pow(2, bit);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			auto b = BitDiff2(i, j);
			v.push_back(b);
//			cout << b << " ";
		}
		v.clear();
//		cout << endl;
	}
}

void BitDiffMatrix3(int bit)
{
	vector<int> v;
	int n = pow(2, bit);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			auto b = BitDiff3(i, j);
			v.push_back(b);
			cout << b << " ";
		}
		v.clear();
		cout << endl;
	}
}


int BitDiff4(int i, int j)
{
	auto x = i ^ j;
	int count = 0;
	while (x)
	{
		++count;
		x = x  &   (x - 1);
	}
	return count;
}

// 200K*200K, release, 10sec
void BitDiffMatrix4(int bit)
{
	vector<int> v;
	int64_t c = 0;
	int64_t cMax = (int64_t)200000 * 200000;
	int n = pow(2, bit);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			auto b = BitDiff4(i, j);
			if (++c >= cMax)
			{
				return;
			}
			v.push_back(b);
//			cout << b << " ";
		}
		v.clear();
//		cout << endl;
	}
}

//////////////////////////////////////////////////////////////////////////
// 

int BitDiff(int i, int j)
{
	auto x = i ^ j;
	int count = 0;
	while (x)
	{
		++count;
		x = x  &   (x - 1);
	}
	return count;
}

class BitCluster
{
	// 0-based
public:
	void Load(const std::string& fn)
	{
		fstream f(fn, ios::in);
		Check(f);
		f >> nNode;
		f >> nBit;
		Check(f);
		uint64_t v = nNode;
		vtGroups.assign(v, 0);
		vtCnt.assign(v, 1);
		auto length = vtGroups.size();
		for (size_t i = 0; i < length; i++)
		{
			vtGroups[i] = i;
		}
		
		auto line = nNode;
		auto row = nBit;
		while (line--)
		{
			int b = 0;
			int res = 0;
			row = nBit;
			while (row--)
			{
				res = res << 1;
				f >> b;
				res = (res + b);
			}
			vtNode.push_back(res);
		}
	}

	// return space after cluster
	int Cluster(int nTargetSpace)
	{
		auto nCluster = nNode;
		auto length = nNode;
		for (size_t i = 0; i < length - 1; i++)
		{
			auto u = vtNode[i];
			if (i % 1000 == 0)
			{
				cout << "proc node from " << i << endl;
			}
			for (size_t j = 1; j < length; j++)
			{
				auto v = vtNode[j];
				auto w = BitDiff(u, v);
				if (w >= nTargetSpace)
				{
					continue;
				}
				if (Union(i, j))
				{
					EXPECT_TRUE((--nCluster) > 0);
				}
			}
		}
		if (nNode < 40)
		{
			cout << "Groups: " << endl;
			for (auto i : vtGroups)
			{
				cout << i << " ";
			}
			cout << endl;
		}
		return nCluster;
	}

	int Find(int x)
	{
		vector<int> nodes;
		while (vtGroups[x] != x)
		{
			nodes.push_back(x);
			x = vtGroups[x];
		}
		// compress
		for (auto i : nodes)
		{
			vtGroups[i] = x;
		}
		return x;
	}

	bool Union(int u, int v)
	{
		auto x = Find(u);
		auto y = Find(v);
		if (x == y)
		{
			return false;
		}
		if (vtCnt[x] < vtCnt[y])
		{
			vtCnt[y] += vtCnt[x];
			vtGroups[x] = y;
		}
		else
		{
			vtCnt[x] += vtCnt[y];
			vtGroups[y] = x;
		}

		return true;
	}
private:
	void Check(fstream& f) 
		{ if (!f) { abort(); } }
	int nNode = 0;
	int nBit = 0;
	vector<int> vtCnt;
	vector<int> vtGroups;
	vector<int> vtNode;

};

int TestBitCluster(const std::string& fn, int nTargetSpace)
{
	auto t = time(nullptr);
	BitCluster bc;
	bc.Load(fn);
	cout << "loaded " << fn << " cost " << time(nullptr) - t << endl;
	auto n = bc.Cluster(nTargetSpace);
	cout << fn << " ANS: " << n << endl;
	return n;
}

void ClusterBig(void)
{
	string fn;
	auto n = 0;
	n = TestBitCluster("data\\zwk10-big-3-2.txt", 3);
	n = TestBitCluster("data\\zwk10-big2-3-2.txt", 3);
	auto t = time(nullptr);
	n = TestBitCluster("data\\zwk10-clustering_big.txt", 3);
	cout << " res for zwk10-clustering_big.txt " << n << " cost " << time(nullptr) - t << endl;
}

void Clustering(void)
{
	ClusterSmall();
//	cout << "ans for prog 1 is 106" << endl;
	ClusterBig();
}