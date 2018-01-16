/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1117Func(void)
{
	return 0;
}


void A1117(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1117Func();
	cout << endl;
}

void A1117(void)
{
	A1117("data\\A1117-1.txt"); // 
}

