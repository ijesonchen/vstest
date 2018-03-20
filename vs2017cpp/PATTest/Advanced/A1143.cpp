/*
1143. Lowest Common Ancestor (30)
200 ms
65536 kB

The lowest common ancestor (LCA) of two nodes U and V in a tree is the deepest node that has both U and V as descendants.

A binary search tree (BST) is recursively defined as a binary tree which has the following properties:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
Given any two nodes in a BST, you are supposed to find their LCA.

Input Specification:

Each input file contains one test case. For each case, the first line gives two positive integers:
M (<= 1000), the number of pairs of nodes to be tested; and 
N (<= 10000), the number of keys in the BST, respectively. 
In the second line, N distinct integers are given as the preorder traversal sequence of the BST. 
Then M lines follow, each contains a pair of integer keys U and V. 
All the keys are in the range of int.

Output Specification:

For each given pair of U and V, print in a line "LCA of U and V is A." if the LCA is found and A is the key. 
But if A is one of U and V, print "X is an ancestor of Y." where X is A and Y is the other node. 
If U or V is not found in the BST, print in a line "ERROR: U is not found." 
or "ERROR: V is not found."
or "ERROR: U and V are not found.".

Sample Input:
6 8
6 3 1 2 5 4 8 7
2 5
8 7
1 9
12 -3
0 8
99 99
Sample Output:
LCA of 2 and 5 is 3.
8 is an ancestor of 7.
ERROR: 9 is not found.
ERROR: 12 and -3 are not found.
ERROR: 0 is not found.
ERROR: 99 and 99 are not found.
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
test: 0 < node < 1000000;
*/

/*
FROM nsA1143A
 
*/
namespace nsA1143B
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) : data(d) {};
	};
	
	Node* Insert(Node* p, int d)
	{
		if (!p)
		{
			p = new Node(d);
			return p;
		}
		if (d < p->data)
		{
			p->left = Insert(p->left, d);
			return p;
		}
		else if (d > p->data)
		{
			p->right = Insert(p->right, d);
			return p;
		}
		else
		{
			throw 0;
		}
		return p;
	}
	
	void LCA(Node* p, int u, int v)
	{
		if (!p) { throw 0; }
		if (u == p->data)
		{
			printf("%d is an ancestor of %d.\n", u, v);
		}
		else if (v == p->data)
		{
			printf("%d is an ancestor of %d.\n", v, u);
		}
		else if ((u > p->data && v < p->data) || 
			(u < p->data && v > p->data))
		{
			printf("LCA of %d and %d is %d.\n", u, v, p->data);
		}
		else if (u < p->data && v < p->data)
		{
			LCA(p->left, u, v);
		}
		else if (u > p->data && v > p->data)
		{
			LCA(p->right, u, v);
		}
		else
		{
			throw 0;
		}
	}

	void main(void)
	{
		int m, n, d;
 		scanf("%d %d", &m, &n);
		Node* pRoot = nullptr;
		vector<bool> vVisit(1000000);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			vVisit[d] = true;
			pRoot = Insert(pRoot, d);
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			bool bu = (u >= 0) && vVisit[u];
			bool bv = (v >= 0) && vVisit[v];
			if (!bu && !bv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!bu && bv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (bu && !bv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{
				LCA(pRoot, u, v);
			}
		}

	}
}

// rename this to main int PAT
int A1143Func(void)
{
	nsA1143B::main();
	return 0;
}


void A1143(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1143Func();
	cout << endl;
}

void A1143(void)
{
	A1143("data\\A1143-1.txt"); // 
}


namespace nsA1143A
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) : data(d) {};
	};

	vector<Node*> vpNodes;

	Node* Insert(Node* p, int d)
	{
		if (!p)
		{
			p = new Node(d);
			//			vpNodes.push_back(p);
			return p;
		}
		if (d < p->data)
		{
			p->left = Insert(p->left, d);
			return p;
		}
		else if (d > p->data)
		{
			p->right = Insert(p->right, d);
			return p;
		}
		else
		{
			throw 0;
		}
		return p;
	}

	Node* FindPath(Node* p, int d, vector<int>& vPath)
	{
		if (!p) { return nullptr; }
		vPath.push_back(p->data);
		if (p->data == d)
		{
			return p;
		}
		else if (d < p->data)
		{
			return FindPath(p->left, d, vPath);
		}
		else
		{
			return FindPath(p->right, d, vPath);
		}
	}


	void main(void)
	{
		int m, n, d;
		cin >> m >> n;
		Node* pRoot = nullptr;
		vector<bool> vVisit(1000000);
		for (int i = 0; i < n; ++i)
		{
			cin >> d;
			vVisit[d] = true;
			pRoot = Insert(pRoot, d);
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			cin >> u >> v;
			bool bu = (u >= 0) && vVisit[u];
			bool bv = (v >= 0) && vVisit[v];
			if (!bu && !bv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!bu && bv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (bu && !bv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{
				vector<int> uPath;
				vector<int> vPath;
				auto pu = FindPath(pRoot, u, uPath);
				auto pv = FindPath(pRoot, v, vPath);
				int iCommon = (int)std::min(uPath.size(), vPath.size()) - 1;
				for (size_t j = 0; j < uPath.size() && j < vPath.size(); ++j)
				{
					if (uPath[j] != vPath[j])
					{
						iCommon = (int)j - 1;
						break;
					}
				}
				if (iCommon < uPath.size() - 1 && iCommon < vPath.size() - 1)
				{
					printf("LCA of %d and %d is %d.\n", u, v, uPath[iCommon]);
				}
				else if (iCommon == uPath.size() - 1)
				{
					printf("%d is an ancestor of %d.\n", u, v);
				}
				else if (iCommon == vPath.size() - 1)
				{
					printf("%d is an ancestor of %d.\n", v, u);
				}
				else
				{
					throw 0;
				}

			}
		}

	}
}

