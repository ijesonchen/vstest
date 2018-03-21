/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1034Func(void)
{
	return 0;
}


void T1034(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1034Func();
	cout << endl;
}

void T1034(void)
{
	T1034("data\\T1034-1.txt"); // 
}

