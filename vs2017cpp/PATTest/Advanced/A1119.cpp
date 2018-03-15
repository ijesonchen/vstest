/*
1119. Pre- and Post-order Traversals (30)
400 ms
65536 kB

Suppose that all the keys in a binary tree are distinct positive integers. 
A unique binary tree can be determined by a given pair of postorder and inorder traversal sequences, 
or preorder and inorder traversal sequences. 
However, if only the postorder and preorder traversal sequences are given, the corresponding tree may no longer be unique.

Now given a pair of postorder and preorder traversal sequences, 
you are supposed to output the corresponding inorder traversal sequence of the tree. 
If the tree is not unique, simply output any one of them.

Input Specification:

Each input file contains one test case. 
For each case, the first line gives a positive integer N (<=30), 
the total number of nodes in the binary tree. 
The second line gives the preorder sequence and 
the third line gives the postorder sequence. 
All the numbers in a line are separated by a space.

Output Specification:

For each test case, first printf in a line "Yes" if the tree is unique, 
or "No" if not. 
Then print in the next line the inorder traversal sequence of the corresponding binary tree. 
If the solution is not unique, any answer would do. 
It is guaranteed that at least one solution exists. 
All the numbers in a line must be separated by exactly one space, 
and there must be no extra space at the end of the line.

Sample Input 1:
7
1 2 3 4 6 7 5
2 6 7 4 5 3 1
Sample Output 1:
Yes
2 1 6 4 7 3 5
Sample Input 2:
4
1 2 3 4
2 4 3 1
Sample Output 2:
No
2 1 3 4
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
16:25
前序，后序判定中序
m m1 l1 r1 m2 l2 r2
m1 l1 r1 m2 l2 r2 m
从根开始，不断查找根的左右节点，同时判断唯一性

16:40 模拟算法

16:45 测试数据情况 [1,n]
17：15 pass
*/
namespace nsA1119A
{
	bool bUnique;

	struct Node
	{
		int d;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int i) :d(i) {};
	};

	// [left, left+len)
	Node* FindChild(const vector<int>& vPre, const vector<int>& vPost, const int pre1, const int pre2, int len)
	{
		if (len <= 0) { return nullptr; }
		Node* pr = new Node(vPre[pre1]);
		if (len == 1) { return pr; }

		if (len==2)
		{
			bUnique = false;
			pr->left = new Node(vPre[pre1 + 1]);
			return pr;
		}

		int m1 = vPre[pre1 + 1];
		int m2 = vPost[pre2 + len - 2];
		if (m1 == m2)
		{
			bUnique = false;
			pr->left = FindChild(vPre, vPost, pre1 + 1, pre2, len - 1);
			return pr;
		}
		int iPreM2 = (int)(find(vPre.begin() + pre1 + 2, vPre.begin() + pre1 + len, m2) - vPre.begin());
		int len1 = iPreM2 - pre1 - 1;
		pr->left = FindChild(vPre, vPost, pre1 + 1, pre2, len1);
		int len2 = len - 1 - len1;
		pr->right = FindChild(vPre, vPost, iPreM2, pre2 + len1, len2);
		return pr;
	}

	vector<int> vIn;
	void InOrder(Node* p)
	{
		if (p)
		{
			InOrder(p->left);
			vIn.push_back(p->d);
			InOrder(p->right);
		}
	}

	void main(void)
	{
		bUnique = true;
		int n;
		cin >> n;
		vector<int> vPre(n);
		vector<int> vPost(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> vPre[i];
		}
		for (int i = 0; i < n; ++i)
		{
			cin >> vPost[i];
		}
		Node* pRoot = FindChild(vPre, vPost, 0, 0, n);
		if (bUnique)
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
		vIn.clear();
		InOrder(pRoot);
		cout << vIn.front();
		for (size_t i = 1; i < vIn.size(); ++i)
		{
			cout << " " << vIn[i];
		}
		cout << endl;
	}
}

// rename this to main int PAT
int A1119Func(void)
{
	nsA1119A::main();
	return 0;
}


void A1119(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1119Func();
	cout << endl;
}

void A1119(void)
{
	A1119("data\\A1119-1.txt"); // 
	A1119("data\\A1119-2.txt"); // 
}

