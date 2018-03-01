/*
1123. Is It a Complete AVL Tree (30)


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

using namespace std;

/*
15:35 
根据题目情况旋转，
2h 22/30 pt2,3 wa

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
//			cout << endl << k << endl;
			pRoot = Insert(pRoot, k);
//			PrintTree(pRoot, 0); cout << endl;
			pRoot = Rebalance(pRoot);
//			PrintTree(pRoot, 0); cout << endl;
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

// rename this to main int PAT
int A1123Func(void)
{
	nsA1123A::main();

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

