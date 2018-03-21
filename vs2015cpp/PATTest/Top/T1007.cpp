/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1007Func(void)
{
	return 0;
}


void T1007(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1007Func();
	cout << endl;
}

void T1007(void)
{
	T1007("data\\T1007-1.txt"); // 
}

