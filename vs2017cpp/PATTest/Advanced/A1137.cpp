/*
1137. Final Grading (25)

For a student taking the online course "Data Structures" on 
China University MOOC (http://www.icourse163.org/), to be qualified 
for a certificate, he/she must first obtain no less than 200 points 
from the online programming assignments, and then receive a final 
grade no less than 60 out of 100. The final grade is calculated by 
G = (Gmid-termx 40% + Gfinalx 60%) if Gmid-term > Gfinal, or Gfinal 
will be taken as the final grade G. Here Gmid-term and Gfinal are 
the student's scores of the mid-term and the final exams, respectively.

The problem is that different exams have different grading sheets. 
Your job is to write a program to merge all the grading sheets into one.

Input Specification:

Each input file contains one test case. For each case, the first line 
gives three positive integers: P , the number of students having done 
the online programming assignments; M, the number of students on the 
mid-term list; and N, the number of students on the final exam list. 
All the numbers are no more than 10,000.

Then three blocks follow. The first block contains P online programming 
scores Gp's; the second one contains M mid-term scores Gmid-term's; and 
the last one contains N final exam scores Gfinal's. Each score occupies 
a line with the format: StudentID Score, where StudentID is a string of 
no more than 20 English letters and digits, and Score is a nonnegative 
integer (the maximum score of the online programming is 900, and that of 
the mid-term and final exams is 100).

Output Specification:

For each case, print the list of students who are qualified for certificates. 
Each student occupies a line with the format:

StudentID Gp Gmid-term Gfinal G

If some score does not exist, output "-1" instead. The output must be sorted 
in descending order of their final grades (G must be rounded up to an integer). 
If there is a tie, output in ascending order of their StudentID's. It is 
guaranteed that the StudentID's are all distinct, and there is at least one 
qualified student.

Sample Input:
6 6 7
01234 880
a1903 199
ydjh2 200
wehu8 300
dx86w 220
missing 400
ydhfu77 99
wehu8 55
ydjh2 98
dx86w 88
a1903 86
01234 39
ydhfu77 88
a1903 66
01234 58
wehu8 84
ydjh2 82
missing 99
dx86w 81

Sample Output:
missing 400 -1 99 99
ydjh2 200 98 82 88
dx86w 220 88 81 84
wehu8 300 55 84 84
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

class A1137Student
{
public:
	string id;
	int gp = -1;
	int gm = -1;
	int gf = -1;
	int g = -1;
public:
	void Calc(void)
	{
		if (gm > gf)
		{
			g = (int)floor(0.5 + gm * 0.4 + gf * 0.6);
		}
		else
		{
			g = gf;
		}
	}
	void Print(void)
	{
		cout << id << " " << gp << " " << gm << " " << gf << " " << g << endl;
	}

	bool operator<(const A1137Student& other)
	{
		if (g == other.g)
		{
			return id < other.id;
		}
		return g > other.g;
	}
};

bool A1137StudentComp(A1137Student* p1, A1137Student* p2)
{
	return *p1 < *p2;
}

// unordered_map + pointer 最快。
// 有两种机器判题，速度不同36ms/92ms
int A1137Func(void)
{
	int p, m, f;
	cin >> p >> m >> f;
	unordered_map<string, A1137Student> data;
	string id;
	int score;
	for (int i = 0; i < p; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gp = score;
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gm = score;
	}
	for (int i = 0; i < f; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gf = score;
	}


	vector<A1137Student*> v;
	for (auto& it : data)
	{
		auto& d = it.second;
		if (d.gp >= 200)
		{
			d.Calc();
			if (d.g >= 60)
			{
				v.push_back(&d);
			}
		}
	}
	sort(v.begin(), v.end(), A1137StudentComp);

	for (auto& it : v)
	{
		it->Print();
	}

	return 0;
}

// unordered_map 70ms
int A1137Func70ms(void)
{
	int p, m, f;
	cin >> p >> m >> f;
	unordered_map<string, A1137Student> data;
	string id;
	int score;
	for (int i = 0; i < p; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gp = score;
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gm = score;
	}
	for (int i = 0; i < f; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gf = score;
	}

	vector<A1137Student> v;
	for (auto& it : data)
	{
		auto& d = it.second;
		if (d.gp >= 200)
		{
			d.Calc();
			if (d.g >= 60)
			{
				v.push_back(d);
			}
		}
	}
	sort(v.begin(), v.end());

	for (auto& it : v)
	{
		it.Print();
	}

	return 0;
}

// 超时
int A1137Func90ms(void)
{
	int p, m, f;
	cin >> p >> m >> f;
	map<string, A1137Student> data;
	string id;
	int score;
	for (int i = 0; i < p; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gp = score;
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gm = score;
	}
	for (int i = 0; i < f; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gf = score;
	}

	vector<A1137Student> v;
	for (auto& it : data)
	{
		auto& d = it.second;
		if (d.gp >= 200)
		{
			d.Calc();
			if (d.g >= 60)
			{
				v.push_back(d);
			}
		}
	}
	sort(v.begin(), v.end());

	for (auto& it : v)
	{
		it.Print();
	}
	
	return 0;
}

// vector<Student*>
int A1137Func95ms(void)
{
	int p, m, f;
	cin >> p >> m >> f;
	map<string, A1137Student> data;
	string id;
	int score;
	for (int i = 0; i < p; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gp = score;
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gm = score;
	}
	for (int i = 0; i < f; ++i)
	{
		cin >> id >> score;
		data[id].id = id;
		data[id].gf = score;
	}

	vector<A1137Student*> v;
	for (auto& it : data)
	{
		auto& d = it.second;
		if (d.gp >= 200)
		{
			d.Calc();
			if (d.g >= 60)
			{
				v.push_back(&d);
			}
		}
	}
	sort(v.begin(), v.end(), A1137StudentComp);

	for (auto& it : v)
	{
		it->Print();
	}

	return 0;
}

void A1137(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1137Func();
}

void A1137(void)
{
	A1137("data\\A1137-1.TXT"); // 
}

