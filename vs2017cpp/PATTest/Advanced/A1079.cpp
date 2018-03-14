/*
1079. Total Sales of Supply Chain (25)
250 ms
65536 kB

A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- 
everyone involved in moving a product from supplier to customer.

Starting from one root supplier, everyone on the chain buys products from one's supplier in a price P 
and sell or distribute them in a price that is r% higher than P. 
Only the retailers will face the customers. 
It is assumed that each member in the supply chain has exactly one supplier except the root supplier,
and there is no supply cycle.

Now given a supply chain, you are supposed to tell the total sales from all the retailers.

Input Specification:

Each input file contains one test case. For each case, the first line contains three positive numbers:
N (<=10^5), the total number of the members in the supply chain 
(and hence their ID's are numbered from 0 to N-1, and the root supplier's ID is 0); 
P, the unit price given by the root supplier; and 
r, the percentage rate of price increment for each distributor or retailer. 
Then N lines follow, each describes a distributor or retailer in the following format:

Ki ID[1] ID[2] ... ID[Ki]

where in the i-th line, Ki is the total number of distributors or retailers who receive products from supplier i, 
and is then followed by the ID's of these distributors or retailers.
Kj being 0 means that the j-th member is a retailer, then instead 
the total amount of the product will be given after Kj. 
All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in one line the total sales we can expect from all the retailers, accurate up to 1 decimal place. 
It is guaranteed that the number will not exceed 10^10.

Sample Input:
10 1.80 1.00
3 2 3 5
1 9
1 4
1 7
0 7
2 6 1
1 8
0 9
0 4
0 3
Sample Output:
42.4
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

/*
19:50
销售网络
确定终端价格，数量，求和。最大10^10 int64_t
20：30 16/25 wa2,3,5,6

数据量较大时WA
改float为double
20:30 pass
*/

namespace nsA1079A
{
	int nTotal;
	double fPrice;
	double fRate;

	// 邻接表表示
	vector<vector<int>> vvAdjs;
	// 零售商的id
	vector<int> vRetailID;
	// 预置数组，id对应数量
	vector<int64_t> vRetailProduct;
	// 预置数组，id对应级别
	vector<int> vLevel;

	// level price
	vector<double> vPrice;
	int nPrice;

	double GetPrice(int n)
	{
		if (vPrice[n] != 0)
		{
			return vPrice[n];
		}
		for (int i = nPrice; i <= n; ++i)
		{
			if (vPrice[n] == 0)
			{
				vPrice[i] = vPrice[i - 1] * (1 + fRate);
			}
		}
		return vPrice[n];
	}

	void main(void)
	{
		cin >> nTotal >> fPrice >> fRate;
		fRate /= 100;
		vRetailID.clear();
		vRetailProduct.resize(nTotal);
		vLevel.resize(nTotal);
		vPrice.resize(nTotal);
		vPrice[0] = fPrice;
		nPrice = 1;
		vvAdjs.assign(nTotal, vector<int>());
		for (int i = 0; i < nTotal; ++i)
		{
			int n, k;
			cin >> n;
			if (!n)
			{
				// retail
				vRetailID.push_back(i);
				cin >> vRetailProduct[i];
			}
			else
			{
				vector<int>& vAdj = vvAdjs[i];
				for (int j = 0; j < n; ++j)
				{
					cin >> k;
					vAdj.push_back(k);
				}
			}
		}

		// bfs
		deque<int> dqNode; 
		vLevel[0] = 0;
		dqNode.push_back(0);
		while (!dqNode.empty())
		{
			int u = dqNode.front();
			dqNode.pop_front();
			int level = vLevel[u];
			auto& vAdj = vvAdjs[u];
			for (auto v : vAdj)
			{
				vLevel[v] = level + 1;
				if (!vvAdjs[v].empty())
				{
					dqNode.push_back(v);
				}
			}
		}
		double sum = 0;
		for (auto v : vRetailID)
		{
			double price = GetPrice(vLevel[v]);
			sum += price * vRetailProduct[v];
		}
		printf("%.1lf", sum);
	}
}

// rename this to main int PAT
int A1079Func(void)
{
	nsA1079A::main();
	return 0;
}


void A1079(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1079Func();
	cout << endl;
}

void A1079(void)
{
	A1079("data\\A1079-1.txt"); // 
}

