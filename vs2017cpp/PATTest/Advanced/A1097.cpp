/*
1097. Deduplication on a Linked List (25)
300 ms
65536 kB

15：15

Given a singly linked list L with integer keys, you are supposed to remove the nodes with duplicated absolute values of the keys. 
That is, for each value K, only the first node of which the value or absolute value of its key equals K will be kept. 
At the mean time, all the removed nodes must be kept in a separate list. 
For example, given L being 21→-15→-15→-7→15, you must output 21→-15→-7, and the removed list -15→15.

Input Specification:

Each input file contains one test case. For each case, the first line contains the address of the first node, 
and a positive N (<= 10^5) which is the total number of nodes. 
The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Key Next

where Address is the position of the node, Key is an integer of which absolute value is no more than 10^4, and Next is the position of the next node.

Output Specification:

For each case, output the resulting linked list first, then the removed list. 
Each node occupies a line, and is printed in the same format as in the input.

Sample Input:
00100 5
99999 -7 87654
23854 -15 00000
87654 15 -1
00000 -15 99999
00100 21 23854
Sample Output:
00100 21 23854
23854 -15 99999
99999 -7 -1
00000 -15 87654
87654 15 -1
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

/*
15:15
找到绝对值相等的后续节点
分别输出两个链表
地址10^5: MAXADDR 100000
值10^4: MAXVAL 10000

vector<int> vVisit(MAXVAL)

vector<int> vData(MAXADDR) // 下标为地址
vector<int> vNext(MAXADDR)

vector<int> vFirstAddr
vector<int> vSecondAddr

1. 读取，遍历，根据vVisit放入vFirstAddr,vSecondAddr，打印
15：48 23/25 wa2,
	可能是某个无结果导致
15:50 buf-fix-1 pass
*/

namespace A1097A
{
	const int MAXADDR = 100000;
	const int MAXDATA = 10000; 

	// 输入数据
	vector<int> vData; // 下标为地址
	vector<int> vNext;

	// 是否重复
	vector<int> vVisit;

	// 两个结果链表
	vector<int> vFirstAddr;
	vector<int> vSecondAddr;

	void Reset(void)
	{
		vData.assign(MAXADDR, 0);
		vNext.assign(MAXADDR, 0);
		vVisit.assign(MAXADDR, false);
		vFirstAddr.clear();
		vSecondAddr.clear();
	}

	void Print(const vector<int>& v)
	{
		// bug-fix-1
		if (v.empty())
		{
			return;
		}
		for (size_t i = 0; i < v.size(); ++i)
		{
			int addr = v[i];
			if (i == 0)
			{
				printf("%05d %d ", addr, vData[addr]);
			}
			else
			{
				printf("%05d\n%05d %d ", addr, addr, vData[addr]);
			}
		}
		printf("-1\n");
	}

	void main(void)
	{
		Reset();

		int start, n;
		int addr, data, next;
		scanf("%d %d", &start, &n);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d %d %d", &addr, &data, &next);
			vData[addr] = data;
			vNext[addr] = next;
		}

		addr = start;
		while (addr != -1)
		{
			data = vData[addr];
			if (!vVisit[abs(data)])
			{
				vVisit[abs(data)] = true;
				vFirstAddr.push_back(addr);
			}
			else
			{
				vSecondAddr.push_back(addr);
			}
			addr = vNext[addr];
		}
		Print(vFirstAddr);
		Print(vSecondAddr);
	}
}

// rename this to main int PAT
int A1097Func(void)
{
	A1097A::main();
	return 0;
}


void A1097(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1097Func();
	cout << endl;
}

void A1097(void)
{
	A1097("data\\A1097-1.txt"); // 
	A1097("data\\A1097-2.txt"); // 
}

