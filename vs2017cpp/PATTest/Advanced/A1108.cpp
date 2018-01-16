/*

*/

#include "..\patMain.h"
#include <iostream>
#include <string>

using namespace std;

// rename this to main int PAT
int A1108Func(void)
{
	return 0;
}


void A1108(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1108Func();
	cout << endl;
}

void A1108(void)
{
	A1108("data\\A1108-1.txt"); // 
}

