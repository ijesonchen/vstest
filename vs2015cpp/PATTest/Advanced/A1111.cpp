/*
1111. Online Map (30)

300 ms

Input our current position and a destination, an online map can recommend several paths. 
Now your job is to recommend two paths to your user: 
one is the shortest, and the other is the fastest. 
It is guaranteed that a path exists for any request.

Input Specification:

Each input file contains one test case. 
For each case, the first line gives two positive integers N (2 <= N <= 500), and M, 
being the total number of streets intersections on a map, and the number of streets, respectively. 
Then M lines follow, each describes a street in the format:

V1 V2 one-way length time

where V1 and V2 are the indices (from 0 to N-1) of the two ends of the street; 
one-way is 1 if the street is one-way from V1 to V2, or 0 if not; 
length is the length of the street;
and time is the time taken to pass the street.

Finally a pair of source and destination is given.

Output Specification:

For each case, first print the shortest path from the source to the destination with distance D in the format:

Distance = D: source -> v1 -> ... -> destination

Then in the next line print the fastest path with total time T:

Time = T: source -> w1 -> ... -> destination

In case the shortest path is not unique, 
output the fastest one among the shortest paths, 
which is guaranteed to be unique. 

In case the fastest path is not unique, 
output the one that passes through the fewest intersections, 
which is guaranteed to be unique.

In case the shortest and the fastest paths are identical, print them in one line in the format:
Distance = D; Time = T: source -> u1 -> ... -> destination

Sample Input 1:
10 15
0 1 0 1 1
8 0 0 1 1
4 8 1 1 1
3 4 0 3 2
3 9 1 4 1
0 6 0 1 1
7 5 1 2 1
8 5 1 2 1
2 3 0 2 2
2 1 1 1 1
1 3 0 3 1
1 4 0 1 1
9 7 1 3 1
5 1 0 5 2
6 5 1 1 2
3 5
Sample Output 1:
Distance = 6: 3 -> 4 -> 8 -> 5
Time = 3: 3 -> 1 -> 5
Sample Input 2:
7 9
0 4 1 1 1
1 6 1 1 3
2 6 1 1 1
2 5 1 2 2
3 0 0 1 1
3 1 1 1 3
3 2 1 1 2
4 5 0 2 2
6 5 1 1 2
3 5
Sample Output 2:
Distance = 3; Time = 4: 3 -> 2 -> 5
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
REF: liuchuo： 两遍dijkstra+dfs

Dijkstra+DFS重建路径要比dfs剪枝搜索要快
*/
namespace nsA111C
{
	const int MAXVALUE = 0x7fffffff;

	struct Edge
	{
		int v = 0;
		int d = 0;
		int t = 0;

		Edge(int v1, int len1, int t1)
			: v(v1), d(len1), t(t1)
		{};
	};

	int nNode; // [2,500], 0-based
	int nEdge; // pos
	int iSrc;
	int iDst;
	vector<vector<Edge>> vvAdj;

	// diskstra shortest path
	vector<bool> vVisit;
	vector<int> vPath;
	vector<int> vDist;
	vector<int> pathDist;
	int nDist;
	int nDistCost;
	vector<int> vTime;
	vector<int> pathTime;
	int nTime;
	int nTimeCost;

	struct Dist
	{
		int idx = 0;
		int dist = 0;
		Dist(int i, int d):idx(i), dist(d) {}

		bool operator<(const Dist& a) const
		{ return dist < a.dist; }
	};

	bool DistLess(const Dist* p1, const Dist* p2)
	{ return *p1 < *p2; }

	bool IntLess(const int* p1, const int* p2)
	{ return *p1 < *p2; }
	
	void PrintPath(const vector<int>& vPath)
	{
		cout << vPath.front();
		for (size_t i = 1; i < vPath.size(); ++i)
		{
			cout << " -> " << vPath[i];
		}
		cout << endl;
	}

	void DijkstraDist(void)
	{
		vVisit.assign(nNode, false);

		int n = nNode;
		vDist.assign(nNode, MAXVALUE);
		vDist[iSrc] = 0;
		
		while (n--)
		{
			size_t u = 0;
			int nMin = MAXVALUE;
			for (size_t i = 0; i < vDist.size(); ++i)
			{
				if (!vVisit[i] && vDist[i] < nMin)
				{
					u = i;
					nMin = vDist[i];
				}
			}
			vVisit[u] = true;
			auto uDist = vDist[u];
			for (auto& e : vvAdj[u])
			{
				if (!vVisit[e.v] && uDist + e.d < vDist[e.v])
				{
					vDist[e.v] = uDist + e.d;
				}
			}
		}		
	}

	void DfsDist(const int start, const int dist, int const cost)
	{
		if (dist > vDist[start]) { return; }
		if (start == iDst)
		{
			if (dist < nDist)
			{
				pathDist = vPath;
				nDist = dist;
				nDistCost = cost;
			}
			else if (dist == nDist && cost < nDistCost)
			{
				pathDist = vPath;
				nDist = dist;
				nDistCost = cost;
			}
			return;
		}
		for (auto& e : vvAdj[start])
		{
			if (!vVisit[e.v])
			{
				vVisit[e.v] = true;
				vPath.push_back(e.v);
				DfsDist(e.v, dist + e.d, cost + e.t);
				vPath.pop_back();
				vVisit[e.v] = false;
			}
		}
	}


	void DijkstraTime(void)
	{
		vVisit.assign(nNode, false);

		int n = nNode;
		vTime.assign(nNode, MAXVALUE);
		vTime[iSrc] = 0;
		while (n--)
		{
			size_t u = 0;
			int nMin = MAXVALUE;
			for (size_t i = 0; i < vTime.size(); ++i)
			{
				if (!vVisit[i] && vTime[i] < nMin)
				{
					u = i;
					nMin = vTime[i];
				}
			}
			vVisit[u] = true;
			auto uTime = vTime[u];
			for (auto& e : vvAdj[u])
			{
				if (!vVisit[e.v] && uTime + e.t < vTime[e.v])
				{
					vTime[e.v] = uTime + e.t;
				}
			}
		}

	}


	void DfsTime(const int start, const int ntime, int const cost)
	{
		if (ntime > vTime[start]) { return; }
		if (start == iDst)
		{
			if (ntime < nTime ||
				(ntime == nTime && cost < nTimeCost))
			{
				pathTime = vPath;
				nTime = ntime;
				nTimeCost = cost;
			}
			return;
		}
		for (auto& e : vvAdj[start])
		{
			if (!vVisit[e.v])
			{
				vVisit[e.v] = true;
				vPath.push_back(e.v);
				DfsTime(e.v, ntime + e.t, cost + 1);
				vPath.pop_back();
				vVisit[e.v] = false;
			}
		}
	}

	void main(void)
	{
		// V1 V2 one-way length time

		cin >> nNode >> nEdge;
		int u, v, len, t;
		bool tag;
		vvAdj.assign(nNode, vector<Edge>());
		for (int i = 0; i < nEdge; ++i)
		{
			cin >> u >> v >> tag >> len >> t;
			vvAdj[u].emplace_back(v,len,t);
			if (!tag)
			{ vvAdj[v].emplace_back(u, len, t); }
		}
		cin >> iSrc >> iDst;
		
		DijkstraDist();
		vVisit.assign(nNode, false);
		nDist = MAXVALUE;
		nDistCost = MAXVALUE;
		vPath.clear();
		vPath.push_back(iSrc);
		DfsDist(iSrc, 0, 0);

		DijkstraTime();
		vVisit.assign(nNode, false);
		nTime = MAXVALUE;
		nTimeCost = MAXVALUE;
		vPath.clear();
		vPath.push_back(iSrc);
		DfsTime(iSrc, 0, 0);

		if (pathDist == pathTime)
		{
			// Distance = 3; Time = 4: 3 -> 2 -> 5
			cout << "Distance = " << nDist << "; Time = " << nTime << ": ";
		}
		else
		{
			cout << "Distance = " << nDist << ": ";
			PrintPath(pathDist);
			cout << "Time = " << nTime << ": ";
		}
		PrintPath(pathTime);


	}
}

// rename this to main int PAT
int A1111Func(void)
{
	nsA111C::main();
	return 0;
}


void A1111(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1111Func();
	cout << endl;
}

void A1111(void)
{
	A1111("data\\A1111-1.txt"); // 
	A1111("data\\A1111-2.txt"); // 
}


/*
16:05
路径一定存在
顶点N:[2,500]
可能有单向路
0-based

长度最短路径（相同取时长最小）
时间最短路径（相同取定点最少）
而这路径相同，合并输出
16:50 27/30 PT4 TLE

保存DFS中间结果(Dijkstra数组)，进一步减枝
17:00 TLE
此时应该放弃该题目

改进：合并两次搜索
17:20 18/30 PT0 错误 PT4 TLE

改进：使用Dijkstra改进？
*/

namespace nsA111A
{
	const int MAXVALUE = 0x7fffffff;
	vector<vector<int>> vvDist;
	vector<vector<int>> vvTime;

	void Reset(int n)
	{
		vvDist.assign(n, vector<int>(n));
		vvTime.assign(n, vector<int>(n));
	}

	int srcNode, dstNode;

	vector<int> pathTemp;
	vector<bool> vVisit;
	vector<int> vAssist;

	int minDist = MAXVALUE;
	int minDistTime = MAXVALUE;
	vector<int> vDist;
	vector<int> pathDist;

	int minTime = MAXVALUE;
	int minTimeTrans = MAXVALUE;
	vector<int> vTime;
	vector<int> pathTime;


	void Dfs(int u, int distTime, int trans)
	{
		if (u == dstNode)
		{
			int dist = vDist[u];
			if (dist < minDist ||
				(dist == minDist && distTime < minDistTime))
			{
				pathDist = pathTemp;
				minDist = dist;
				minDistTime = distTime;
			}
			int t = vTime[u];
			if (t < minTime ||
				(t == minTime && trans < minTimeTrans))
			{
				pathTime = pathTemp;
				minTime = t;
				minTimeTrans = trans;
			}
			return;
		}

		vector<int>& vAdjDist = vvDist[u];
		vector<int>& vAdjTime = vvTime[u];
		for (size_t i = 0; i < vAdjDist.size(); ++i)
		{
			if (!vVisit[i] && vAdjDist[i])
			{
				int iDist = vDist[u] + vAdjDist[i];
				int iTime = vTime[u] + vAdjTime[i];
				if (iDist > vDist[i] && iTime > vTime[i])
				{
					continue;
				}
				if (iDist < vDist[i]) { vDist[i] = iDist; }
				if (iTime < vTime[i]) { vTime[i] = iTime; }

				vVisit[i] = true;
				pathTemp.push_back((int)i);
				Dfs((int)i, distTime + vAdjTime[i], trans + 1);
				vVisit[i] = false;
				pathTemp.pop_back();
			}
		}
	}

	void DfsDist(int u, int dist, int distTime)
	{
		if (dist > vAssist[u]) { return; }
		if (u == dstNode)
		{
			if (dist < minDist ||
				(dist == minDist && distTime < minDistTime))
			{
				pathDist = pathTemp;
				minDist = dist;
				minDistTime = distTime;
			}
			return;
		}
		vector<int>& vAdj = vvDist[u];
		for (size_t i = 0; i < vAdj.size(); ++i)
		{
			if (!vVisit[i] && vAdj[i])
			{
				int iDist = dist + vAdj[i];
				if (iDist > vAssist[i])
				{
					continue;
				}
				vAssist[i] = iDist;
				vVisit[i] = true;
				pathTemp.push_back((int)i);
				DfsDist((int)i, iDist, distTime + vvTime[u][i]);
				vVisit[i] = false;
				pathTemp.pop_back();
			}
		}
	}

	void DfsTime(int u, int t, int trans)
	{
		if (t > vAssist[u]) { return; }
		if (u == dstNode)
		{
			if (t < minTime ||
				(t == minTime && trans < minTimeTrans))
			{
				pathTime = pathTemp;
				minTime = t;
				minTimeTrans = trans;
			}
			return;
		}
		vector<int>& vAdj = vvTime[u];
		for (size_t i = 0; i < vAdj.size(); ++i)
		{
			if (!vVisit[i] && vAdj[i])
			{
				int iTime = t + vAdj[i];
				if (iTime > vAssist[i])
				{
					continue;
				}
				vAssist[i] = iTime;
				vVisit[i] = true;
				pathTemp.push_back((int)i);
				DfsTime((int)i, iTime, trans + 1);
				vVisit[i] = false;
				pathTemp.pop_back();
			}
		}
	}

	void PrintPath(const vector<int>& vPath)
	{
		cout << vPath.front();
		for (size_t i = 1; i < vPath.size(); ++i)
		{
			cout << " -> " << vPath[i];
		}
		cout << endl;
	}

	void main(void)
	{
		int n, m;
		cin >> n >> m;
		Reset(n);
		for (int i = 0; i < m; ++i)
		{
			int u, v, tag, dist, t;
			cin >> u >> v >> tag >> dist >> t;
			vvDist[u][v] = dist;
			vvTime[u][v] = t;
			if (!tag)
			{
				vvDist[v][u] = dist;
				vvTime[v][u] = t;
			}
		}

		cin >> srcNode >> dstNode;

		pathTemp.clear();
		vVisit.assign(n, false);
		vDist.assign(n, MAXVALUE);
		vTime.assign(n, MAXVALUE);
		minDist = MAXVALUE;
		minDistTime = MAXVALUE;
		minTime = MAXVALUE;
		minTimeTrans = MAXVALUE;

		vVisit[srcNode] = true;
		pathTemp.push_back(srcNode);
		Dfs(srcNode, 0, 0);

		if (pathDist == pathTime)
		{
			// Distance = 3; Time = 4: 3 -> 2 -> 5
			cout << "Distance = " << minDist << "; Time = " << minTime << ": ";
		}
		else
		{
			cout << "Distance = " << minDist << ": ";
			PrintPath(pathDist);
			cout << "Time = " << minTime << ": ";
		}
		PrintPath(pathTime);
	}
}


namespace nsA111B
{
	const int MAXVALUE = 0x7fffffff;
	vector<vector<int>> vvDist;
	vector<vector<int>> vvTime;

	void Reset(int n)
	{
		vvDist.assign(n, vector<int>(n));
		vvTime.assign(n, vector<int>(n));
	}

	int srcNode, dstNode;

	vector<int> pathTemp;
	vector<bool> vVisit;

	int minDist = MAXVALUE;
	int minDistTime = MAXVALUE;
	vector<int> vDist;
	vector<int> pathDist;

	int minTime = MAXVALUE;
	int minTimeTrans = MAXVALUE;
	vector<int> vTime;
	vector<int> pathTime;


	void Dfs(int u, int distTime, int trans)
	{
		if (u == dstNode)
		{
			int dist = vDist[u];
			if (dist < minDist ||
				(dist == minDist && distTime < minDistTime))
			{
				pathDist = pathTemp;
				minDist = dist;
				minDistTime = distTime;
			}
			int t = vTime[u];
			if (t < minTime ||
				(t == minTime && trans < minTimeTrans))
			{
				pathTime = pathTemp;
				minTime = t;
				minTimeTrans = trans;
			}
			return;
		}

		vector<int>& vAdjDist = vvDist[u];
		vector<int>& vAdjTime = vvTime[u];
		for (size_t i = 0; i < vAdjDist.size(); ++i)
		{
			if (!vVisit[i] && vAdjDist[i])
			{
				int iDist = vDist[u] + vAdjDist[i];
				int iTime = vTime[u] + vAdjTime[i];
				if (iDist > vDist[i] && iTime > vTime[i])
				{
					continue;
				}
				if (iDist < vDist[i]) { vDist[i] = iDist; }
				if (iTime < vTime[i]) { vTime[i] = iTime; }

				vVisit[i] = true;
				pathTemp.push_back((int)i);
				Dfs((int)i, distTime + vAdjTime[i], trans + 1);
				vVisit[i] = false;
				pathTemp.pop_back();
			}
		}
	}

	void PrintPath(const vector<int>& vPath)
	{
		cout << vPath.front();
		for (size_t i = 1; i < vPath.size(); ++i)
		{
			cout << " -> " << vPath[i];
		}
		cout << endl;
	}

	void main(void)
	{
		int n, m;
		cin >> n >> m;
		Reset(n);
		for (int i = 0; i < m; ++i)
		{
			int u, v, tag, dist, t;
			cin >> u >> v >> tag >> dist >> t;
			vvDist[u][v] = dist;
			vvTime[u][v] = t;
			if (!tag)
			{
				vvDist[v][u] = dist;
				vvTime[v][u] = t;
			}
		}

		cin >> srcNode >> dstNode;

		pathTemp.clear();
		vVisit.assign(n, false);
		vDist.assign(n, MAXVALUE);
		vTime.assign(n, MAXVALUE);
		minDist = MAXVALUE;
		minDistTime = MAXVALUE;
		minTime = MAXVALUE;
		minTimeTrans = MAXVALUE;

		vVisit[srcNode] = true;
		vDist[srcNode] = 0;
		vTime[srcNode] = 0;
		pathTemp.push_back(srcNode);
		Dfs(srcNode, 0, 0);

		if (pathDist == pathTime)
		{
			// Distance = 3; Time = 4: 3 -> 2 -> 5
			cout << "Distance = " << minDist << "; Time = " << minTime << ": ";
		}
		else
		{
			cout << "Distance = " << minDist << ": ";
			PrintPath(pathDist);
			cout << "Time = " << minTime << ": ";
		}
		PrintPath(pathTime);
	}
}
