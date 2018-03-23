/*
1147. Heaps (30)
200 ms
65536 kB

In computer science, a heap is a specialized tree-based data structure that satisfies the heap property: 
if P is a parent node of C, then the key (the value) of P is either greater than or equal to (in a max heap) or 
less than or equal to (in a min heap) the key of C. 
A common implementation of a heap is the binary heap, in which the tree is a complete binary tree. 
(Quoted from Wikipedia at https://en.wikipedia.org/wiki/Heap_(data_structure))

Your job is to tell if a given complete binary tree is a heap.

Input Specification:

Each input file contains one test case. For each case, the first line gives two positive integers: 
M (<= 100), the number of trees to be tested; and 
N (1 < N <= 1000), the number of keys in each tree, respectively. 
Then M lines follow, each contains N distinct integer keys (all in the range of int), 
which gives the level order traversal sequence of a complete binary tree.

Output Specification:

For each given tree, print in a line "Max Heap" if it is a max heap, or 
"Min Heap" for a min heap, or 
"Not Heap" if it is not a heap at all.
Then in the next line print the tree's postorder traversal sequence. 
All the numbers are separated by a space, and there must no extra space at the beginning or the end of the line.

Sample Input:
3 8
98 72 86 60 65 12 23 50
8 38 25 58 52 82 70 60
10 28 15 12 34 9 8 56
Sample Output:
Max Heap
50 60 65 72 12 23 86 98
Min Heap
60 58 52 38 82 70 25 8
Not Heap
56 12 34 28 9 8 15 10
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

/*
implement is_heap
*/

namespace nsA1174B
{
	template<typename Comp>
	bool IsHeap(const vector<int>& vData, Comp comp)
	{
		for (size_t i = 0; i < vData.size() / 2; ++i)
		{
			size_t left = 2 * i + 1;
			if (left < vData.size() && !comp(vData[left], vData[i]))
			{
				return false;
			}
			size_t right = left + 1;
			if (right < vData.size() && !comp(vData[right], vData[i]))
			{
				return false;
			}
		}
		return true;
	}

	void PostOrder(const vector<int>& vData, vector<int>& vOrder, int iRoot)
	{
		if (iRoot >= vData.size()) { return; }
		PostOrder(vData, vOrder, 2 * iRoot + 1);
		PostOrder(vData, vOrder, 2 * iRoot + 2);
		vOrder.push_back(vData[iRoot]);
	}
	
	void TestHeap(const vector<int>& vData)
	{
		if (IsHeap(vData, std::less<int>()))
		{
			cout << "Max Heap" << endl;
		}
		else if (IsHeap(vData, std::greater<int>()))
		{
			cout << "Min Heap" << endl;
		}
		else
		{
			cout << "Not Heap" << endl;
		}
		vector<int> vOrder;
		PostOrder(vData, vOrder, 0);
		cout << vOrder.front();
		for (size_t i = 1; i < vOrder.size(); ++i)
		{
			cout << " " << vOrder[i];
		}
		cout << endl;
	}

	void main(void)
	{
		int n, m;
		cin >> n >> m;
		vector<int> vData(m);
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				cin >> vData[j];
			}
			TestHeap(vData);
		}
	}
}

// rename this to main int PAT
int A1147Func(void)
{
	nsA1174B::main();
	return 0;
}


void A1147(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1147Func();
	cout << endl;
}

void A1147(void)
{
	A1147("data\\A1147-1.txt"); // 
}


/*
20m pass
*/
namespace nsA1174A
{
	void PostOrder(const vector<int>& vData, vector<int>& vOrder, int iRoot)
	{
		if (iRoot >= vData.size()) { return; }
		PostOrder(vData, vOrder, 2 * iRoot + 1);
		PostOrder(vData, vOrder, 2 * iRoot + 2);
		vOrder.push_back(vData[iRoot]);
	}

	void TestHeap(const vector<int>& vData)
	{
		if (is_heap(vData.begin(), vData.end(), std::less<int>()))
		{
			cout << "Max Heap" << endl;
		}
		else if (is_heap(vData.begin(), vData.end(), std::greater<int>()))
		{
			cout << "Min Heap" << endl;
		}
		else
		{
			cout << "Not Heap" << endl;
		}
		vector<int> vOrder;
		PostOrder(vData, vOrder, 0);
		cout << vOrder.front();
		for (size_t i = 1; i < vOrder.size(); ++i)
		{
			cout << " " << vOrder[i];
		}
		cout << endl;
	}

	void main(void)
	{
		int n, m;
		cin >> n >> m;
		vector<int> vData(m);
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				cin >> vData[j];
			}
			TestHeap(vData);
		}
	}
}