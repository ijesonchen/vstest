/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1099Func(void)
{
	return 0;
}


void A1099(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1099Func();
	cout << endl;
}

void A1099(void)
{
	A1099("data\\A1099-1.txt"); // 
}

