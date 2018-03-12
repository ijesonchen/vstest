/*
1095. Cars on Campus (30)
220 ms
65536 kB

Zhejiang University has 6 campuses and a lot of gates. 
From each gate we can collect the in/out times and the plate numbers of the cars crossing the gate. 
Now with all the information available, you are supposed to tell, at any specific time point,
the number of cars parking on campus, and at the end of the day find the cars that have parked for the longest time period.

Input Specification:

Each input file contains one test case.
Each case starts with two positive integers N (<= 10000), the number of records,
and K (<= 80000) the number of queries. 
Then N lines follow, each gives a record in the format

plate_number hh:mm:ss status

where plate_number is a string of 7 English capital letters or 1-digit numbers; 
hh:mm:ss represents the time point in a day by hour:minute:second, 
with the earliest time being 00:00:00 and the latest 23:59:59; 
and status is either in or out.

Note that all times will be within a single day. 
Each "in" record is paired with the chronologically next record for the same car provided it is an "out" record.
Any "in" records that are not paired with an "out" record are ignored, as are "out" records not paired with an "in" record. 
It is guaranteed that at least one car is well paired in the input, 
and no car is both "in" and "out" at the same moment. 
Times are recorded using a 24-hour clock.

Then K lines of queries follow, each gives a time point in the format hh:mm:ss. 
Note: the queries are given in ascending order of the times.

Output Specification:

For each query, output in a line the total number of cars parking on campus. 
The last line of output is supposed to give the plate number of the car 
that has parked for the longest time period, and the corresponding time length. 
If such a car is not unique, then output all of their plate numbers in a line 
in alphabetical order, separated by a space.

Sample Input:
16 7
JH007BD 18:00:01 in
ZD00001 11:30:08 out
DB8888A 13:00:00 out
ZA3Q625 23:59:50 out
ZA133CH 10:23:00 in
ZD00001 04:09:59 in
JH007BD 05:09:59 in
ZA3Q625 11:42:01 out
JH007BD 05:10:33 in
ZA3Q625 06:30:50 in
JH007BD 12:23:42 out
ZA3Q625 23:55:00 in
JH007BD 12:24:23 out
ZA133CH 17:11:22 out
JH007BD 18:07:01 out
DB8888A 06:30:50 in
05:10:00
06:30:50
11:00:00
12:23:42
14:00:00
18:00:00
23:59:00
Sample Output:
1
4
5
2
1
0
1
JH007BD ZD00001 07:20:09
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
16：50
匹配in/out
in/out不匹配丢弃

任意时刻车辆数
停放时长最长的车号及时间

1. 
	// 发生进出的时间
	vector<int> vTime
	vector<int> vbTime
	// 每一时刻进出车辆
	vector<int> vIn
	vector<int> vOut

	vector<string> vLongest
	int nLongest
	预处理数据：
		车辆，进出时间，排序，
			匹配: vTime vbTime
			计算停车时长 -> 最长停车时间
	
	vTime排序
	计算到time为止的车辆数

17:50 0/0

bug-fix-1 时间点转时间串
18:00 pass
*/

namespace nsA1095A
{
	const int MAXTIMEPOINT = 24 * 3600;

	int n, k;
	// 发生进出的时间点
	vector<int> vTime;
	vector<bool> vbTime(MAXTIMEPOINT);
	// 每刻进出车辆
	vector<int> vInOut(MAXTIMEPOINT);

	vector<string> vLongest;
	int nLongest = 0;

	int TimePoint(char* p)
	{
		p[2] = 0;
		p[5] = 0;
		int h = atoi(p);
		int m = atoi(p + 3);
		int s = atoi(p + 6);
		return h * 3600 + m * 60 + s;
	}

	char* TimeStr(int n)
	{
		static char p[9];
		int s = n % 60;
		// bug-fix-1 m = n / 3600 % 60;
		int m = n / 60 % 60;
		int h = n / 3600;
		sprintf(p, "%02d:%02d:%02d", h, m, s);
		return p;
	}

	struct Event
	{
		int tp = 0;
		bool bin = false;
		string s;

		Event() {};

		Event(char* ptp, char* ptag)
		{
			s = ptp;
			tp = TimePoint(ptp);
			if (ptag[0] == 'i')
			{
				bin = true;
			}
			else
			{
				bin = false;
			}
		}

		bool operator<(const Event& a)
		{
			return tp < a.tp;
		}
	};

	unordered_map<string, vector<Event>> mapNameEvent;
	unordered_map<string, int> mapNameTime;

	void main(void)
	{
		scanf("%d %d", &n, &k);
		char name[8];
		char tp[9];
		char tag[4];
		for (int i = 0; i < n; ++i)
		{
			scanf("%s %s %s", name, tp, tag);
			mapNameEvent[name].emplace_back(tp, tag);
		}

		for (auto& p : mapNameEvent)
		{
			auto& v = p.second;
			sort(v.begin(), v.end());
			Event last;
			for (size_t i = 0; i < v.size() - 1; ++i)
			{
				if (v[i].bin && !v[i+1].bin)
				{
					mapNameTime[p.first] += v[i + 1].tp - v[i].tp;
					if (!vbTime[v[i].tp]) {
						vbTime[v[i].tp] = true; 
						vTime.push_back(v[i].tp);
					}
					if (!vbTime[v[i+1].tp]) { 
						vbTime[v[i + 1].tp] = true;
						vTime.push_back(v[i + 1].tp);
					}
					++vInOut[v[i].tp];
					--vInOut[v[i+1].tp];
					++i;
				}
			}
			int nTime = mapNameTime[p.first];
			if (nTime > nLongest)
			{
				nLongest = nTime;
				vLongest.clear();
				vLongest.push_back(p.first);
			}
			else if (nTime == nLongest)
			{
				vLongest.push_back(p.first);
			}
		}

		sort(vTime.begin(), vTime.end());
		int j = 0;
		int cars = 0;
		for (int i = 0; i < k; ++i)
		{
			scanf("%s", &tp);
			int nTimepoint = TimePoint(tp);
			for (; j < vTime.size(); ++j)
			{
				if (vTime[j] > nTimepoint)
				{
					break;
				}
				cars += vInOut[vTime[j]];
			}
			printf("%d\n", cars);
		}
		sort(vLongest.begin(), vLongest.end());
		printf("%s", vLongest.front().c_str());
		for (size_t i = 1; i < vLongest.size(); ++i)
		{
			printf(" %s", vLongest[i].c_str());
		}
		printf(" %s", TimeStr(nLongest));
	}
}

// rename this to main int PAT
int A1095Func(void)
{
	nsA1095A::main();
	return 0;
}


void A1095(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1095Func();
	cout << endl;
}

void A1095(void)
{
	A1095("data\\A1095-1.txt"); // 
}

