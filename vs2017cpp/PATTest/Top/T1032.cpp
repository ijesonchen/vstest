/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1032Func(void)
{
	return 0;
}


void T1032(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1032Func();
	cout << endl;
}

void T1032(void)
{
	T1032("data\\T1032-1.txt"); // 
}

