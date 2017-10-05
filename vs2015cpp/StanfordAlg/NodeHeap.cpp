#include "NodeHeap.h"


void TestLinkNodeHead(NodeHeapType ht)
{
	NodeHeap<IntBinNode> h(ht);
	
	h.Push(new IntBinNode(3));
	h.Push(new IntBinNode(8));
	h.Push(new IntBinNode(6));
	h.Push(new IntBinNode(4));
	h.PrintSorted();

	h.Pop();
	h.PrintSorted();
	h.Push(new IntBinNode(2));
	h.PrintSorted();
	h.Pop();
	h.Push(new IntBinNode(5));
	h.PrintSorted();

}

void TestNodeHead(void)
{
	TestLinkNodeHead(NodeHeapMin);
	TestLinkNodeHead(NodeHeapMax);
}