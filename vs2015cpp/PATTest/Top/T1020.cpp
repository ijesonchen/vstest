/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1020Func(void)
{
	return 0;
}


void T1020(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1020Func();
	cout << endl;
}

void T1020(void)
{
	T1020("data\\T1020-1.txt"); // 
}

