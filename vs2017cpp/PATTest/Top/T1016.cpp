/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1016Func(void)
{
	return 0;
}


void T1016(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1016Func();
	cout << endl;
}

void T1016(void)
{
	T1016("data\\T1016-1.txt"); // 
}

