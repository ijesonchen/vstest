/*
1135. Is It A Red-Black Tree (30)

review：ref Liuchuo 输入可能不是BST？
	验证：BST中序为递增序列

关于二叉树的遍历与重建：涉及什么情况下可以根据遍历重建二叉树
ref：https://zhuanlan.zhihu.com/p/26418233

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
	14:50 70min 21/30 pt2,3 wa

SLN3：Every leaf (NULL) is black。根据leaf定义重新判断5 
	LeafBlackNodes
	(BlackNodes和SetBlackNodes函数错误，sln4中修正)
	20min pass

sln4: 根据leaf定义, 修正BlackNodes：只要子节点有一个为NULL，即比较路径黑节点数
	LeafBlackNodes 和 BlackNodes都可以正确判断
	5min pass
	

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
#include <algorithm>
#include <deque>

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

		bool IsLeaf(void) const { return !left || !right; };
		bool Red(void) const { return val < 0; };
		bool Black(void) const { return val > 0; };

		Node(int v) : val(v) {};
	};

	vector<int> vPreOrcer;
	vector<Node> vNode;
	int nBlack = -1;

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

	bool LeafBlackNodes(Node* p, int nb)
	{
		if (!p)
		{
			if (nBlack == -1)
			{
				nBlack = nb;
				return true;
			}
			else
			{
				return nBlack == nb;
			}
		}
		p->black = nb;
		if (p->Black())
		{
			++p->black;
		}

		if (!LeafBlackNodes(p->left, p->black))
		{
			return false;
		}
		if (!LeafBlackNodes(p->right, p->black))
		{
			return false;
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
// 		if (!LeafBlackNodes(pRoot, 0))
// 		{
// 			return false;
// 		}
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
		nBlack = -1;
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

// ref https://www.liuchuo.net/archives/4099
namespace nsA1135Liuchuo
{
	vector<int> pre, post, arr;

	struct node 
	{
		int val;
		struct node *left, 
					*right;
	};

	node* build(node *root, int v) 
	{
		if (root == NULL) {
			root = new node();
			root->val = v;
			root->left = root->right = NULL;
		}
		else if (abs(v) <= abs(root->val))
		{
			root->left = build(root->left, v);
		}
		else
		{
			root->right = build(root->right, v);
		}
		return root;
	}

	void getPost(int root, int end)
	{
		if (root > end) {return;}
		int i = root + 1, 
			j = end;
		while (i <= end && pre[root] > pre[i]) {i++;}
		while (j >= root + 1 && pre[root] <= pre[j]) {j--;}
		if (i != j + 1) {return;}
		getPost(root + 1, j);
		getPost(i, end);
		post.push_back(pre[root]);
	}

	bool judge1(node *root) 
	{
		if (root == NULL) {return true;}
		if (root->val < 0) 
		{
			if (root->left != NULL && root->left->val < 0) {return false;}
			if (root->right != NULL && root->right->val < 0) {return false;}
		}
		return judge1(root->left) && judge1(root->right);
	}

	int getNum(node *root) 
	{
		if (root == NULL) {return 0;}
		int l = getNum(root->left);
		int r = getNum(root->right);
		return root->val > 0 ? std::max(l, r) + 1 : std::max(l, r);
	}

	bool judge2(node *root) 
	{
		if (root == NULL) {return true;}
		int l = getNum(root->left);
		int r = getNum(root->right);
		if (l != r) {return false;}
		return judge2(root->left) && judge2(root->right);
	}

	int main() {
		int k, n;
		scanf("%d", &k);
		for (int i = 0; i < k; i++) 
		{
			scanf("%d", &n);
			arr.resize(n);
			pre.resize(n);
			node *root = NULL;
			for (int j = 0; j < n; j++) 
			{
				scanf("%d", &arr[j]);
				root = build(root, arr[j]);
				pre[j] = abs(arr[j]);
			}
			post.clear();
			getPost(0, n - 1);
			if (post.size() != n || arr[0] < 0 || judge1(root) == false || judge2(root) == false)
				{printf("No\n");}
			else
				{printf("Yes\n");}
		}
		return 0;
	}
}

namespace nsA1135BstValid
{
	struct Node 
	{
		int d;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int i) :d(i) {};
	};

	vector<int> preOrder;
	vector<int> inOrder;
	vector<Node> vPreNode;
	Node* pRoot = nullptr;
	vector<bool> redColor;

	void PrintTree(Node* pNode, int indent)
	{
		if (pNode)
		{
			for (int i = 0; i < indent; ++i)
			{
				cout << " .";
			}
			cout << "-+" << pNode->d << endl;
			if (pNode->left || pNode->right)
			{
				PrintTree(pNode->left, indent + 1);
				PrintTree(pNode->right, indent + 1);
			}
		}
		else
		{
			for (int i = 0; i < indent; ++i)
			{
				cout << " .";
			}
			cout << "-+*" << endl;
		}
	}
	
	Node* BuildTreePreIn(vector<int>& preOrder, vector<int>& inOrder, int pre0, int in0, int len)
	{
		if (len <= 0) { return nullptr; }
		int root = preOrder[pre0];
		Node* pRoot = new Node(root);
		int iRootIn = in0;
		while (inOrder[iRootIn++] != root) {}
		int nLeft = iRootIn - in0 - 1;
		pRoot->left = BuildTreePreIn(preOrder, inOrder, pre0 + 1, in0, nLeft);
		pRoot->right = BuildTreePreIn(preOrder, inOrder, pre0 + 1 + nLeft, in0 + nLeft + 1, len - 1 - nLeft);
		return pRoot;
	}

	bool BuildTreePreIn(Node*& pRoot, int pre1, int in1, int len)
	{
		pRoot = &vPreNode[pre1];
		int root = preOrder[pre1];
		int iRootIn = in1;
		int in2 = in1 + len;
		while (inOrder[iRootIn] != root)
		{
			++iRootIn;
			if (iRootIn >= in2)
			{
				// not a BST tree;
				return false;
			}
		}
		int inLeft = iRootIn - in1;
		if (inLeft > 0)
		{
			BuildTreePreIn(pRoot->left, pre1 + 1, in1, inLeft);
		}
		int inRight = len - inLeft - 1;
		if (inRight > 0)
		{
			BuildTreePreIn(pRoot->right, pre1 + 1 + inLeft, iRootIn + 1, inRight);
		}
	}

	bool IsBst(Node* p)
	{
		int root = p->d;
		if (p->left)
		{
			if (p->left->d > root || !IsBst(p->left))
			{
				return false;
			}
		}
		if (p->right)
		{
			if (p->right->d < root || !IsBst(p->right))
			{
				return false;
			}
		}
		return true;
	}

	void ReadTree(void)
	{
		int m, k;
		cin >> m;
		redColor.assign(m, false);
		preOrder.assign(m, 0);
		for (int i = 0; i < m; ++i)
		{
			cin >> k;
			if (k < 0)
			{
				redColor[i] = true;
				k = -k;
			}
			preOrder[i] = k;
			vPreNode.push_back(k);
		}
		inOrder = preOrder;
		sort(inOrder.begin(), inOrder.end());
	}

	int main(void)
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			preOrder.clear();
			inOrder.clear();
			vPreNode.clear();
			pRoot = nullptr;
			redColor.clear();
			ReadTree();
			auto p = BuildTreePreIn(preOrder, inOrder, 0, 0, (int)preOrder.size());
			PrintTree(p, 0);
			cout << endl;
// 			if (!BuildTreePreIn(pRoot, 0, 0, (int)preOrder.size()))
// 			{
// 				cout << "No" << endl;
// 			}
// 			if (!IsBst(pRoot))
// 			{
// 				throw 0;
// 			}
		}

		return 0;
	}
}

namespace nsA1135BuildTree
{
	using nsA1135BstValid::Node;

}


// rename this to main int PAT
int A1135Func(void)
{
//	nsA1135B::Read();
	nsA1135BstValid::main();
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
	A1135("data\\A1135-2.txt"); // 
}

