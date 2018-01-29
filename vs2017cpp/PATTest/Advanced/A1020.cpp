/*
1020. Tree Traversals (25)

cost: 21:10 80min

sln: µ›πÈº∆À„ pass


Suppose that all the keys in a binary tree are distinct positive integers. 
Given the postorder and inorder traversal sequences,
you are supposed to output the level order traversal sequence of the corresponding binary tree.

Input Specification:

Each input file contains one test case. For each case, 
the first line gives a positive integer N (<=30), the total number of nodes in the binary tree. 
The second line gives the postorder sequence and 
the third line gives the inorder sequence. 
All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in one line the level order traversal sequence of the corresponding binary tree. 
All the numbers in a line must be separated by exactly one space, 
and there must be no extra space at the end of the line.

Sample Input:
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7
Sample Output:
4 1 6 3 5 7 2

*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <deque>

using namespace std;

struct A1020Node
{
	int value = 0;
	A1020Node* left = nullptr;
	A1020Node* right = nullptr;

	A1020Node(const int i) : value(i) {};
};

vector<unique_ptr<A1020Node>> A1020g_vsp;
vector<int> A1020g_postOrder;
vector<int> A1020g_inOrder;

int A1020FindIdx(const vector<int>& vt, int beg, int end, int value)
{
	for (int i = beg; i <= end; ++i)
	{
		if (vt[i] == value)
		{
			return i;
		}
	}
	throw 0;
}

void A1020MakeNode(A1020Node*& pNode, int value)
{
	A1020Node* pNew = new A1020Node(value);
	A1020g_vsp.emplace_back(pNew);
	pNode = pNew;
}

void A1020BuildTree(A1020Node*& pNode, const int postBeg1, const int postRoot, const int inBeg1, const int inEnd2)
{
	int postEnd2 = postRoot - 1;
	int inEnd1, inBeg2, postEnd1, postBeg2;

	int rootValue = A1020g_postOrder[postRoot];
	A1020MakeNode(pNode, rootValue);
	int inRootIdx = A1020FindIdx(A1020g_inOrder, inBeg1, inEnd2, rootValue);
	inEnd1 = inRootIdx - 1;
	inBeg2 = inRootIdx + 1;
	int inLeft = inEnd1 - inBeg1;
	int inRight = inEnd2 - inBeg2;
	postEnd1 = postBeg1 + inLeft;
	postBeg2 = postEnd2 - inRight;

	if (inLeft < -1 || inRight < -1)
	{
		throw 0;
	}
	// left part
	if (inLeft < 0)
	{
	}
	else if (inLeft == 0)
	{
		// left node
		A1020MakeNode(pNode->left, A1020g_inOrder[inBeg1]);
	}
	else
	{
		A1020BuildTree(pNode->left, postBeg1, postEnd1, inBeg1, inEnd1);
	}
	if (inRight < 0)
	{
	}
	else if (inRight == 0)
	{
		A1020MakeNode(pNode->right, A1020g_inOrder[inBeg2]);
	}
	else
	{
		A1020BuildTree(pNode->right, postBeg2, postEnd2, inBeg2, inEnd2);
	}
}

void A1020PrintLevelOrder(A1020Node* pNode)
{
	cout << pNode->value;
	deque<A1020Node*> dqp;
	dqp.push_back(pNode->left);
	dqp.push_back(pNode->right);
	while (!dqp.empty())
	{
		auto p = dqp.front();
		dqp.pop_front();
		if (!p)
		{
			continue;
		}
		cout << " " << p->value;
		dqp.push_back(p->left);
		dqp.push_back(p->right);
	}
}

// rename this to main int PAT
int A1020Func(void)
{
	int n, k;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> k;
		A1020g_postOrder.push_back(k);
	}
	for (int i = 0; i < n; ++i)
	{
		cin >> k;
		A1020g_inOrder.push_back(k);
	}

	A1020Node* pRoot = nullptr;
	A1020BuildTree(pRoot, 0, n - 1, 0, n - 1);
	A1020PrintLevelOrder(pRoot);
	return 0;
}


void A1020(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1020Func();
	cout << endl;
}

void A1020(void)
{
	A1020("data\\A1020-1.txt"); // 
}

