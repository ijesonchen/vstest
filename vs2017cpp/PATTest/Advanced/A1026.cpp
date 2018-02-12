/*
1026. Table Tennis (30)

cost: 9:50 100min 14:20 50min

数据：pt3含有21:00:00到达的用户。但是不影响(table <= closeTime)

sln1: 直接计算。注意时序
	150min 24/30 pt4,5,7错误

sln2: 最大2小时
	60min 26/30 pt5,7错误

snl3: 重写。计算时，取当前空闲桌，最早的vip，最早的norm，然后分支判断。
	60min 14/30 pt2-8错误

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
#include <functional>  

using namespace std;

namespace nsA1026
{
	const int StartSec = 8 * 3600;
	const int CloseSec = 21 * 3600;
	const int MaxPlayMinu = 2 * 60;

	int Str2Time(string str)
	{
		int h = atoi(str.substr(0, 2).c_str());
		int m = atoi(str.substr(3, 2).c_str());
		int s = atoi(str.substr(6, 2).c_str());
		return (h * 60 + m) * 60 + s;
	}

	string Time2Str(int n)
	{
		const int ARRLEN = 3;
		int t[ARRLEN] = { n / 3600 , n % 3600 / 60, n % 60 };
		string str("00:00:00");
		for (int i = 0; i < ARRLEN; ++i)
		{
			int k = t[i];
			str[ARRLEN * i + 0] += k / 10;
			str[ARRLEN * i + 1] += k % 10;
		}
		return str;
	}

	struct Table 
	{
		int next = StartSec;
		bool vip = false;
		int served = 0;

		bool operator<(const Table& t)
		{
			return next < t.next;
		}
	};

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
	vector<Player> vPlayer;
	deque<Player*> dqppNorm;
	deque<Player*> dqppVip;

	Player ReadPlayer(void) 
	{
		string str;
		int cost;
		bool vip;
		cin >> str >> cost >> vip;
		if (cost > MaxPlayMinu)
		{
			cost = MaxPlayMinu;
		}
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

		for (int i = 0; i < m; ++i)
		{
			cin >> l;
			vTable[--l].vip = true;
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

	deque<Player*>* EarliestPlayerDeque(void)
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
		return vip ? &dqppVip : &dqppNorm;
	}

	void CheckTable(void)
	{
		auto dqPlayer = EarliestPlayerDeque();
		if (!dqPlayer)
		{
			return;
		}
		auto arriveSec = dqPlayer->front()->arriveSec;
		for (auto& t : vTable)
		{
			if (arriveSec > t.next)
			{
				t.next = arriveSec;
			}
		}
	}

	Player* ServePlayer(Table* pTable)
	{
		if (dqppNorm.empty() && dqppVip.empty())
		{
			return nullptr;
		}
		deque<Player*>* dqpPlayer = nullptr;
		Player* pPlayer = nullptr;
		if (pTable->vip && 
			!dqppVip.empty() && 
			dqppVip.front()->arriveSec < pTable->next)
		{
			dqpPlayer = &dqppVip;
		}
		else
		{
			dqpPlayer = EarliestPlayerDeque();
		}
		pPlayer = dqpPlayer->front();
		dqpPlayer->pop_front();

		if (pPlayer->arriveSec < pTable->next)
		{
			
			pPlayer->waitMinu = (pTable->next - pPlayer->arriveSec + 30) / 60;
			pPlayer->strServe = Time2Str(pTable->next);
			pTable->next += pPlayer->costSec;
		}
		else
		{
			pPlayer->strServe = pPlayer->strArrive;
			pTable->next = pPlayer->arriveSec + pPlayer->costSec;
		}
		++pTable->served;
		return pPlayer;
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
		cout << *pPlayer << endl;
		CheckTable();
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

namespace nsA1026_1
{
	using nsA1026::Str2Time;
	using nsA1026::Time2Str;
	using nsA1026::StartSec;
	using nsA1026::CloseSec;
	using nsA1026::MaxPlayMinu;
	// table info
	vector<bool> vtVip;
	vector<int> vtNext;
	vector<int> vtServed;


	struct Player
	{
		int arriveSec = 0;
		int costSec = 0;
		bool vip = false;

		int serveSec = 0;

		bool operator<(const Player& p)
		{
			return arriveSec < p.arriveSec;
		}
	};

	ostream& operator<<(ostream& os, const Player& p)
	{
		auto arv = p.arriveSec;
		auto srv = p.serveSec;
		os << Time2Str(arv) << " " << Time2Str(srv) << " " << (srv - arv + 30) / 60;
		return os;
	}

	vector<Player> vpPlayer;
	vector<Player*> vppNorm;
	vector<Player*> vppVip;

	void ReadData(void)
	{
		int n;
		cin >> n; 
		for (int i = 0; i < n; ++i)
		{
			vpPlayer.emplace_back();
			auto& p = vpPlayer.back();
			string s;
			int c;
			cin >> s >> c >> p.vip;
			if (s >= "21:00:00")
			{
				vpPlayer.pop_back();
				continue;
			}
			p.arriveSec = Str2Time(s);
			p.costSec = std::min(c, MaxPlayMinu) * 60;
		}
		sort(vpPlayer.begin(), vpPlayer.end());
		for (auto& p : vpPlayer)
		{
			if (p.vip)
			{
				vppVip.push_back(&p);
			}
			else
			{
				vppNorm.push_back(&p);
			}
		}
		int k, m, mi;
		cin >> k >> m;
		vtVip.assign(k, false);
		vtServed.assign(k, 0);
		vtNext.assign(k, 0);
		for (int i = 0; i < m; ++i)
		{
			cin >> mi;
			vtVip[mi] = true;
		}
	}

	int NextTable(void)
	{
		auto p = min_element(vtNext.begin(), vtNext.end());
		if (*p >= CloseSec)
		{
			return -1;
		}
		return int(p - vtNext.begin());
	}

	void ServePlayer(Player* p, int nTable)
	{

		p->serveSec = vtNext[nTable];
		vtNext[nTable] += p->costSec;
		++vtServed[nTable];
	}
}

// rename this to main int PAT
int A1026Func1(void)
{
	using namespace nsA1026_1;
	ReadData();
	size_t iVip = 0, iNorm = 0, nv = vppVip.size(), nn = vppNorm.size();
	Player* pServedPlayer = nullptr;
	while (iVip < nv && iNorm < nn)
	{
		auto inext = NextTable();
		if (inext < 0)
		{
			break;
		}
		auto tnext = vtNext[inext];
		if (tnext >= CloseSec)
		{
			break;
		}
		bool bServeVip = false;
		bool hasSpare = false;
		auto pVip = vppVip[iVip];
		auto pNorm = vppNorm[iNorm];
		if (pVip->arriveSec <= tnext)
		{
			bServeVip = true;
		}
		else if (pNorm->arriveSec <= tnext)
		{
			bServeVip = false;
		}
		else
		{
			hasSpare = true;
			if (pVip->arriveSec < pNorm->arriveSec)
			{
				bServeVip = true;
			}
			else if (pVip->arriveSec > pNorm->arriveSec)
			{
				bServeVip = false;
			}
			else { throw 0; }
		}
		if (bServeVip)
		{
			pServedPlayer = pVip;
			++iVip;
		}
		else
		{
			pServedPlayer = pNorm;
			++iNorm;
		}
		if (hasSpare)
		{
			for (auto& it : vtNext)
			{
				if (it < pServedPlayer->arriveSec)
				{
					it = pServedPlayer->arriveSec;
				}
			}
		}
		ServePlayer(pServedPlayer, NextTable());
		cout << *pServedPlayer << endl;
	}
	auto its = vtServed.begin();
	cout << *its;
	for (++its; its != vtServed.end(); ++its)
	{
		cout << " " << *its;
	}
	cout << endl;

	return 0;
}

namespace nsA1026ref1
{

	typedef struct Player
	{
		int ArriveTime;
		int ServeTime;
		int P;
	}Player;

	int N, K, M;
	bool VipTableNum[105] = { false };
	vector<Player> Ordinary;
	vector<Player> Vip;

	vector<int> NumOfServeTable;

	bool cmp(Player p1, Player p2)
	{
		return (p1.ArriveTime < p2.ArriveTime);
	}

	void OutPutTime(int tmp)
	{
		int hh, mm, ss;
		ss = tmp % 60;
		mm = tmp / 60 % 60;
		hh = tmp / 3600;
		printf("%02d:%02d:%02d ", hh, mm, ss);
	}

	void OutPut(Player p)
	{
		OutPutTime(p.ArriveTime);
		OutPutTime(p.ServeTime);
		cout << (p.ServeTime - p.ArriveTime + 30) / 60 << endl;
	}

	int main(const string& fn)
	{
		freopen(fn.c_str(), "r", stdin);
		scanf("%d", &N);
		Player tmp;
		int i, j;
		int hh, mm, ss;
		int flag;
		for (i = 0; i < N; i++)
		{
			scanf("%d:%d:%d %d %d", &hh, &mm, &ss, &tmp.P, &flag);

			if (hh >= 21)
			{
				continue;
			}

			if (tmp.P > 120)
			{
				tmp.P = 120;
			}

			tmp.ArriveTime = hh * 3600 + mm * 60 + ss;
			if (flag == 0)
			{
				Ordinary.push_back(tmp);
			}
			else
				Vip.push_back(tmp);
		}

		scanf("%d %d", &K, &M);
		for (i = 0; i < M; i++)
		{
			cin >> hh;
			VipTableNum[hh] = true;
		}

		NumOfServeTable.resize(K + 1);
		fill(NumOfServeTable.begin(), NumOfServeTable.end(), 0);

		sort(Ordinary.begin(), Ordinary.end(), cmp);
		sort(Vip.begin(), Vip.end(), cmp);

		i = 0;
		j = 0;
		int CurrTime[105];
		fill(CurrTime, CurrTime + K + 1, 8 * 3600);

		int ordtime, viptime;

		int MinTime = 21 * 3600;
		int MinTimeIndex = -1;

		int i1;
		while (i + j < Ordinary.size() + Vip.size())
		{
			MinTime = 21 * 3600;
			ordtime = 21 * 3600;
			viptime = 21 * 3600;

			// 最早的table
			for (i1 = 1; i1 <= K; i1++)
			{
				if (CurrTime[i1] < MinTime)
				{
					MinTime = CurrTime[i1];
					MinTimeIndex = i1;
				}
			}
			// 最早的普通用户
			if (i < Ordinary.size())
			{
				ordtime = Ordinary[i].ArriveTime;
				if (ordtime < MinTime)
				{
					ordtime = MinTime;
				}
			}
			// 最早的vip用户
			if (j < Vip.size())
			{
				viptime = Vip[j].ArriveTime;
				if (viptime < MinTime)
				{
					viptime = MinTime;
				}
			}

			bool serveVip = true;
			if (ordtime < viptime && ordtime < 21 * 3600)// serve ordinary player  
			{
				serveVip = false;
			}
			else if (ordtime > viptime && viptime < 21 * 3600) //vip  
			{
				serveVip = true;
			}
			else if (ordtime == viptime && viptime < 21 * 3600)
			{
				if (VipTableNum[MinTimeIndex] ||
					(!VipTableNum[MinTimeIndex] && Vip[j].ArriveTime < Ordinary[i].ArriveTime))
				{
					//vip  
					serveVip = true;
				}
				else
				{
					//ordinary  
					serveVip = false;
				}
			}
			else if (ordtime == 21 * 3600 && viptime == 21 * 3600)
			{
				break;
			}

			if (serveVip)
			{
				//判断当前时间是否有空余的vip窗口  
				if (VipTableNum[MinTimeIndex] == false)
				{
					for (i1 = 1; i1 <= K; i1++)
					{
						if (VipTableNum[i1] && CurrTime[i1] == MinTime)
						{
							MinTimeIndex = i1;
						}
					}
				}

				Vip[j].ServeTime = viptime;
				CurrTime[MinTimeIndex] = viptime + Vip[j].P * 60;
				OutPut(Vip[j]);
				NumOfServeTable[MinTimeIndex]++;
				j++;
			}
			else
			{
				Ordinary[i].ServeTime = ordtime;
				CurrTime[MinTimeIndex] = ordtime + Ordinary[i].P * 60;
				OutPut(Ordinary[i]);
				NumOfServeTable[MinTimeIndex]++;
				i++;
			}
		}

		cout << NumOfServeTable[1];
		for (i = 2; i <= K; i++)
		{
			cout << " " << NumOfServeTable[i];
		}
		return 0;
	}
}

void A1026(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1026Func1();

// 	nsA1026ref1::main(fn);
// 	cout << endl;
}

void A1026(void)
{
	A1026("data\\A1026-1.txt"); // 
}

