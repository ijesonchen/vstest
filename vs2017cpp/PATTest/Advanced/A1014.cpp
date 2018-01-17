/*
1014. Waiting in Line (30)

cost: 15:50 90min 19/30

sln1: 
	1. 新建customer对象，记录开始时间，处理时间，结束时间
	2. 新建N个窗口对象，每次找最小的，加入队列
	pt2,4,5 错误

Suppose a bank has N windows open for service. There is a yellow 
line in front of the windows which divides the waiting area into 
two parts. The rules for the customers to wait in line are:

The space inside the yellow line in front of each window is enough 
to contain a line with M customers. Hence when all the N lines are 
full, all the customers after (and including) the (NM+1)st one will
have to wait in a line behind the yellow line.
Each customer will choose the shortest line to wait in when crossing
the yellow line. If there are two or more lines with the same length,
the customer will always choose the window with the smallest number.
Customer[i] will take T[i] minutes to have his/her transaction processed.
The first N customers are assumed to be served at 8:00am.
Now given the processing time of each customer, you are supposed to 
tell the exact time at which a customer has his/her business done.

For example, suppose that a bank has 2 windows and each window may 
have 2 customers waiting inside the yellow line. There are 5 customers
waiting with transactions taking 1, 2, 6, 4 and 3 minutes, respectively. 
At 08:00 in the morning, customer1 is served at window1 while customer2
is served at window2. Customer3 will wait in front of window1 and customer4 
will wait in front of window2. Customer5 will wait behind the yellow line.

At 08:01, customer1 is done and customer5 enters the line in front of
window1 since that line seems shorter now. Customer2 will leave at 08:02,
customer4 at 08:06, customer3 at 08:07, and finally customer5 at 08:10.

Input

Each input file contains one test case. Each case starts with a line 
containing 4 positive integers: N (<=20, number of windows),
M (<=10, the maximum capacity of each line inside the yellow line),
K (<=1000, number of customers), and Q (<=1000, number of customer queries).

The next line contains K positive integers, which are the processing 
time of the K customers.

The last line contains Q positive integers, which represent the customers
who are asking about the time they can have their transactions done. 
The customers are numbered from 1 to K.

Output

For each of the Q customers, print in one line the time at which his/her 
transaction is finished, in the format HH:MM where HH is in [08, 17] and 
MM is in [00, 59]. Note that since the bank is closed everyday after 17:00,
for those customers who cannot be served before 17:00, you must output
"Sorry" instead.

Sample Input
2 2 7 5
1 2 6 4 3 534 2
3 4 5 6 7
Sample Output
08:07
08:06
08:10
17:00
Sorry

*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

const int A1014MAXTM = 540;

struct A1014Custom 
{
	A1014Custom(int p, int i) :proc(p), idx(i) {}
	int idx = 0;
	int proc = 0;
	int end = 0;
	bool timeout = false;
	void Query(void)
	{
		if (timeout || (end > A1014MAXTM))
		{
			cout << "Sorry" << endl;
			return;
		}
		int h = end / 60;
		int m = end % 60;
		printf("%02d:%02d\n", h + 8, m);
	}
};

struct A1014Wnd
{
	bool done = false;
	int tmNext = 0;
	deque<A1014Custom*> dqCustoms;

	void Init(void)
	{
		if (dqCustoms.empty())
		{
			return;
		}
		tmNext = dqCustoms.front()->proc;
		dqCustoms.front()->end = tmNext;
		if (tmNext > A1014MAXTM)
		{
			done = true;
		}
	}

	void Next(void)
	{
		if (dqCustoms.empty())
		{
			return;
		}
		tmNext += dqCustoms.front()->proc;
		dqCustoms.front()->end = tmNext;
		if (tmNext > A1014MAXTM)
		{
			done = true;
		}
	}

	void Push(A1014Custom* p)
	{
		if (done)
		{
			throw 0;
		}
		dqCustoms.pop_front();
		dqCustoms.push_back(p);
		Next();
	}

	void Done(void)
	{
		for (int i = 1; i < dqCustoms.size(); ++i)
		{
			auto p = dqCustoms[i];
			if (done)
			{
				p->timeout = true;
				continue;
			}
			tmNext += p->proc;
			p->end = tmNext;
			if (p->end > A1014MAXTM)
			{
				done = true;
			}
		}
	}
};

int A1014FindWnd(vector<A1014Wnd>& vWnd)
{
	int iWnd = 0;
	int t = vWnd[0].tmNext;
	for (int i = 1; i < vWnd.size(); ++i)
	{
		if (vWnd[i].tmNext < t)
		{
			t = vWnd[i].tmNext;
			iWnd = i;
		}
	}
	return iWnd;
}

// rename this to main int PAT
int A1014Func(void)
{
	int n, m, k, q;
	cin >> n >> m >> k >> q;
	int proc, query;
	vector<A1014Custom> vCustom;
	for (int i = 0; i < k; ++i)
	{
		cin >> proc;
		vCustom.push_back(A1014Custom(proc, i + 1));
	}
	
	vector<A1014Wnd> vWnd(n, A1014Wnd());

	// first queue
	auto k1 = std::min(k, n * m);
	int n1 = 0;
	for (int i = 0; i < k1; ++i)
	{
		vWnd[n1++].dqCustoms.push_back(&vCustom[i]);
		if (n1 >= n)
		{
			n1 = 0;
		}
	}
	// first tmNext
	for (auto& w : vWnd)
	{
		w.Init();
	}

	// proc left one by one
	for (int i = n * m; i < k; ++i)
	{
		// find next wnd
		int minWnd = 0;
		for (; minWnd < n; ++minWnd)
		{
			if (!vWnd[minWnd].done)
			{
				break;
			}
		}
		if (minWnd >= n)
		{
			// all time out
			for (auto it : vCustom)
			{
				it.timeout = true;
			}
			break;
		}
		int tmNext = vWnd[minWnd].tmNext;
		for (int k = minWnd + 1; k < n; ++k)
		{
			if (vWnd[k].tmNext < tmNext)
			{
				tmNext = vWnd[minWnd].tmNext;
				minWnd = k;
			}
		}
		vWnd[minWnd].Push(&vCustom[i]);
	}

	// exhaust 
	for (auto w : vWnd)
	{
		w.Done();
	}


	for (int i = 0; i < q; ++i)
	{
		cin >> query;
		vCustom[--query].Query();
	}


	return 0;
}


void A1014(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1014Func();
	cout << endl;
}

void A1014(void)
{
	A1014("data\\A1014-1.txt"); // 
}

