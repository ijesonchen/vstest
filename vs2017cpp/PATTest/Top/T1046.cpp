/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int T1046Func(void)
{
	return 0;
}


void T1046(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1046Func();
	cout << endl;
}

void T1046(void)
{
	T1046("data\\T1046-1.txt"); // 
}

