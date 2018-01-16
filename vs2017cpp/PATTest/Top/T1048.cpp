/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1048Func(void)
{
	return 0;
}


void T1048(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1048Func();
	cout << endl;
}

void T1048(void)
{
	T1048("data\\T1048-1.txt"); // 
}

