/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1025Func(void)
{
	return 0;
}


void T1025(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1025Func();
	cout << endl;
}

void T1025(void)
{
	T1025("data\\T1025-1.txt"); // 
}

