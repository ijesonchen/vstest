/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1011Func(void)
{
	return 0;
}


void T1011(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1011Func();
	cout << endl;
}

void T1011(void)
{
	T1011("data\\T1011-1.txt"); // 
}

