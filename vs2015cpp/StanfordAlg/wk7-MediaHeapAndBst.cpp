//////////////////////////////////////////////////////////////////////////
/*
Download the following text file:
Median.txt

The goal of this problem is to implement the "Median Maintenance" algorithm
(covered in the Week 3 lecture on heap applications). The text file contains
a list of the integers from 1 to 10000 in unsorted order; you should treat
this as a stream of numbers, arriving one by one. Letting xi denote the ith
number of the file, the kth median mk is defined as the median of the numbers
x1,бн,xk. (So, if k is odd, then mk is ((k+1)/2)th smallest number among
x1,бн,xk; if k is even, then mk is the (k/2)th smallest number among x1,бн,xk.)

In the box below you should type the sum of these 10000 medians, modulo 10000
(i.e., only the last 4 digits). That is, you should compute
(m1+m2+m3+?+m10000)mod10000.

OPTIONAL EXERCISE: Compare the performance achieved by heap-based and
search-tree-based implementations of the algorithm.
*/
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>
#include "common.h"

using namespace std;


class Heap
{
public:
	enum HeapType
	{
		MinHeap = 0,
		MaxHeap = 1
	};

	Heap(Heap::HeapType ht)
	{
		if (ht == MinHeap) { comp = std::less<int>(); }
		else if (ht == MaxHeap) { comp = std::greater<int>(); }
		else { abort(); }
	}

	void Push(int x) { Insert(x); }
	int  Pop(void) { return Delete(); }
	int  Peak(void) const { return v.front(); }
	int  Size(void) const { return v.size(); }

	void PrintSorted(void) const
	{
		auto h = *this;
		std::cout << Size() << ": ";
		auto i = unsigned(-1);
		int last = unsigned(-1) / 2 + 2;
		while (h.Size())
		{
			auto top = h.Pop();
			std::cout << top << " ";
			EXPECT_TRUE(last < top);
			top = last;
		}
		std::cout << std::endl;
	}

private:
	// 0-based: 
	// p: (i+1)/2 - 1 
	// l:2i+1 r: 2*i+2
	void Insert(int x)
	{
		v.push_back(x);
		auto i = v.size() - 1;
		auto p = 0;
		while ((p = ((i + 1) / 2 - 1)) >= 0)
		{
			if (comp(v[i], v[p])) { std::swap(v[i], v[p]); }
			i = p;
		}
	}

	int Delete(void)
	{
		auto fn = [](int l, int r) -> bool {return l < r; };
		auto headVal = Peak();
		std::swap(v.front(), v.back());
		v.erase(v.end() - 1);
		auto p = 0;
		auto l = 2 * p + 1;
		auto r = 2 * p + 2;
		while (l < v.size())
		{
			auto idx = p;
			auto val = v[idx];
			if (comp(v[l], val)) { idx = l; val = v[l]; }
			if (r < v.size() && comp(v[r], val)) { idx = r; val = v[r]; }
			if (idx == p) { break; }
			std::swap(v[idx], v[p]);
			p = idx;
			l = 2 * p + 1;
			r = 2 * p + 2;
		}
		return headVal;
	}
	std::vector<int> v;
	std::function<bool(int, int)> comp;
};

struct Node
{
	int key = 0;
	int nodes = 1;
	shared_ptr<Node> p = nullptr;
	shared_ptr<Node> l = nullptr;
	shared_ptr<Node> r = nullptr;

	Node(int k) :key(k) {}
	int ith(void)
	{
		auto i = nodes;
		if (r) { i -= r->nodes; };
		return i;
	}
};
bool operator==(const Node& l, const Node& r)
{
	return l.key == r.key;
}

bool operator<(const Node& l, const Node& r)
{
	return l.key < r.key;
}

bool operator>(const Node& l, const Node& r)
{
	return !(l < r);
}

class Bst
{
public:
	Bst(){};
	~Bst(){};

	void Push(const int x){ Insert(x); }
	int  Size(void) const { return root ? root->nodes : 0; }

	void PrintSorted(void) 
	{
		if (root) { cout << "root: " << root->key << endl; }
		RecurPrintVal(root);
		cout << endl;
	}

	void PrintNodes(void)
	{
		RecurPrintNode(root);
		cout << endl;
	}

public:
	int GetMedian(void)
	{
		return Get1Basedith((Size() + 1) / 2);
	}
	// i 1-based.
	int Get1Basedith(int i)
	{
		if (i <= 0 || i > Size()) { abort(); }
		return RecurGet1Baseith(root, i);
	}

	int RecurGet1Baseith(const shared_ptr<Node>& p, int i)
	{
		if (i <= 0) { abort(); }
		auto ip = p->ith();
		if (i == ip)	{ return p->key; }
		if (i < ip) { return RecurGet1Baseith(p->l, i); }
		if (i > ip) { return RecurGet1Baseith(p->r, i - ip); }
		abort();
	}

private:

	void Insert(const int x)
	{
		auto px = make_shared<Node>(x);
		if (!root) { root = px; return; }
		auto pp = root;
		auto p = root;
		while (p)
		{
			p->nodes++;
			pp = p;
			if (*px < *p) { p = p->l; }
			else if (*px > *p) { p = p->r; }
			else { abort(); }
		}
		px->p = pp;
		if (*px < *pp) { pp->l = px; }
		else if (*px > *pp) { pp->r = px; }
		else { abort(); }
	}

	void RecurPrintVal(const shared_ptr<Node>& p)
	{
		if (!p) { return; }
		RecurPrintVal(p->l);
		cout << p->key << " ";
		RecurPrintVal(p->r);
	}

	void RecurPrintNode(const shared_ptr<Node>& p)
	{
		if (!p) { return; }
		RecurPrintNode(p->l);
		cout << p->nodes << " ";
		RecurPrintNode(p->r);
	}


	shared_ptr<Node> root = nullptr;
};

void TestBst(void)
{
	auto wk7fn = "data\\wk7-Median-1213.txt"; // 1213
	auto v = ReadInt(wk7fn);
	auto length = 20;
	Bst b;
	for (size_t i = 0; i < length; i++)
	{
		b.Push(v[i]);
		b.PrintSorted();
		cout << b.GetMedian() << endl;
	}
	for (size_t i = 0; i < length; i++)
	{
		cout << i << ": " << b.Get1Basedith(i+1) << endl;
	}
}

int BstMedian(const std::string& fileName)
{
	auto vals = ReadInt(fileName);
	Bst b;
	auto total = 0;
	for (auto i : vals)
	{
		b.Push(i);
		total += b.GetMedian();
	}

	cout << "total " << total << endl;
	return total % 10000;
}

int HeapMedian(const std::string& fileName)
{
	auto vals = ReadInt(fileName);
	EXPECT_TRUE(vals.size() > 3);
	Heap leftHeap(Heap::MaxHeap); // left n/2
	Heap rightHeap(Heap::MinHeap); // right n - n/2
	auto a = vals[0];
	auto b = vals[1];
	leftHeap.Push(min(a, b));
	rightHeap.Push(max(a, b));
	auto length = vals.size();
	auto total = 0;
	total += vals[0];
	total += leftHeap.Peak();

	vector<int> vtMid;
	vtMid.push_back(vals[0]);
	vtMid.push_back(leftHeap.Peak());

	for (size_t i = 2; i < length; i++)
	{
		auto left = i / 2 + 1;
		auto right = i + 1 - left;
		auto current = vals[i];
		if (current < rightHeap.Peak())
		{
			leftHeap.Push(current);
			if (leftHeap.Size() > left)
			{
				rightHeap.Push(leftHeap.Pop());
			}
		}
		else
		{
			rightHeap.Push(current);
			if (rightHeap.Size() > right)
			{
				leftHeap.Push(rightHeap.Pop());
			}
		}
		auto mid = leftHeap.Peak();
		vtMid.push_back(mid);
//		cout << leftHeap.Size() << " " << rightHeap.Size() << " " << i+1 << " " << mid << " " << total << endl;
		total += mid;
	}
	cout << "total " << total << endl;
	return total % 10000;
}

void MedianHeap(void)
{	
	auto wk7fn = "data\\wk7-Median-1213.txt"; // 1213
	vector<string> fns = { "data\\wk7-test1-142.txt", "data\\wk7-test2-9335.txt", "data\\wk7-Median-1213.txt" };
	vector<int> res = { 142, 9335, 1213 };
	auto length = fns.size();
	for (size_t i = 0; i < length; i++)
	{
		auto midBst = BstMedian(fns[i]);
		cout << fns[i] << " BstMedian: " << midBst << " answer: " << res[i] << endl;
		EXPECT_TRUE(res[i] == midBst);

		auto midHeap = HeapMedian(fns[i]);
		cout << fns[i] << " HeapMedian: " << midHeap << " answer: " << res[i] << endl;
		EXPECT_TRUE(res[i] == midHeap);
	}
}
