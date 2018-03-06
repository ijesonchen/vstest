/*
1107. Social Clusters (30)
1000 ms

15：50

When register on a social network, you are always asked to specify your hobbies in order to 
find some potential friends with the same hobbies.
A "social cluster" is a set of people who have some of their hobbies in common. 
You are supposed to find all the clusters.

Input Specification:

Each input file contains one test case. For each test case, 
the first line contains a positive integer N (<=1000), the total number of people in a social network. 
Hence the people are numbered from 1 to N. 
Then N lines follow, each gives the hobby list of a person in the format:

Ki: hi[1] hi[2] ... hi[Ki]

where Ki (>0) is the number of hobbies, and hi[j] is the index of the j-th hobby, which is an integer in [1, 1000].

Output Specification:

For each case, print in one line the total number of clusters in the network.
Then in the second line, print the numbers of people in the clusters in non-increasing order. 
The numbers must be separated by exactly one space, and there must be no extra space at the end of the line.

Sample Input:
8
3: 2 7 10
1: 4
2: 5 3
1: 4
1: 3
1: 4
4: 6 8 1 5
1: 4
Sample Output:
3
4 3 1

*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
15：50
N: [1,1000] people, 1-based
k > 0
h: [1,1000]
输出:
total cluster
people in clusters, non-increasing order
dfs，连通分量, union-find
？转换hobby -> connection
	1. 双色图？
	2. 二次重建？
	3. 改进搜索：邻接map
采用3进行搜索。首个访问节点作为clusterid，使用map记录数量

16:20 20/30 PT1,4,5 WA
*/

namespace nsA1107A
{
	const int MAXHOBBY = 1001;
	// people's hobby
	vector<vector<int>> vvPeople2Hobby;
	// vvHobby2People[i]: all people with hobby i
	vector<vector<int>> vvHobby2People;
	vector<bool> vVisit;

	// cluster count
	unordered_map<int, int> mapClusterCount;


	void main()
	{
		int n, k, h;
		cin >> n;
		string s;
		vvPeople2Hobby.assign(n + 1, vector<int>());
		vvHobby2People.assign(MAXHOBBY, vector<int>());
		vVisit.assign(n + 1, false);
		vVisit[0] = true;
		mapClusterCount.clear();
		for (int i = 0; i < n; ++i)
		{
			cin >> k;
			cin >> s;
			for (int j = 0; j < k; ++j)
			{
				cin >> h;
				vvPeople2Hobby[i+1].push_back(h);
				vvHobby2People[h].push_back(i + 1);
			}
		}

		// dfs
		for (int i = 1; i <= n; ++i)
		{
			if (!vVisit[i])
			{
				int iCluster = i;
				++mapClusterCount[iCluster];
				vVisit[i] = true;
				vector<int>& vHobby = vvPeople2Hobby[i];
				for (auto hob : vHobby)
				{
					vector<int>& vPeople = vvHobby2People[hob];
					for (auto p : vPeople)
					{
						if (!vVisit[p])
						{
							vVisit[p] = true;
							++mapClusterCount[iCluster];
						}
					}
				}
			}
		}
		cout << mapClusterCount.size() << endl;
		vector<int> vCluster;
		for (auto c : mapClusterCount)
		{
			vCluster.push_back(c.second);
		}
		sort(vCluster.rbegin(), vCluster.rend());
		cout << vCluster.front();
		for (size_t i = 1; i < vCluster.size(); ++i)
		{
			cout << " " << vCluster[i];
		}
		cout << endl;
	}
}

// rename this to main int PAT
int A1107Func(void)
{
	nsA1107A::main();
	return 0;
}


void A1107(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1107Func();
	cout << endl;
}

void A1107(void)
{
	A1107("data\\A1107-1.txt"); // 
}

