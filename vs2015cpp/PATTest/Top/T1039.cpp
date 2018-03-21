/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1039Func(void)
{
	return 0;
}


void T1039(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1039Func();
	cout << endl;
}

void T1039(void)
{
	T1039("data\\T1039-1.txt"); // 
}

