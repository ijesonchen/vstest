/*
1¡£
In this programming problem and the next you'll code up the greedy algorithms 
from lecture for minimizing the weighted sum of completion times..
Download the text file below.
jobs.txt
This file describes a set of jobs with positive and integral weights and lengths. 
It has the format

[number_of_jobs]

[job_1_weight] [job_1_length]

[job_2_weight] [job_2_length]

...

For example, the third line of the file is "74 59", indicating that the second 
job has weight 74 and length 59.

You should NOT assume that edge weights or lengths are distinct.

Your task in this problem is to run the greedy algorithm that schedules jobs in 
decreasing order of the difference (weight - length). Recall from lecture that this 
algorithm is not always optimal. IMPORTANT: if two jobs have equal difference 
(weight - length), you should schedule the job with higher weight first. 
Beware: if you break ties in a different way, you are likely to get the wrong answer. 
You should report the sum of weighted completion times of the resulting 
schedule --- a positive integer --- in the box below.

ADVICE: If you get the wrong answer, try out some small test cases to debug your 
algorithm (and post your test cases to the discussion forum).

2¡£
For this problem, use the same data set as in the previous problem.

Your task now is to run the greedy algorithm that schedules jobs (optimally) in 
decreasing order of the ratio (weight/length). In this algorithm, it does not matter 
how you break ties. You should report the sum of weighted completion times of the 
resulting schedule --- a positive integer --- in the box below.

3¡£
In this programming problem you'll code up Prim's minimum spanning tree algorithm.

Download the text file below.

edges.txt
This file describes an undirected graph with integer edge costs. It has the format

[number_of_nodes] [number_of_edges]

[one_node_of_edge_1] [other_node_of_edge_1] [edge_1_cost]

[one_node_of_edge_2] [other_node_of_edge_2] [edge_2_cost]

...

For example, the third line of the file is "2 3 -8874", indicating that there is an 
edge connecting vertex #2 and vertex #3 that has cost -8874.

You should NOT assume that edge costs are positive, nor should you assume that they 
are distinct.

Your task is to run Prim's minimum spanning tree algorithm on this graph. You should 
report the overall cost of a minimum spanning tree --- an integer, which may or may 
not be negative --- in the box below.

IMPLEMENTATION NOTES: This graph is small enough that the straightforward O(mn) time 
implementation of Prim's algorithm should work fine. OPTIONAL: For those of you seeking 
an additional challenge, try implementing a heap-based version. The simpler approach, 
which should already give you a healthy speed-up, is to maintain relevant edges in a 
heap (with keys = edge costs). The superior approach stores the unprocessed vertices 
in the heap, as described in lecture. Note this requires a heap that supports deletions, 
and you'll probably need to maintain some kind of mapping between vertices and their 
positions in the heap.
*/


#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <fstream>
#include "common.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
// minimum weighted sum

struct Job
{
	int i = 0;
	int w = 0;
	int l = 0;
	float score = 0;
};

std::vector<Job> ReadJob(const std::string& filename)
{
	fstream f(filename, ios::in);
	if (!f) { abort(); }

	vector<Job> v;

	int64_t x = 0;
	int64_t y = 0;
	int64_t jobs = 0;
	f >> jobs;
	if (!f)
	{
		abort();
	}
	int i = 0;
	while (f >> x && f >> y)
	{
		Job job;
		job.i = ++i;
		job.w = x;
		job.l = y;
		v.push_back(job);
	}

	if (v.size() != jobs)
	{
		abort();
	}

	return std::move(v);
}

bool JobGreat (const Job& lhs, const Job& rhs)
{
	if (lhs.score > rhs.score)
	{
		return true;
	}
	else if (lhs.score == rhs.score)
	{
		return lhs.w > rhs.w;
	}

	return false;
}

int64_t CalcMWS(const std::vector<Job>& v)
{
	auto length = v.size();
	int64_t c = 0;
	int64_t sum = 0;
	for (auto& i : v)
	{
		c += i.l;
		sum += i.w * c;
	}
	return sum;
}

int64_t SubMWS(const string& fn)
{
//	auto v = ReadJob("data\\zwk9-jobs.txt");
	auto v = ReadJob(fn);
	// scores
	for (auto& i : v)
	{
		i.score = i.w - i.l;
	}
	sort(v.begin(), v.end(), JobGreat);
	return CalcMWS(v);
}

int64_t RatioMWS(const string& fn)
{
	auto v = ReadJob(fn);
	// scores
	for (auto& i : v)
	{
		i.score = float(i.w) / i.l;
	}
	sort(v.begin(), v.end(), JobGreat);
	return CalcMWS(v);
}

void Mws(void)
{
	vector<int64_t> v;
	int64_t res = 0;
	res = SubMWS("data\\zwk9-jobs.txt");
	v.push_back(res);
	res = SubMWS("data\\zwk9-jobs-test1.txt");
	v.push_back(res);
	res = SubMWS("data\\zwk9-jobs-test2.txt");
	v.push_back(res);
	res = RatioMWS("data\\zwk9-jobs.txt");
	v.push_back(res);
	res = RatioMWS("data\\zwk9-jobs-test1.txt");
	v.push_back(res);
	res = RatioMWS("data\\zwk9-jobs-test2.txt");
	v.push_back(res);

	for (auto i : v)
	{
		cout << i << " ";
	}
	cout << endl;

	/*
	result :
	sub		69119377652 23 41
	ratio	67311454237 22 40
	*/
}

//////////////////////////////////////////////////////////////////////////
// PrimMST

class PrimGraph
{
public:
	void Load(const string& fn)
	{
		fstream f(fn, ios::in);
		if (!f) { abort(); }

		f >> v;
		f >> e;
		if (!f) abort();

		vtDist.assign(v + 1, maxDist);
		vtSrc.assign(v + 1, false);
		vtVertices.assign(v + 1, vector<Edge>());
		vtSrc[0] = true;

		int s = 0;
		int t = 0;
		int w = 0;
		int i = 0;
		while (f >> s && f >> t && f >> w)
		{
			++i;
			if (s > v || t > v) abort();
			vtVertices[s].push_back(Edge(t, w));
			vtVertices[t].push_back(Edge(s, w));
		}
		if (i != e) abort();
	};

	int64_t Mst(void)
	{
		int length = v;
		auto& v1 = vtVertices[1];
		for (auto& i : v1)
		{
			vtDist[i.t] = i.w;
		}
		vtSrc[1] = true;

		int64_t cost = 0;

		while (--length)
		{
			auto p = min_element(vtDist.begin(), vtDist.end());
			auto i = p - vtDist.begin();
			vtSrc[i] = true;
			cost += vtDist[i];
			vtDist[i] = maxDist;
			// update i-t weight
			auto vi = vtVertices[i];
			for (auto& ei : vi)
			{
				auto t = ei.t;
				auto w = ei.w;
				if (vtSrc[t])
				{
					continue;
				}
				if (w < vtDist[t])
				{
					vtDist[t] = w;
				}
			}
		}
		return cost;
	}
private:
	struct Edge
	{
		Edge(int tt, int ww) : t(tt), w(ww) {};
		int t = 0;
		int w = 0;
	};
	// 1-based
	vector<int> vtDist;
	vector<bool> vtSrc;
	vector<vector<Edge>> vtVertices;
	int v = 0;
	int e = 0;
	const int maxDist = 1000000;
};

void PrimMST(const string& fn)
{
	PrimGraph pg;
	pg.Load(fn);
	cout << pg.Mst() << endl;
}

void PrimTest(void)
{
	PrimMST("data\\zwk9-edges-test1.txt"); // 7
	PrimMST("data\\zwk9-edges-test2.txt"); // 14
	PrimMST("data\\zwk9-edges.txt"); // -3612829
}

void Greedy(void)
{
	Mws();
	PrimTest();
}