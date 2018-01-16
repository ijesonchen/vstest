/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1004Func(void)
{
	return 0;
}


void T1004(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1004Func();
	cout << endl;
}

void T1004(void)
{
	T1004("data\\T1004-1.txt"); // 
}

