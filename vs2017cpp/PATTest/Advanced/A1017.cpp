/*
1017. Queueing at Bank (25)
cost: 

test: 
	1. arrive time >= "17:00:01"
	2. proc minute > 60

sln1: 直接处理
	注意：求等待时间，而非处理时间。
	23/25 pt5:错误

Suppose a bank has K windows open for service. There is a 
yellow line in front of the windows which divides the waiting 
area into two parts. All the customers have to wait in line
behind the yellow line, until it is his/her turn to be served 
and there is a window available. It is assumed that no window 
can be occupied by a single customer for more than 1 hour.

Now given the arriving time T and the processing time P of each
customer, you are supposed to tell the average waiting time of 
all the customers.

Input Specification:

Each input file contains one test case. For each case, the first 
line contains 2 numbers: N (<=10000) - the total number of customers,
and K (<=100) - the number of windows. Then N lines follow, each
contains 2 times: HH:MM:SS - the arriving time, and P - the processing 
time in minutes of a customer. Here HH is in the range [00, 23], 
MM and SS are both in [00, 59]. It is assumed that no two customers 
arrives at the same time.

Notice that the bank opens from 08:00 to 17:00. Anyone arrives early 
will have to wait in line till 08:00, and anyone comes too late 
(at or after 17:00:01) will not be served nor counted into the average.

Output Specification:

For each test case, print in one line the average waiting time of 
all the customers, in minutes and accurate up to 1 decimal place.

Sample Input:
7 3
07:55:00 16
17:00:01 2
07:59:59 15
08:01:00 60
08:00:00 30
08:00:02 2
08:03:00 10
Sample Output:
8.2
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int A1017Time2Sec(const string& s)
{
	int h = atoi(s.substr(0, 2).c_str());
	int m = atoi(s.substr(3, 2).c_str());
	int sec = atoi(s.substr(6, 2).c_str());
	return h * 3600 + m * 60 + sec;
}

const int A1017StartSec = 8 * 3600;
const int A1017CloseSec = 17 * 3600 + 1;
const string A1017CloseTime = "17:00:01";

struct A1017User
{
	// arrive sec from 00:0):00
	int arrive = 0;
	// wait time before proc
	int wait = 0;
	// proc time
	int proc = 0;

	A1017User(const string& strtm, int pminu)
	{
		proc = pminu > 60 ? 60 : pminu;
		proc *= 60;
		arrive = A1017Time2Sec(strtm);
		if (arrive < A1017StartSec)
		{
			wait = A1017StartSec - arrive;
		}
		else
		{
			wait = 0;
		}
	}

	bool operator<(const A1017User& u)
	{
		return arrive < u.arrive;
	}
};

struct A1017Wnd
{
	int next = A1017StartSec;
	bool closed = false;
	
	bool Proc(A1017User& u)
	{
		if (next >= u.arrive)
		{
			u.wait = next - u.arrive;
		}
		else
		{
			next = u.arrive;
		}
		next += u.proc;
		if (next >= A1017CloseSec)
		{
			closed = true;
		}
		return closed;
	}
};

int A1017FindNextWnd(vector<A1017Wnd>& vtWnd)
{
	int nextSec = A1017CloseSec;
	int nextWnd = -1;
	int len = (int)vtWnd.size();
	for (int  i = 0; i < len; ++i)
	{
		if (vtWnd[i].next < nextSec)
		{
			nextSec = vtWnd[i].next;
			nextWnd = i;
		}
	}
	return nextWnd;
}

bool A1017UserLess(const A1017User& u1, const A1017User& u2)
{
	return u1.arrive < u2.arrive;
}

// rename this to main int PAT
int A1017Func(void)
{
	int n, k;
	cin >> n >> k;

	vector<A1017User> vtUser;
	for (int i = 0; i < n; ++i)
	{
		string s;
		int p;
		cin >> s >> p;
		if (s >= A1017CloseTime)
		{
			continue;
		}
		vtUser.push_back(A1017User(s, p));
	}

	sort(vtUser.begin(), vtUser.end());

	vector<A1017Wnd> vtWnd(k);
	vector<int> vtt;
	for (int i =0; i < vtUser.size(); ++i)
	{
		auto iw = A1017FindNextWnd(vtWnd);
		if (iw <= -1)
		{
			break;
		}
		auto& user = vtUser[i];
		vtWnd[iw].Proc(user);
		vtt.push_back(user.wait);
	}

	int sec = accumulate(vtt.begin(), vtt.end(), 0);
	float minu = float(sec) / vtt.size() / 60;
	printf("%.1f", minu);

	return 0;
}


void A1017(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1017Func();
	cout << endl;
}

void A1017(void)
{
	A1017("data\\A1017-1.txt"); // 
}

