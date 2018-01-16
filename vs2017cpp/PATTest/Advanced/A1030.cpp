/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1030Func(void)
{
	return 0;
}


void A1030(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1030Func();
	cout << endl;
}

void A1030(void)
{
	A1030("data\\A1030-1.txt"); // 
}

