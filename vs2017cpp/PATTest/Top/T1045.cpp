/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1045Func(void)
{
	return 0;
}


void T1045(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1045Func();
	cout << endl;
}

void T1045(void)
{
	T1045("data\\T1045-1.txt"); // 
}

