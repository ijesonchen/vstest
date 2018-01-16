/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1037Func(void)
{
	return 0;
}


void T1037(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1037Func();
	cout << endl;
}

void T1037(void)
{
	T1037("data\\T1037-1.txt"); // 
}

