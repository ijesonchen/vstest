/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1033Func(void)
{
	return 0;
}


void A1033(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1033Func();
	cout << endl;
}

void A1033(void)
{
	A1033("data\\A1033-1.txt"); // 
}

