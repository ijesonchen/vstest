/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1041Func(void)
{
	return 0;
}


void T1041(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1041Func();
	cout << endl;
}

void T1041(void)
{
	T1041("data\\T1041-1.txt"); // 
}

