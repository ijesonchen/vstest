#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace nsA1135B
{
	struct Node
	{
		int val = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		int black = 0;

		bool IsLeaf(void) const { return !left && !right; };
		bool Red(void) const { return val < 0; };
		bool Black(void) const { return val > 0; };

		Node(int v) : val(v) {};
	};

	vector<int> vPreOrcer;
	vector<Node> vNode;
	int nBlack = -1;

	// [first, last]. return last + 1 if not found.
	int RightLeftIndex(int first, int last)
	{
		int root = abs(vPreOrcer[first]);
		for (int i = first + 1; i <= last; ++i)
		{
			if (abs(vPreOrcer[i]) > root)
			{
				return i;
			}
		}
		return last + 1;
	}

	// [first, last]
	void BuildTree(Node*& pRoot, int first, int last)
	{
		if (last < first)
		{
			return;
		}
		pRoot = &vNode[first];
		if (first == last)
		{
			return;
		}
		// left: first+1, right-1
		// right: right, last
		int iLeft1 = first + 1;
		int iRight1 = RightLeftIndex(first, last);
		int iLeft2 = iRight1 - 1;
		int iRight2 = last;
		BuildTree(pRoot->left, iLeft1, iLeft2);
		BuildTree(pRoot->right, iRight1, iRight2);
	}
	bool BlackChild(Node* pRoot)
	{
		if (!pRoot)
		{
			return true;
		}
		if (pRoot->Red())
		{
			if ((pRoot->left && pRoot->left->Red()) ||
				(pRoot->right && pRoot->right->Red()))
			{
				return false;
			}
		}
		return BlackChild(pRoot->left) && BlackChild(pRoot->right);
	}


	bool LeafBlackNodes(Node* p, int nb)
	{
		if (!p)
		{
			if (nBlack == -1)
			{
				nBlack = nb;
				return true;
			}
			else
			{
				return nBlack == nb;
			}
		}
		p->black = nb;
		if (p->Black())
		{
			++p->black;
		}

		if (!LeafBlackNodes(p->left, p->black))
		{
			return false;
		}
		if (!LeafBlackNodes(p->right, p->black))
		{
			return false;
		}
		return true;
	}

	bool IsRbTree(Node* pRoot)
	{
		if (!pRoot->Black())
		{
			return false;
		}
		if (!BlackChild(pRoot))
		{
			return false;
		}
		if (!LeafBlackNodes(pRoot, 0))
		{
			return false;
		}
		return true;
	}

	bool ReadTree(int nNode)
	{
		vPreOrcer.clear();
		vNode.assign(nNode, Node(0));
		nBlack = -1;
		for (int i = 0; i < nNode; ++i)
		{
			int t;
			cin >> t;
			vPreOrcer.push_back(t);
			vNode[i].val = t;
		}
		Node* pRoot = nullptr;
		int last = (int)vNode.size() - 1;
		BuildTree(pRoot, 0, last);
		return IsRbTree(pRoot);
	}

	void Read(void)
	{
		int k, n;
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> n;
			if (ReadTree(n))
			{
				cout << "Yes" << endl;
			}
			else
			{
				cout << "No" << endl;
			}
		}
	}
}


// rename this to main int PAT
int main(void)
{
	nsA1135B::Read();
	return 0;
}
