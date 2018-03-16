/*
1127. ZigZagging on a Tree (30)
400 ms
65536 kB

Suppose that all the keys in a binary tree are distinct positive integers. 
A unique binary tree can be determined by a given pair of postorder and inorder traversal sequences. 
And it is a simple standard routine to print the numbers in level-order. 
However, if you think the problem is too simple, then you are too naive.
This time you are supposed to print the numbers in "zigzagging order" -- that is, 
starting from the root, print the numbers level-by-level, alternating between left to right and right to left. 
For example, for the following tree you must output: 1 11 5 8 17 12 20 15.

Input Specification:

Each input file contains one test case. For each case, the first line gives a 
positive integer N (<= 30), the total number of nodes in the binary tree. 
The second line gives the inorder sequence and the third line gives the postorder sequence. 
All the numbers in a line are separated by a space.

Output Specification:

For each test case, print the zigzagging sequence of the tree in a line. 
All the numbers in a line must be separated by exactly one space, 
and there must be no extra space at the end of the line.

Sample Input:
8
12 11 20 17 1 15 8 5
12 20 17 11 15 8 5 1
Sample Output:
1 11 5 8 17 12 20 15

*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
16：30
binary tree
不同的正整数

inorder+preorder build
zigzag print

17:00 1/30 WA0,1,3
*/

namespace nsA1127A
{
	struct Node
	{
		int data;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) : data(d) {};
	};

	int nNode;
	vector<int> vIn;
	vector<int> vPost;

	Node* Build(int in1, int post1, int len)
	{
		if (len <= 0) { return nullptr; }
		// caution memory leakage
		int root = vPost[post1 + len - 1];
		Node* pr = new Node(root);

		int inRoot = int(find(vIn.begin() + in1, vIn.begin() + in1 + len, root) - vIn.begin());
		int nLeft = inRoot - in1;
		pr->left = Build(in1, post1, nLeft);
		int nRight = len - nLeft - 1;
		pr->right = Build(inRoot + 1, post1 + nLeft, nRight);
		return pr;
	}

	bool bLeft = true;
	vector<int> vZigZag;
	void ZigZag(Node* pRoot)
	{
		cout << pRoot->data;
		vector<Node*> pNode;
		vector<Node*> pTemp;
		if (pRoot->left) pNode.push_back(pRoot->left);
		if (pRoot->right) pNode.push_back(pRoot->right);
		bLeft = false;
		while (!pNode.empty())
		{
			pTemp.clear();
			pTemp.swap(pNode);
			if (!bLeft)
			{
				reverse(pTemp.begin(), pTemp.end());
			}
			for (auto p : pTemp)
			{
				cout << " " << p->data;
				if (bLeft)
				{
					if (p->left) pNode.push_back(p->left);
					if (p->right) pNode.push_back(p->right);
				}
				else
				{
					if (p->right) pNode.push_back(p->right);
					if (p->left) pNode.push_back(p->left);
				}
			}
			bLeft = !bLeft;
		}
		cout << endl;
	}

	void main(void)
	{
		cin >> nNode;
		vIn.resize(nNode);
		vPost.resize(nNode);

		for (int i = 0; i < nNode; ++i)
		{
			cin >> vIn[i];
		}
		for (int i = 0; i < nNode; ++i)
		{
			cin >> vPost[i];
		}

		Node* pRoot = Build(0, 0, nNode);
		ZigZag(pRoot);
	}
}

// rename this to main int PAT
int A1127Func(void)
{
	nsA1127A::main();
	return 0;
}


void A1127(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1127Func();
	cout << endl;
}

void A1127(void)
{
	A1127("data\\A1127-1.txt"); // 
}

