/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1018Func(void)
{
	return 0;
}


void T1018(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1018Func();
	cout << endl;
}

void T1018(void)
{
	T1018("data\\T1018-1.txt"); // 
}

