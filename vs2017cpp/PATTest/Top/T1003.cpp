/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1003Func(void)
{
	return 0;
}


void T1003(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1003Func();
	cout << endl;
}

void T1003(void)
{
	T1003("data\\T1003-1.txt"); // 
}

