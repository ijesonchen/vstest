/*
1032. Sharing (25)

cost: 20:45

sln: 15min 
	第一遍遍历+标记
	第二遍遍历到标记-》相同
	找不到-》没有
	PASS

To store English words, one method is to use linked lists and store a word letter by letter. 
To save some space, we may let the words share the same sublist if they share the same suffix. 
For example, "loading" and "being" are stored as showed in Figure 1.

Figure 1
word1: load
			ing -> NULL
word2: be

You are supposed to find the starting position of the common suffix (e.g. the position of "i" in Figure 1).

Input Specification:

Each input file contains one test case. 
For each case, the first line contains two addresses of nodes and a positive N (<= 105), 
where the two addresses are the addresses of the first nodes of the two words, 
and N is the total number of nodes. 
The address of a node is a 5-digit positive integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Data Next

where Address is the position of the node, 
Data is the letter contained by this node which is an English letter chosen from {a-z, A-Z}, 
and Next is the position of the next node.

Output Specification:

For each case, simply output the 5-digit starting position of the common suffix. 
If the two words have no common suffix, output "-1" instead.

Sample Input 1:
11111 22222 9
67890 i 00002
00010 a 12345
00003 g -1
12345 D 67890
00002 n 00003
22222 B 23456
11111 L 00001
23456 e 67890
00001 o 00010
Sample Output 1:
67890
Sample Input 2:
00001 00002 4
00001 a 10001
10001 s -1
00002 a 10002
10002 t -1
Sample Output 2:
-1
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace nsA1032A
{
	const int MAXNODE = 100000;
	vector<bool> vVisit;
	vector<char> vData;
	vector<int> vNext;
	
	int main(void)
	{
		vVisit.assign(MAXNODE, false);
		vData.assign(MAXNODE, 0);
		vNext.assign(MAXNODE, 0);

		int n1, n2, n, addr;
		cin >> n1 >> n2 >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> addr;
			cin >> vData[addr] >> vNext[addr];
		}

		addr = n1;
		while (addr != -1)
		{
			vVisit[addr] = true;
			addr = vNext[addr];
		}
		addr = n2;
		while (addr != -1)
		{
			if (vVisit[addr])
			{
				printf("%05d\n", addr);
				return 0;
			}
			addr = vNext[addr];
		}
		cout << "-1" << endl;

		return 0;
	}
}

// rename this to main int PAT
int A1032Func(void)
{
	nsA1032A::main();
	return 0;
}


void A1032(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1032Func();
	cout << endl;
}

void A1032(void)
{
	A1032("data\\A1032-1.txt"); // 
	A1032("data\\A1032-2.txt"); // 
}

