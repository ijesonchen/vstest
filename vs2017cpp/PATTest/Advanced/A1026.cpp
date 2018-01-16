/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1026Func(void)
{
	return 0;
}


void A1026(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1026Func();
	cout << endl;
}

void A1026(void)
{
	A1026("data\\A1026-1.txt"); // 
}

