/*
1123. Is It a Complete AVL Tree (30)

模拟测试：A1020-A1023: 20 23 25 0 = 68
	总结：
		1. 不要过早优化。发现错误时，不要耗费过多时间检查，优先做下一题。
		2. 熟悉常见算法的实现（AVL）
		A1021一开始就应该用int而非short存储数据（不要过早优化！！）
			第一次23分时，不应该再次检查，耗费15分钟，否则A1023有机会提交得22分
		A1023 AVL树算法不了解，凭猜测做题，方法复杂，容易出错，并且部分结果不对。

An AVL tree is a self-balancing binary search tree. 
In an AVL tree, the heights of the two child subtrees of any node differ by at most one; 
if at any time they differ by more than one, rebalancing is done to restore this property. 
Figures 1-4 illustrate the rotation rules.

Now given a sequence of insertions, you are supposed to output the level-order traversal sequence of the resulting AVL tree, 
and to tell if it is a complete binary tree.

Input Specification:

Each input file contains one test case. 
For each case, the first line contains a positive integer N (<= 20). 
Then N distinct integer keys are given in the next line. 
All the numbers in a line are separated by a space.

Output Specification:

For each test case, insert the keys one by one into an initially empty AVL tree.
Then first print in a line the level-order traversal sequence of the resulting AVL tree. 
All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.
Then in the next line, print "YES" if the tree is complete, or "NO" if not.

Sample Input 1:
5
88 70 61 63 65
Sample Output 1:
70 63 88 61 65
YES
Sample Input 2:
8
88 70 61 96 120 90 65 68
Sample Output 2:
88 65 96 61 70 90 120 68
NO
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

/*
15:35 
根据题目情况旋转，
2h 22/30 pt2,3 wa

虽然是平衡BST，但是不是avl树（再平衡算法不对），因此结果不正确。
并且，逻辑太复杂。
*/
namespace nsA1123A
{
	struct Node
	{
		int data;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int v) :data(v) {};
	};

	Node* pRoot = nullptr;

	int Level(Node* p)
	{
		if (!p) { return 0; }
		int nl = Level(p->left) + 1;
		int nr = Level(p->right) + 1;
		return std::max(nl, nr);
	}

	Node* Rebalance(Node* p)
	{
		if (!p) { return nullptr; };
		p->left = Rebalance(p->left);
		p->right = Rebalance(p->right);
		int nl = Level(p->left);
		int nr = Level(p->right);
		int diff = nl - nr;
		Node* pr = nullptr;
		if (diff <=1 && diff >= -1)
		{
			return p;
		}
		else if (diff > 1)
		{
			if (nr == 0)
			{
				if (p->left->left)
				{
					pr = p->left;
					p->left = nullptr;
					pr->right = p;
				}
				else
				{
					pr = p->left->right;
					p->left->right = nullptr;
					pr->left = p->left;
					pr->right = p;
					p->left = nullptr;
				}
			}
			else
			{
				Node* pll = p->left->left;
				Node* plr = p->left->right;
				if (plr->left || plr->right)
				{
					Node* plrl = plr->left;
					Node* plrr = plr->right;
					if (plrr)
					{
						pr = plrr;
						plr->right = nullptr;
						pr->left = p->left;
						pr->right = p;
						p->left = nullptr;
					}
					else
					{
						pr = plr;
						p->left->right = plrl;
						pr->left = p->left;
						pr->right = p;
						p->left = nullptr;
					}
				}
				else
				{
					pr = plr;
					p->left->right = nullptr;
					pr->left = p->left;
					pr->right = p;
					p->left = nullptr;
					pr->left = Rebalance(pr->left);
				}
			}
		}
		else
		{
			if (nl == 0)
			{
				if (p->right->right)
				{
					pr = p->right;
					p->right = nullptr;
					pr->left = p;
				}
				else
				{
					pr = p->right->left;
					p->right->left = nullptr;
					pr->left = p;
					pr->right = p->right;
					p->right = nullptr;
				}
			}
			else
			{
				Node* prl = p->right->left;
				Node* prr = p->right->right;
				if (prl->left || prl->right)
				{
					Node* prll = prl->left;
					Node* prlr = prl->right;
					if (prll)
					{
						pr = prll;
						prl->left = nullptr;
						pr->left = p;
						pr->right = p->right;
						p->right = nullptr;
					}
					else
					{
						pr = prl;
						p->right->left = prlr;
						pr->left = p;
						pr->right = p->right;
						p->right = nullptr;
					}
				}
				else
				{
					pr = prl;
					p->right->left = nullptr;
					pr->left = p;
					pr->right = p->right;
					p->right = nullptr;
					pr->right = Rebalance(pr->right);
				}
			}
		}
		return pr;
	}

	Node* Insert(Node* p, int v)
	{
		if (!p) { return new Node(v); };
		int data = p->data;
		if (v < data)
		{
			p->left = Insert(p->left, v);
		}
		else
		{
			p->right = Insert(p->right, v);
		}
		return p;
	}

	vector<int> vLevel;
	bool bComplete = true;
	void IsComplete(Node* p)
	{
		if (p && bComplete)
		{
			if (p->left && !p->right ||
				(!p->left && p->right))
			{
				bComplete = false;
			}
			IsComplete(p->left);
			IsComplete(p->right);
		}
	}

	void PrintTree(Node* p, int indent)
	{
		if (p)
		{
			for (int i = 0; i < indent; ++i)
			{
				cout << "  ";
			}
			cout << "++" << p->data << endl;
			if (p->left || p->right)
			{
				PrintTree(p->left, indent + 1);
				PrintTree(p->right, indent + 1);
			}
		}
		else
		{
			for (int i = 0; i < indent; ++i)
			{
				cout << "  ";
			}
			cout << "++x" << endl;
		}
	}

	int main(void)
	{
		// memory leakage
		pRoot = nullptr;
		int n, k;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> k;
// 			cout << endl << k << endl;
 			pRoot = Insert(pRoot, k);
//			PrintTree(pRoot, 0); cout << Level(pRoot->left) << " " << Level(pRoot->right) << endl;
			pRoot = Rebalance(pRoot);
//			PrintTree(pRoot, 0); cout << endl;
		}

		int nLeft = Level(pRoot->left);
		int nRight = Level(pRoot->right);
		if (abs(nLeft - nRight) > 1)
		{
			throw 0;
		}

		vLevel.clear();


		deque<Node*> dqpNodes;
		dqpNodes.push_back(pRoot);
		while (!dqpNodes.empty())
		{
			Node* p = dqpNodes.front();
			dqpNodes.pop_front();
			vLevel.push_back(p->data);
			if (p->left) { dqpNodes.push_back(p->left); };
			if (p->right) { dqpNodes.push_back(p->right); };
		}

		cout << vLevel.front();
		for (size_t i = 1; i < vLevel.size(); ++i)
		{
			cout << " " << vLevel[i];
		}
		cout << endl;
		bComplete = true;
		IsComplete(pRoot);
		if (bComplete)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}

		
		return 0;
	}
}

// ref https://www.liuchuo.net/archives/2732
/*
BST插入时，一定是插入到叶子节点（最后一层）
BST平衡原则：不平衡时，将对应子树压缩1，必要时调整父节点再平衡
	插入左子树引起不平衡为例：根p，左子pl，右子pr
		前提：插入前肯定左侧高1
		插入后不平衡，可能行有2种：
	1. 插入到左左（lll/llr)
		向右旋，p1作为新根：
			左侧高度-1，右侧高度+1，重新平衡
	2. 插入到左右(lrl/lrr)，
		先pl部分参照1左旋：
			pll高度+1，plr高度-1，变为情况1
		整体右旋
			同1：重新平衡
	插入到右子树引起不平衡类似。

	整体调整不平衡，不要局限在示例局部类型。否则调整后顺序不同。
*/
namespace nsA1123RefLiuchuo
{
	struct Node 
	{
		int val;
		Node *left, 
			*right;
	};

	Node* leftRotate(Node *tree) 
	{
		struct Node *temp = tree->right;
		tree->right = temp->left;
		temp->left = tree;
		return temp;
	}

	Node* rightRotate(Node *tree) 
	{
		struct Node *temp = tree->left;
		tree->left = temp->right;
		temp->right = tree;
		return temp;
	}

	int getHeight(Node *tree) 
	{
		if (tree == NULL) return 0;
		int l = getHeight(tree->left);
		int r = getHeight(tree->right);
		return l > r ? l + 1 : r + 1;
	}

	Node* leftRightRotate(Node *tree) 
	{
		tree->left = leftRotate(tree->left);
		tree = rightRotate(tree);
		return tree;
	}

	Node* rightLeftRotate(Node *tree) 
	{
		tree->right = rightRotate(tree->right);
		tree = leftRotate(tree);
		return tree;
	}

	Node* insert(Node *tree, int val) 
	{
		if (tree == NULL) {
			tree = new struct Node();
			tree->val = val;
			return tree;
		}

		if (tree->val > val)
		{
			tree->left = insert(tree->left, val);
			int l = getHeight(tree->left);
			int r = getHeight(tree->right);
			if (l - r >= 2) {
				if (val < tree->left->val)
					tree = rightRotate(tree);
				else
					tree = leftRightRotate(tree);
			}
		}
		else 
		{
			tree->right = insert(tree->right, val);
			int l = getHeight(tree->left), 
				r = getHeight(tree->right);
			if (r - l >= 2) 
			{
				if (val > tree->right->val)
					tree = leftRotate(tree);
				else
					tree = rightLeftRotate(tree);
			}
		}
		return tree;
	}

	int isComplete = 1, after = 0;
	vector<int> levelOrder(struct Node *tree) 
	{
		vector<int> v;
		queue<Node *> queue;
		queue.push(tree);
		while (queue.size() != 0) 
		{
			struct Node *temp = queue.front();
			queue.pop();
			v.push_back(temp->val);
			if (temp->left != NULL) 
			{
				if (after) isComplete = 0;
				queue.push(temp->left);
			}
			else 
			{
				after = 1;
			}
			if (temp->right != NULL) 
			{
				if (after) isComplete = 0;
				queue.push(temp->right);
			}
			else 
			{
				after = 1;
			}
		}
		return v;
	}

	int main() 
	{
		int n = 0;
		scanf("%d", &n);
		Node *tree = NULL;
		for (int i = 0; i < n; i++) 
		{
			int temp = 0;
			scanf("%d", &temp);
			tree = insert(tree, temp);
		}
		vector<int> v = levelOrder(tree);
		for (int i = 0; i < v.size(); i++)
		{
			if (i != 0) printf(" ");
			printf("%d", v[i]);
		}
		printf("\n%s", isComplete ? "YES" : "NO");
		return 0;
	}
}

// revisit 9:40 10:30
// 22/30 PT2,3 WA
namespace nsA1123B
{
	struct Node
	{
		int data;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int v) :data(v) {};
	};


	Node* RightRotate(Node* p);
	Node* LeftRotate(Node* p);

	Node* RightRotate(Node* p)
	{
		Node* pLeft = p->left;
		Node* pc = pLeft->right;
		pLeft->right = p;
		p->left = pc;
		return pLeft;
	}

	Node* LeftRightRotate(Node* p)
	{
		p->left = LeftRotate(p->left);
		p = RightRotate(p);
		return p;
	}

	Node* LeftRotate(Node* p)
	{
		Node* pRight = p->right;
		Node* pb = pRight->left;
		pRight->left = p;
		p->right = pb;
		return pRight;
	}

	Node* RightLeftRotate(Node* p)
	{
		p->right = RightRotate(p->right);
		p = LeftRotate(p);
		return p;
	}

	int TreeHight(Node* p)
	{
		if (!p) { return 0; }
		return std::max(TreeHight(p->left), TreeHight(p->right)) + 1;
	}

	Node* InsertData(Node* p, int val)
	{
		if (!p)
		{
			p = new Node(val);
			return p;
		}
		if (val < p->data)
		{
			p->left = InsertData(p->left, val);
		}
		else
		{
			p->right = InsertData(p->right, val);
		}

		// AVL rebalance
		int nleft = TreeHight(p->left);
		int nRight = TreeHight(p->right);
		int nDiff = nleft - nRight;
		if (nDiff > 2 || nDiff < -2) { throw 0; }
		if (nDiff == 2)
		{
			bool bLL = val < p->left->data;
			if ( bLL ) { p = RightRotate(p); }
			else { p = LeftRightRotate(p); }
		}
		if (nDiff == -2)
		{
			bool bRR = val > p->right->data;
			if (bRR) { p = LeftRotate(p); }
			else { p = RightLeftRotate(p); }
		}

		return p;
	}

	void LevelPrint(Node* pRoot)
	{
		vector<int> vData;
		deque<Node*> dqNode;
		dqNode.push_back(pRoot);
		while (!dqNode.empty())
		{
			Node* p = dqNode.front();
			dqNode.pop_front();
			vData.push_back(p->data);
			if (p->left) { dqNode.push_back(p->left); }
			if (p->right) { dqNode.push_back(p->right); }
		}
		cout << vData.front();
		for (size_t i = 1; i < vData.size(); ++i)
		{
			cout << " " << vData[i];
		}
		cout << endl;
	}

	bool IsCompleteTree(Node* p)
	{
		if (p)
		{
			if ((p->left && !p->right) ||
				(p->right && !p->left))
			{
				return false;
			}
			return IsCompleteTree(p->left) && IsCompleteTree(p->right);
		}
		return true;
	}

	int main(void)
	{
		int n, k;
		cin >> n;
		Node* pRoot = nullptr;
		for (int i = 0; i < n; ++i)
		{
			cin >> k;
			pRoot = InsertData(pRoot, k);

		}

		LevelPrint(pRoot);

		if (IsCompleteTree(pRoot))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}

		return 0;
	}
}

// rename this to main int PAT
int A1123Func(void)
{
	nsA1123B::main();

	return 0;
}


void A1123(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1123Func();
	cout << endl;
}

void A1123(void)
{
	A1123("data\\A1123-1.txt"); // 
 	A1123("data\\A1123-2.txt"); // 

}

