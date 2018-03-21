/*
1143. Lowest Common Ancestor (30)
200 ms
65536 kB

test: 0 < node < 1000000;

总结：
	带返回值的递归效率要比参数引用的递归低（2-4倍性能差距）
	发生TLE时，如果感觉代码无法优化，不要凭直觉判断，二分法确定性能瓶颈。一开始一直怀疑查询较慢，实际上是建树插入函数慢。
	优化插入后，A/B方案都可以通过。即问题出在插入上面。
	仔细看方案D，其实不需要建树。仅根据前序+中序（大小序）即可。7ms pass(方案I）
	遇到问题时，先思考再尝试。减少已有思路的影响，尝试有没有其他方案。

日志：(为通过部分标注时间为PT5时间。A-E TLE3,4 FG MLE, HI PASS)
nsA1143A：160 
	vector<bool> 节点是否存在
	FindPath：BST搜索并记录路径

nsA1143B：110 
	vector<bool> 节点是否存在
	LCA: 二分查找同时判断公共节点

nsA1143C：170
	vector<bool> 节点是否存在
	双向链表，vector<Node*>记录节点指针
	两次反向搜索，找到第一个公共节点

nsA1143D：110
	类似B
	vector<bool> 节点是否存在
	preOrder+inOrder(大小序)查找


nsA1143E：110
	类似B
	vector<bool> 节点是否存在
	LCA : 二分查找同时判断公共节点
	合并u或v相同的查询，使用umap<int, v<Node*>>存储
	最后统一输出结果

nsA1143F: 建树时记录路径数组 MLE

nsA1143H: nsA1143B性能测试：
	仅build，107ms TLE3,4
	Insert改为无返回值，引用传参 102s

	使用nsA1143B，改Insert返回值为参数引用。PASS 110ms

nsA1143I:
	使用nsA1143A，改Insert返回值为参数引用。PASS 180ms

nsA1143J：
	使用nsA1143D，不创建树，仅根据树的前序+中序判断

The lowest common ancestor (LCA) of two nodes U and V in a tree is the deepest node that has both U and V as descendants.

A binary search tree (BST) is recursively defined as a binary tree which has the following properties:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
Given any two nodes in a BST, you are supposed to find their LCA.

Input Specification:

Each input file contains one test case. For each case, the first line gives two positive integers:
M (<= 1000), the number of pairs of nodes to be tested; and 
N (<= 10000), the number of keys in the BST, respectively. 
In the second line, N distinct integers are given as the preorder traversal sequence of the BST. 
Then M lines follow, each contains a pair of integer keys U and V. 
All the keys are in the range of int.

Output Specification:

For each given pair of U and V, print in a line "LCA of U and V is A." if the LCA is found and A is the key. 
But if A is one of U and V, print "X is an ancestor of Y." where X is A and Y is the other node. 
If U or V is not found in the BST, print in a line "ERROR: U is not found." 
or "ERROR: V is not found."
or "ERROR: U and V are not found.".

Sample Input:
6 8
6 3 1 2 5 4 8 7
2 5
8 7
1 9
12 -3
0 8
99 99
Sample Output:
LCA of 2 and 5 is 3.
8 is an ancestor of 7.
ERROR: 9 is not found.
ERROR: 12 and -3 are not found.
ERROR: 0 is not found.
ERROR: 99 and 99 are not found.
*/

#include "..\patMain.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <unordered_set>

using namespace std;


/*
nsA1143L: from E, 180ms
*/
namespace nsA1143L
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) : data(d) {};
	};

	void Insert(Node*& p, int d)
	{
		if (!p)
		{
			p = new Node(d);
			return;
		}
		if (d < p->data)
		{
			Insert(p->left, d);
		}
		else if (d > p->data)
		{
			Insert(p->right, d);
		}
		else
		{
			throw 0;
		}
		return;
	}

	enum ResType
	{
		eEXCEP,
		eLCA,
		eANC,
		eEu,
		eEv,
		eEBoth,
	};

	struct Result
	{
		int u;
		int v;
		int anc;
		ResType type = eEXCEP;

		bool operator<(const Result& a) const
		{
			return v < a.v;
		}

		void Print(void)
		{
			switch (type)
			{
			case eLCA:
				printf("LCA of %d and %d is %d.\n", u, v, anc);
				break;
			case eANC:
				if (u == anc)
				{
					printf("%d is an ancestor of %d.\n", u, v);
				}
				else if (v == anc)
				{
					printf("%d is an ancestor of %d.\n", v, u);
				}
				else
				{
					throw 0;
				}
				break;
			case eEu:
				printf("ERROR: %d is not found.\n", u);
				break;
			case eEv:
				printf("ERROR: %d is not found.\n", v);
				break;
			case eEBoth:
				printf("ERROR: %d and %d are not found.\n", u, v);
				break;
			default:
				throw 0;
				break;
			}
		}
	};

	bool ResultLess(const Result* p1, const Result* p2)
	{
		return *p1 < *p2;
	}

	void LCA(Node* p, const int u, vector<Result*>& vpResult)
	{
		if (!p) { throw 0; }
		int data = p->data;
		if (u == data)
		{
			for (auto pRes : vpResult)
			{
				pRes->type = eANC;
				pRes->anc = u;
			}
		}
		else
		{
			vector<Result*> vp1; // < data
			vector<Result*> vp2; // > data
			for (auto pRes : vpResult)
			{
				if (pRes->v < data)
				{
					vp1.push_back(pRes);
				}
				else if (pRes->v == data)
				{
					pRes->type = eANC;
					pRes->anc = pRes->v;
				}
				else
				{
					vp2.push_back(pRes);
				}
			}
			if (u < data)
			{
				LCA(p->left, u, vp1);
				for (auto pRes : vp2)
				{
					pRes->anc = data;
					pRes->type = eLCA;
				}
			}
			else
			{
				for (auto pRes : vp1)
				{
					pRes->anc = data;
					pRes->type = eLCA;
				}
				LCA(p->right, u, vp2);
			}
		}
	}


	void main(void)
	{
		int m, n, d;
		scanf("%d %d", &m, &n);
		Node* pRoot = nullptr;
		vector<bool> vVisit(1000000);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			vVisit[d] = true;
			Insert(pRoot, d);
		}
		int u, v;

		vector<Result> vResult(m);

		vector<Result*> vpResult;
		unordered_map<int, vector<Result*>> mapUResult;

		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			Result& res = vResult[i];
			res.u = u;
			res.v = v;
			bool bu = (u >= 0) && vVisit[u];
			bool bv = (v >= 0) && vVisit[v];
			if (!bu && !bv)
			{
				res.type = eEBoth;
			}
			else if (!bu && bv)
			{
				res.type = eEu;
			}
			else if (bu && !bv)
			{
				res.type = eEv;
			}
			else
			{
				mapUResult[u].push_back(&res);
			}
		}

		for (auto& it : mapUResult)
		{
			LCA(pRoot, it.first, it.second);
		}

		for (auto& res : vResult)
		{
			res.Print();
		}
	}
}

// rename this to main int PAT
int A1143Func(void)
{
	nsA1143L::main();
	return 0;
}



void A1143(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1143Func();
	cout << endl;
}

void A1143(void)
{
	A1143("data\\A1143-1.txt"); // 
}


/*
from nsA1143J 10ms
用uset替换vector
证明可能的情况下，vec要比uset快
*/

namespace nsA1143K
{
	vector<int> vData;

	inline int LCA(int u, int v)
	{
		// u < v
		for (size_t i = 0; i < vData.size(); ++i)
		{
			if (vData[i] >= u && vData[i] <= v)
			{
				return vData[i];
			}
		}
		throw 0;
		return 0;
	}

	void main(void)
	{
		int m, n, d;
		scanf("%d %d", &m, &n);
		vData.resize(n);
		unordered_set<int> setData;

		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			vData[i] = d;
			setData.insert(d);
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			bool bu = (u >= 0) && (setData.find(u) != setData.end());
			bool bv = (v >= 0) && (setData.find(v) != setData.end());
			if (!bu && !bv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!bu && bv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (bu && !bv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{
				int a = u, b = v;
				if (a > b)
				{
					swap(a, b);
				}
				int lca = LCA(a, b);
				if (lca == u)
				{
					printf("%d is an ancestor of %d.\n", u, v);
				}
				else if (lca == v)
				{
					printf("%d is an ancestor of %d.\n", v, u);
				}
				else
				{
					printf("LCA of %d and %d is %d.\n", u, v, lca);
				}
			}
		}

	}
}
/*
from D
pass 7ms
*/

namespace nsA1143J
{
	vector<int> vData;

	inline int LCA(int u, int v)
	{
		// u < v
		for (size_t i = 0; i < vData.size(); ++i)
		{
			if (vData[i] >= u && vData[i] <= v)
			{
				return vData[i];
			}
		}
		throw 0;
		return 0;
	}

	void main(void)
	{
		int m, n, d;
		scanf("%d %d", &m, &n);
		vData.resize(n);
		vector<bool> vVisit(1000000);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			vData[i] = d;
			vVisit[d] = true;
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			bool bu = (u >= 0) && vVisit[u];
			bool bv = (v >= 0) && vVisit[v];
			if (!bu && !bv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!bu && bv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (bu && !bv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{
				int a = u, b = v;
				if (a > b)
				{
					swap(a, b);
				}
				int lca = LCA(a, b);
				if (lca == u)
				{
					printf("%d is an ancestor of %d.\n", u, v);
				}
				else if (lca == v)
				{
					printf("%d is an ancestor of %d.\n", v, u);
				}
				else
				{
					printf("LCA of %d and %d is %d.\n", u, v, lca);
				}
			}
		}

	}
}

/*
FROM nsA1143A
PASS
*/

namespace nsA1143I
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) : data(d) {};
	};

	void Insert(Node*& p, int d)
	{
		if (!p)
		{
			p = new Node(d);
			return;
		}
		if (d < p->data)
		{
			Insert(p->left, d);
		}
		else if (d > p->data)
		{
			Insert(p->right, d);
		}
		else
		{
			throw 0;
		}
	}

	Node* FindPath(Node* p, int d, vector<int>& vPath)
	{
		if (!p) { return nullptr; }
		vPath.push_back(p->data);
		if (p->data == d)
		{
			return p;
		}
		else if (d < p->data)
		{
			return FindPath(p->left, d, vPath);
		}
		else
		{
			return FindPath(p->right, d, vPath);
		}
	}


	void main(void)
	{
		int m, n, d;
		cin >> m >> n;
		Node* pRoot = nullptr;
		vector<bool> vHasNode(1000000);
		for (int i = 0; i < n; ++i)
		{
			cin >> d;
			vHasNode[d] = true;
			Insert(pRoot, d);
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			cin >> u >> v;
			bool bu = (u >= 0) && vHasNode[u];
			bool bv = (v >= 0) && vHasNode[v];
			if (!bu && !bv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!bu && bv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (bu && !bv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{
				vector<int> uPath;
				vector<int> vPath;
				auto pu = FindPath(pRoot, u, uPath);
				auto pv = FindPath(pRoot, v, vPath);
				int iCommon = (int)std::min(uPath.size(), vPath.size()) - 1;
				for (size_t j = 0; j < uPath.size() && j < vPath.size(); ++j)
				{
					if (uPath[j] != vPath[j])
					{
						iCommon = (int)j - 1;
						break;
					}
				}
				if (iCommon < uPath.size() - 1 && iCommon < vPath.size() - 1)
				{
					printf("LCA of %d and %d is %d.\n", u, v, uPath[iCommon]);
				}
				else if (iCommon == uPath.size() - 1)
				{
					printf("%d is an ancestor of %d.\n", u, v);
				}
				else if (iCommon == vPath.size() - 1)
				{
					printf("%d is an ancestor of %d.\n", v, u);
				}
				else
				{
					throw 0;
				}

			}
		}

	}
}

/*
PASS 110ms
*/
namespace nsA1143H
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) : data(d) {};
	};

	void Insert(Node*& p, int d)
	{
		if (!p)
		{
			p = new Node(d);
			return;
		}
		if (d < p->data)
		{
			Insert(p->left, d);
		}
		else if (d > p->data)
		{
			Insert(p->right, d);
		}
		else
		{
			throw 0;
		}
	}

	void LCA(Node* p, int u, int v)
	{
		if (!p) { throw 0; }
		if (u == p->data)
		{
			printf("%d is an ancestor of %d.\n", u, v);
		}
		else if (v == p->data)
		{
			printf("%d is an ancestor of %d.\n", v, u);
		}
		else if ((u > p->data && v < p->data) ||
			(u < p->data && v > p->data))
		{
			printf("LCA of %d and %d is %d.\n", u, v, p->data);
		}
		else if (u < p->data && v < p->data)
		{
			LCA(p->left, u, v);
		}
		else if (u > p->data && v > p->data)
		{
			LCA(p->right, u, v);
		}
		else
		{
			throw 0;
		}
	}

	void main(void)
	{
		int m, n, d;
		scanf("%d %d", &m, &n);
		Node* pRoot = nullptr;
		vector<bool> vVisit(1000000);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			vVisit[d] = true;
			Insert(pRoot, d);
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			bool bu = (u >= 0) && vVisit[u];
			bool bv = (v >= 0) && vVisit[v];
			if (!bu && !bv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!bu && bv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (bu && !bv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{
				LCA(pRoot, u, v);
			}
		}

	}
}

/*
from nsA1143F
build path when insert
18/30 MLE
*/
namespace nsA1143G
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;
		vector<int> vPath;

		Node(int d) : data(d) {};
	};

	unordered_map<int, Node*> mappNode;

	Node* Insert(Node* p, Node* pParent, int d)
	{
		if (!p)
		{
			p = new Node(d);
			mappNode[d] = p;
			if (pParent)
			{
				p->vPath = pParent->vPath;
			}
			p->vPath.push_back(d);
			return p;
		}
		if (d < p->data)
		{
			p->left = Insert(p->left, p, d);
			return p;
		}
		else if (d > p->data)
		{
			p->right = Insert(p->right, p, d);
			return p;
		}
		else
		{
			throw 0;
		}
		return p;
	}

	void LCA(Node* p, int u, int v)
	{
		if (!p) { throw 0; }
		if (u == p->data)
		{
			printf("%d is an ancestor of %d.\n", u, v);
		}
		else if (v == p->data)
		{
			printf("%d is an ancestor of %d.\n", v, u);
		}
		else if ((u > p->data && v < p->data) ||
			(u < p->data && v > p->data))
		{
			printf("LCA of %d and %d is %d.\n", u, v, p->data);
		}
		else if (u < p->data && v < p->data)
		{
			LCA(p->left, u, v);
		}
		else if (u > p->data && v > p->data)
		{
			LCA(p->right, u, v);
		}
		else
		{
			throw 0;
		}
	}

	void main(void)
	{
		int m, n, d;
		scanf("%d %d", &m, &n);
		Node* pRoot = nullptr;

		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			pRoot = Insert(pRoot, pRoot, d);
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			Node* pu = (u >= 0) ? mappNode[u] : nullptr;
			Node* pv = (v >= 0) ? mappNode[v] : nullptr;
			if (!pu && !pv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!pu && pv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (pu && !pv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{

				vector<int>& uPath = pu->vPath;
				vector<int>& vPath = pv->vPath;
				int iCommon = (int)std::min(uPath.size(), vPath.size()) - 1;
				for (size_t j = 0; j < uPath.size() && j < vPath.size(); ++j)
				{
					if (uPath[j] != vPath[j])
					{
						iCommon = (int)j - 1;
						break;
					}
				}
				if (iCommon < uPath.size() - 1 && iCommon < vPath.size() - 1)
				{
					printf("LCA of %d and %d is %d.\n", u, v, uPath[iCommon]);
				}
				else if (iCommon == uPath.size() - 1)
				{
					printf("%d is an ancestor of %d.\n", u, v);
				}
				else if (iCommon == vPath.size() - 1)
				{
					printf("%d is an ancestor of %d.\n", v, u);
				}
				else
				{
					throw 0;
				}
			}
		}

	}
}
/*
from nsA1143B
build path when insert
18/30 MLE
*/
namespace nsA1143F
{
	const int MAXNODE = 1000000;
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;
		vector<int> vPath;

		Node(int d) : data(d) {};
	};

	vector<Node*> vpNode(MAXNODE);

	Node* Insert(Node* p, Node* pParent, int d)
	{
		if (!p)
		{
			p = new Node(d);
			vpNode[d] = p;
			if (pParent)
			{
				p->vPath = pParent->vPath;
			}
			p->vPath.push_back(d);
			return p;
		}
		if (d < p->data)
		{
			p->left = Insert(p->left, p, d);
			return p;
		}
		else if (d > p->data)
		{
			p->right = Insert(p->right, p, d);
			return p;
		}
		else
		{
			throw 0;
		}
		return p;
	}

	void LCA(Node* p, int u, int v)
	{
		if (!p) { throw 0; }
		if (u == p->data)
		{
			printf("%d is an ancestor of %d.\n", u, v);
		}
		else if (v == p->data)
		{
			printf("%d is an ancestor of %d.\n", v, u);
		}
		else if ((u > p->data && v < p->data) ||
			(u < p->data && v > p->data))
		{
			printf("LCA of %d and %d is %d.\n", u, v, p->data);
		}
		else if (u < p->data && v < p->data)
		{
			LCA(p->left, u, v);
		}
		else if (u > p->data && v > p->data)
		{
			LCA(p->right, u, v);
		}
		else
		{
			throw 0;
		}
	}

	void main(void)
	{
		int m, n, d;
		scanf("%d %d", &m, &n);
		Node* pRoot = nullptr;

		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			pRoot = Insert(pRoot, pRoot, d);
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			Node* pu = (u >= 0) ? vpNode[u] : nullptr;
			Node* pv = (v >= 0) ? vpNode[v] : nullptr;
			if (!pu && !pv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!pu && pv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (pu && !pv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{

				vector<int>& uPath = pu->vPath;
				vector<int>& vPath = pv->vPath;
				int iCommon = (int)std::min(uPath.size(), vPath.size()) - 1;
				for (size_t j = 0; j < uPath.size() && j < vPath.size(); ++j)
				{
					if (uPath[j] != vPath[j])
					{
						iCommon = (int)j - 1;
						break;
					}
				}
				if (iCommon < uPath.size() - 1 && iCommon < vPath.size() - 1)
				{
					printf("LCA of %d and %d is %d.\n", u, v, uPath[iCommon]);
				}
				else if (iCommon == uPath.size() - 1)
				{
					printf("%d is an ancestor of %d.\n", u, v);
				}
				else if (iCommon == vPath.size() - 1)
				{
					printf("%d is an ancestor of %d.\n", v, u);
				}
				else
				{
					throw 0;
				}
			}
		}

	}
}
/*
FROM nsA1143B

合并？
22/30 TLE 3,4
*/
namespace nsA1143E
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) : data(d) {};
	};

	Node* Insert(Node* p, int d)
	{
		if (!p)
		{
			p = new Node(d);
			return p;
		}
		if (d < p->data)
		{
			p->left = Insert(p->left, d);
			return p;
		}
		else if (d > p->data)
		{
			p->right = Insert(p->right, d);
			return p;
		}
		else
		{
			throw 0;
		}
		return p;
	}

	enum ResType
	{
		eEXCEP,
		eLCA,
		eANC,
		eEu,
		eEv,
		eEBoth,
	};

	struct Result
	{
		int u;
		int v;
		int anc;
		ResType type = eEXCEP;

		bool operator<(const Result& a) const
		{
			return v < a.v;
		}

		void Print(void)
		{
			switch (type)
			{
			case eLCA:
				printf("LCA of %d and %d is %d.\n", u, v, anc);
				break;
			case eANC:
				if (u == anc)
				{
					printf("%d is an ancestor of %d.\n", u, v);
				}
				else if (v == anc)
				{
					printf("%d is an ancestor of %d.\n", v, u);
				}
				else
				{
					throw 0;
				}
				break;
			case eEu:
				printf("ERROR: %d is not found.\n", u);
				break;
			case eEv:
				printf("ERROR: %d is not found.\n", v);
				break;
			case eEBoth:
				printf("ERROR: %d and %d are not found.\n", u, v);
				break;
			default:
				throw 0;
				break;
			}
		}
	};

	bool ResultLess(const Result* p1, const Result* p2)
	{
		return *p1 < *p2;
	}

	void LCA(Node* p, const int u, vector<Result*>& vpResult)
	{
		if (!p) { throw 0; }
		int data = p->data;
		if (u == data)
		{
			for (auto pRes : vpResult)
			{
				pRes->type = eANC;
				pRes->anc = u;
			}
		}
		else
		{
			vector<Result*> vp1; // < data
			vector<Result*> vp2; // > data
			for (auto pRes : vpResult)
			{
				if (pRes->v < data)
				{
					vp1.push_back(pRes);
				}
				else if (pRes->v == data)
				{
					pRes->type = eANC;
					pRes->anc = pRes->v;
				}
				else
				{
					vp2.push_back(pRes);
				}
			}
			if (u < data)
			{
				LCA(p->left, u, vp1);
				for (auto pRes : vp2)
				{
					pRes->anc = data;
					pRes->type = eLCA;
				}
			}
			else
			{
				for (auto pRes : vp1)
				{
					pRes->anc = data;
					pRes->type = eLCA;
				}
				LCA(p->right, u, vp2);
			}
		}
	}


	void main(void)
	{
		int m, n, d;
		scanf("%d %d", &m, &n);
		Node* pRoot = nullptr;
		vector<bool> vVisit(1000000);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			vVisit[d] = true;
			pRoot = Insert(pRoot, d);
		}
		int u, v;

		vector<Result> vResult(m);

		vector<Result*> vpResult;
		unordered_map<int, vector<Result*>> mapUResult;

		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			Result& res = vResult[i];
			res.u = u;
			res.v = v;
			bool bu = (u >= 0) && vVisit[u];
			bool bv = (v >= 0) && vVisit[v];
			if (!bu && !bv)
			{
				res.type = eEBoth;
			}
			else if (!bu && bv)
			{
				res.type = eEu;
			}
			else if (bu && !bv)
			{
				res.type = eEv;
			}
			else
			{
				mapUResult[u].push_back(&res);
			}
		}

		for (auto& it : mapUResult)
		{
			LCA(pRoot, it.first, it.second);
		}

		for (auto& res : vResult)
		{
			res.Print();
		}
	}
}
/*
FROM nsA1143B

22/30 TLE 3,4
*/
namespace nsA1143D
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) : data(d) {};
	};

	Node* Insert(Node* p, int d)
	{
		if (!p)
		{
			p = new Node(d);
			return p;
		}
		if (d < p->data)
		{
			p->left = Insert(p->left, d);
			return p;
		}
		else if (d > p->data)
		{
			p->right = Insert(p->right, d);
			return p;
		}
		else
		{
			throw 0;
		}
		return p;
	}

	vector<int> vData;

	inline int LCA(int u, int v)
	{
		// u < v
		for (size_t i = 0; i < vData.size(); ++i)
		{
			if (vData[i] >= u && vData[i] <= v)
			{
				return vData[i];
			}
		}
		throw 0;
		return 0;
	}

	void main(void)
	{
		int m, n, d;
		scanf("%d %d", &m, &n);
		Node* pRoot = nullptr;
		vData.resize(n);
		vector<bool> vVisit(1000000);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			vData[i] = d;
			vVisit[d] = true;
			pRoot = Insert(pRoot, d);
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			bool bu = (u >= 0) && vVisit[u];
			bool bv = (v >= 0) && vVisit[v];
			if (!bu && !bv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!bu && bv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (bu && !bv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{
				int a = u, b = v;
				if (a > b)
				{
					swap(a, b);
				}
				int lca = LCA(a, b);
				if (lca == u)
				{
					printf("%d is an ancestor of %d.\n", u, v);
				}
				else if (lca == v)
				{
					printf("%d is an ancestor of %d.\n", v, u);
				}
				else
				{
					printf("LCA of %d and %d is %d.\n", u, v, lca);
				}
			}
		}

	}
}



/*
FROM nsA1143B

根据双向链表，分别u，v向根反向搜索两次
TLE
性能比nsA1143B差
*/
namespace nsA1143C 
{
	const int MAXNODE = 1000000;
	struct Node
	{
		int data = 0;
		Node* parent = nullptr;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) : data(d) {};
	};

	vector<bool> vHasNode(MAXNODE);
	vector<Node*> vpNode(MAXNODE);

	Node* Insert(Node* p, int d)
	{
		if (!p)
		{
			p = new Node(d);
			vpNode[d] = p;
			return p;
		}
		if (d < p->data)
		{
			p->left = Insert(p->left, d);
			p->left->parent = p;
			return p;
		}
		else if (d > p->data)
		{
			p->right = Insert(p->right, d);
			p->right->parent = p;
			return p;
		}
		else
		{
			throw 0;
		}
		return p;
	}

	int LCA(const int u, const int v)
	{
		// u < v;
		vector<bool> vVisit(MAXNODE);
		Node* p = vpNode[u];
		while (p && p->data <= v)
		{
			vVisit[p->data] = true;
			p = p->parent;
		}
		p = vpNode[v];
		while (p && p->data >= u)
		{
			if (vVisit[p->data])
			{
				// on the path
				return p->data;
			}
			p = p->parent;
		}
		throw 0;
		return -1;
	}

	void main(void)
	{
		int m, n, d;
		scanf("%d %d", &m, &n);
		Node* pRoot = nullptr;
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			vHasNode[d] = true;
			pRoot = Insert(pRoot, d);
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			bool bu = (u >= 0) && vHasNode[u];
			bool bv = (v >= 0) && vHasNode[v];
			if (!bu && !bv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!bu && bv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (bu && !bv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{
				int a = u, b = v;
				if (a > b)
				{
					swap(a, b);
				}
				int lca = LCA(a, b);
				if (lca == u)
				{
					printf("%d is an ancestor of %d.\n", u, v);
				}
				else if (lca == v)
				{
					printf("%d is an ancestor of %d.\n", v, u);
				}
				else
				{
					printf("LCA of %d and %d is %d.\n", u, v, lca);
				}
			}
		}

	}
}

/*
FROM nsA1143A

LCA on-the-fly
scanf
TLE3,4
*/
namespace nsA1143B
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) : data(d) {};
	};

	Node* Insert(Node* p, int d)
	{
		if (!p)
		{
			p = new Node(d);
			return p;
		}
		if (d < p->data)
		{
			p->left = Insert(p->left, d);
			return p;
		}
		else if (d > p->data)
		{
			p->right = Insert(p->right, d);
			return p;
		}
		else
		{
			throw 0;
		}
		return p;
	}

	void LCA(Node* p, int u, int v)
	{
		if (!p) { throw 0; }
		if (u == p->data)
		{
			printf("%d is an ancestor of %d.\n", u, v);
		}
		else if (v == p->data)
		{
			printf("%d is an ancestor of %d.\n", v, u);
		}
		else if ((u > p->data && v < p->data) ||
			(u < p->data && v > p->data))
		{
			printf("LCA of %d and %d is %d.\n", u, v, p->data);
		}
		else if (u < p->data && v < p->data)
		{
			LCA(p->left, u, v);
		}
		else if (u > p->data && v > p->data)
		{
			LCA(p->right, u, v);
		}
		else
		{
			throw 0;
		}
	}

	void main(void)
	{
		int m, n, d;
		scanf("%d %d", &m, &n);
		Node* pRoot = nullptr;
		vector<bool> vVisit(1000000);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &d);
			vVisit[d] = true;
			pRoot = Insert(pRoot, d);
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &u, &v);
			bool bu = (u >= 0) && vVisit[u];
			bool bv = (v >= 0) && vVisit[v];
			if (!bu && !bv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!bu && bv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (bu && !bv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{
				LCA(pRoot, u, v);
			}
		}

	}
}
namespace nsA1143A
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) : data(d) {};
	};
	
	Node* Insert(Node* p, int d)
	{
		if (!p)
		{
			p = new Node(d);
			return p;
		}
		if (d < p->data)
		{
			p->left = Insert(p->left, d);
			return p;
		}
		else if (d > p->data)
		{
			p->right = Insert(p->right, d);
			return p;
		}
		else
		{
			throw 0;
		}
		return p;
	}

	Node* FindPath(Node* p, int d, vector<int>& vPath)
	{
		if (!p) { return nullptr; }
		vPath.push_back(p->data);
		if (p->data == d)
		{
			return p;
		}
		else if (d < p->data)
		{
			return FindPath(p->left, d, vPath);
		}
		else
		{
			return FindPath(p->right, d, vPath);
		}
	}


	void main(void)
	{
		int m, n, d;
		cin >> m >> n;
		Node* pRoot = nullptr;
		vector<bool> vHasNode(1000000);
		for (int i = 0; i < n; ++i)
		{
			cin >> d;
			vHasNode[d] = true;
			pRoot = Insert(pRoot, d);
		}
		int u, v;

		for (int i = 0; i < m; ++i)
		{
			cin >> u >> v;
			bool bu = (u >= 0) && vHasNode[u];
			bool bv = (v >= 0) && vHasNode[v];
			if (!bu && !bv)
			{
				printf("ERROR: %d and %d are not found.\n", u, v);
			}
			else if (!bu && bv)
			{
				printf("ERROR: %d is not found.\n", u);
			}
			else if (bu && !bv)
			{
				printf("ERROR: %d is not found.\n", v);
			}
			else
			{
				vector<int> uPath;
				vector<int> vPath;
				auto pu = FindPath(pRoot, u, uPath);
				auto pv = FindPath(pRoot, v, vPath);
				int iCommon = (int)std::min(uPath.size(), vPath.size()) - 1;
				for (size_t j = 0; j < uPath.size() && j < vPath.size(); ++j)
				{
					if (uPath[j] != vPath[j])
					{
						iCommon = (int)j - 1;
						break;
					}
				}
				if (iCommon < uPath.size() - 1 && iCommon < vPath.size() - 1)
				{
					printf("LCA of %d and %d is %d.\n", u, v, uPath[iCommon]);
				}
				else if (iCommon == uPath.size() - 1)
				{
					printf("%d is an ancestor of %d.\n", u, v);
				}
				else if (iCommon == vPath.size() - 1)
				{
					printf("%d is an ancestor of %d.\n", v, u);
				}
				else
				{
					throw 0;
				}

			}
		}

	}
}

