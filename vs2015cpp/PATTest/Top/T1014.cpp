/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1014Func(void)
{
	return 0;
}


void T1014(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1014Func();
	cout << endl;
}

void T1014(void)
{
	T1014("data\\T1014-1.txt"); // 
}

