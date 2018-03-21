/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1021Func(void)
{
	return 0;
}


void T1021(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1021Func();
	cout << endl;
}

void T1021(void)
{
	T1021("data\\T1021-1.txt"); // 
}

