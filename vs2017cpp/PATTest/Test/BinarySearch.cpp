/*
遍历所有路径：
GraphAdj::PrintAllPath
遍历从起点0开始的所有可能路径
原理：
记录当前路径vPath,
使用DFS递归处理当前路径尾部所有分支
当无分支（尾部无路径或所有路径已被遍历）
输出当前路径
用途1：求所有可能的最短路径（局部减枝）
如果有最短路径数组(如Dijkstra求最短路径数组）
可以对使用该数组作为剪枝条件
遍历所有可能的最短路径
非减枝直接遍历复杂度(n-1)!
*/

#include "..\patMain.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace nsTestBinarySearchIter
{
	int BinarySearch(const vector<int>& vec, const int val, int left, int right)
	{
		if (right < left) { return -1; }
		int mid = left + (right - left) / 2;
		if (val == vec[mid])
		{
			return mid;
		}
		else if (val < vec[mid])
		{
			return BinarySearch(vec, val, left, mid - 1);
		}
		else
		{
			return BinarySearch(vec, val, mid + 1, right);
		}
	}


	void main(void)
	{
		int n,k, t;
		cin >> n;
		vector<int> vData(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> vData[i];
		}
		sort(vData.begin(), vData.end());
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> t;
			cout << BinarySearch(vData, t, 0, n - 1) << " ";
		}
		cout << endl;
	}
}

namespace nsTestBinarySearchLoop
{
	int BinarySearch(const vector<int>& vec, const int val, int left, int right)
	{
		if (right < left) { throw 0; }
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (val == vec[mid])
			{
				return mid;
			}
			else if (val < vec[mid])
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		return -1;
	}
	void main(void)
	{
		int n, k, t;
		cin >> n;
		vector<int> vData(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> vData[i];
		}
		sort(vData.begin(), vData.end());
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> t;
			cout << BinarySearch(vData, t, 0, n - 1) << " ";
		}
		cout << endl;

	}

}

void TestBinarySearch(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	cout << "nsTestBinarySearchIter" << endl;
	nsTestBinarySearchIter::main();
	RedirCin(fn);
	cout << "nsTestBinarySearchLoop" << endl;
	nsTestBinarySearchLoop::main();
	cout << endl;
}

void TestBinarySearch(void)
{
	TestBinarySearch("data\\TBinarySearch-1.txt"); // 
}

