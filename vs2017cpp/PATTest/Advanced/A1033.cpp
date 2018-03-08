/*
1033. To Fill or Not to Fill (25)
100 ms
65536 kB

9:50


With highways available, driving a car from Hangzhou to any other city is easy. 
But since the tank capacity of a car is limited, we have to find gas stations on the way from time to time. 
Different gas station may give different price. You are asked to carefully design the cheapest route to go.

Input Specification:

Each input file contains one test case.
For each case, the first line contains 4 positive numbers: 
Cmax (<= 100), the maximum capacity of the tank; 
D (<=30000), the distance between Hangzhou and the destination city; 
Davg (<=20), the average distance per unit gas that the car can run; and 
N (<= 500), the total number of gas stations. 

Then N lines follow, each contains a pair of non-negative numbers:
Pi, the unit gas price, and Di (<=D), the distance between this station and Hangzhou, 
for i=1,...N. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print the cheapest price in a line, accurate up to 2 decimal places. 
It is assumed that the tank is empty at the beginning.
If it is impossible to reach the destination, print "The maximum travel distance = X" 
where X is the maximum possible distance the car can run, accurate up to 2 decimal places.

Sample Input 1:
50 1300 12 8
6.00 1250
7.00 600
7.00 150
7.10 0
7.20 200
7.50 400
7.30 1000
6.85 300
Sample Output 1:
749.17
Sample Input 2:
50 1300 12 2
7.10 0
7.00 600
Sample Output 2:
The maximum travel distance = 1200.00
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
9:50
起始油量为空
正数：cmax油箱容量100] D 目标距离30000] Davg单位油距离20] N油站数量500]
非负：pi油价 di起点距离

.2f 最低价格，或无法到达时最大距离

动态规划？递归
最多加油30000/20=1500
最加50次油
每次加油最多distTank=cmax*davg，要小于各油站间距：无法到达时的处理
每次价格p[i]，剩余油量gleft[i]，加油量gadd[i]，可用续航dgas[i]，总价total[i]

贪心：
增加目的加油站，油价为0
当前开始（含），
当前油箱覆盖的站点
最大油箱距离能覆盖的油站
11：00 放弃

*/

namespace nsA1033A
{
	struct Station 
	{
		float dist = 0;
		float p = 0;

		bool operator<(const Station& s)
		{ return dist != s.dist ? dist < s.dist : p < s.p; }
	};



	void main(void)
	{
		int n;
		float cMax, dist, davg;
		scanf("%f %f %f %d", &cMax, &dist, &davg, &n);
		vector<Station> vStation;
		for (int i = 0; i < n; ++i)
		{
			vStation.emplace_back();
			scanf("%f %f", &vStation.back().p, &vStation.back().dist);
		}
		vStation.emplace_back();
		vStation.back().p = 0; vStation.back().dist = dist;
		sort(vStation.begin(), vStation.end());
		if (vStation.front().dist != 0)
		{
			printf("The maximum travel distance = 0.00\n");
			return;
		}
		bool bImpossible = false;

		float pTotal = 0;
		float gLeft = 0;
		Station* pPrev = &vStation.front();
		float gPrice = pPrev->p;
		for (size_t i = 1; i < vStation.size(); ++i)
		{
			Station& next = vStation[i];
			if (next.dist >= dist)
			{
				break;
			}
			float gCost = (next.dist - pPrev->dist) / davg;
			if (gCost > cMax)
			{
				bImpossible = true;
				break;
			}
			float gNeed;
			if (pPrev->p < next.p) {  gNeed = cMax; } // fufill
			else { gNeed =  gCost; }
			pTotal = gPrice * (gNeed - gLeft);
			gPrice = next.p;
			gLeft = gNeed - gCost;
			pPrev = &next;
		}
		if (bImpossible)
		{
			float totolDist = pPrev->dist + gLeft * davg;
			printf("The maximum travel distance = %.2f\n", totolDist);
		}
		else
		{
			printf("%.2f\n", pTotal);
		}
	}
}


/*
14：30
贪心：
站点按价格排序，每次取最小的加满
选取下一最小站点i：价格pi，油量gLeft，最大加油量
未加油位置链表表示
15:30 放弃
*/
namespace nsA1133B
{
	struct Station 
	{
		float d;
		float p;

		bool operator<(const Station& a) 
		{ return p != a.p ? p < a.p : d < a.d; }
	};

	struct Dist
	{
		float start = 0;
		float end = 0;
		bool filled = false;
		Dist* next = nullptr;

		Dist(float s, float e, bool f) : start(s), end(e), filled(f) {};

		bool Include(int d) 
			{ return start <= d && d >= end; }
		float MaxDist(void) const { return end - start; }
	};

	Dist* FindPos(Dist* pRoot, int d)
	{
		while (!pRoot->Include(d))
		{
			pRoot = pRoot->next;
		}
	}

	void main(void)
	{
		float tankCap, dstDist, distPerGas;
		int nStation;
		scanf("%f %f %f %d\n", &tankCap, &dstDist, &distPerGas, &nStation);
		float maxFullTankDist = tankCap * distPerGas;
		vector<Station> vStation;
		bool bImpossible = true;
		for (int i = 0; i < nStation; ++i)
		{
			vStation.emplace_back();
			scanf("%f %f\n", &vStation.back().p, &vStation.back().d);
			if (vStation.back().d == 0)
			{
				bImpossible = false;
			}
		}
		vStation.emplace_back();
		sort(vStation.begin(), vStation.end());
		
		// memory leakage
		Dist* pRoot = new Dist(0, dstDist, false);
		float totalPrice = 0;
		for (int i = 0; i < nStation; ++i)
		{
			auto& station = vStation[i];
			if (station.d >= dstDist) { continue; }
			Dist* pCurrent = FindPos(pRoot, station.d);
			// 决定最大加油量，处理链表
			if (pCurrent->filled)
			{
				if (!pCurrent->next) { continue; }
				Dist* pNext = pCurrent->next;
				float maxDist = pNext->MaxDist();
				if (maxDist == maxFullTankDist)
				{ 
				}
			}
		}
	}
}

// rename this to main int PAT
int A1033Func(void)
{
	nsA1033A::main();
	return 0;
}


void A1033(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1033Func();
	cout << endl;
}

void A1033(void)
{
	A1033("data\\A1033-1.txt"); // 
	A1033("data\\A1033-2.txt"); // 
}

