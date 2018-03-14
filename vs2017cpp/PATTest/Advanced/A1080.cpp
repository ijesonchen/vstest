/*
1080. Graduate Admission (30)
200 ms
65536 kB
16000 B

20:30

It is said that in 2013, there were about 100 graduate schools ready to proceed over 40,000 applications in Zhejiang Province. 
It would help a lot if you could write a program to automate the admission procedure.

Each applicant will have to provide two grades:
the national entrance exam grade GE, 
and the interview grade GI. 
The final grade of an applicant is (GE + GI) / 2. 

The admission rules are:
The applicants are ranked according to their final grades, 
and will be admitted one by one from the top of the rank list.

If there is a tied final grade, the applicants will be ranked 
according to their national entrance exam grade GE. 
If still tied, their ranks must be the same.


Each applicant may have K choices and the admission will be done according to his/her choices: 
if according to the rank list, it is one's turn to be admitted; and 
if the quota of one's most preferred shcool is not exceeded, then one will be admitted to this school, 
or one's other choices will be considered one by one in order. 
If one gets rejected by all of preferred schools, then this unfortunate applicant will be rejected.

If there is a tied rank, and if the corresponding applicants are applying to the same school, 
then that school must admit all the applicants with the same rank, even if its quota will be exceeded.


Input Specification:

Each input file contains one test case.
Each case starts with a line containing three positive integers: 
N (<=40,000), the total number of applicants; 
M (<=100), the total number of graduate schools; 
and K (<=5), the number of choices an applicant may have.

In the next line, separated by a space, there are M positive integers. 
The i-th integer is the quota of the i-th graduate school respectively.

Then N lines follow, each contains 2+K integers separated by a space. 
The first 2 integers are the applicant's GE and GI, respectively.
The next K integers represent the preferred schools. 
For the sake of simplicity, we assume that the schools are numbered from 0 to M-1, 
and the applicants are numbered from 0 to N-1.

Output Specification:

For each test case you should output the admission results for all the graduate schools. 
The results of each school must occupy a line, which contains the applicants' numbers that school admits. 
The numbers must be in increasing order and be separated by a space. 
There must be no extra space at the end of each line. 
If no applicant is admitted by a school, you must output an empty line correspondingly.

Sample Input:
11 6 3
2 1 2 2 2 3
100 100 0 1 2
60 60 2 3 5
100 90 0 3 4
90 100 1 2 0
90 90 5 1 3
80 90 1 0 2
80 80 0 1 2
80 80 0 1 2
80 70 1 3 2
70 80 1 2 3
100 100 0 2 4
Sample Output:
0 10
3
5 6 7
2 8

1 4
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/*
20：30 
ge gi
final = (ge+gi)/2

rank：
按final，ge排序
final，ge相同则rank相同

按rank逐一处理每人
按学校：
有名额，或名额已满但rank相同，录取
下一个学校

输出:每个学校录取人id。无录取输出空行
21:15 12/30 wa0

如果某个学校quota为0？
21：20 6/30 wa0,3,4

*/
namespace nsA1080A
{
	struct Student
	{
		int id = 0;
		int ge = 0;
		int gi = 0;
		float gfinal = 0;
		int rank = -1;

		void Final(void) { gfinal = float(ge + gi) / 2; }

		bool operator==(const Student& a)
		{
			return gfinal == a.gfinal && ge == a.ge;
		}
		bool operator<(const Student& a)
		{
			return gfinal != a.gfinal ? gfinal > a.gfinal : ge > a.ge;
		}
	};

	// result
	vector<vector<int>> vvApp;

	int nStudent;
	int nSchool;
	int nChoice;
	// school quota
	vector<int> vQuota;
	// school last rank
	vector<int> vRank;
	// student
	vector<Student> vStudent;
	vector<vector<int>> vvChoice;

	void main(void)
	{
		cin >> nStudent >> nSchool >> nChoice;
		vvApp.clear();
		vvApp.resize(nSchool);
		vQuota.resize(nSchool);
		vStudent.resize(nStudent);
		vRank.assign(nStudent, -1);
		vvChoice.assign(nStudent, vector<int>(nChoice));
		for (int i = 0; i < nSchool; ++i)
		{
			cin >> vQuota[i];
		}
		for (int i = 0; i < nStudent; ++i)
		{
			Student& stu = vStudent[i];
			stu.id = i;
			cin >> stu.ge >> stu.gi;
			stu.Final();
			auto& vChoice = vvChoice[i];
			for (int j = 0; j < nChoice; ++j)
			{
				cin >> vChoice[j];
			}
		}

		// rank
		sort(vStudent.begin(), vStudent.end());
		int rank = 0;
		Student* pLast = &vStudent[0];
		pLast->rank = 0;
		for (int i = 1; i < nStudent; ++i)
		{
			if (vStudent[i] == *pLast)
			{
				vStudent[i].rank = pLast->rank;
			}
			else
			{
				vStudent[i].rank = i;
			}
			pLast = &vStudent[i];
		}

		// applicant
		for (auto& stu : vStudent)
		{
			auto& vChoice = vvChoice[stu.id];
			for (auto sch : vChoice)
			{
				if (vQuota[sch])
				{
					--vQuota[sch];
					vRank[sch] == stu.rank;
					vvApp[sch].push_back(stu.id);
					break;
				}
				else if (vRank[sch] == stu.rank)
				{
					vvApp[sch].push_back(stu.id);
					break;
				}
			}
		}
		for (auto& v : vvApp)
		{
			if (v.empty())
			{
				cout << endl;
				continue;
			}
			sort(v.begin(), v.end());
			cout << v.front();
			for (size_t i = 1; i < v.size(); ++i)
			{
				cout << " " << v[i];
			}
			cout << endl;
		}
	}
}

// rename this to main int PAT
int A1080Func(void)
{
	nsA1080A::main();
	return 0;
}


void A1080(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1080Func();
	cout << endl;
}

void A1080(void)
{
	A1080("data\\A1080-1.txt"); // 
}

