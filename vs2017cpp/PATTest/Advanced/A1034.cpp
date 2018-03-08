/*
1034. Head of a Gang (30)
100 ms
65536 kB

One way that the police finds the head of a gang is to check people's phone calls. 
If there is a phone call between A and B, we say that A and B is related. 
The weight of a relation is defined to be the total time length of all the phone calls made between the two persons. 
A "Gang" is a cluster of more than 2 persons 
who are related to each other with total relation weight being greater than a given threshold K. 
In each gang, the one with maximum total weight is the head. 
Now given a list of phone calls, you are supposed to find the gangs and the heads.

Input Specification:

Each input file contains one test case. For each case, 
the first line contains two positive numbers N and K (both less than or equal to 1000), 
the number of phone calls and the weight threshold, respectively. 
Then N lines follow, each in the following format:

Name1 Name2 Time

where Name1 and Name2 are the names of people at the two ends of the call, 
and Time is the length of the call. 
A name is a string of three capital letters chosen from A-Z. 
A time length is a positive integer which is no more than 1000 minutes.

Output Specification:

For each test case, first print in a line the total number of gangs. 
Then for each gang, print in a line the name of the head and the total number of the members. 
It is guaranteed that the head is unique for each gang. 
The output must be sorted according to the alphabetical order of the names of the heads.

Sample Input 1:
8 59
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
Sample Output 1:
2
AAA 3
GGG 3
Sample Input 2:
8 70
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
Sample Output 2:
0
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <deque>
#include <algorithm>


using namespace std;

/*
11£º05
12:10: 28/30 PT3 ¶Î´íÎó
*/

namespace nsA1034A
{
//	const int MAXNAME = 26 * 26 * 26; // 20K
	int Name2ID(const char* p)
	{
		return (p[0] - 'A')* 26*26+(p[1] - 'A')*26+(p[2] - 'A');
	}

	char* ID2Name(int n)
	{
		static char name[4];
		name[0] = n / (26 * 26) + 'A';
		name[1] = n / 26 % 26 + 'A';
		name[2] = n % (26) + 'A';
		name[3] = 0;
		return name;
	}

	struct Result
	{
		int name = 0;
		int size = 0;

		bool operator < (const Result& a)
		{
			return name < a.name;
		}
	};



	void main(void)
	{
		int n, k, t;
		char name1[4], name2[4];
		scanf("%d %d", &n, &k);
		k *= 2;
		vector<int> vWeight(1);
		vector<int> vName(1);
		vector<vector<int>> vvAdj(n+2); // max n+2 people
		unordered_map<int, int> mapNameIndex;
		for (int i = 0; i < n; ++i)
		{
			scanf("%s %s %d", name1, name2, &t);
			int id1 = Name2ID(name1);
			int id2 = Name2ID(name2);
			int& idx1 = mapNameIndex[id1];
			if (!idx1)
			{
				idx1 = (int)vWeight.size();
				vWeight.push_back(0);
				vName.push_back(id1);
			}
			int& idx2 = mapNameIndex[id2];
			if (!idx2)
			{
				idx2 = (int)vWeight.size();
				vWeight.push_back(0);
				vName.push_back(id2);
			}
			vWeight[idx1] += t;
			vWeight[idx2] += t;
			vvAdj[idx1].push_back(idx2);
			vvAdj[idx2].push_back(idx1);
		}
		vector<Result> vResult;
		vector<bool> vVisit(vWeight.size());
		vVisit[0] = true;
		for (size_t i = 0; i < vVisit.size(); ++i)
		{
			if (vVisit[i])
			{
				continue;
			}
			vVisit[i] = true;
			int idMax = (int)i;
			int totalWeight = vWeight[idMax];
			int maxWeight = vWeight[idMax];
			int nMember = 1;
			deque<int> dqNodes;
			dqNodes.push_back(idMax);
			while (!dqNodes.empty())
			{
				int u = dqNodes.front();
				dqNodes.pop_front();
				vector<int>& uAdj = vvAdj[u];
				for (auto v : uAdj)
				{
					if (vVisit[v])
					{
						continue;
					}
					++nMember;
					vVisit[v] = true;
					dqNodes.push_back(v);
					totalWeight += vWeight[v];
					if (vWeight[v] > maxWeight)
					{
						idMax = v;
						maxWeight = vWeight[idMax];
					}
				}
			}
			if ((totalWeight > k) && (nMember > 2))
			{
				vResult.emplace_back();
				vResult.back().name = vName[idMax];
				vResult.back().size = nMember;
			}			
		}
		sort(vResult.begin(), vResult.end());
		printf("%d\n", (int)vResult.size());
		for (auto& res : vResult)
		{
			printf("%s %d\n", ID2Name(res.name), res.size);
		}
		return;
	}
}

// rename this to main int PAT
int A1034Func(void)
{
	nsA1034A::main();
	return 0;
}


void A1034(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1034Func();
	cout << endl;
}

void A1034(void)
{
//	A1034("data\\A1034-1.txt"); // 
	A1034("data\\A1034-2.txt"); // 
}

