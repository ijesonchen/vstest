/*
1135. Is It A Red-Black Tree (30)

cost: 10:40

sln1: 仅前序无法唯一确定一棵树。应该是前序和RB树有关系。
	看题目，猜测如下关系：
	BRBBRRBBRR...
	25min 21/30 PT2,3 WA
	猜测末尾应为 BR
	5min 21/30 pt2,3 wa

SLN2: 搜索红黑树 前序遍历，介绍红黑树的资料提到：红黑树是二叉搜索树
	因此，满足搜索树的条件
	前序： 根 左 右
	二叉树前序： 根 小 大
	70min 21/30 pt2,3 wa

There is a kind of balanced binary search tree named red-black tree in the data structure. 
It has the following 5 properties:

(1) Every node is either red or black.
(2) The root is black.
(3) Every leaf (NULL) is black.
(4) If a node is red, then both its children are black.
(5) For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.

For example, the tree in Figure 1 is a red-black tree, while the ones in Figure 2 and 3 are not.

fig1
      7
  2      11
1   5   8  14
   4         15
fig2

fig3


For each given binary search tree, you are supposed to tell if it is a legal red-black tree.

Input Specification:

Each input file contains several test cases. 
The first line gives a positive integer K (<=30) which is the total number of cases. 
For each case, the first line gives a positive integer N (<=30), 
the total number of nodes in the binary tree. 
The second line gives the preorder traversal sequence of the tree. 
While all the keys in a tree are positive integers, 
we use negative signs to represent red nodes. 
All the numbers in a line are separated by a space.
The sample input cases correspond to the trees shown in Figure 1, 2 and 3.

Output Specification:

For each test case, print in a line "Yes" if the given tree is a red-black tree, or "No" if not.

Sample Input:
3
9
7 -2 1 5 -4 -11 8 14 -15
9
11 -2 1 -7 5 -4 8 14 -15
8
10 -7 5 -6 8 15 -11 17
Sample Output:
Yes
No
No
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace nsA1135
{
	bool IsRBTree(int nNode)
	{
		vector<int> vNode;
		for (int i = 0; i < nNode; ++i)
		{
			int t;
			cin >> t;
			vNode.push_back(t);
		}
		if (vNode[0] < 0)
		{
			return false;
		}
		int len = (int)vNode.size();
		if (len >= 2)
		{
			if (vNode[1] > 0 || vNode.back() > 0)
			{
				return false;
			}
			if (vNode[len - 2] < 0)
			{
				return false;
			}
		}
		for (int i = 2; i < len; ++i)
		{
			bool pos = i / 2 % 2;
			if (pos)
			{
				if (vNode[i] < 0)
				{
					return false;
				}
			}
			else
			{
				if (vNode[i] > 0)
				{
					return false;
				}
			}
		}
		return true;
	}

	void Read(void)
	{
		int k, n;
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> n;
			if (IsRBTree(n))
			{
				cout << "Yes" << endl;
			}
			else
			{
				cout << "No" << endl;
			}
		}
	}
}

namespace nsA1135B
{
	struct Node
	{
		int val = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		int black = 0;

		bool IsLeaf(void) const { return !left && !right; };
		bool Red(void) const { return val < 0; };
		bool Black(void) const { return val > 0; };

		Node(int v) : val(v) {};
	};

	vector<int> vPreOrcer;
	vector<Node> vNode;

	// [first, last]. return last + 1 if not found.
	int RightLeftIndex(int first, int last)
	{
		int root = abs(vPreOrcer[first]);
		for (int i = first + 1; i <= last; ++i)
		{
			if (abs(vPreOrcer[i]) > root)
			{
				return i;
			}
		}
		return last + 1;
	}

	// [first, last]
	void BuildTree(Node*& pRoot, int first, int last)
	{
		if (last < first)
		{
			return;
		}
		pRoot = &vNode[first];
		if (first == last)
		{
			return;
		}
		// left: first+1, right-1
		// right: right, last
		int iLeft1 = first + 1;
		int iRight1 = RightLeftIndex(first, last);
		int iLeft2 = iRight1 - 1;
		int iRight2 = last;
		BuildTree(pRoot->left, iLeft1, iLeft2);
		BuildTree(pRoot->right, iRight1, iRight2);
	}
	bool BlackChild(Node* pRoot)
	{
		if (!pRoot)
		{
			return true;
		}
		if (pRoot->Red())
		{
			if ((pRoot->left && pRoot->left->Red()) ||
				(pRoot->right && pRoot->right->Red()))
			{
				return false;
			}
		}
		return BlackChild(pRoot->left) && BlackChild(pRoot->right);
	}

	void SetBlackNodes(Node* pRoot)
	{
		if (!pRoot)
		{
			return;
		}
		int& black = pRoot->black;
		if (pRoot->Black())
		{
			black++;
		}
		if (pRoot->left)
		{
			pRoot->left->black = black;
			SetBlackNodes(pRoot->left);
		}
		if (pRoot->right)
		{
			pRoot->right->black = black;
			SetBlackNodes(pRoot->right);
		}
	}

	bool BlackNodes(Node* pRoot)
	{
		SetBlackNodes(pRoot);
		int black = -1;
		for (auto& n : vNode)
		{
			if (n.IsLeaf())
			{
				if (black == -1)
				{
					black = n.black;
				}
				else
				{
					if (black != n.black)
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	bool IsRbTree(Node* pRoot)
	{
		if (!pRoot->Black())
		{
			return false;
		}
		if (!BlackChild(pRoot))
		{
			return false;
		}
		if (!BlackNodes(pRoot))
		{
			return false;
		}
		return true;
	}

	bool ReadTree(int nNode)
	{
		vPreOrcer.clear();
		vNode.assign(nNode, Node(0));
		for (int i = 0; i < nNode; ++i)
		{
			int t;
			cin >> t;
			vPreOrcer.push_back(t);
			vNode[i].val = t;
		}
		Node* pRoot = nullptr;
		int last = (int)vNode.size() - 1;
		BuildTree(pRoot, 0, last);
		return IsRbTree(pRoot);
	}

	void Read(void)
	{
		int k, n;
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> n;
			if (ReadTree(n))
			{
				cout << "Yes" << endl;
			}
			else
			{
				cout << "No" << endl;
			}
		}
	}
}


// rename this to main int PAT
int A1135Func(void)
{
	nsA1135B::Read();
	return 0;
}


void A1135(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1135Func();
	cout << endl;
}

void A1135(void)
{
	A1135("data\\A1135-1.txt"); // 
}

