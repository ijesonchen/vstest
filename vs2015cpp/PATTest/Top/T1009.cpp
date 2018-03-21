/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1009Func(void)
{
	return 0;
}


void T1009(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1009Func();
	cout << endl;
}

void T1009(void)
{
	T1009("data\\T1009-1.txt"); // 
}

