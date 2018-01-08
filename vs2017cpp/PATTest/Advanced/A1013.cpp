/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1013Func(void)
{
	return 0;
}


void A1013(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1013Func();
	cout << endl;
}

void A1013(void)
{
	A1013("data\\A1013-1.txt"); // 
}

