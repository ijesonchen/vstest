#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

namespace nsA1135Revisit
{
	struct Node
	{
		int data = 0;
		bool red = false;
		int black = 0;

		Node* left = nullptr;
		Node* right = nullptr;

		Node(int v) : data(abs(v)), red(v < 0) {};
	};

	vector<int> preOrder;
	vector<int> inOrder;
	vector<Node> vNode;
	Node* pRoot = nullptr;
	bool bValid = false;

	void Read(void)
	{
		int m, k;
		cin >> m;
		for (int i = 0; i < m; ++i)
		{
			cin >> k;
			vNode.push_back(k);
			preOrder.push_back(abs(k));
		}
		inOrder = preOrder;
		sort(inOrder.begin(), inOrder.end());
	}

	void BuildTree(Node*& p, int pre1, int in1, int len)
	{
		if (len <= 0) { throw 0; }
		if (!bValid) { return; }
		p = &vNode[pre1];
		int inRoot = in1;
		int in2 = in1 + len;
		while (inOrder[inRoot++] != p->data)
		{
			if (inRoot == in2)
			{
				bValid = false;
				return;
			}
		}
		int nLeft = --inRoot - in1;
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

	int nBlack = 0;
	void ValidTree(Node* p, int parentBlack)
	{
		if (!bValid) { return; }
		if (p)
		{
			p->black = parentBlack;
			if (p->red)
			{
				if (p->left && p->left->red || p->right && p->right->red)
				{
					bValid = false;
					return;
				}
			}
			else
			{
				++p->black;
			}
			ValidTree(p->left, p->black);
			ValidTree(p->right, p->black);
		}
		else
		{
			if (!nBlack)
			{
				nBlack = parentBlack;
			}
			else if (nBlack != parentBlack)
			{
				bValid = false;
				return;
			}
		}
	}

	void ValidTree(Node* p)
	{
		if (!bValid) { return; }
		ValidTree(p->left, p->black);
		ValidTree(p->right, p->black);
	}

	int main(void)
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			preOrder.clear();
			inOrder.clear();
			vNode.clear();
			pRoot = nullptr;
			Read();
			bValid = true;
			BuildTree(pRoot, 0, 0, (int)preOrder.size());
			if (!bValid || pRoot->red)
			{
				cout << "No" << endl;
				continue;
			}
			nBlack = 0;
			bValid = true;
			pRoot->black = 1;
			ValidTree(pRoot);
			if (!bValid)
			{
				cout << "No" << endl;
				continue;
			}
			cout << "Yes" << endl;
		}
		return 0;
	}
}

int main(void)
{
	return nsA1135Revisit::main();
}