/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1115Func(void)
{
	return 0;
}


void A1115(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1115Func();
	cout << endl;
}

void A1115(void)
{
	A1115("data\\A1115-1.txt"); // 
}

