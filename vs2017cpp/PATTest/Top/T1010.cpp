/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1010Func(void)
{
	return 0;
}


void T1010(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1010Func();
	cout << endl;
}

void T1010(void)
{
	T1010("data\\T1010-1.txt"); // 
}

