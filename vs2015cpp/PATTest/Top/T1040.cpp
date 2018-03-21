/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1040Func(void)
{
	return 0;
}


void T1040(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1040Func();
	cout << endl;
}

void T1040(void)
{
	T1040("data\\T1040-1.txt"); // 
}

