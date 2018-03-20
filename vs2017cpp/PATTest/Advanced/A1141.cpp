/*
1141. PAT Ranking of Institutions (25)
500 ms
65536 kB

After each PAT, the PAT Center will announce the ranking of institutions based on their students' performances. 
Now you are asked to generate the ranklist.

Input Specification:

Each input file contains one test case. 
For each case, the first line gives a positive integer N (<=10^5), which is the number of testees. 
Then N lines follow, each gives the information of a testee in the following format:

ID Score School

where "ID" is a string of 6 characters with the first one representing the test level: 
"B" stands for the basic level, "A" the advanced level and "T" the top level; 
"Score" is an integer in [0, 100]; and 
"School" is the institution code which is a string of no more than 6 English letters (case insensitive). 
Note: it is guaranteed that "ID" is unique for each testee.

Output Specification:

For each case, first print in a line the total number of institutions. 
Then output the ranklist of institutions in nondecreasing order of their ranks in the following format:

Rank School TWS Ns

where "Rank" is the rank (start from 1) of the institution; 
"School" is the institution code (all in lower case); 
"TWS" is the total weighted score which is defined to be the integer part of 
"ScoreB/1.5 + ScoreA + ScoreT*1.5", where "ScoreX" is the total score of the testees belong to this institution on level X; 
and "Ns" is the total number of testees who belong to this institution.

The institutions are ranked according to their TWS. 
If there is a tie, the institutions are supposed to have the same rank, 
and they shall be printed in ascending order of Ns. 
If there is still a tie, they shall be printed in alphabetical order of their codes.

Sample Input:
10
A57908 85 Au
B57908 54 LanX
A37487 60 au
T28374 67 CMU
T32486 24 hypu
A66734 92 cmu
B76378 71 AU
A47780 45 lanx
A72809 100 pku
A03274 45 hypu
Sample Output:
5
1 cmu 192 2
1 au 192 3
3 pku 100 1
4 hypu 81 2
4 lanx 81 2
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

namespace nsA1141A
{
	struct School 
	{
		string name;
		// scores
		int sa, sb, st;
		int tws;
		int ns;

		School() :sa(0), sb(0), st(0), tws(0), ns(0) {};

		bool operator<(const School& a) const
		{
			if (tws != a.tws)
			{
				return tws > a.tws;
			}
			else if (ns != a.ns)
			{
				return ns < a.ns;
			}
			else
			{
				return name < a.name;
			}
		}
	};

	void main(void)
	{
		unordered_map<string, School> mapSchool;
		int n, score;
		string id, name;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> id >> score >> name;
			for_each(name.begin(), name.end(), [](char& ch) { ch = tolower(ch); });
			School& school = mapSchool[name];
			switch (id[0])
			{
			case 'A':
				school.sa += score;
				break;
			case 'B':
				school.sb += score;
				break;
			case 'T':
				school.st += score;
				break;
			default:
				throw 0;
				break;
			}
			++school.ns;
		}
		vector<School> vSchool;
		for (auto& it : mapSchool)
		{
			School& school = it.second;
			school.name = it.first;
			school.tws = int(school.sb / 1.5 + school.sa + school.st * 1.5);
			vSchool.push_back(school);
		}
		sort(vSchool.begin(), vSchool.end());

		cout << vSchool.size() << endl;
		int rank = 1;
		cout << rank << " " << vSchool[0].name << " " << vSchool[0].tws << " " << vSchool[0].ns << endl;
		for (size_t i = 1; i < vSchool.size(); ++i)
		{
			if (vSchool[i].tws != vSchool[i-1].tws)
			{
				rank = (int)i+1;
			}
			cout << rank << " " << vSchool[i].name << " " << vSchool[i].tws << " " << vSchool[i].ns << endl;
		}
	}
}
// rename this to main int PAT
int A1141Func(void)
{
	nsA1141A::main();
	return 0;
}


void A1141(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1141Func();
	cout << endl;
}

void A1141(void)
{
	A1141("data\\A1141-1.txt"); // 
}

