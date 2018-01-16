/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1005Func(void)
{
	return 0;
}


void T1005(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1005Func();
	cout << endl;
}

void T1005(void)
{
	T1005("data\\T1005-1.txt"); // 
}

