/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1035Func(void)
{
	return 0;
}


void T1035(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1035Func();
	cout << endl;
}

void T1035(void)
{
	T1035("data\\T1035-1.txt"); // 
}

