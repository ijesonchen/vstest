/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1022Func(void)
{
	return 0;
}


void T1022(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1022Func();
	cout << endl;
}

void T1022(void)
{
	T1022("data\\T1022-1.txt"); // 
}

