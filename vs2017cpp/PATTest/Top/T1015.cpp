/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1015Func(void)
{
	return 0;
}


void T1015(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1015Func();
	cout << endl;
}

void T1015(void)
{
	T1015("data\\T1015-1.txt"); // 
}

