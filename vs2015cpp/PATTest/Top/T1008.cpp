/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1008Func(void)
{
	return 0;
}


void T1008(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1008Func();
	cout << endl;
}

void T1008(void)
{
	T1008("data\\T1008-1.txt"); // 
}

