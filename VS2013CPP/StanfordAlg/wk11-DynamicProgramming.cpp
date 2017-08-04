/*
1¡£
In this programming problem and the next you'll code up the greedy algorithm from 
the lectures on Huffman coding.
Download the text file below.
huffman.txt
This file describes an instance of the problem. It has the following format:
[number_of_symbols]
[weight of symbol #1]
[weight of symbol #2]
...

For example, the third line of the file is "6852892," indicating that the weight 
of the second symbol of the alphabet is 6852892. (We're using weights instead of 
frequencies, like in the "A More Complex Example" video.)
Your task in this problem is to run the Huffman coding algorithm from lecture on 
this data set. What is the maximum length of a codeword in the resulting Huffman code?
ADVICE: If you're not getting the correct answer, try debugging your algorithm 
using some small test cases. And then post them to the discussion forum!

2¡£
Continuing the previous problem, what is the minimum length of a codeword in your 
Huffman code?

3¡£
In this programming problem you'll code up the dynamic programming algorithm for 
computing a maximum-weight independent set of a path graph.
Download the text file below.
mwis.txt
This file describes the weights of the vertices in a path graph (with the weights 
listed in the order in which vertices appear in the path). It has the following format:
[number_of_vertices]
[weight of first vertex]
[weight of second vertex]
...
For example, the third line of the file is "6395702," indicating that the weight of 
the second vertex of the graph is 6395702.
Your task in this problem is to run the dynamic programming algorithm (and the 
reconstruction procedure) from lecture on this data set. The question is: of the 
vertices 1, 2, 3, 4, 17, 117, 517, and 997, which ones belong to the maximum-weight 
independent set? (By "vertex 1" we mean the first vertex of the graph---there is no 
vertex 0.) In the box below, enter a 8-bit string, where the ith bit should be 1 if 
the ith of these 8 vertices is in the maximum-weight independent set, and 0 otherwise. 
For example, if you think that the vertices 1, 4, 17, and 517 are in the maximum-weight 
independent set and the other four vertices are not, then you should enter the 
string 10011010 in the box below.
*/
#include "common.h"
#include "NodeHeap.h"

using namespace std;

void TestHaffman(const std::string& fn)
{
	auto v = ReadIntSkipFirst(fn);
	NodeHeap<IntBinNode> heap(NodeHeapMin);

	vector<shared_ptr<IntBinNode>> resMgr;

	for (auto i : v)
	{
		heap.Push(new IntBinNode(i));
	}
	
	while (heap.Size() >= 2)
	{
		auto a = heap.Pop();
		auto b = heap.Pop();

		auto p = new IntBinNode(a->v + b->v);
		p->l = a;
		p->r = b;
		p->v1 = min(a->v1, b->v1) + 1;
		p->v2 = max(a->v2, b->v2) + 1;
		p->h = max(a->h, b->h) + 1;
		heap.Push(p);
	}

	auto p = heap.Pop();
	auto n = heap.Size();
	cout << fn << " " << p->v1 << " " << p->v2 << endl;
}

void Haffman(void)
{
	TestHaffman("data\\zwk11-huffman-2-5.txt");
	TestHaffman("data\\zwk11-huffman-3-6.txt");
	TestHaffman("data\\zwk11-huffman.txt");	// 9, 19
}


void Mwis(const std::string& fn)
{
	;
}

void Mwis(void)
{

}

void DynamicProgramming(void)
{
	Mwis();
}