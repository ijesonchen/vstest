/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1017Func(void)
{
	return 0;
}


void T1017(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1017Func();
	cout << endl;
}

void T1017(void)
{
	T1017("data\\T1017-1.txt"); // 
}

