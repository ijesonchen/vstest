/*
1025. PAT Ranking (25)

cost: 21:05 40min

sln1: ≈≈–Ú

Programming Ability Test (PAT) is organized by the College of Computer Science and Technology of Zhejiang University. 
Each test is supposed to run simultaneously in several places, 
and the ranklists will be merged immediately after the test.
Now it is your job to write a program to correctly merge all the ranklists and generate the final rank.

Input Specification:

Each input file contains one test case. For each case, 
the first line contains a positive number 
N (<=100), the number of test locations. 
Then N ranklists follow, each starts with a line containing a positive integer 
K (<=300), the number of testees, and 
then K lines containing the 
registration number (a 13-digit number) and 
the total score of each testee. 
All the numbers in a line are separated by a space.

Output Specification:

For each test case, first print in one line the total number of testees. 
Then print the final ranklist in the following format:

registration_number final_rank location_number local_rank

The locations are numbered from 1 to N. 
The output must be sorted in nondecreasing order of the final ranks. 
The testees with the same score must have the same rank, 
and the output must be sorted in nondecreasing order of their registration numbers.

Sample Input:
2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
4
1234567890013 65
1234567890011 25
1234567890014 100
1234567890012 85
Sample Output:
9
1234567890005 1 1 1
1234567890014 1 2 1
1234567890001 3 1 2
1234567890003 3 1 2
1234567890004 5 1 4
1234567890012 5 2 2
1234567890002 7 1 5
1234567890013 8 2 3
1234567890011 9 2 4
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct A1025Score
{
	string num;
	int score = 0;
	int local = 0;
	int localrank = 0;

	A1025Score(const string& n, int s, int l) : num(n), score(s), local(l) {}
};

bool A1025ScoreGreat(const A1025Score* p1, const A1025Score* p2)
{
	if (p1->score > p2->score)
	{
		return true;
	}
	if (p1->score == p2->score)
	{
		return p1->num < p2->num;
	}
	return false;
}


// rename this to main int PAT
int A1025Func(void)
{
	int n, k;
	string num;
	int score;

	vector<A1025Score> vScore;
	vector<int> vLocalSize;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> k;
		vLocalSize.push_back(k);
		for (int j = 0; j < k; ++j)
		{
			cin >> num >> score;
			vScore.push_back(A1025Score(num, score, i + 1));
		}
	}
	
	vector<vector<A1025Score*>> vpScores(n+1);

	int idx = 0;
	for (int i = 0; i < n; ++i)
	{
		int localSize = vLocalSize[i];
		auto& vpLocalScore = vpScores[i];
		for (int j = 0; j < localSize; ++j)
		{
			vpLocalScore.push_back(&vScore[idx + j]);
		}
		idx += localSize;
	}
	
	for (int i = 0; i < n; ++i)
	{
		auto& vpLocal = vpScores[i];
		sort(vpLocal.begin(), vpLocal.end(), A1025ScoreGreat);
		vpLocal.front()->localrank = 1;
		size_t len = vpLocal.size();
		for (size_t j = 1; j < len; ++j)
		{
			auto last = vpLocal[j - 1];
			auto p = vpLocal[j];
			if (p->score == last->score)
			{
				p->localrank = last->localrank;
			}
			else
			{
				p->localrank = (int)j + 1;
			}
		}
	}

	auto& vpFinalScore = vpScores.back();
	for (auto& s : vScore)
	{
		vpFinalScore.push_back(&s);
	}
	sort(vpFinalScore.begin(), vpFinalScore.end(), A1025ScoreGreat);

	auto& first = vpFinalScore.front();
	int lastScore = first->score;
	size_t len = vpFinalScore.size();
	cout << len << endl;
	cout << first->num << " 1 " << first->local << " " << first->localrank << endl;
	int rank = 1;
	for (int i = 1; i < vpFinalScore.size(); ++i)
	{
		auto last = vpFinalScore[i - 1];
		auto p = vpFinalScore[i];
		if (p->score < last->score)
		{
			rank = i + 1;
		}
		else if (p->score > last->score)
		{
			throw 0;
		}
		cout << p->num << " " << rank << " " << p->local << " " << p->localrank << endl;
	}

	return 0;
}


void A1025(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1025Func();
	cout << endl;
}

void A1025(void)
{
	A1025("data\\A1025-1.txt"); // 
}

