void A1133(void);
/*
PT2不过 原因：只有1个点时，不能正确打印结果。

测试：有数据，地址除-1外为正
题目：5-digit nonnegative integer， the list is not empty.
positive K <= 1000
问题：仔细读题，注意每个数据的限制条件
	（大部分都有交代，没有交代的一定要考虑各种情况）

1133. Splitting A Linked List (25)
Given a singly linked list, you are supposed to rearrange 
its elements so that all the negative values appear before
all of the non-negatives, and all the values in [0, K] appear 
before all those greater than K. The order of the elements 
inside each class must not be changed. For example, given the
list being 18→7→-4→0→5→-6→10→11→-2 and K being 10,
you must output -4→-6→-2→7→0→5→10→18→11.

Input Specification:

Each input file contains one test case. For each case, the
first line contains the address of the first node, a positive 
N (<= 10^5) which is the total number of nodes, and a positive
K (<=1000). The address of a node is a 5-digit nonnegative 
integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Data Next

where Address is the position of the node, Data is an integer 
in [-105, 105], and Next is the position of the next node. It 
is guaranteed that the list is not empty.

Output Specification:

For each case, output in order (from beginning to the end of 
the list) the resulting linked list. Each node occupies a line, 
and is printed in the same format as in the input.

Sample Input:
00100 9 10
23333 10 27777
00000 0 99999
00100 18 12309
68237 -6 23333
33218 -4 00000
48652 -2 -1
99999 5 68237
27777 11 48652
12309 7 33218

Sample Output:
33218 -4 68237
68237 -6 48652
48652 -2 12309
12309 7 00000
00000 0 99999
99999 5 23333
23333 10 00100
00100 18 27777
27777 11 -1
*/

#include "patMain.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

string AddrStr(int n)
{
	if (n == -1)
	{
		return "-1";
	}
	char s[6];
	sprintf(s, "%05d", n);
	s[5] = 0;
	return s;
}

struct A1133Node
{
	int addr;
	int val;
	int next;

	A1133Node(int a, int v, int n)
		: addr(a)
		, val(v)
		, next(n)
	{
	}

	void Print(void)
	{
		cout << AddrStr(addr) << " " << val << " " << AddrStr(next) << endl;
	}
};

int A1133Func(void)
{
	// avoid memory leakage with smart pointer
	int start, cnt, b;
	cin >> start >> cnt >> b;
	
	int a,val,n;
	map<int, A1133Node*> m;
	A1133Node* p = nullptr;
	while (cin >> a >> val >> n)
	{
		p = new A1133Node(a, val, n);
		m[a] = p;
	}
	// to list
	vector<A1133Node*> v;
	p = m[start];
	v.push_back(p);
	while (p->next != -1) 
	{
		p = m[p->next];
		v.push_back(p);
	}
	
	vector<A1133Node*> v1;
	vector<A1133Node*> v2;
	vector<A1133Node*> v3;
	for (int i = 0; i < v.size(); ++i)
	{
		int val = v[i]->val;
		if (v[i]->val < 0)
		{
			v1.push_back(v[i]);
		}
		else if (val > b)
		{
			v3.push_back(v[i]);
		}
		else
		{
			v2.push_back(v[i]);
		}
	}
	v1.insert(v1.end(), v2.begin(), v2.end());
	v1.insert(v1.end(), v3.begin(), v3.end());
	
	int length = (int)v1.size();
	for (int i = 1; i < length; ++i)
	{
		A1133Node* pPrev = v1[i - 1];
		pPrev->next = v1[i]->addr;
		pPrev->Print();
	}
	A1133Node* last = v1.back();
	last->next = -1;
	// 原来这里有判断 len>1 才打印
	// 会导致总数为1的时候不打印结果
	last->Print();

	return 0;
}

void A1133(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);

	A1133Func();
}

void A1133(void)
{
	A1133("data\\A1133-1.TXT");
	A1133("data\\A1133-2.TXT");
}