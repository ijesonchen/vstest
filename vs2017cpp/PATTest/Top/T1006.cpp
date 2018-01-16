/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1006Func(void)
{
	return 0;
}


void T1006(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1006Func();
	cout << endl;
}

void T1006(void)
{
	T1006("data\\T1006-1.txt"); // 
}

