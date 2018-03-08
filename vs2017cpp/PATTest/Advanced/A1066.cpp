/*
1066. Root of AVL Tree (25)
100 ms
65536 kB


An AVL tree is a self-balancing binary search tree. 
In an AVL tree, the heights of the two child subtrees of any node differ by at most one; 
if at any time they differ by more than one, rebalancing is done to restore this property.
Figures 1-4 illustrate the rotation rules.

Now given a sequence of insertions, you are supposed to tell the root of the resulting AVL tree.

Input Specification:

Each input file contains one test case. 
For each case, the first line contains a positive integer N (<=20) which is the total number of keys to be inserted. 
Then N distinct integer keys are given in the next line. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print the root of the resulting AVL tree in one line.

Sample Input 1:
5
88 70 61 96 120
Sample Output 1:
70
Sample Input 2:
7
88 70 61 96 120 90 65
Sample Output 2:
88
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
16£º45
AVLÊ÷
17:15 pass
*/

namespace nsA1066A
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) :data(d) {};
	};

	int Hight(const Node* p)
	{
		if (!p) { return 0; }
		int nl = Hight(p->left);
		int nr = Hight(p->right);
		return std::max(nl, nr) + 1;
	}

	Node* RightRotate(Node* p)
	{
		Node* pr = p->left;
		p->left = pr->right;
		pr->right = p;
		return pr;
	}

	Node* LeftRotate(Node* p)
	{
		Node* pr = p->right;
		p->right = pr->left;
		pr->left = p;
		return pr;
	}

	Node* RightLeftRotate(Node* p)
	{
		p->right = RightRotate(p->right);
		return LeftRotate(p);
	}

	Node* LeftRightRotate(Node* p)
	{
		p->left = LeftRotate(p->left);
		return RightRotate(p);
	}

	Node* Insert(Node* p, int d)
	{
		if (!p) { return new Node(d); }
		int data = p->data;
		if (d < data) 
		{
			p->left = Insert(p->left, d); 
			int hl = Hight(p->left);
			int hr = Hight(p->right);
			if (hl - hr > 1)
			{
				if (d < p->left->data)
				{
					p = RightRotate(p);
				}
				else
				{
					p = LeftRightRotate(p);
				}
			}
			if (hr - hl > 1)
			{
				throw 0;
			}
		}
		else 
		{
			p->right = Insert(p->right, d);
			int hl = Hight(p->left);
			int hr = Hight(p->right);
			if (hr - hl > 1)
			{
				if (d > p->right->data)
				{
					p = LeftRotate(p);
				}
				else
				{
					p = RightLeftRotate(p);
				}
			}
			if (hl - hr > 1)
			{
				throw 0;
			}
		}
		return p;
	}


	void main(void)
	{
		int n, t;
		cin >> n;
		Node* p = nullptr;
		for (int i = 0; i < n; ++i)
		{
			cin >> t;
			p = Insert(p, t);
		}
		cout << p->data << endl;
	}
}

// rename this to main int PAT
int A1066Func(void)
{
	nsA1066A::main();
	return 0;
}


void A1066(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1066Func();
	cout << endl;
}

void A1066(void)
{
	A1066("data\\A1066-1.txt"); // 
	A1066("data\\A1066-2.txt"); // 
}

