/*
1110. Complete Binary Tree (25)

Given a tree, you are supposed to tell if it is a complete binary tree.

Input Specification:

Each input file contains one test case. 
For each case, the first line gives a positive integer N (<=20)
which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to N-1. 

Then N lines follow, each corresponds to a node, 
and gives the indices of the left and right children of the node. 
If the child does not exist, a "-" will be put at the position.
Any pair of children are separated by a space.

Output Specification:

For each case, 
print in one line "YES" and the index of the last node if the tree is a complete binary tree, 
or "NO" and the index of the root if not.
There must be exactly one space separating the word and the number.

Sample Input 1:
9
7 8
- -
- -
- -
0 1
2 3
4 5
- -
- -
Sample Output 1:
YES 8
Sample Input 2:
8
- -
4 5
0 6
- -
2 3
- 7
- -
- -
Sample Output 2:
NO 1
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

/*
15:25
双向链表
找到根
判断
16:00 14/25 PT0,2,6 WA
test: n >= 2;

16:05
bug-fix: IsComplete 递归部分路径未返回。
	！！注意编译警告！！
24/25 PT6 异常

*/

namespace nsA1110A
{
	struct Node
	{
		int parent = -1;
		int left = -1;
		int right = -1;
	};

	int Index(const string& s)
	{
		if (s == "-")
		{
			return -1;
		}
		return stoi(s);
	}

	bool IsComplete(const vector<Node>& vNode, int iRoot)
	{
		bool noChild = false;
		deque<int> dqNode;
		dqNode.push_back(iRoot);
		while (!dqNode.empty())
		{
			int iNode = dqNode.front();
			dqNode.pop_front();
			const Node& node = vNode[iNode];
			if (node.left == -1)
				{ noChild = true; }
			else
			{
				if (noChild) { return false; }
				dqNode.push_back(node.left);
			}
			if (node.right == -1)
				{ noChild = true; }
			else
			{
				if (noChild) { return false; }
				dqNode.push_back(node.right);
			}
		}
		return true;
	}

	int LastChild(const vector<Node>& vNode, int iRoot)
	{
		int last = iRoot;
		deque<int> dqNode;
		dqNode.push_back(iRoot);
		while (!dqNode.empty())
		{
			last = dqNode.front();
			dqNode.pop_front();
			const Node& node = vNode[last];
			if (node.left != -1)
				{ dqNode.push_back(node.left); }
			if (node.right != -1)
				{ dqNode.push_back(node.right); }
		}
		return last;
	}

	void main(void)
	{
		int n;
		cin >> n;
		vector<Node> vNode(n);
		int iRoot = -1;
		for (int i = 0; i < n; ++i)
		{
			string s1, s2;
			cin >> s1 >> s2;
			int u = Index(s1);
			int v = Index(s2);			
			if (u >= 0) 
			{
				iRoot = u;
				vNode[i].left = u;
				vNode[u].parent = i; 
			}
			if (v >= 0)
			{
				iRoot = v;
				vNode[i].right = v; 
				vNode[v].parent = i;
			}
		}
		
		// find root
		while (vNode[iRoot].parent != -1)
		{
			iRoot = vNode[iRoot].parent;
		}
		if (IsComplete(vNode, iRoot))
		{
			cout << "YES " << LastChild(vNode, iRoot) << endl;
		}
		else
		{
			cout << "NO " << iRoot << endl;
		}
	}
}


// rename this to main int PAT
int A1110Func(void)
{
	nsA1110A::main();
	return 0;
}


void A1110(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1110Func();
	cout << endl;
}

void A1110(void)
{
// 	A1110("data\\A1110-1.txt"); // 
// 	A1110("data\\A1110-2.txt"); // 
	A1110("data\\A1110-3.txt"); // 
}

