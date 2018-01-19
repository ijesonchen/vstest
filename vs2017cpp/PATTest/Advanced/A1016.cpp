/*
1016. Phone Bills (25)

cost: 10:00 100min 15/25

sln1£∫÷±Ω”º∆À„
	pt1,2,3  ¥ÌŒÛ

A long-distance telephone company charges its customers by the 
following rules:

Making a long-distance call costs a certain amount per minute,
depending on the time of day when the call is made. When a customer 
starts connecting a long-distance call, the time will be recorded,
and so will be the time when the customer hangs up the phone. Every 
calendar month, a bill is sent to the customer for each minute 
called (at a rate determined by the time of day). Your job is to
prepare the bills for each month, given a set of phone call records.

Input Specification:

Each input file contains one test case. Each case has two parts: 
the rate structure, and the phone call records.

The rate structure consists of a line with 24 non-negative integers 
denoting the toll (cents/minute) from 00:00 - 01:00, the toll from 
01:00 - 02:00, and so on for each hour in the day.

The next line contains a positive number N (<= 1000), followed by N 
lines of records. Each phone call record consists of the 
name of the customer (string of up to 20 characters without space), 
the time and date (mm:dd:hh:mm), 
and the word "on-line" or "off-line".

For each test case, 
all dates will be within a single month. 
Each "on-line" record is paired with the chronologically next record for
the same customer provided it is an "off-line" record. 
Any "on-line" records that are not paired with an "off-line" record are ignored, 
as are "off-line" records not paired with an "on-line" record. It is
guaranteed that at least one call is well paired in the input. You
may assume that no two records for the same customer have the same 
time. Times are recorded using a 24-hour clock.

Output Specification:

For each test case, you must print a phone bill for each customer.

Bills must be printed in alphabetical order of customers' names. For
each customer, first print in a line the name of the customer and the 
month of the bill in the format shown by the sample. Then for each 
time period of a call, print in one line the beginning and ending time
and date (dd:hh:mm), the lasting time (in minute) and the charge of 
the call. The calls must be listed in chronological order. Finally,
print the total charge for the month in the format shown by the sample.

Sample Input:
10 10 10 10 10 10 20 20 20 15 15 15 15 15 15 15 20 30 20 15 15 10 10 10
10
CYLL 01:01:06:01 on-line
CYLL 01:28:16:05 off-line
CYJJ 01:01:07:00 off-line
CYLL 01:01:08:03 off-line
CYJJ 01:01:05:59 on-line
aaa 01:01:01:03 on-line
aaa 01:02:00:01 on-line
CYLL 01:28:15:41 on-line
aaa 01:05:02:24 on-line
aaa 01:04:23:59 off-line
Sample Output:
CYJJ 01
01:05:59 01:07:00 61 $12.10
Total amount: $12.10
CYLL 01
01:06:01 01:08:03 122 $24.40
28:15:41 28:16:05 24 $3.85
Total amount: $28.25
aaa 01
02:00:01 04:23:59 4318 $638.80
Total amount: $638.80
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <numeric>

using namespace std;

const int A1016HourCount = 24;

vector<int> A1016vtCost;
int A1016nDayCost = 0;

struct A1016Record
{
	string time;
	bool off = false;

	A1016Record(string s, bool o) :time(s), off(o) {};
};

bool operator<(const A1016Record& lhs, const A1016Record& rhs)
{
	return lhs.time < rhs.time;
}

bool A1016IsOffline(const string& s)
{
	return s[1] == 'f';
}

int A1016HourCost(int h1, int h2)
{
	int total = 0;
	for (int h = h1; h < h2; ++h)
	{
		total += 60 * A1016vtCost[h];
	}
	return total;
}

int A1016Time2Min(const string& s1)
{
	const int d1 = atoi(s1.substr(3, 2).c_str());
	const int h1 = atoi(s1.substr(6, 2).c_str());
	const int m1 = atoi(s1.substr(9, 2).c_str());
	return (d1 * 24 + h1) * 60 + m1;
}

int A1016PrintCharge(const string& s1, const string& s2)
{
	int total = 0;
	auto t1 = s1.substr(3);
	auto t2 = s2.substr(3);
	auto minu = A1016Time2Min(s2) - A1016Time2Min(s1);
	// d h m  00:00:00
	const int d1 = atoi(t1.substr(0, 2).c_str());
	const int h1 = atoi(t1.substr(3, 2).c_str());
	const int m1 = atoi(t1.substr(6, 2).c_str());
	const int d2 = atoi(t2.substr(0, 2).c_str());
	const int h2 = atoi(t2.substr(3, 2).c_str());
	const int m2 = atoi(t2.substr(6, 2).c_str());
	int day = d2 - d1;
	bool twoPart = t1.substr(3) > t2.substr(3);
	if (twoPart)
	{
		--day;
		total += (60 - m1) * A1016vtCost[h1];
		total += A1016HourCost(h1 + 1, 24);
		total += A1016HourCost(0, h2 - 1);
		total += m2* A1016vtCost[h2];
	}
	else
	{
		if (h1 == h2)
		{
			total += (m2 - m1)*A1016vtCost[h1];
		}
		else
		{
			total += (60 - m1) * A1016vtCost[h1];
			total += A1016HourCost(h1 + 1, h2);
			total += m2* A1016vtCost[h2];
		}
	}
	total += day * A1016nDayCost;

	cout << t1 << " " << t2;
	printf(" %d $%.2f\n", minu, (float)total / 100);
	return total;
}

void A1016PrintBill(const string& name, const set<A1016Record>& setRec)
{
	auto it = setRec.begin();
	while (it->off && it != setRec.end())
	{
		++it;
	}
	if (it == setRec.end())
	{
		return;
	}

	auto first = it++;
	bool header = false;

	int total = 0;

	for (; it != setRec.end(); ++it)
	{
		if (!it->off)
		{
			first = it;
			continue;
		}
		if (!header)
		{
			cout << name << " " << first->time.substr(0,2) << endl;
			header = true;
		}
		total += A1016PrintCharge(first->time, it->time);

		do 
		{
			++it;
		} while (it != setRec.end() && it->off);
		if (it == setRec.end())
		{
			break;
		}
		first = it;
	}	
	if (total)
	{
		cout << "Total amount: $";
		printf("%.2f\n", float(total) / 100);
	}
}

// rename this to main int PAT
int A1016Func(void)
{
	A1016vtCost.clear();
	for (int i = 0; i < A1016HourCount; ++i)
	{
		int tmp;
		cin >> tmp;
		A1016vtCost.push_back(tmp);
	}

	A1016nDayCost = std::accumulate(A1016vtCost.begin(), A1016vtCost.end(), 0);
	A1016nDayCost *= 60;

	map<string, set<A1016Record>> mData;

	int rec;
	cin >> rec;
	for (int i = 0; i < rec; ++i)
	{
		// name time tag
		string name, time, stag;
		cin >> name >> time >> stag;
		auto tag = A1016IsOffline(stag);
		mData[name].insert(A1016Record(time, tag));
	}

	for (auto& user : mData)
	{
		A1016PrintBill(user.first, user.second);
	}

	return 0;
}


void A1016(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1016Func();
	cout << endl;
}

void A1016(void)
{
	A1016("data\\A1016-1.txt"); // 
}

