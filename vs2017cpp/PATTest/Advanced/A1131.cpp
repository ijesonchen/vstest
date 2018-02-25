/*
1131. Subway Map (30)

cost: 11:00 2h

总结：不熟悉多最短路径搜索，导致编码慢，并且有bug
	打印路径编码较慢。

test: m > 0

sln1: 
	1. bfs搜索最短路径
	2. dfs减枝搜索最少换乘站
	3. 打印路径
		3.1 每条边所属line EDGE-LINE map映射，key：s1*10000+s2
		3.2 检查下一边和上一边是否相同line
	n: 线路数 1-100
	m：站点数 1-100
		站点标识 0000-9999 10000个
		每个站点最多5条线（10个边，稀疏矩阵）
		最多9900条边
	k：查询数 1-10
	2h pass

sln: ref: luochuo
	通过一遍DFS减枝搜索路径
	将nsA1131修改为
	nsA1131RefOneDfs
	10min 7/30 pt0,2,3 WA
	
	bug-fix: 路径判断条件错误
	dist < minDist ||
	(dist == minDist && trans < minTrans)
	10min pass

In the big cities, the subway systems always look so complex to the visitors. 
To give you some sense, the following figure shows the map of Beijing subway.
Now you are supposed to help people with your computer skills! 
Given the starting position of your user, 
your task is to find the quickest way to his/her destination.


Input Specification:

Each input file contains one test case. 
For each case, the first line contains a positive integer N (< =100), 
the number of subway lines. 
Then N lines follow, with the i-th (i = 1, ..., N) line describes the i-th subway line in the format:

M S[1] S[2] ... S[M]

where M (<= 100) is the number of stops, 
and S[i]'s (i = 1, ... M) are the indices of the stations 
(the indices are 4-digit numbers from 0000 to 9999) along the line. 
It is guaranteed that the stations are given in the correct order -- that is, 
the train travels between S[i] and S[i+1] (i = 1, ..., M-1) without any stop.

Note: It is possible to have loops, but not self-loop 
(no train starts from S and stops at S without passing through another station). 
Each station interval belongs to a unique subway line. 

Although the lines may cross each other at some stations (so called "transfer stations"), 
no station can be the conjunction of more than 5 lines.

After the description of the subway, another positive integer K (<= 10) is given. 
Then K lines follow, each gives a query from your user: 
the two indices as the starting station and the destination, respectively.

The following figure shows the sample map.


Note: It is guaranteed that all the stations are reachable, 
and all the queries consist of legal station numbers.

Output Specification:

For each query, first print in a line the minimum number of stops. 
Then you are supposed to show the optimal path in a friendly format as the following:

Take Line#X1 from S1 to S2.
Take Line#X2 from S2 to S3.
......
where Xi's are the line numbers and Si's are the station indices.
Note: Besides the starting and ending stations, only the transfer stations shall be printed.

If the quickest path is not unique, output the one with the minimum number of transfers, 
which is guaranteed to be unique.

Sample Input:
4
7 1001 3212 1003 1204 1005 1306 7797
9 9988 2333 1204 2006 2005 2004 2003 2302 2001
13 3011 3812 3013 3001 1306 3003 2333 3066 3212 3008 2302 3010 3011
4 6666 8432 4011 1306
3
3011 3013
6666 2001
2004 3001
Sample Output:
2
Take Line#3 from 3011 to 3013.
10
Take Line#4 from 6666 to 1306.
Take Line#3 from 1306 to 2302.
Take Line#2 from 2302 to 2001.
6
Take Line#2 from 2004 to 1204.
Take Line#1 from 1204 to 1306.
Take Line#3 from 1306 to 3001.
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>

using namespace std;

namespace nsA1131A
{
	typedef unordered_map<int, int> MapIntInt;


	const int MAXNODE = 10000;
	vector<vector<int>> vAdjencents;
	MapIntInt mapEdge2Line;

	// for search
	int dstNode = 0;
	vector<int> vDist;
	int minTrans = MAXNODE;
	vector<int> vPathNode;
	vector<int> vPathTemp;
	vector<bool> vVisit;

	int EdgeId(int s1, int s2) { return (s1 << 16) + s2; }
	int EdgeSrc(int e) { return e >> 16; }
	int EdgeDst(int e) { return e & 0xFFFF; }

	void Read()
	{
		vAdjencents.assign(MAXNODE, vector<int>());
		mapEdge2Line.clear();

		int n, m;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			int line = i + 1;
			int s1, s2;
			cin >> m >> s1;
			for (int j = 1; j < m; ++j)
			{
				cin >> s2;
				vAdjencents[s1].push_back(s2);
				vAdjencents[s2].push_back(s1);
				mapEdge2Line[EdgeId(s1, s2)] = line;
				mapEdge2Line[EdgeId(s2, s1)] = line;
				s1 = s2;
			}
		}
	}

	void Bfs(int s1)
	{
		vDist.assign(MAXNODE, 0);
		vVisit.assign(MAXNODE, false);
		vVisit[s1] = true;
		deque<int> dqNodes;
		dqNodes.push_back(s1);
		while (!dqNodes.empty())
		{
			int u = dqNodes.front();
			int distu = vDist[u];
			dqNodes.pop_front();
			vector<int>& vAdj = vAdjencents[u];
			for (auto v : vAdj)
			{
				if (vVisit[v])
				{
					continue;
				}
				vDist[v] = distu + 1;
				vVisit[v] = true;
				dqNodes.push_back(v);
			}
		}
	}

	void Dfs(int from, int dist, int trans, int line)
	{
		if (dist > vDist[from])
		{
			return;
		}
		if (from == dstNode)
		{
			// found path
			if (trans < minTrans)
			{
				minTrans = trans;
				vPathNode = vPathTemp;
			}
			return;
		}
		vector<int>& vAdj = vAdjencents[from];
		for (auto next : vAdj)
		{
			if (vVisit[next])
			{
				continue;
			}
			int nextTrans = trans;
			int nextLine = mapEdge2Line[EdgeId(from, next)];
			if (line != -1 && line != nextLine)
			{
				++nextTrans;
			}
			vVisit[next] = true;
			vPathTemp.push_back(next);
			Dfs(next, dist + 1, nextTrans, nextLine);
			vVisit[next] = false;
			vPathTemp.pop_back();
		}
	}

	void PrintLine(int line, int from, int to)
	{
		// Take Line#3 from 3011 to 3013.
		printf("Take Line#%d from %04d to %04d.\n", line, from, to);
	}

	void PrintPath(void) 
	{
		size_t len = vPathNode.size();
		cout << len - 1 << endl;
		int from = vPathNode[0];
		int to = vPathNode[1];
		int line1 = mapEdge2Line[EdgeId(from, to)];
		for (int i = 2; i < len; ++i)
		{
			int next = vPathNode[i];
			int line2 = mapEdge2Line[EdgeId(to, next)];
			if (line2 != line1)
			{
				PrintLine(line1, from, to);
				from = to;
				line1 = line2;
			}
			to = next;
		}
		PrintLine(line1, from, to);
	}

	void ResetDfs(int src, int dst)
	{
		dstNode = dst;
		minTrans = MAXNODE;
		vPathNode.clear();
		vPathTemp.clear();
		vVisit.assign(MAXNODE, false);
		vVisit[src] = true;
		vPathTemp.push_back(src);
	}

	void Search(int s1, int s2)
	{
		Bfs(s1);
		ResetDfs(s1, s2);
		Dfs(s1, 0, 0, -1);
		PrintPath();
	}

	void Query(void)
	{
		int k, s1, s2;
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> s1 >> s2;
			Search(s1, s2);
		}
	}

	void main(void)
	{
		Read();
		Query();
	}
}

// ref: luochuo
// 修改为只用一遍DFS搜索路径
namespace nsA1131RefOneDfs
{
	typedef unordered_map<int, int> MapIntInt;


	const int MAXNODE = 10000;
	vector<vector<int>> vAdjencents;
	MapIntInt mapEdge2Line;

	// for search
	int dstNode = 0;
	int minDist = MAXNODE;
	int minTrans = MAXNODE;
	vector<int> vPathNode;
	vector<int> vPathTemp;
	vector<bool> vVisit;

	int EdgeId(int s1, int s2) { return (s1 << 16) + s2; }
	int EdgeSrc(int e) { return e >> 16; }
	int EdgeDst(int e) { return e & 0xFFFF; }

	void Read()
	{
		vAdjencents.assign(MAXNODE, vector<int>());
		mapEdge2Line.clear();

		int n, m;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			int line = i + 1;
			int s1, s2;
			cin >> m >> s1;
			for (int j = 1; j < m; ++j)
			{
				cin >> s2;
				vAdjencents[s1].push_back(s2);
				vAdjencents[s2].push_back(s1);
				mapEdge2Line[EdgeId(s1, s2)] = line;
				mapEdge2Line[EdgeId(s2, s1)] = line;
				s1 = s2;
			}
		}
	}

	void Dfs(int from, int dist, int trans, int line)
	{
		if (dist > minDist)
		{
			return;
		}
		if (from == dstNode)
		{
			// found path
			if (dist < minDist ||
				(dist == minDist && trans < minTrans))
			{
				minDist = dist;
				minTrans = trans;
				vPathNode = vPathTemp;
			}
			return;
		}
		vector<int>& vAdj = vAdjencents[from];
		for (auto next : vAdj)
		{
			if (vVisit[next])
			{
				continue;
			}
			int nextTrans = trans;
			int nextLine = mapEdge2Line[EdgeId(from, next)];
			if (line != -1 && line != nextLine)
			{
				++nextTrans;
			}
			vVisit[next] = true;
			vPathTemp.push_back(next);
			Dfs(next, dist + 1, nextTrans, nextLine);
			vVisit[next] = false;
			vPathTemp.pop_back();
		}
	}

	void PrintLine(int line, int from, int to)
	{
		// Take Line#3 from 3011 to 3013.
		printf("Take Line#%d from %04d to %04d.\n", line, from, to);
	}

	void PrintPath(void)
	{
		size_t len = vPathNode.size();
		cout << len - 1 << endl;
		int from = vPathNode[0];
		int to = vPathNode[1];
		int line1 = mapEdge2Line[EdgeId(from, to)];
		for (int i = 2; i < len; ++i)
		{
			int next = vPathNode[i];
			int line2 = mapEdge2Line[EdgeId(to, next)];
			if (line2 != line1)
			{
				PrintLine(line1, from, to);
				from = to;
				line1 = line2;
			}
			to = next;
		}
		PrintLine(line1, from, to);
	}

	void ResetDfs(int src, int dst)
	{
		dstNode = dst;
		minDist = MAXNODE;
		minTrans = MAXNODE;
		vPathNode.clear();
		vPathTemp.clear();
		vVisit.assign(MAXNODE, false);
		vVisit[src] = true;
		vPathTemp.push_back(src);
	}

	void Search(int s1, int s2)
	{
		ResetDfs(s1, s2);
		Dfs(s1, 0, 0, -1);
		PrintPath();
	}

	void Query(void)
	{
		int k, s1, s2;
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> s1 >> s2;
			Search(s1, s2);
		}
	}

	void main(void)
	{
		Read();
		Query();
	}
}

// https://www.liuchuo.net/archives/3850
// 通过一边DFS减枝实现路径搜索。
namespace nsA1131LiuchuoRef
{
	// 路径邻接链表
	vector<vector<int>> v(10000);

	// 边-线路映射
	int line[10000][10000];
	int	visit[10000], 
		minCnt, 
		minTransfer, 
		start, 
		end1;
	vector<int> path, tempPath;

	int transferCnt(vector<int> a) 
	{
		int cnt = -1, preLine = 0;
		for (int i = 1; i < a.size(); i++) 
		{
			if (line[a[i - 1]][a[i]] != preLine)
			{
				cnt++;
			}
			preLine = line[a[i - 1]][a[i]];
		}
		return cnt;
	}

	void dfs(int node, int cnt) 
	{
		if (node == end1 && 
			(cnt < minCnt || 
				(cnt == minCnt && 
					transferCnt(tempPath) < minTransfer))) 
		{
			minCnt = cnt;
			minTransfer = transferCnt(tempPath);
			path = tempPath;
		}
		if (node == end1) 
		{
			return;
		}
		for (int i = 0; i < v[node].size(); i++) 
		{
			if (visit[v[node][i]] == 0) 
			{
				visit[v[node][i]] = 1;
				tempPath.push_back(v[node][i]);
				dfs(v[node][i], cnt + 1);
				visit[v[node][i]] = 0;
				tempPath.pop_back();
			}
		}
	}

	int main() {
		int n, m, k, pre, temp;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) 
		{
			scanf("%d%d", &m, &pre);
			for (int j = 1; j < m; j++) 
			{
				scanf("%d", &temp);
				v[pre].push_back(temp);
				v[temp].push_back(pre);
				line[pre][temp] = line[temp][pre] = i + 1;
				pre = temp;
			}
		}

		scanf("%d", &k);
		for (int i = 0; i < k; i++) 
		{
			scanf("%d%d", &start, &end1);
			minCnt = 99999, minTransfer = 99999;
			tempPath.clear();
			tempPath.push_back(start);
			visit[start] = 1;
			dfs(start, 0);
			visit[start] = 0;
			printf("%d\n", minCnt);
			int preLine = 0, preTransfer = start;
			for (int j = 1; j < path.size(); j++) 
			{
				if (line[path[j - 1]][path[j]] != preLine) 
				{
					if (preLine != 0) 
					{
						printf("Take Line#%d from %04d to %04d.\n", preLine, preTransfer, path[j - 1]);
					}
					preLine = line[path[j - 1]][path[j]];
					preTransfer = path[j - 1];
				}
			}
			printf("Take Line#%d from %04d to %04d.\n", preLine, preTransfer, end1);
		}
		return 0;
	}
}

// rename this to main int PAT
int A1131Func(void)
{
	nsA1131RefOneDfs::main();
	return 0;
}


void A1131(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1131Func();
	cout << endl;
}

void A1131(void)
{
	A1131("data\\A1131-1.txt"); // 
}

