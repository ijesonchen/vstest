/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1030Func(void)
{
	return 0;
}


void T1030(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1030Func();
	cout << endl;
}

void T1030(void)
{
	T1030("data\\T1030-1.txt"); // 
}

