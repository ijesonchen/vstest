/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1043Func(void)
{
	return 0;
}


void T1043(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1043Func();
	cout << endl;
}

void T1043(void)
{
	T1043("data\\T1043-1.txt"); // 
}

