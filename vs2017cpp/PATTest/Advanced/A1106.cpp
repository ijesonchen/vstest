/*
1106. Lowest Price in Supply Chain (25)
200 ms

15：10

A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- 
everyone involved in moving a product from supplier to customer.

Starting from one root supplier, everyone on the chain buys products from one's supplier in a price P and 
sell or distribute them in a price that is r% higher than P. 
Only the retailers will face the customers. 
It is assumed that each member in the supply chain has exactly one supplier except the root supplier, 
and there is no supply cycle.

Now given a supply chain, you are supposed to tell the lowest price a customer can expect from some retailers.

Input Specification:

Each input file contains one test case. For each case, 
The first line contains three positive numbers: N (<=10^5), the total number of the members in the supply chain 
(and hence their ID's are numbered from 0 to N-1, and the root supplier's ID is 0); 
P, the price given by the root supplier; 
and r, the percentage rate of price increment for each distributor or retailer. 
Then N lines follow, each describes a distributor or retailer in the following format:

Ki ID[1] ID[2] ... ID[Ki]

where in the i-th line, 
Ki is the total number of distributors or retailers who receive products from supplier i, 
and is then followed by the ID's of these distributors or retailers. 
Kj being 0 means that the j-th member is a retailer.
All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in one line the lowest price we can expect from some retailers, 
accurate up to 4 decimal places, 
and the number of retailers that sell at the lowest price. 
There must be one space between the two numbers. 
It is guaranteed that the all the prices will not exceed 10^10.

Sample Input:
10 1.80 1.00
3 2 3 5
1 9
1 4
1 7
0
2 6 1
1 8
0
0
0
Sample Output:
1.8362 2
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
15:10 销售网络。最短路径。搜索所有最短路径。
15:40 17/25 pt3,5,7 WA pt6 MLE

不记录结果路径，仅记录数量
15:45 17/25 pt3,5,6,7 wa

改float为double
15:50 pass
*/

namespace nsA1106A
{
	vector<vector<int>> vvData;
	vector<bool> vRetailer;

	int cntPath = 0;
	int nPath = 0x7fffffff;
	vector<int> vTemp;
	vector<bool> vVisit;

	void Dfs(int u, int dist)
	{
		if (dist > nPath) { return; }
		if (vRetailer[u])
		{
			if (dist < nPath)
			{
				nPath = dist;
				cntPath = 1;
			}
			else if (dist == nPath)
			{
				++cntPath;
			}
			return;
		}
		vector<int>& uAdj = vvData[u];
		for (auto v : uAdj)
		{
			if (!vVisit[v])
			{
				vVisit[v] = true;
				vTemp.push_back(v);
				Dfs(v, dist + 1);
				vVisit[v] = false;
				vTemp.pop_back();
			}
		}
	}

	void main(void)
	{

		int n, k;
		double p, r;
		cin >> n >> p >> r;
		r = 1 + r / 100;

		vvData.assign(n, vector<int>());
		vRetailer.assign(n, false);
		for (int i = 0; i < n; ++i)
		{
			cin >> k;
			if (!k)
			{
				vRetailer[i] = true;
				continue;
			}
			vector<int>& v = vvData[i];
			v.assign(k, 0);
			for (int j = 0; j < k; ++j)
			{
				cin >> v[j];
			}
		}

		cntPath = 0;
		nPath = 0x7fffffff;
		vTemp.clear();
		vVisit.assign(n, false);
		vVisit[0] = true;
		Dfs(0, 0);

		for (int i = 0; i < nPath; ++i)
		{
			p *= r;
		}
		printf("%.4f %d\n", p, cntPath);
	}
}

// rename this to main int PAT
int A1106Func(void)
{
	nsA1106A::main();
	return 0;
}


void A1106(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1106Func();
	cout << endl;
}

void A1106(void)
{
	A1106("data\\A1106-1.txt"); // 
}

