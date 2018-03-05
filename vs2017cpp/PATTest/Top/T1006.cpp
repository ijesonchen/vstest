/*
1006. Tree Traversals - Hard Version (35)

Given the partial results of a binary tree's traversals in in-order, pre-order, and post-order. 
You are supposed to output the complete results and the level order traversal sequence of the corresponding tree.

Input Specification:

Each input file contains one test case. 
For each case, a positive integer N (<=100) is given in the first line. 
Then three lines follow, containing the incomplete in-order, pre-order and post-order traversal sequences, respectively. 
It is assumed that the tree nodes are numbered from 1 to N and no number is given out of the range. A "-" represents a missing number.

Output Specification:

For each case, print in four lines the complete in-order, pre-order and post-order traversal sequences, 
together with the level order traversal sequence of the corresponding tree. 
The numbers must be separated by a space, and there must be no extra space at the end of each line. 
If it is impossible to reconstruct the unique tree from the given information, simply print "Impossible".

Sample Input 1:
9
3 - 2 1 7 9 - 4 6
9 - 5 3 2 1 - 6 4
3 1 - - 7 - 6 8 -
Sample Output 1:
3 5 2 1 7 9 8 4 6
9 7 5 3 2 1 8 6 4
3 1 2 5 7 4 6 8 9
9 7 8 5 6 3 2 4 1
Sample Input 2:
3
- - -
- 1 -
1 - -
Sample Output 2:
Impossible
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <deque>

using namespace std;

/*
15:50
利用in/pre/post根的位置不断切分
0表示未知
17:50 22/35 PT2,3,4,5 WA
*/

namespace nsT1006A
{
	enum IDEnum
	{
		INID = 0,
		PREID,
		POSTID
	};
	const int TOTALORDER = 3;

	struct Node
	{
		int data = 0;
		int left = 0;
		int right = 0;
	};
	vector<Node> vNode;

	int nNode;
	vector<vector<int>> vvOrder;
	vector<int> vRest;

	bool bImpossible = false;
	vector<int> vLevel;

	void Reset(void)
	{
		nNode = 0;
		vNode.clear();
		vvOrder.assign(3, vector<int>());
		vRest.assign(3, 0);
		bImpossible = false;
		vLevel.clear();
	}

	int GetNode(const string& s)
	{
		if (s == "-")
		{
			return 0;
		}
		return stoi(s);
	}

	int GetRest(const vector<int>& v, int start, int len)
	{
		return (int)count(v.begin() + start, v.begin() + start + len, 0);
	}

	void GetMiss(const unordered_set<int>& nodes, vector<int>& v, int start, int len)
	{
		for (auto i : nodes)
		{
			auto it = find(v.begin() + start, v.begin() + start + len, i);
			if (it != v.end())
			{
				*it = i;
				break;
			}
		}
	}

	int Build(int in1, int pre1, int post1, int len)
	{
		if (len <= 0 || bImpossible) { return 0; }
		// root ?
		int root = 0;
		int rootLeft = 0;
		int rootRight = 0;
		int& preRoot = vvOrder[PREID][pre1];
		int& postRoot = vvOrder[POSTID][post1 + len - 1];
		if (preRoot || postRoot)
		{
			if (preRoot && postRoot && (preRoot != postRoot))
			{
				bImpossible = true;
				return 0;
			}
			if (!preRoot)
			{
				preRoot = postRoot;
				--vRest[PREID];
			}
			if (!postRoot)
			{
				postRoot = preRoot;
				--vRest[POSTID];
			}
			root = preRoot;
			vector<int>& inOrder = vvOrder[INID];
			auto inIt = find(inOrder.begin(), inOrder.end(), root);
			if (inIt == inOrder.end())
			{
				// no in root
				if (GetRest(inOrder, in1, len) != 1)
				{
					bImpossible = true;
					return 0;
				}
				inIt = find(inOrder.begin() + in1, inOrder.begin() + in1 + len, 0);
			}
			*inIt = root;
			int nLeft = int(inIt - inOrder.begin()) - in1;
			int nRight = len - nLeft - 1;
			if (nLeft > 0)
			{
				rootLeft = Build(in1, pre1 + 1, post1, nLeft);
			}
			if (nRight > 0)
			{
				rootRight = Build(in1 + nLeft + 1, pre1 + nLeft + 1, post1 + nLeft, nRight);
			}
		}
		else
		{
			// no pre && post
			bool bIn = GetRest(vvOrder[INID], in1, len) <= 1;
			bool bPre = GetRest(vvOrder[PREID], in1, len) <= 1;
			bool bPost = GetRest(vvOrder[POSTID], in1, len) <= 1;
			int vecRest = 0;

			if (bIn) { ++vecRest; }
			if (bPre) { ++vecRest; }
			if (bPost) { ++vecRest; }

			if (vecRest < 2)
			{
				bImpossible = true;
				return 0;
			}
			unordered_set<int> allSet;
			vector<int> v{ in1, pre1, post1 };
			for (int i = 0; i < TOTALORDER; ++i)
			{
				for (int j = 0; j < len; ++j)
				{
					int iNode = vvOrder[i][j + v[i]];
					if (!iNode)
					{
						continue;
					}
					allSet.insert(iNode);
					if (allSet.size() == len) { break; }
				}
				if (allSet.size() == len) { break; }
			}

			if (allSet.size() != len)
			{
				bImpossible = true;
				return 0;
			}
			GetMiss(allSet, vvOrder[PREID], pre1, len);
			GetMiss(allSet, vvOrder[POSTID], post1, len);
			if (bIn)
			{
				GetMiss(allSet, vvOrder[INID], in1, len);
			}
			root = preRoot;
		}

		vNode[root].left = rootLeft;
		vNode[root].right = rootRight;
// 		if (root) Level.push_back(root);
// 		if (rootRight) Level.push_back(rootRight);
// 		if (rootLeft) Level.push_back(rootLeft);
		return root;
	}

	void PrintVec(const vector<int>& v)
	{
		cout << v.front();
		for (size_t i = 1; i < v.size(); ++i)
		{
			cout << " " << v[i];
		}
		cout << endl;
	}

	void LevelPrint(int root)
	{
		deque<int> dqNodes;
		dqNodes.push_back(root);
		while (!dqNodes.empty())
		{
			root = dqNodes.front();
			dqNodes.pop_front();
			vLevel.push_back(root);
			if (vNode[root].left)
			{
				dqNodes.push_back(vNode[root].left);
			}
			if (vNode[root].right)
			{
				dqNodes.push_back(vNode[root].right);
			}
		}
		PrintVec(vLevel);
	}

	void main(void)
	{
		Reset();
		cin >> nNode;
		vNode.assign(nNode + 1, Node());
		string s;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < nNode; ++j)
			{
				cin >> s;
				int node = GetNode(s);
				if (!node)
				{
					++vRest[i];
				}
				vvOrder[i].push_back(node);
			}
		}

		int root = Build(0, 0, 0, nNode);
		if (bImpossible)
		{
			cout << "Impossible" << endl;
			return;
		}
		PrintVec(vvOrder[INID]);
		PrintVec(vvOrder[PREID]);
		PrintVec(vvOrder[POSTID]);
		LevelPrint(root);
//		if (root) Level.push_back(root);
	}
}

// rename this to main int PAT
int T1006Func(void)
{
	nsT1006A::main();
	return 0;
}


void T1006(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1006Func();
	cout << endl;
}

void T1006(void)
{
	T1006("data\\T1006-1.txt"); // 
	T1006("data\\T1006-2.txt"); // 
}

