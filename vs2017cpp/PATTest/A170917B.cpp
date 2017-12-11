void A170917B(void);
/*
B. Splitting A Linked List (25)
Given a singly linked list, you are supposed to rearrange 
its elements so that all the negative values appear before
all of the non-negatives, and all the values in [0, K] appear 
before all those greater than K. The order of the elements 
inside each class must not be changed. For example, given the
list being 18¡ú7¡ú-4¡ú0¡ú5¡ú-6¡ú10¡ú11¡ú-2 and K being 10,
you must output -4¡ú-6¡ú-2¡ú7¡ú0¡ú5¡ú10¡ú18¡ú11.

Input Specification:

Each input file contains one test case. For each case, the
first line contains the address of the first node, a positive 
N (<= 105) which is the total number of nodes, and a positive
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

using namespace std;

struct A170917BNode
{
	int addr;
	int val;
	int next;
	string saddr;
	string snext;

	A170917BNode(string s1, int v, string s2)
		: saddr(s1)
		, val(v)
		, snext(s2)
	{
		addr = atoi(s1.c_str());
		next = atoi(s2.c_str());
	}
};

void A170917BFunc(void)
{
	int start, cnt, b;
	cin >> start >> cnt >> b;

	int n;
	string saddr, snext;
	map<int, A170917BNode*> m;
	A170917BNode* p = nullptr;
	while (cin >> saddr >> n >> snext)
	{
		p = new A170917BNode(saddr, n, snext);
		m[n] = p;
	}
	vector<A170917BNode*> v;
	p = m[start];
	v.push_back(p);
	while (p->next != -1) 
	{
		p = m[p->next];
		v.push_back(p);
	}
	int idx = 0;
	for (int i = 0; i < cnt; ++i)
	{
	}
}

void A170917B(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);

	A170917BFunc();
}

void A170917B(void)
{
	A170917B("data\\A170917B-1.TXT"); // Yes No No
}