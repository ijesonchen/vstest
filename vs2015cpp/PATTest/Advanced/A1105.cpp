/*
1105. Spiral Matrix (25)
150 ms

14:20

This time your job is to fill a sequence of N positive integers into a spiral matrix in non-increasing order. 
A spiral matrix is filled in from the first element at the upper-left corner, then move in a clockwise spiral. 
The matrix has m rows and n columns, where m and n satisfy the following: 
m*n must be equal to N; 
m>=n; 
and m-n is the minimum of all the possible values.

Input Specification:

Each input file contains one test case. 
For each case, the first line gives a positive integer N. 
Then the next line contains N positive integers to be filled into the spiral matrix. 
All the numbers are no more than 10^4. The numbers in a line are separated by spaces.

Output Specification:

For each test case, output the resulting matrix in m lines, 
each contains n numbers. There must be exactly 1 space between two adjacent numbers, 
and no extra space at the end of each line.

Sample Input:
12
37 76 20 98 76 42 53 95 60 81 58 93
Sample Output:
98 95 93
42 37 81
53 20 76
58 60 76
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
14:20
1. 确定m n：sqrt（N）开始搜索
2. 输入排序
3. 模拟填充vv：根据方向（dir），边界（当前位置及中止位置）
	确定：下一位置、下一方向。
15:10 pass
*/

namespace nsA1105A
{
	int total, m, n;

	void CalcMN(void)
	{
		int mid = (int)sqrt(total);
		for (int i = mid; i >= 1; --i)
		{
			int t = total / i;
			if (t*i == total)
			{
				m = t;
				n = i;
				break;
			}
		}
	}

	void main(void)
	{
		m = -1, n = -1;
		cin >> total;
		CalcMN();

		int temp;
		vector<int> vData;
		for (int i = 0; i < total; ++i)
		{
			cin >> temp;
			vData.push_back(temp);
		}
		sort(vData.rbegin(), vData.rend());

		vector<vector<int>> vvMatrix(m, vector<int>(n));
		int mi = 0;
		int ni = 0;
		int off1 = 1;
		int off2 = 1;
		int off3 = 0;
		int off4 = 1;
		int dir = 0;
		for (int i = 0; i < total; ++i)
		{
			vvMatrix[mi][ni] = vData[i];
			switch (dir)
			{
			case 0:
			{
				if (ni == n - off1)
				{
					++off1;
					dir = 1;
					++mi;
				}
				else { ++ni; }
				break;
			}
			case 1:
			{
				if (mi == m - off2)
				{
					++off2;
					dir = 2;
					--ni;
				}
				else { ++mi; }
				break;
			}
			case 2:
			{
				if (ni == off3)
				{
					++off3;
					dir = 3;
					--mi;
				}
				else { --ni; }
				break;
			}
			case 3:
			{
				if (mi == off4)
				{
					++off4;
					dir = 0;
					++ni;
				}
				else { --mi; }
				break;
			}
			}
		}
		for (int i = 0; i < m; ++i)
		{
			vector<int>& v = vvMatrix[i];
			cout << v.front();
			for (size_t j = 1; j < v.size(); ++j)
			{
				cout << " " << v[j];
			}
			cout << endl;
		}
	}
}

// rename this to main int PAT
int A1105Func(void)
{
	nsA1105A::main();
	return 0;
}


void A1105(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1105Func();
	cout << endl;
}

void A1105(void)
{
	A1105("data\\A1105-1.txt"); // 
}

