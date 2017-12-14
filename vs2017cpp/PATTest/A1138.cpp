/*
1138. Postorder Traversal (25)

sln1: 简单判断：前序 a0 a1 ... 中序 b0, b1, ...
	1. a0是根
	2. b0 == a1,时，取 bi=a0的前一个
	3. b0 != a1时，取b0
	19/25 pt2,4
sln2: 
	前序： 根 左序列 右序列
	中序： 左序列 根 右序列
	后续： 左序列 右序列 根
	递归：通过根不断分割左右序列，直到
			1.左序列只有1个元素
			2.左序列无元素，右序列只有一个元素
	ac
	

Suppose that all the keys in a binary tree are distinct positive
integers. Given the preorder and inorder traversal sequences, you
are supposed to output the first number of the postorder traversal
sequence of the corresponding binary tree.

Input Specification:

Each input file contains one test case. For each case, the first
line gives a positive integer N (<=50000), the total number of nodes
in the binary tree. The second line gives the preorder sequence and
the third line gives the inorder sequence. All the numbers in a line
are separated by a space.

Output Specification:

For each test case, print in one line the first number of the postorder
traversal sequence of the corresponding binary tree.

Sample Input:
7
1 2 3 4 5 6 7
2 3 1 5 4 7 6
Sample Output:
3
*/

#include "patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

// 简单算法，仅两种情况，19/25pt
int A1138FuncWrong19(void)
{
	int n, a0, a1, b0, last, t;
	cin >> n;
	if (n == 1)
	{
		cin >> a0;
		cout << a0 << endl;
		return 0;
	}
	cin >> a0 >> a1;
	for (int i = 2; i < n; ++i)
	{
		cin >> t;
	}
	cin >> b0;
	if (b0 != a1)
	{
		cout << b0 << endl;
		return 0;
	}
	last = b0;
	for (int i = 1; i < n; ++i)
	{
		cin >> t;
		if (t == a0)
		{
			cout << last << endl;
			return 0;
		}
		last = t;
	}
	return 0;
}


void FindFirstPost(int* const pPre, int* const pIn, const int len)
{
	int root = *pPre;
	int* pInRoot = pIn;
	while (*pInRoot++ != root);
	--pInRoot;
	int nLeft = (int)(pInRoot - pIn);
	int nRight = len - nLeft - 1;
	if (nLeft == 0)
	{
		if (nRight == 1)
		{
			cout << *(pInRoot + 1) << endl;
			return;
		}
		FindFirstPost(pPre + 1, pInRoot + 1, nRight);
	}
	else if (nLeft == 1)
	{
		cout << *pIn << endl;
		return;
	}
	else
	{
		FindFirstPost(pPre + 1, pIn, nLeft);
	}
}

int A1138Func(void)
{
	int n, t;
	cin >> n;
	if (n == 1)
	{
		cin >> t;
		cout << t << endl;
		return 0;
	}
	vector<int> vPre;
	vector<int> vIn;

	for (int i = 0; i < n; ++i)
	{
		cin >> t;
		vPre.push_back(t);
	}
	for (int i = 0; i < n; ++i)
	{
		cin >> t;
		vIn.push_back(t);
	}
	
	int len = (int)vPre.size();
	FindFirstPost(vPre.data(), vIn.data(), len);

	return 0;
}

void A1138(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1138Func();
}

void A1138(void)
{
	A1138("data\\A1138-1.txt"); // 3
	A1138("data\\A1138-2.txt"); // 1
	A1138("data\\A1138-3.txt"); // 3
	A1138("data\\A1138-4.txt"); // 5
}

