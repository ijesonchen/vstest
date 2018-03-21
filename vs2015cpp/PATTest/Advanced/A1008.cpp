/*
1008. Elevator (20)
cost: 20min

The highest building in our city has only one elevator. 
A request list is made up with N positive numbers. The 
numbers denote at which floors the elevator will stop, 
in specified order. It costs 6 seconds to move the elevator
up one floor, and 4 seconds to move down one floor. The 
elevator will stay for 5 seconds at each stop.

For a given request list, you are to compute the total 
time spent to fulfill the requests on the list. The elevator 
is on the 0th floor at the beginning and does not have to 
return to the ground floor when the requests are fulfilled.

Input Specification:

Each input file contains one test case. Each case contains
a positive integer N, followed by N positive numbers. All 
the numbers in the input are less than 100.

Output Specification:

For each test case, print the total time on a single line.

Sample Input:
3 2 3 1
Sample Output:
41
*/


#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1008Func(void)
{
	int n;
	cin >> n;
	int total = 0;
	total += n * 5;
	int last = 0;
	cin >> last;
	total += last * 6;
	while (cin >> n)
	{
		if (n >= last)
		{
			total += (n - last) * 6;
		}
		else
		{
			total += (last - n) * 4;
		}
		last = n;
	}
	cout << total << endl;
	return 0;
}


void A1008(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1008Func();
	cout << endl;
}

void A1008(void)
{
	A1008("data\\A1008-1.txt"); // 41
	A1008("data\\A1008-2.txt"); // 23
	A1008("data\\A1008-3.txt"); // 31
}