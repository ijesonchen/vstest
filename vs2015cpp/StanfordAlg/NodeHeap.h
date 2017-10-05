#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdint>
#include <ctime>
#include <functional>
#include <memory>

template<typename T>
struct BinNode
{
	BinNode(int vv) { v = vv; }
	T v = 0;
	int h = 0;
	int v1 = 0;
	int v2 = 0;
	BinNode* l = nullptr;
	BinNode* r = nullptr;
};

using IntBinNode = BinNode<int>;

inline bool operator <  (const IntBinNode& lhs, const IntBinNode& rhs) { return lhs.v < rhs.v; }
inline bool operator >(const IntBinNode& lhs, const IntBinNode& rhs) { return lhs.v > rhs.v; }
inline bool operator == (const IntBinNode& lhs, const IntBinNode& rhs) { return lhs.v == rhs.v; }

inline std::ostream& operator<< (std::ostream& os, IntBinNode& v)
{
	os << v.v;
	return os;
}

enum NodeHeapType
{
	NodeHeapMin = 0,
	NodeHeapMax = 1
};

template<typename T>
class NodeHeap
{
public:
	NodeHeap(NodeHeapType ht)
	{
		if (ht == NodeHeapMin) { comp = std::less<T>(); }
		else if (ht == NodeHeapMax) { comp = std::greater<T>(); }
		else { abort(); }
	}

	void Push(T* p) { Insert(p); }
	T* Pop(void) { return Delete(); }
	T* Peak(void) const { return v.front(); }
	int Size(void) const { return (int)v.size(); }

	void PrintSorted(void) const
	{
		auto h = *this;
		std::cout << Size() << ": ";
		auto i = unsigned(-1);
		int last = unsigned(-1) / 2 + 2;
		while (h.Size())
		{
			auto top = h.Pop();
			std::cout << *top << " ";
		}
		std::cout << std::endl;
	}
private:
	// 0-based: 
	// p: (i+1)/2 - 1 
	// l:2i+1 r: 2*i+2
	void Insert(T* pv)
	{
		v.push_back(pv);
		auto i = (int)v.size() - 1;
		auto p = 0;
		while ((p = ((i + 1) / 2 - 1)) >= 0)
		{
			if (comp(*(v[i]), *(v[p]))) { std::swap(v[i], v[p]); }
			i = p;
		}
	}

	T* Delete(void)
	{
		auto fn = [](int l, int r) -> bool {return l < r; };
		auto headVal = Peak();
		std::swap(v.front(), v.back());
		v.erase(v.end() - 1);
		auto p = 0;
		auto l = 2 * p + 1;
		auto r = 2 * p + 2;
		while (l < (int)v.size())
		{
			auto idx = p;
			auto pVal = v[idx];
			if (comp(*(v[l]), *pVal)) { idx = l; pVal = v[l]; }
			if (r < (int)v.size() && comp(*(v[r]), *pVal)) { idx = r; pVal = v[r]; }
			if (idx == p) { break; }
			std::swap(v[idx], v[p]);
			p = idx;
			l = 2 * p + 1;
			r = 2 * p + 2;
		}
		return headVal;
	}

	std::vector<T*> v;
	std::function<bool(T, T)> comp;
};

void TestNodeHead(void);