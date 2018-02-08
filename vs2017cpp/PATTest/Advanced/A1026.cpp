/*
1026. Table Tennis (30)

cost: 9:50 100min 14:20 50min

sln1: 直接计算。注意时序
	150min 24/30 pt4,5,7错误
	

A table tennis club has N tables available to the public. 
The tables are numbered from 1 to N. 
For any pair of players, 
if there are some tables open when they arrive, 
they will be assigned to the available table with the smallest number.
If all the tables are occupied, they will have to wait in a queue.
It is assumed that every pair of players can play for at most 2 hours.

Your job is to count for everyone in queue their waiting time, 
and for each table the number of players it has served for the day.

One thing that makes this procedure a bit complicated is that 
the club reserves some tables for their VIP members. 
When a VIP table is open, the first VIP pair in the queue will have the privilege to take it.
However, if there is no VIP in the queue, the next pair of players can take it. 
On the other hand, if when it is the turn of a VIP pair, 
yet no VIP table is available, they can be assigned as any ordinary players.

Input Specification:

Each input file contains one test case. 
For each case, the first line contains an integer 
N (<=10000) - the total number of pairs of players. 
Then N lines follow, each contains 2 times and a VIP tag: 
HH:MM:SS - the arriving time, 
P - the playing time in minutes of a pair of players, 
and tag - which is 1 if they hold a VIP card, or 0 if not. 

It is guaranteed that the arriving time is 
between 08:00:00 and 21:00:00 while the club is open. 
It is assumed that no two customers arrives at the same time.

Following the players' info, there are 2 positive integers: 
K (<=100) - the number of tables, 
and M (< K) - the number of VIP tables. 
The last line contains M table numbers.

Output Specification:

For each test case, 
first print the arriving time, serving time and the waiting time 
for each pair of players in the format shown by the sample. 

Then print in a line the number of players served by each table. 
Notice that the output must be listed in chronological order of the serving time. 
The waiting time must be rounded up to an integer minute(s). 
If one cannot get a table before the closing time, their information must NOT be printed.

Sample Input:
9
20:52:00 10 0
08:00:00 20 0
08:02:00 30 0
20:51:00 10 0
08:10:00 5 0
08:12:00 10 1
20:50:00 10 0
08:01:30 15 1
20:53:00 10 1
3 1
2
Sample Output:
08:00:00 08:00:00 0
08:01:30 08:01:30 0
08:02:00 08:02:00 0
08:12:00 08:16:30 5
08:10:00 08:20:00 10
20:50:00 20:50:00 0
20:51:00 20:51:00 0
20:52:00 20:52:00 0
3 3 2
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

namespace nsA1026
{
	const int StartSec = 8 * 3600;
	const int CloseSec = 21 * 3600;

	int Str2Time(string str)
	{
		int h = atoi(str.substr(0, 2).c_str());
		int m = atoi(str.substr(3, 2).c_str());
		int s = atoi(str.substr(6, 2).c_str());
		return (h * 60 + m) * 60 + s;
	}

	string Time2Str(int n)
	{
		int h = n / 3600;
		n -= h * 3600;
		int m = n / 60;
		n -= m * 60;
		int s = n;
		string str("00:00:00");
		str[0] += h / 10;
		str[1] += h % 10;
		str[3] += m / 10;
		str[4] += m % 10;
		str[6] += s / 10;
		str[7] += s % 10;
		return str;
	}

	struct Table 
	{
		int id = 0;
		int next = StartSec;
		bool vip = false;
		int served = 0;

		bool operator<(const Table& t)
		{
			return next < t.next;
		}
	};

	bool LessTable(const Table* p1, const Table* p2)
	{
		return p1->next < p2->next;
	}

	struct Player
	{
		int arriveSec = 0;
		string strArrive;
		int costSec = 0;
		bool vip = false;

		string strServe;
		int waitMinu = 0;

		bool operator<(const Player& p)
		{
			return arriveSec < p.arriveSec;
		}
	};

	ostream& operator<<(ostream& os, const Player& p)
	{
		os << p.strArrive << " " << p.strServe << " " << p.waitMinu;
		return os;
	}

	vector<Table> vTable;
	vector<Table*> vptNorm;
	vector<Table*> vptVip;
	vector<Player> vPlayer;
	deque<Player*> dqppNorm;
	deque<Player*> dqppVip;

	Player ReadPlayer(void) 
	{
		string str;
		int cost;
		bool vip;
		cin >> str >> cost >> vip;
		Player p;
		p.strArrive = str;
		p.arriveSec = Str2Time(str);
		p.costSec = cost * 60;
		p.vip = vip;
		return p;
	};
	
	void ReadData(void)
	{
		int n, k, m, l;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			vPlayer.push_back(ReadPlayer());
		}
		sort(vPlayer.begin(), vPlayer.end());
		for (auto& p : vPlayer)
		{
			if (p.vip)
			{
				dqppVip.push_back(&p);
			}
			else
			{
				dqppNorm.push_back(&p);
			}
		}
		cin >> k >> m;
		vTable.assign(k, Table());

		for (int i = 0; i < vTable.size(); ++i)
		{
			vTable[i].id = i + 1;
		}

		for (int i = 0; i < m; ++i)
		{
			cin >> l;
			vTable[--l].vip = true;
		}
		for (auto& t : vTable)
		{
			if (t.vip)
			{
				vptVip.push_back(&t);
			}
			else
			{
				vptNorm.push_back(&t);
			}
		}
	}

	Table* NextTable(void)
	{
		auto& table = *min_element(vTable.begin(), vTable.end());
		if (table.next >= CloseSec)
		{
			return nullptr;
		}
		return &table;
	}

	Player* NextPlayer(void)
	{
		if (dqppNorm.empty() && dqppVip.empty())
		{
			return nullptr;
		}
		bool vip = false;
		if (!dqppVip.empty())
		{
			if (dqppNorm.empty())
			{
				vip = true;
			}
			else
			{
				if (dqppVip.front()->arriveSec < dqppNorm.front()->arriveSec)
				{
					vip = true;
				}
			}
		}
		return vip ? dqppVip.front() : dqppNorm.front();
	}

	void CheckTable(void)
	{
		auto player = NextPlayer();
		if (!player)
		{
			return;
		}
		for (auto& t : vTable)
		{
			if (player->arriveSec > t.next)
			{
				t.next = player->arriveSec;
			}
		}
	}

	Player* ServePlayer(Table* pTable)
	{
		if (dqppNorm.empty() && dqppVip.empty())
		{
			return nullptr;
		}
		Player* p = nullptr;
		bool vip = false;
		if (pTable->vip)			
		{
			if (!dqppVip.empty() && dqppVip.front()->arriveSec <= pTable->next)
			{
				vip = true;
			}
		}
		else
		{
			if (!dqppVip.empty())
			{
				if (dqppNorm.empty())
				{
					vip = true;
				}
				else
				{
					if (dqppVip.front()->arriveSec < dqppNorm.front()->arriveSec)
					{
						vip = true;
					}
				}
			}
		}
		if (vip)
		{
			p = dqppVip.front();
			dqppVip.pop_front();
		}
		else
		{
			p = dqppNorm.front();
			dqppNorm.pop_front();
		}
		if (p->arriveSec < pTable->next)
		{
			
			p->waitMinu = (pTable->next - p->arriveSec + 30) / 60;
			p->strServe = Time2Str(pTable->next);
			pTable->next += p->costSec;
		}
		else
		{
			p->strServe = p->strArrive;
			pTable->next = p->arriveSec + p->costSec;
		}
		++pTable->served;
		return p;
	}
	
}

// rename this to main int PAT
int A1026Func(void)
{
	using namespace nsA1026;
	ReadData();
	Table* pTable = nullptr;
	Player* pPlayer = nullptr;
	while ((pTable = NextTable()) && (pPlayer = ServePlayer(pTable)))
	{
		CheckTable();
		cout << *pPlayer << endl;
	}
	auto itt = vTable.begin();
	cout << itt->served;
	for (++itt; itt != vTable.end(); ++itt)
	{
		cout << " " << itt->served;
	}
	cout << endl;

	return 0;
}

void A1026(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1026Func();
	cout << endl;
}

void A1026(void)
{
	A1026("data\\A1026-1.txt"); // 
}

