/*
1028. List Sorting (25)

cost: 21:20

总结：排序超时时，可以考虑是否能将比较中的字串改为数值。

sln: 直接计算
	10min 21/25 pt6 超时
	5min 预先分配vector 超时
	10min 换用qsort 超时
	5min 直接new指针 超时

sln2: 题解 直接对结构体sort不超时，但是id使用int
	更改Student::id类型string -> int pass
	5min pass

Excel can sort records according to any column. 
Now you are supposed to imitate this function.

Input

Each input file contains one test case. 
For each case, the first line contains two integers N (<=100000) and C,
where N is the number of records 
and C is the column that you are supposed to sort the records with. 
Then N lines follow, each contains a record of a student. 
A student's record consists of his or her
distinct ID (a 6-digit number), 
name (a string with no more than 8 characters without space),
and grade (an integer between 0 and 100, inclusive).

Output

For each test case, output the sorting result in N lines.
That is, if C = 1 then the records must be sorted in increasing order according to ID's; 
if C = 2 then the records must be sorted in non-decreasing order according to names; 
and if C = 3 then the records must be sorted in non-decreasing order according to grades. 

If there are several students who have the same name or grade, 
they must be sorted according to their ID's in increasing order.

Sample Input 1
3 1
000007 James 85
000010 Amy 90
000001 Zoe 60
Sample Output 1
000001 Zoe 60
000007 James 85
000010 Amy 90
Sample Input 2
4 2
000007 James 85
000010 Amy 90
000001 Zoe 60
000002 James 98
Sample Output 2
000010 Amy 90
000002 James 98
000007 James 85
000001 Zoe 60
Sample Input 3
4 3
000007 James 85
000010 Amy 90
000001 Zoe 60
000002 James 90
Sample Output 3
000001 Zoe 60
000007 James 85
000002 James 90
000010 Amy 90
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

namespace nsA1028
{
	struct Student
	{
		int id;
		string name;
		int grade = 0;
	};

	ostream& operator<<(ostream& os, const Student& stu)
	{
		os << stu.id << " " << stu.name << " " << stu.grade;
		return os;
	}

	void Print(const Student& stu)
	{
		printf("%06d %s %d\n", stu.id, stu.name.c_str(), stu.grade);
	}

	bool Comp1(const Student* p1, const Student* p2)
	{
		return p1->id < p2->id;
	}

	int Comp1p(const void* pp1, const void* pp2)
	{
		Student* p1 = *(Student**)pp1;
		Student* p2 = *(Student**)pp2;
		if (p1->id < p2->id)
		{
			return -1;
		}
		return 1;
	}

	bool Comp2(const Student* p1, const Student* p2)
	{
		if (p1->name < p2->name)
		{
			return true;
		}
		else if (p1->name == p2->name)
		{
			return p1->id < p2->id;
		}
		return false;
	}

	int Comp2p(const void* pp1, const void* pp2)
	{
		Student* p1 = *(Student**)pp1;
		Student* p2 = *(Student**)pp2;
		if (Comp2(p1, p2))
		{
			return -1;
		}
		return 1;
	}

	bool Comp3(const Student* p1, const Student* p2)
	{
		if (p1->grade < p2->grade)
		{
			return true;
		}
		else if (p1->grade == p2->grade)
		{
			return p1->id < p2->id;
		}
		return false;
	}

	int Comp3p(const void* pp1, const void* pp2)
	{
		Student* p1 = *(Student**)pp1;
		Student* p2 = *(Student**)pp2;
		if (Comp3(p1, p2))
		{
			return -1;
		}
		return 1;
	}
}

// rename this to main int PAT
int A1028Func(void)
{
	using namespace nsA1028;
	int n, c;
	cin >> n >> c;
	vector<Student> vtStudent(n);
	vector<Student*> vpStudent;
	for (int i = 0; i < n; ++i)
	{
		auto& stu = vtStudent[i];
		cin >> stu.id >> stu.name >> stu.grade;
		vpStudent.push_back(&stu);
	}

	switch (c)
	{
	case 1:
		sort(vpStudent.begin(), vpStudent.end(), Comp1);
		break;
	case 2:
		sort(vpStudent.begin(), vpStudent.end(), Comp2);
		break;
	case 3:
		sort(vpStudent.begin(), vpStudent.end(), Comp3);
		break;
	default:
		throw 0;
		break;
	}

	for (auto p : vpStudent)
	{
		Print(*p);
	}
	
	return 0;
}


void A1028(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1028Func();
	cout << endl;
}

void A1028(void)
{
	A1028("data\\A1028-1.txt"); // 
	A1028("data\\A1028-2.txt"); // 
	A1028("data\\A1028-3.txt"); // 
}

