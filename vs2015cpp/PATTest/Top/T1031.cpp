/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1031Func(void)
{
	return 0;
}


void T1031(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1031Func();
	cout << endl;
}

void T1031(void)
{
	T1031("data\\T1031-1.txt"); // 
}

