/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1013Func(void)
{
	return 0;
}


void T1013(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1013Func();
	cout << endl;
}

void T1013(void)
{
	T1013("data\\T1013-1.txt"); // 
}

