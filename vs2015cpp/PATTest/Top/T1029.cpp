/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1029Func(void)
{
	return 0;
}


void T1029(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1029Func();
	cout << endl;
}

void T1029(void)
{
	T1029("data\\T1029-1.txt"); // 
}

