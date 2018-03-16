void TestKnapsack(void);


/*
0-1背包 动态规划
问题: n个物品，价值vi,重量wi，背包大小W。
要求：背包中所装物品的总价值V最大
即求子集S，使sigma(wi) <= W 时，sigma(vi)最大

思路：已知S是最优解，考虑最后一个元素n
1）不选n，则s    是前n-1 背包W    价值V    下最优解
2）选取n，则s-{n}是前n-1 背包W-wi 价值V-vi 下最优解

最优子结构
令A[i,x]表示 前i个元素，背包x下的价值
则A[i,x] = max{ A[i-1, x],    // 包含n
		   vi + A[i-1, x-wi]} // 不包含n 
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace nsKnapsack01 
{
	vector<int> vValue = { 3,2,4,4 };
	vector<int> vWeight = { 4,3,2,3 };
	int nSackVolume = 6;
	int nItem = (int)vValue.size();
	vector<vector<int>> vvValue(nItem + 1, vector<int>(nSackVolume + 1));

	int Value(int nFirst, int nTotal, int nItemValue)
	{
		if (nFirst < 0) { throw 0; };
		if (nTotal < 0) { return 0; };
		return vvValue[nFirst][nTotal] + nItemValue;
	}

	void PrintVV(void)
	{
		int n1 = (int)vvValue.size();
		int n2 = (int)vvValue.front().size();
		for (int j = 0; j < n2; ++j)
		{
			for (int i = 0; i < n1; ++i)
			{
				cout << vvValue[i][n2 - j - 1] << " ";
			}
			cout << endl;
		}
	}

	void main(void)
	{
		// a[i,x] = max{ a[i-1,x], vi + a[i-1, x-wi] }
		// i: [0, nItem], x: [0, nSackVolume]
		// vvValue[0][.] = 0;
		for (int i = 1; i <= nItem; ++i)
		{
			for (int j = 0; j <= nSackVolume; ++j)
			{
				int v1 = Value(i - 1, j, 0);
				int v2 = Value(i - 1, j - vWeight[i - 1], vValue[i - 1]);
				vvValue[i][j] = std::max(v1, v2);
			}
		}
		PrintVV();
	}
}


void TestKnapsack(void)
{
	nsKnapsack01::main();
}