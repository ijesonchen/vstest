/*
1039. Course List for Student (25)
200 ms
65536 kB

18:00
20min 23/25 pt5 TLE
50min pass
总结：时间要求非常高的情况下：
	umap<string,set<int>>
	1. io使用scanf / printf
	2. map[string] -> map[int] (4字节名字提示）
	3. set改用vector+排序


Zhejiang University has 40000 students and provides 2500 courses.
Now given the student name lists of all the courses, 
you are supposed to output the registered course list for each student 
who comes for a query.

Input Specification:

Each input file contains one test case. 
For each case, the first line contains 2 positive integers: 
N (<=40000), the number of students who look for their course lists, 
and K (<=2500), the total number of courses. 
Then the student name lists are given for the 
courses (numbered from 1 to K) in the following format: 
for each course i, 
first the course index i and the number of registered students Ni (<= 200) are given in a line. 
Then in the next line, Ni student names are given.
A student name consists of 3 capital English letters plus a one-digit number. 
Finally the last line contains the N names of students who come for a query. 
All the names and numbers in a line are separated by a space.

Output Specification:

For each test case, print your results in N lines. 

Each line corresponds to one student, in the following format: 
first print the student's name,
then the total number of registered courses of that student, 
and finally the indices of the courses in increasing order. 
The query results must be printed in the same order as input. 

All the data in a line must be separated by a space,
with no extra space at the end of the line.

Sample Input:
11 5
4 7
BOB5 DON2 FRA8 JAY9 KAT3 LOR6 ZOE1
1 4
ANN0 BOB5 JAY9 LOR6
2 7
ANN0 BOB5 FRA8 JAY9 JOE4 KAT3 LOR6
3 1
BOB5
5 9
AMY7 ANN0 BOB5 DON2 FRA8 JAY9 KAT3 LOR6 ZOE1
ZOE1 ANN0 BOB5 JOE4 JAY9 FRA8 DON2 AMY7 KAT3 LOR6 NON9
Sample Output:
ZOE1 2 4 5
ANN0 3 1 2 5
BOB5 5 1 2 3 4 5
JOE4 1 2
JAY9 4 1 2 4 5
FRA8 3 2 4 5
DON2 2 4 5
AMY7 1 5
KAT3 3 2 4 5
LOR6 4 1 2 4 5
NON9 0

*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

/*
18：00
输入：
n：学生数 k：课程数[1,k]
i 课程索引 ni 学生数
ni*名字[XXXm]。。。
。。。
n*名字

输出（同输入）：
name total-course courses...(inc)

sln：结果：umap<string, set<int>> mapNameCourse
18:15: 23/25 PT5 TLE

set改为vector（取消排序，看速度）
18:17: 6/25 PT0,2WA pt5TLE
*/

namespace nsA1039A
{

	void main(void)
	{
		unordered_map<string, set<int>> mapNameCourse;
		int n, k, c, ni;
		string name;
		cin >> n >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> c >> ni;
			for (int j = 0; j < ni; ++j)
			{
				cin >> name;
				mapNameCourse[name].insert(c);
			}
		}
		for (int i = 0; i < n; ++i)
		{
			cin >> name;
			auto& res = mapNameCourse[name];
			cout << name << " " << res.size();
			if (res.size())
			{
				for (auto c : res)
				{
					cout << " " << c;
				}
			}
			cout << endl;
		}
	}
}

/*
名字改为整形映射
18:24 TLE
*/
namespace nsA1039B
{
	int Name2ID(const string& s)
	{
		int* p = (int*)s.c_str();
		return *p;
	}

	void main(void)
	{
		unordered_map<int, set<int>> mapNameCourse;
		int n, k, c, ni;
		string name;
		cin >> n >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> c >> ni;
			for (int j = 0; j < ni; ++j)
			{
				cin >> name;
				int id = Name2ID(name);
				mapNameCourse[id].insert(c);
			}
		}
		for (int i = 0; i < n; ++i)
		{
			cin >> name;
			int id = Name2ID(name);
			auto& res = mapNameCourse[id];
			cout << name << " " << res.size();
			if (res.size())
			{
				for (auto c : res)
				{
					cout << " " << c;
				}
			}
			cout << endl;
		}
	}
}


/*
cin/cout, name->int, vector排序
TLE
*/
namespace nsA1039F
{
	void main(void)
	{
		unordered_map<int, vector<int>> mapNameCourse;
		int n, k, c, ni;
		string name;
		cin >> n >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> c >> ni;
			for (int j = 0; j < ni; ++j)
			{
				cin >> name;
				int id = *(int*)name.c_str();
				mapNameCourse[id].push_back(c);
			}
		}
		for (int i = 0; i < n; ++i)
		{
			cin >> name;
			int id = *(int*)name.c_str();
			auto& res = mapNameCourse[id];
			cout << name << " " << res.size();
			if (res.size())
			{
				sort(res.begin(), res.end());
				for (auto c : res)
				{
					cout << " " << c;
				}
			}
			cout << endl;
		}
	}
}

/*
使用scanf和printf
18:33 23/25 TLE
问题：Name2ID构造了string, 改为Name2ID(const char* s), 替换set后pass
*/
namespace nsA1039C
{
	int Name2ID(const string& s)
	{
		int* p = (int*)s.c_str();
		return *p;
	}

	void main(void)
	{
		unordered_map<int, set<int>> mapNameCourse;
		int n, k, c, ni;
		char name[5];
		scanf("%d %d\n", &n, &k);
		for (int i = 0; i < k; ++i)
		{
			scanf("%d %d\n", &c, &ni);
			for (int j = 0; j < ni; ++j)
			{
				scanf("%s", name);
				int id = Name2ID(name);
				mapNameCourse[id].insert(c);
			}
			scanf("\n");
		}
		for (int i = 0; i < n; ++i)
		{
			scanf("%s", name);
			int id = Name2ID(name);
			auto& res = mapNameCourse[id];
			printf("%s %d", name, (int)res.size());
			if (res.size())
			{
				for (auto c : res)
				{
					printf(" %d", c);
				}
			}
			printf("\n");
		}

	}
}

/*
替换set,Name2ID
18:42 MLE
*/
namespace nsA1039D
{
	const int MAXCOURSE = 2501;
	struct Course 
	{
		vector<bool> vc;
		int n = 0;

		Course() :vc(MAXCOURSE), n(0) {};

		inline void Insert(int i)
		{
			++n;
			vc[i] = true;
		}
	};

	void main(void)
	{
		unordered_map<int, Course> mapNameCourse;
		int n, k, c, ni;
		char name[5];
		scanf("%d %d\n", &n, &k);
		for (int i = 0; i < k; ++i)
		{
			scanf("%d %d\n", &c, &ni);
			for (int j = 0; j < ni; ++j)
			{
				scanf("%s", name);
				int id = *(int*)name;
				mapNameCourse[id].Insert(c);
			}
			scanf("\n");
		}
		for (int i = 0; i < n; ++i)
		{
			scanf("%s", name);
			int id = *(int*)name;
			auto& res = mapNameCourse[id];
			printf("%s %d", name, res.n);
			if (res.n)
			{
				for (int j = 1; j < MAXCOURSE; ++j)
				{
					if (res.vc[j])
					{
						printf(" %d", j);
					}
				}
			}
			printf("\n");
		}

	}
}

/*
先vector后排序
18:45 pass
*/
namespace nsA1039E
{
	void main(void)
	{
		unordered_map<int, vector<int>> mapNameCourse;
		int n, k, c, ni;
		char name[5];
		scanf("%d %d\n", &n, &k);
		for (int i = 0; i < k; ++i)
		{
			scanf("%d %d\n", &c, &ni);
			for (int j = 0; j < ni; ++j)
			{
				scanf("%s", name);
				int id = *(int*)name;
				mapNameCourse[id].push_back(c);
			}
			scanf("\n");
		}
		for (int i = 0; i < n; ++i)
		{
			scanf("%s", name);
			int id = *(int*)name;
			auto& res = mapNameCourse[id];
			printf("%s %d", name, (int)res.size());
			if (res.size())
			{
				sort(res.begin(), res.end());
				for (auto c : res)
				{
					printf(" %d", c);
				}
			}
			printf("\n");
		}
	}
}
// rename this to main int PAT
int A1039Func(void)
{
	nsA1039F::main();
	return 0;
}


void A1039(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
//	freopen(fn.c_str(), "r", stdin);
	A1039Func();
	cout << endl;
}

void A1039(void)
{
	A1039("data\\A1039-1.txt"); // 
}

