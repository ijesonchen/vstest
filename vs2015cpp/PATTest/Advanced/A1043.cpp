/*
1043. Is It a Binary Search Tree (25)

cost: 70min

总结：一定要注意输出格式（大小写之类）

A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.

If we swap the left and right subtrees of every node, 
then the resulting tree is called the Mirror Image of a BST.

Now given a sequence of integer keys, you are supposed to tell 
if it is the preorder traversal sequence of a BST or the mirror image of a BST.

Input Specification:
Each input file contains one test case. 
For each case, the first line contains a positive integer N (<=1000). 
Then N integer keys are given in the next line. 
All the numbers in a line are separated by a space.

Output Specification:
For each test case, first print in a line 
"YES" if the sequence is the preorder traversal sequence of a BST or the mirror image of a BST, 
or "NO" if not. 
Then if the answer is "YES", print in the next line the postorder traversal sequence of that tree. 
All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input 1:
7
8 6 5 7 10 8 11
Sample Output 1:
YES
5 7 6 8 11 10 8
Sample Input 2:
7
8 10 11 8 6 7 5
Sample Output 2:
YES
11 8 10 7 5 6 8
Sample Input 3:
7
8 6 8 5 10 9 11
Sample Output 3:
NO
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


/*
20:40
	1. 前序+中序 重建树
		小序/大序各一遍，那个通过算哪个
	2. 是否合法？
	3. 后序输出
21:20 20/25 pt4,6wa

	增加BST验证
21:25 20/25 pt4,6 wa

	bug-fix1: 大序时inRoot判定
21:35 23/30 pt6 wa

	bug-fix2: 输出Yes -> YES
	不需BST验证
21:50 pass
*/

namespace nsA1043Deprecated
{
	struct Node
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) :data(d) {};
	};

	bool ValidTreeLt(Node* p)
	{
		if (!p) { return true; }
		if (p->left && p->left->data >= p->data ||
			p->right && p->right->data < p->data)
		{
			return false;
		}
		return ValidTreeLt(p->left) && ValidTreeLt(p->right);
	}

	bool ValidTreeGte(Node* p)
	{
		if (!p) { return true; }
		if (p->left && p->left->data < p->data ||
			p->right && p->right->data >= p->data)
		{
			return false;
		}
		return ValidTreeGte(p->left) && ValidTreeGte(p->right);
	}
}

namespace nsA1043A
{
	struct Node 
	{
		int data = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int d) :data(d) {};
	};

	vector<int> preOrder;
	vector<Node> vNode;

	vector<int> inOrder;
	Node* pRoot = nullptr;
	bool bLess = true;

	vector<int> postOrder;

	bool bValid = true;

	void BuildTree(Node*& p, int pre1, int in1, int len)
	{
		if (!bValid) { return; }
		p = &vNode[pre1];
		int inRoot;
		if (bLess)
		{
			inRoot = in1;
			int in2 = in1 + len;
			while (inOrder[inRoot++] != p->data)
			{
				if (inRoot >= in2)
				{
					bValid = false;
					return;
				}
			}
			--inRoot;
		}
		else
		{
			inRoot = in1 + len - 1;
			while (inOrder[inRoot--] != p->data)
			{
				// bug-fix1
				if (inRoot < in1)
				{
					bValid = false;
					return;
				}
			}
			++inRoot;
		}
		int nLeft = inRoot - in1;
		if (nLeft)
		{
			BuildTree(p->left, pre1 + 1, in1, nLeft);
		}
		int nRight = len - nLeft - 1;
		if (nRight)
		{
			BuildTree(p->right, pre1 + 1 + nLeft, inRoot + 1, nRight);
		}
	}

	void PostOrder(Node* p)
	{
		if (p)
		{
			PostOrder(p->left);
			PostOrder(p->right);
			postOrder.push_back(p->data);
		}
	}

	void PrintPostOrder(void)
	{
		postOrder.clear();
		PostOrder(pRoot);
		cout << postOrder.front();
		for (size_t i = 1; i < postOrder.size(); ++i)
		{
			cout << " " << postOrder[i];
		}
		cout << endl;
	}

	int main(void)
	{
		preOrder.clear();
		inOrder.clear();
		vNode.clear();

		int n, k;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> k;
			preOrder.push_back(k);
			vNode.push_back(k);
		}
		if (n == 1)
		{
			// bug-fix 2
			cout << "YES" << endl << preOrder.front() << endl;
			return 0;
		}
		inOrder = preOrder;
		// lt
		bLess = true;
		sort(inOrder.begin(), inOrder.end());
		bValid = true;
		BuildTree(pRoot, 0, 0, n);
		if (bValid)
		{
			cout << "YES" << endl;
			PrintPostOrder();
			return 0;
		}
		// gte
		bLess = false;
		for (int i = 0; i < n/2; ++i)
			{ swap(inOrder[i], inOrder[n - 1 - i]); }
		bValid = true;
		BuildTree(pRoot, 0, 0, n);
		if (bValid)
		{
			cout << "YES" << endl;
			PrintPostOrder();
			return 0;
		}
		cout << "NO" << endl;
		return 0;
	}
}

// ref https://www.liuchuo.net/archives/2153
/*
根据前序直接生成后序
小序/大序各一遍
2H 22/25 pt3 wa
*/

namespace nsA1043Liuchuo
{
	using namespace std;
	bool isMirror;
	vector<int> pre, post;
	void getpost(int root, int tail) 
	{
		if (root > tail) return;
		int i = root + 1, 
			j = tail;
		if (!isMirror)
		{
			while (i <= tail && pre[root] > pre[i]) i++;
			while (j > root && pre[root] <= pre[j]) j--;
		}
		else 
		{
			while (i <= tail && pre[root] <= pre[i]) i++;
			while (j > root && pre[root] > pre[j]) j--;
		}
		if (i - j != 1) return;
		getpost(root + 1, j);
		getpost(i, tail);
		post.push_back(pre[root]);
	}

	int main() 
	{
		int n;
		scanf("%d", &n);
		pre.resize(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &pre[i]);

		getpost(0, n - 1);
		if (post.size() != n) 
		{
			isMirror = true;
			post.clear();
			getpost(0, n - 1);
		}

		if (post.size() == n) 
		{
			printf("YES\n%d", post[0]);
			for (int i = 1; i < n; i++)
				printf(" %d", post[i]);
		}
		else 
		{
			printf("NO");
		}
		return 0;
	}
}

namespace nsA1043RefPre2Post
{
	vector<int> pre;
	vector<int> post;
	bool mirror = false;

	void GetPost(int left, int right)
	{
		if (left > right)
		{
			return;
		}
		int root = pre[left];
		if (left == right)
		{
			post.push_back(root);
			return;
		}
		int i = left + 1, j = right;
		int t = 0;
		if (!mirror)
		{
			while (i <= right && pre[i] < root) { ++i; }
			while (j >= left && pre[j] >= root) { --j; }
			if (j + 1 != i) { return; }
		}
		else
		{
			while (i <= right && pre[i] >= root) { ++i; }
			while (j >= left && pre[j] < root) { --j; }
			if (j + 1 != i) { return; }
		}
		--i , ++j;
		GetPost(left + 1, i);
		GetPost(j, right);
		post.push_back(root);
	}

	void PrintPost(void)
	{
		cout << post.front();
		for (size_t i = 1; i < post.size(); ++i)
		{
			cout << " " << post[i];
		}
		cout << endl;
	}

	int main(void)
	{
		int n;
		cin >> n;
		pre.resize(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> pre[i];
		}
		if (n==1)
		{
			cout << "YES" << endl
				<< pre.front() << endl;
			return 0;
		}
		mirror = false;
		post.clear();
		GetPost(0, n-1);
		if (post.size() == pre.size())
		{
			cout << "YES" << endl;
			PrintPost();
			return 0;
		}
		mirror = true;
		post.clear();
		GetPost(0, n-1);
		if (post.size() == pre.size())
		{
			cout << "YES" << endl;
			PrintPost();
			return 0;
		}
		cout << "NO" << endl;

		return 0;
	}
}

// rename this to main int PAT
int A1043Func(void)
{
	return nsA1043RefPre2Post::main();
}


void A1043(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1043Func();
	cout << endl;
}

void A1043(void)
{
	A1043("data\\A1043-1.txt"); // 
	A1043("data\\A1043-2.txt"); // 
	A1043("data\\A1043-3.txt"); // 
	A1043("data\\A1043-4.txt"); // YES 8 9 8
}

