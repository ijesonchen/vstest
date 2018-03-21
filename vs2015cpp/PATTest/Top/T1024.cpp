/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1024Func(void)
{
	return 0;
}


void T1024(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1024Func();
	cout << endl;
}

void T1024(void)
{
	T1024("data\\T1024-1.txt"); // 
}

