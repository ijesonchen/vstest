/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1025Func(void)
{
	return 0;
}


void A1025(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1025Func();
	cout << endl;
}

void A1025(void)
{
	A1025("data\\A1025-1.txt"); // 
}

