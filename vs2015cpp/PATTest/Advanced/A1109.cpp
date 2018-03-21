/*
1109. Group Photo (25)

Formation is very important when taking a group photo. 
Given the rules of forming K rows with N people as the following:

The number of people in each row must be N/K (round down to the nearest integer), 
with all the extra people (if any) standing in the last row;

All the people in the rear row must be no shorter than anyone standing in the front rows;

In each row, the tallest one stands at the central position 
(which is defined to be the position (m/2+1), 
where m is the total number of people in that row, 
and the division result must be rounded down to the nearest integer);

In each row, other people must enter the row in non-increasing order of their heights, 
alternately taking their positions first to the right and then to the left of the tallest one 
(For example, given five people with their heights 190, 188, 186, 175, and 170, 
the final formation would be 175, 188, 190, 186, and 170. 
Here we assume that you are facing the group 
so your left-hand side is the right-hand side of the one at the central position.);

When there are many people having the same height, 
they must be ordered in alphabetical (increasing) order of their names, 
and it is guaranteed that there is no duplication of names.

Now given the information of a group of people, you are supposed to write a program to output their formation.

Input Specification:

Each input file contains one test case. 
For each test case, the first line contains two positive integers N (<=10000), 
the total number of people, and K (<=10), the total number of rows. 
Then N lines follow, each gives the name of a person (no more than 8 English letters without space) and 
his/her height (an integer in [30, 300]).

Output Specification:

For each case, print the formation -- that is, print the names of people in K lines.
The names must be separated by exactly one space,
but there must be no extra space at the end of each line. 
Note: since you are facing the group, people in the rear rows must be printed above the people in the front rows.

Sample Input:
10 3
Tom 188
Mike 170
Eva 168
Tim 160
Joe 190
Ann 168
Bob 175
Nick 186
Amy 160
John 159

Sample Output:
Bob Tom Joe Nick
Ann Mike Eva
Tim Amy John
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
14:45 
1. n/k行，多的放最后一行
2. 后排都比前排高
3. 每行中间（m/2+1)最高，
4. 从高到低，中间->两边，先小号后大号(5人：32415)
5. 从最后一排开始打印
6. 同身高先名字
15:25 40min pass
*/

namespace nsA1109A
{
	struct People
	{
		string name;
		int height = 0;

		People() {};
		People(string n, int h) : name(n), height(h) {};

	};

	// p1 > p2
	bool Cmp1(const People& p1, const People& p2)
	{
		return p1.height != p2.height ? p1.height > p2.height : p1.name < p2.name;
	}

	void FillRow(vector<People>& vRow, const vector<People>& vPeople, int start, int cnt)
	{
		vRow.assign(cnt, People());
		int mid = cnt / 2;
		// right 
		for (int i = 0, j = mid; i < cnt; i+=2, ++j)
		{
			vRow[j] = vPeople[start + i];
		}
		for (int i = 1, j = mid - 1; i < cnt; i+=2, --j)
		{
			vRow[j] = vPeople[start + i];
		}
	}

	void PrintRow(const vector<People>& vRow)
	{
		cout << vRow.front().name;
		for (size_t i = 1; i < vRow.size(); ++i)
		{
			cout << " " << vRow[i].name;
		}
		cout << endl;
	}

	void main(void)
	{
		int n, k;
		vector<People> vPeople;
		cin >> n >> k;
		for (int i = 0; i < n; ++i)
		{
			People p;
			cin >> p.name >> p.height;
			vPeople.push_back(p);
		}
		int perRow = n / k;
		int firstRow = n - k * perRow + perRow;
		vector<vector<People>> vvRows(k);
		sort(vPeople.begin(), vPeople.end(), Cmp1);
		int start = 0;
		for (int i = 0; i < k; ++i)
		{
			int cnt = i ? perRow : firstRow;
			FillRow(vvRows[i], vPeople, start, cnt);
			start += cnt;
		}
		for (int i = 0; i < k; ++i)
		{
			PrintRow(vvRows[i]);
		}
	}
}

// rename this to main int PAT
int A1109Func(void)
{
	nsA1109A::main();
	return 0;
}


void A1109(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1109Func();
	cout << endl;
}

void A1109(void)
{
	A1109("data\\A1109-1.txt"); // 
}

