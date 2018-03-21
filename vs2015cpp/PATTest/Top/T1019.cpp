/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1019Func(void)
{
	return 0;
}


void T1019(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1019Func();
	cout << endl;
}

void T1019(void)
{
	T1019("data\\T1019-1.txt"); // 
}

