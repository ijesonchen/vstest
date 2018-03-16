/*
1124. Raffle for Weibo Followers (20)
400 ms
65536 kB


John got a full mark on PAT. He was so happy that he decided to hold a raffle（抽奖） for his followers on Weibo -- 
that is, he would select winners from every N followers who forwarded his post, and give away gifts. 
Now you are supposed to help him generate the list of winners.

Input Specification:

Each input file contains one test case. For each case, the first line gives 
three positive integers M (<= 1000),N and S, being 
the total number of forwards, 
the skip number of winners, and 
the index of the first winner (the indices start from 1). 
Then M lines follow, each gives the nickname (a nonempty string of no more than 20 characters, 
with no white space or return) of a follower who has forwarded John's post.

Note: it is possible that someone would forward more than once, but no one can win more than once. 
Hence if the current candidate of a winner has won before, we must skip him/her and consider the next one.

Output Specification:

For each case, print the list of winners in the same order as in the input, 
each nickname occupies a line. 
If there is no winner yet, print "Keep going..." instead.

Sample Input 1:
9 3 2
Imgonnawin!
PickMe
PickMeMeMeee
LookHere
Imgonnawin!
TryAgainAgain
TryAgainAgain
Imgonnawin!
TryAgainAgain

Sample Output 1:
PickMe
Imgonnawin!
TryAgainAgain

Sample Input 2:
2 3 5
Imgonnawin!
PickMe

Sample Output 2:
Keep going...

*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

/*
15:10
正整数
m [1,1000] 转发总数
n 跳过
s 第一个

m行，<20字符
跳过重复
15:25 15/20 wa3

bug-fix-1: 记录第一个中奖的
15:30 pass
*/

namespace nsA1124A
{
	void main(void)
	{
		int m, n, s;
		cin >> m >> n >> s;
		if (n>m || s > m)
		{
			cout << "Keep going..." << endl;
			return;
		}
		string name;
		
		set<string> setWin;
		int left = s;
		while (left--)
		{
			cin >> name;
		}
		cout << name << endl;
		// bug-fix-1: record first win.
		setWin.insert(name);
		int step = 0;
		for (int i = s; i < m; ++i)
		{
			cin >> name;
			++step;
			if (step == n) // win
			{				
				if (setWin.find(name) != setWin.end()) // again 
				{
					--step;
				}
				else
				{
					step = 0;
					setWin.insert(name);
					cout << name << endl;
				}
			}
		}
	}
}

// rename this to main int PAT
int A1124Func(void)
{
	nsA1124A::main();
	return 0;
}


void A1124(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1124Func();
	cout << endl;
}

void A1124(void)
{
	A1124("data\\A1124-1.txt"); // 
	A1124("data\\A1124-2.txt"); // 
}

