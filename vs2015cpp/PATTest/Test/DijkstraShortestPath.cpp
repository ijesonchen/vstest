/*
关于Dijkstra算法：
1. findMin采用数组o(V*V+E), 采用二叉堆 o(V*lgV+ElgV)。
	因此，稠密图用数组，稀疏图用堆优化。
	临界点E=V*V/lgV (E/V=V/lgV)
	但是，如果结合visit[]，这部分操作非常少，可能性能不是很大。待测试
2. 二叉堆方式时，每次更新边都要更新堆：
	1) Heap.Delete(key), update, Heap.Push(new key)
	其中Heap.Delete(key)需要自己实现，一般lgn
	2) Heap.Decrease(key)
	直接根据key大小调整位置(lgn)

3. 网上经常使用priority_queue实现
	q.push(start)
	while(!q.empty)
		u = q.pop
		if (visit[u]) continue;
		for v : Adj(u)
			if (visit[v]) continue;
			if shorter(v) q.push(v)
	这种方案有两个问题：
	1) 极端情况下，while循环E次
	2) q.push(v)时v重复入队，不会更新前一个v，会破坏q的性质，可能存在bug
*/

#include "..\patMain.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

namespace nsTestVectorHeap
{
	void Print(const vector<int>& v)
	{
		for (auto i : v)
		{
			cout << i << " ";
		}
		cout << endl;
	}

	void main(void)
	{
		int n = 15;
		vector<int> v;
		int k = 0;
		while (k++<n)
		{
			v.push_back(n-k+1);
		}
// 		for (int i = 1; i < n; ++i)
// 		{
// 			make_heap(v.begin(), v.begin()+i);
// 			cout << "* " << i << endl;
// 			Print(v);
// 		}
		make_heap(v.begin(), v.end());
		Print(v);
		while (v.size())
		{
			cout << "* " << v.size() << endl;
			v[3] = 18; // 证明直接更改heap中元素大小可能导致堆算法错误
			v.push_back(18);
			push_heap(v.begin(), v.end());
//			pop_heap(v.begin(), v.end());
			Print(v);
			v.pop_back();
		}

	}
}


/*
ref: https://www.cnblogs.com/dancer16/p/6964454.html
add函数巧妙地使用数组实现图的邻接表

*/
namespace nsTestDijkstraShortestPath1
{
	int n, // node count
		m, // edge count
		S, // start node
		tot, // edge index
		Next[500010], // next edge index of E(u,v)
		head[20000], // first edge index of E(u,v)
		tree[500010], // v of edge index
		val[500010]; // weight of edge i
	bool visit[20000]; // in DIJKSTRA
	long long dis[20000]; // min dist from S
	struct cmp
	{
		bool operator()(int a, int b)
		{
			return dis[a]>dis[b];
		}
	};
	priority_queue<int, vector<int>, cmp> Q;
	void add(int x, int y, int z)
	{
		tot++; // edge index
		Next[tot] = head[x]; // edge from link list
		head[x] = tot;	// edge from link header
		tree[tot] = y; // edge to
		val[tot] = z; // edge value
	}
	int main()
	{
		scanf("%d%d%d", &n, &m, &S);
		tot = 0;
		for (int i = 1; i <= m; i++)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			if (x == y) continue;
			add(x, y, z);
			add(y, x, z);
		}
		for (int i = 1; i <= n; i++)
		{
			visit[i] = false;
			dis[i] = 2147483647;
		}

		// dijk with heap
		Q.push(S);
		dis[S] = 0;
		int nPush = 1;
		int nLoop = 0;
		int nFor = 0;
		int nWhile = 0;
		// 区别于CLRS上的示例算法：CLRS是先初始化Q为V，每次更新某个点
		// 如果Q支持DEC（修改）操作，则可以变为V*lgV+E*lgV
		// 即使Q不支持DEC操作，由于有visit数组，可以极大降低循环复杂度，V*V*lgV+E*lgV
		while (!Q.empty()) // n(n-1)/2 -> nE
		{
			++nWhile;
			int u = Q.top();
			Q.pop();	// lgn
			if (visit[u]) continue; // n
			++nLoop;
			visit[u] = true; // n
			for (int i = head[u]; i; i = Next[i]) // 每个点最多n-1个临接点，整体最多(n-1)^2 -> nE
			{
				++nFor;
				int v = tree[i];
				if (!visit[v] && dis[v]>dis[u] + (long long)val[i])
				{
					// !visit[v] 跳过内部点，只更新未处理的。
					// 第k个，最多n-k个未处理，最多n(n-1)/2次
					// k-1: k: n-1 -> 1
					dis[v] = dis[u] + val[i];
					// E * push,每次push耗时lgn
					Q.push(v); // may push v multi-times, & cause heap invalid
					// 如果Q支持delete(v)，则改为Q.pop(v), Q.push(v) while循环n次
					++nPush;
				}
			}
		}
		for (int i = 1; i <= n - 1; i++) printf("%lld ", dis[i]);
		printf("%lld\n", dis[n]);
		printf("count: while %d loop %d for %d push %d", nWhile, nLoop, nFor, nPush);

		// CLRS sample 
		// init Q with V
		// V*pop E*dec	impl
		// V*V	 E*1	list(V*V)
		// V*lgV E*lgV	binary heap (VlgV+ElgV)
		// V*lgV E*1	Fibonacci heap (VlgV+E)
		while (Q.empty()) // n
		{
			auto u = Q.top();
			Q.pop(); // logn
//			for (auto v : vvAdj[u]) // 最多E次
			{
				// update Q[v]
				// Q.Decrease(v)
			}
		}

		// dijk with linear findmin
		// o(n*n+e): findmin: n*n, update: e
/*
		V*pop	E*dec	impl
		V*V		E*1		list
		V*lgV	E*lgV	binary heap
*/		
		for (int i = 0; i < n; ++i) // n
		{
			int u = 0;
			// find min u o(n^2)
			vector<int> uAdj;
			for (auto v : uAdj) // 最大(n-1)*n -> edge count
			{
				//	if (!visit && shorter)  // 
				{
					// Decrease  n(n-1)/2
				}
			}
		}

 		return 0;
	}
}

void TestDijkstraShortestPath(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	nsTestVectorHeap::main();
	cout << endl;
}

void TestDijkstraShortestPath(void)
{
//	TestDijkstraShortestPath("data\\TDijkstraShortestPath-1.txt"); // 
//	TestDijkstraShortestPath("data\\TDijkstraShortestPath-2.txt"); // 0 1 2 1 4 3 3 6 5
	TestDijkstraShortestPath("data\\TDijkstraShortestPath-3.txt"); // 0 1 2 1 4 3 3 6 5
}

