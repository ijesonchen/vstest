/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1002Func(void)
{
	return 0;
}


void T1002(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1002Func();
	cout << endl;
}

void T1002(void)
{
	T1002("data\\T1002-1.txt"); // 
}

