/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1042Func(void)
{
	return 0;
}


void T1042(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1042Func();
	cout << endl;
}

void T1042(void)
{
	T1042("data\\T1042-1.txt"); // 
}

