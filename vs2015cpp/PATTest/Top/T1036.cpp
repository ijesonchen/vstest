/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1036Func(void)
{
	return 0;
}


void T1036(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1036Func();
	cout << endl;
}

void T1036(void)
{
	T1036("data\\T1036-1.txt"); // 
}

