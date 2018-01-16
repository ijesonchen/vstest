/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1027Func(void)
{
	return 0;
}


void T1027(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1027Func();
	cout << endl;
}

void T1027(void)
{
	T1027("data\\T1027-1.txt"); // 
}

