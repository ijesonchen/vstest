/*
1012. The Best Rank (25)
cost: 20:00  1h

sln1： 读取，排序，计算bast rank
	21/25
sln2：排序后可能有并列排名：
	pass

To evaluate the performance of our first year CS majored
students, we consider their grades of three courses only: 
C - C Programming Language, 
M - Mathematics (Calculus or Linear Algebra), and
E - English. At the mean time, we encourage students by 
emphasizing on their best ranks -- that is, among the four 
ranks with respect to the three courses and the average 
grade, we print the best rank for each student.

For example, The grades of C, M, E and A - Average of 4 
students are given as the following:

StudentID  C  M  E  A
310101     98 85 88 90
310102     70 95 88 84
310103     82 87 94 88
310104     91 91 91 91
Then the best ranks for all the students are No.1 since 
the 1st one has done the best in C Programming Language, 
while the 2nd one in Mathematics, the 3rd one in English, 
and the last one in average.

Input

Each input file contains one test case. Each case starts 
with a line containing 2 numbers N and M (<=2000), which 
are the total number of students, and the number of students
who would check their ranks, respectively. Then N lines 
follow, each contains a student ID which is a string of 6 
digits, followed by the three integer grades (in the range 
of [0, 100]) of that student in the order of C, M and E. 
Then there are M lines, each containing a student ID.

Output

For each of the M students, print in one line the best rank 
for him/her, and the symbol of the corresponding rank, 
separated by a space.

The priorities of the ranking methods are ordered as 
A > C > M > E. Hence if there are two or more ways for a 
student to obtain the same best rank, output the one with 
the highest priority.

If a student is not on the grading list, simply output "N/A".

Sample Input
5 6
310101 98 85 88
310102 70 95 88
310103 82 87 94
310104 91 91 91
310105 85 90 90
310101
310102
310103
310104
310105
999999
Sample Output
1 C
1 M
1 E
1 A
3 A
N/A
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// rename this to main int PAT
struct A1012Score 
{
	string id;
	int c = 0;
	int m = 0;
	int e = 0;
	int a = 0;

	int rank = 3000;
	char symbol = 0;

	void Average(void)
	{
		a = (c + m + e) / 3;
	}

	void Best(void)
	{
		if (rank > 2000)
		{
			throw 0;
		}
		cout << rank << " " << symbol << endl;
	}

	void Rank(int r, char s)
	{
		if (r < rank)
		{
			rank = r;
			symbol = s;
		}
	}
};

bool A1012GreatA(const A1012Score* p1, const A1012Score* p2)
{
	return p1->a > p2->a;
}

bool A1012GreatC(const A1012Score* p1, const A1012Score* p2)
{
	return p1->c > p2->c;
}

bool A1012GreatM(const A1012Score* p1, const A1012Score* p2)
{
	return p1->m > p2->m;
}

bool A1012GreatE(const A1012Score* p1, const A1012Score* p2)
{
	return p1->e > p2->e;
}


bool A1012EqA(const A1012Score* p1, const A1012Score* p2)
{
	return p1->a == p2->a;
}

bool A1012EqC(const A1012Score* p1, const A1012Score* p2)
{
	return p1->c == p2->c;
}

bool A1012EqM(const A1012Score* p1, const A1012Score* p2)
{
	return p1->m == p2->m;
}

bool A1012EqE(const A1012Score* p1, const A1012Score* p2)
{
	return p1->e == p2->e;
}

void ProcRank(vector<A1012Score*>& vp, char symbol,
	bool(*fnSort)(const A1012Score* p1, const A1012Score* p2),
	bool(*fnEq)(const A1012Score* p1, const A1012Score* p2))
{
	sort(vp.begin(), vp.end(), fnSort);
	int idx = 1;
	int lastRank = 0;
	A1012Score* last = nullptr;
	for (auto p : vp)
	{
		if (!last)
		{
			p->Rank(1, symbol);
			last = p;
			lastRank = 1;
			continue;
		}
		++idx;
		if (!fnEq(last, p))
		{
			lastRank = idx;
		}
		p->Rank(lastRank, symbol);
		last = p;
	}
}

int A1012Func(void)
{
	int n, m;
	cin >> n >> m;
	
	vector<A1012Score> vscore;
	string id;
	for (int i = 0; i < n; ++i)
	{
		A1012Score score;
		cin >> score.id >> score.c >> score.m >> score.e;
		score.Average();
		vscore.push_back(score);
	}
	
	map<string, A1012Score*> mapid;
	vector<A1012Score*> vp;
	for (auto& it : vscore)
	{
		mapid[it.id] = &it;
		vp.push_back(&it);
	}

	// a c m e
	ProcRank(vp, 'A', A1012GreatA, A1012EqA);
	ProcRank(vp, 'C', A1012GreatC, A1012EqC);
	ProcRank(vp, 'M', A1012GreatM, A1012EqM);
	ProcRank(vp, 'E', A1012GreatE, A1012EqE);

	for (int i = 0; i < m; ++i)
	{
		cin >> id;
		auto p = mapid[id];
		if (!p)
		{
			cout << "N/A" << endl;
			continue;
		}
		p->Best();
	}

	return 0;
}


void A1012(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1012Func();
	cout << endl;
}

void A1012(void)
{
//	A1012("data\\A1012-1.txt"); // 
	A1012("data\\A1012-2.txt"); // 
}

