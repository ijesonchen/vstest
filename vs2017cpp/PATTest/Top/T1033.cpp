/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1033Func(void)
{
	return 0;
}


void T1033(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1033Func();
	cout << endl;
}

void T1033(void)
{
	T1033("data\\T1033-1.txt"); // 
}

