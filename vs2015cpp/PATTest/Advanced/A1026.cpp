/*
1026. Table Tennis (30)

cost: 5d6.5h

数据：pt3含有21:00:00到达的用户。但是不影响(table <= closeTime)

sln1: 直接计算。注意时序
	150min 24/30 pt4,5,7错误

sln2: 最大2小时
	60min 26/30 pt5,7错误
	ref：
	https://www.sigmainfy.com/blog/pat-1026-table-tennis.html
	https://www.liuchuo.net/archives/2955
	注意点：
	这个题目最大的坑点就是:在情况(3)中，当有多个乒乓球桌子空闲时，
	vip玩家要是到了的话会使用最小标号的vip球桌，而不是最小标号的球台.
	还有注意每个玩家最多玩两个小时.

snl3: 重写。计算时，取当前空闲桌，最早的vip，最早的norm，然后分支判断。
	60min 14/30 pt2-8错误
	bug-fix: 读取vip桌号时转换0基。
	重写分支判断
	60min 15/30 pt2-7错误
	bug: 循环内部为对pPlayer数组边界进行控制，有可能导致越界？

sln4: 重写分支判断。尽量模拟人处理的逻辑，有时候复杂逻辑需要分段简化
	60min pass
	下一桌，下一人。有桌没人时，设定桌子时刻到有人。（减少逻辑：有桌一定有人）
	人是vip时：看有没有vip空桌，有，换桌子。
	桌是vip时：看有没有vip等着，有，换人。
	提供服务。


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
#include <cstdio>
#include <cmath>

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

namespace nsA1026v2
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
	deque<Player*> dqppNorm;
	deque<Player*> dqppVip;

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
				dqppVip.push_back(&p);
			}
			else
			{
				dqppNorm.push_back(&p);
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
			vtVip[--mi] = true;
		}
	}

	int NextTable(void) {
		auto p = min_element(vtNext.begin(), vtNext.end());
		if (*p >= CloseSec) {
			return -1;
		}
		return int(p - vtNext.begin());
	}

	int NextVipTable(void) {
		int k = -1, t = CloseSec;
		auto len = vtNext.size();
		for (size_t i = 0; i < len; ++i)
		{
			if (vtVip[i] && vtNext[i] < t)
			{
				t = vtNext[i];
				k = (int)i;
			}
		}
		return k;
	}

	Player* NextPlayer(void) {
		if (dqppVip.empty() && dqppNorm.empty()) {
			return nullptr;
		}
		if (dqppNorm.empty()) {
			return dqppVip.front();
		}
		if (dqppVip.empty()) {
			return dqppNorm.front();
		}
		if (dqppNorm.front()->arriveSec < dqppVip.front()->arriveSec) {
			return dqppNorm.front();
		}
		else {
			return dqppVip.front();
		}
	}

	Player* NextVipPlayer(void)
	{
		return dqppVip.empty() ? nullptr : dqppVip.front();
	}

	void PopPlayer(Player* p) {
		if (p->vip) {
			dqppVip.pop_front();
		}
		else {
			dqppNorm.pop_front();
		}
	}

	void ServePlayer(Player* p, int nTable) {
		p->serveSec = vtNext[nTable];
		vtNext[nTable] += p->costSec;
		++vtServed[nTable];
	}
}

// rename this to main int PAT
int A1026Func2(void)
{
	using namespace nsA1026v2;
	ReadData();
	size_t iVip = 0, iNorm = 0, nv = dqppVip.size(), nn = dqppNorm.size();
	while (true)
	{
		auto itable = NextTable();
		if (itable < 0) {
			// closed
			break;
		}
		auto tTable = vtNext[itable];
		auto pNext = NextPlayer();
		if (!pNext) {
			// no player
			break;
		}
		auto arriveSec = pNext->arriveSec;
		if (arriveSec > tTable) {
			// no arrived
			for (auto& t : vtNext) {
				if (t < arriveSec) {
					// till one arrived
					t = pNext->arriveSec;
				}
			}
			continue;
		}
		if (pNext->vip) {
			if (!vtVip[itable]) {
				auto iVipTbl = NextVipTable();
				if (iVipTbl >= 0 && vtNext[iVipTbl] <= pNext->arriveSec)
				{
					itable = iVipTbl;
				}
			}
		}
		if (vtVip[itable]) {
			auto pvNext = NextVipPlayer();
			if (pvNext && pvNext->arriveSec < tTable) {
				pNext = pvNext;
			}
		}
		PopPlayer(pNext);
		ServePlayer(pNext, itable);
		cout << *pNext << endl;
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

namespace nsA1026ref2
{
	struct person {
		int arrive, start, time;
		bool vip;
	}tempperson;
	struct tablenode {
		int end = 8 * 3600, num;
		bool vip;
	};
	bool cmp1(person a, person b) {
		return a.arrive < b.arrive;
	}
	bool cmp2(person a, person b) {
		return a.start < b.start;
	}
	vector<person> player;
	vector<tablenode> table;
	void alloctable(int personid, int tableid) {
		if (player[personid].arrive <= table[tableid].end)
			player[personid].start = table[tableid].end;
		else
			player[personid].start = player[personid].arrive;
		table[tableid].end = player[personid].start + player[personid].time;
		table[tableid].num++;
	}
	int findnextvip(int vipid) {
		vipid++;
		while (vipid < player.size() && player[vipid].vip == false) {
			vipid++;
		}
		return vipid;
	}
	int main() {
		int n, k, m, viptable;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			int h, m, s, temptime, flag;
			scanf("%d:%d:%d %d %d", &h, &m, &s, &temptime, &flag);
			tempperson.arrive = h * 3600 + m * 60 + s;
			tempperson.start = 21 * 3600;
			if (tempperson.arrive >= 21 * 3600)
				continue;
			tempperson.time = temptime <= 120 ? temptime * 60 : 7200;
			tempperson.vip = ((flag == 1) ? true : false);
			player.push_back(tempperson);
		}
		scanf("%d%d", &k, &m);
		table.resize(k + 1);
		for (int i = 0; i < m; i++) {
			scanf("%d", &viptable);
			table[viptable].vip = true;
		}
		sort(player.begin(), player.end(), cmp1);
		int i = 0, vipid = -1;
		vipid = findnextvip(vipid);
		while (i < player.size()) {
			int index = -1, minendtime = 999999999;
			// 第一个空桌
			for (int j = 1; j <= k; j++) {
				if (table[j].end < minendtime) {
					minendtime = table[j].end;
					index = j;
				}
			}
			if (table[index].end >= 21 * 3600)
				break;
			if (player[i].vip == true && i < vipid) {
				i++;
				continue;
			}
			if (table[index].vip == true) {
				// vip桌
				if (player[i].vip == true) {
					// vip客
					alloctable(i, index);
					if (vipid == i)
						vipid = findnextvip(vipid);
					i++;
				}
				else {
					// 非vip客
					if (vipid < player.size() && player[vipid].arrive <= table[index].end) {
						// 有vip客
						alloctable(vipid, index);
						vipid = findnextvip(vipid);
					}
					else {
						alloctable(i, index);
						i++;
					}
				}
			}
			else {
				if (player[i].vip == false) {
					// 非vip客
					alloctable(i, index);
					i++;
				}
				else {
					// vip客
					int vipindex = -1, minvipendtime = 999999999;
					// 下一个vip桌
					for (int j = 1; j <= k; j++) {
						if (table[j].vip == true && table[j].end < minvipendtime) {
							minvipendtime = table[j].end;
							vipindex = j;
						}
					}
					if (vipindex != -1 && player[i].arrive >= table[vipindex].end) {
						alloctable(i, vipindex);
						if (vipid == i)
							vipid = findnextvip(vipid);
						i++;
					}
					else {
						alloctable(i, index);
						if (vipid == i)
							vipid = findnextvip(vipid);
						i++;
					}
				}
			}
		}
		sort(player.begin(), player.end(), cmp2);
		for (i = 0; i < player.size() && player[i].start < 21 * 3600; i++) {
			printf("%02d:%02d:%02d ", player[i].arrive / 3600, player[i].arrive % 3600 / 60, player[i].arrive % 60);
			printf("%02d:%02d:%02d ", player[i].start / 3600, player[i].start % 3600 / 60, player[i].start % 60);
			printf("%.0f\n", round((player[i].start - player[i].arrive) / 60.0));
		}
		for (int i = 1; i <= k; i++) {
			if (i != 1)
				printf(" ");
			printf("%d", table[i].num);
		}
		return 0;
	}
}

void A1026(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1026Func2();

// 	nsA1026ref1::main(fn);
// 	cout << endl;
}

void A1026(void)
{
	A1026("data\\A1026-1.txt"); // 
}

