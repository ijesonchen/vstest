/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1040Func(void)
{
	return 0;
}


void A1040(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1040Func();
	cout << endl;
}

void A1040(void)
{
	A1040("data\\A1040-1.txt"); // 
}

