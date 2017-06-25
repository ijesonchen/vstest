/*
In this programming problem you'll code up Dijkstra's shortest-path algorithm.

Download the following text file:
dijkstraData.txt

The file contains an adjacency list representation of an undirected weighted graph 
with 200 vertices labeled 1 to 200. Each row consists of the node tuples that are
adjacent to that particular vertex along with the length of that edge. For example,
the 6th row has 6 as the first entry indicating that this row corresponds to the 
vertex labeled 6. The next entry of this row "141,8200" indicates that there is an
edge between vertex 6 and vertex 141 that has length 8200. The rest of the pairs of
this row indicate the other vertices adjacent to vertex 6 and the lengths of the 
corresponding edges.

Your task is to run Dijkstra's shortest-path algorithm on this graph, using 1 (the 
first vertex) as the source vertex, and to compute the shortest-path distances 
between 1 and every other vertex of the graph. If there is no path between a vertex 
v and vertex 1, we'll define the shortest-path distance between 1 and v to be 1000000.

You should report the shortest-path distances to the following ten vertices, in order: 
7,37,59,82,99,115,133,165,188,197. You should encode the distances as a comma-separated 
string of integers. So if you find that all ten of these vertices except 115 are at 
distance 1000 away from vertex 1 and 115 is 2000 distance away, then your answer should 
be 1000,1000,1000,1000,1000,2000,1000,1000,1000,1000. Remember the order of reporting 
DOES MATTER, and the string should be in the same order in which the above ten vertices 
are given. The string should not contain any spaces. Please type your answer in the 
space provided.

IMPLEMENTATION NOTES: This graph is small enough that the straightforward O(mn) time 
implementation of Dijkstra's algorithm should work fine. 

OPTIONAL: For those of you seeking an additional challenge, try implementing the 
heap-based version. Note this requires a heap that supports deletions, and you'll probably 
need to maintain some kind of mapping between vertices and their positions in the heap.
*/

/*
result for wk6-test1-8.txt
1 0 []
2 1 [2]
3 2 [2, 3]
4 3 [2, 3, 4]
5 4 [2, 3, 4, 5]
6 4 [8, 7, 6]
7 3 [8, 7]
8 2 [8]
*/

#include <vector>
#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <algorithm>
#include "common.h"

using namespace std;

struct Edge
{
//	Edge(int a, int b) : v(a), w(b) {}
	int v; // vertex
	int w; // weight
};

// undirected, weighted
class WeightedGraph
{
public:
	WeightedGraph(int nVertices)
		: adj(nVertices + 1)
	{
	}

	void AddEdge(int from, int to, int weight) { adj[from].push_front({ to, weight }); ++nEdge; }
	int V(void) const { return adj.size() - 1; }
	int E(void) const { return nEdge; }
	deque<Edge> Adj(int v) const { return adj[v]; };

	WeightedGraph Reverse(void)
	{
		WeightedGraph g(V());
		for (int from = 1; from < adj.size(); ++from)
		{
			for (auto to : adj[from])
			{
				g.AddEdge(to.v, from, to.w);
			}
		}
		return g;
	}

	void Print(void)
	{
		cout << V() << " " << E() << endl;
		for (int i = 1; i < adj.size(); ++i)
		{
			cout << i << ": ";
			for (auto n : adj[i]) { cout << n.v << "," << n.w << " "; }
			cout << endl;
		}
	}

	void Print0Base(void)
	{
		cout << V() << " " << E() << endl;
		for (int i = 1; i < adj.size(); ++i)
		{
			cout << i - 1 << ": ";
			for (auto n : adj[i]) { cout << n.v - 1 << "," << n.w << " "; }
			cout << endl;
		}
	}
private:
	vector<deque<Edge>> adj;
	int nEdge = 0;
};

class ShortestPath
{
public:
	ShortestPath(const WeightedGraph& g, int src)
		:graph(g)
	{
		auto len = graph.V();
		marked.assign(len + 1, false);
		dist.assign(len + 1, 1000000);
		dist[src] = 0;
		srcNodes.push_back(src);
		for (int i = 1; i <= len; ++i)
		{
			if (i != src)
			{
				dstNodes.push_back(i);
			}
		}
		for (auto dst : graph.Adj(src))
		{
			dist[dst.v] = dst.w;
		}
	}

	void Calc(void)
	{
		if (dstNodes.empty())
		{
			return;
		}
		// find min dst
		while (!dstNodes.empty())
		{
			int minDstVertex = 0;
			int minLen = 1000001;
			int nPos = -1;
			for (int ii = 0, ni = dstNodes.size(); ii < ni; ++ii)
			{				
				auto idx = dstNodes[ii];
				if (dist[idx] < minLen)
				{
					minDstVertex = idx;
					minLen = dist[idx];
					nPos = ii;
				}
			}
			if (nPos < 0)
			{
				abort();
			}
			dstNodes.erase(dstNodes.begin() + nPos);
			srcNodes.push_back(minDstVertex);
			dist[minDstVertex] = minLen;
			UpdateDstLen(minDstVertex);
		}
	}

	void PrintDst()
	{
		cout << "dist: " << endl;
		for (int i = 1; i < dist.size(); ++i)
		{
			cout << i << ": " << dist[i] << " ";
		}
		cout << endl;
	}

private:
	void UpdateDstLen(int src)
	{
		auto srcDist = dist[src];
		for (auto dst : graph.Adj(src))
		{
			if (dstNodes.end() != find(dstNodes.begin(), dstNodes.end(), dst.v))
			{
				auto& oldDist = dist[dst.v];
				auto newDist = srcDist + dst.w;
				if (newDist < oldDist)
				{
					oldDist = newDist;
				}
			}
		}
	}
	vector<bool> marked;
	vector<int64_t> dist;
	vector<int> srcNodes;
	vector<int> dstNodes;
	WeightedGraph graph;
};

WeightedGraph ReadFromFile(const std::string& fileName, int nVertices)
{
	WeightedGraph g(nVertices);

	fstream f(fileName, ios::in);
	if (!f) { abort(); }
	string s;
	while (getline(f, s))
	{
		for (auto& ch : s)
		{
			if (ch == ',') ch = ' ';
		}
		stringstream ss(s);
		int x;
		int vertex;
		int weight;
		ss >> x;
		while (ss >> vertex && ss >> weight)
		{
			g.AddEdge(x, vertex, weight);
		}
	}
	return g;
}


void DijkstraShortestPath(void)
{
//	auto g = ReadFromFile("data\\wk6-test1-8.txt", 8);
	auto g = ReadFromFile("data\\wk6-dijkstra-200.txt", 200);

	/*
	dist:
	1: 0 2: 2971 3: 2644 4: 3056 5: 2525 6: 2818 7: 2599 8: 1875 9: 745 10: 3205 11: 1551 12: 2906 13: 2394 14: 1803 15: 2942 16: 1837 17: 3111
	18: 2284 19: 1044 20: 2351 21: 3630 22: 4028 23: 2650 24: 3653 25: 2249 26: 2150 27: 1222 28: 2090 29: 3540 30: 2303 31: 3455 32: 3004 33: 2
	551 34: 2656 35: 998 36: 2236 37: 2610 38: 3548 39: 1851 40: 4091 41: 2732 42: 2040 43: 3312 44: 2142 45: 3438 46: 2937 47: 2979 48: 2757 49
	: 2437 50: 3152 51: 2503 52: 2817 53: 2420 54: 3369 55: 2862 56: 2609 57: 2857 58: 3668 59: 2947 60: 2592 61: 1676 62: 2573 63: 2498 64: 204
	7 65: 826 66: 3393 67: 2535 68: 4636 69: 3650 70: 743 71: 1265 72: 1539 73: 3007 74: 4286 75: 2720 76: 3220 77: 2298 78: 2795 79: 2806 80: 9
	82 81: 2976 82: 2052 83: 3997 84: 2656 85: 1193 86: 2461 87: 1608 88: 3046 89: 3261 90: 2018 91: 2786 92: 647 93: 3542 94: 3415 95: 2186 96:
	2398 97: 4248 98: 3515 99: 2367 100: 2970 101: 3536 102: 2478 103: 1826 104: 2551 105: 3368 106: 2303 107: 2540 108: 1169 109: 3140 110: 23
	17 111: 2535 112: 1759 113: 1899 114: 508 115: 2399 116: 3513 117: 2597 118: 2176 119: 1090 120: 2328 121: 2818 122: 1306 123: 2805 124: 205
	7 125: 2618 126: 1694 127: 3285 128: 1203 129: 676 130: 1820 131: 1445 132: 2468 133: 2029 134: 1257 135: 1533 136: 2417 137: 3599 138: 2494
	139: 4101 140: 546 141: 1889 142: 2616 143: 2141 144: 2359 145: 648 146: 2682 147: 3464 148: 2873 149: 3109 150: 2183 151: 4159 152: 1832 1
	53: 2080 154: 1831 155: 2001 156: 3013 157: 2143 158: 1376 159: 1627 160: 2403 161: 4772 162: 2556 163: 2124 164: 1693 165: 2442 166: 3814 1
	67: 2630 168: 2038 169: 2776 170: 1365 171: 3929 172: 1990 173: 2069 174: 3558 175: 1432 176: 2279 177: 3829 178: 2435 179: 3691 180: 3027 1
	81: 2345 182: 3807 183: 2145 184: 2703 185: 2884 186: 3806 187: 1151 188: 2505 189: 2340 190: 2596 191: 4123 192: 1737 193: 3136 194: 1073 1
	95: 1707 196: 2417 197: 3068 198: 1724 199: 815 200: 2060
	*/
	ShortestPath sp(g, 1);
	sp.Calc();
	sp.PrintDst();
}