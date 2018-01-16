/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1026Func(void)
{
	return 0;
}


void T1026(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1026Func();
	cout << endl;
}

void T1026(void)
{
	T1026("data\\T1026-1.txt"); // 
}

